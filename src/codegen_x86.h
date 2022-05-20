#ifndef SKE_X86_CODEGEN_H
#define SKE_X86_CODEGEN_H

typedef enum
{
    REG_RBX,
    REG_R10,
    REG_R11,
    REG_R12,
    REG_R13,
    REG_R14,
    REG_R15,
    REG_COUNT
} Scratch_Register;

typedef struct
{
    bool inuse_table[REG_COUNT];
} Scratch_Register_Table;

void scratch_table_init(Scratch_Register_Table* table)
{
    table->inuse_table[REG_RBX] = false;
    table->inuse_table[REG_R10] = false;
    table->inuse_table[REG_R11] = false;
    table->inuse_table[REG_R12] = false;
    table->inuse_table[REG_R13] = false;
    table->inuse_table[REG_R14] = false;
    table->inuse_table[REG_R15] = false;
}

Scratch_Register scratch_alloc(Scratch_Register_Table* table)
{
    for (i32 i = 0; i < REG_COUNT; i++)
    {
        if (!table->inuse_table[i])
        {
            table->inuse_table[i] = true;
            return i;
        }
    }
    assert("No available scratch registers" && false);
    return -1;
}

const char* scratch_name(Scratch_Register reg);
void scratch_free(Scratch_Register_Table* table, Scratch_Register reg)
{
    table->inuse_table[reg] = false;
}

const char* scratch_register_names[REG_COUNT] =
{
    [REG_RBX] = "%rbx",
    [REG_R10] = "%r10",
    [REG_R11] = "%r11",
    [REG_R12] = "%r12",
    [REG_R13] = "%r13",
    [REG_R14] = "%r14",
    [REG_R15] = "%r15",
};

typedef struct Temp_Table_Entry Temp_Table_Entry;
i32 hash_int(i32 a)
{
      a ^= (a << 13);
      a ^= (a >> 17);        
      a ^= (a << 5);
      return a;   
}

typedef struct Temp_Table Temp_Table;
struct Temp_Table
{
    i32* keys;
    Scratch_Register* entries;
    i32 count;
    i32 capacity;
};

static void temp_table_init(Temp_Table* table)
{
    table->count    = 0;
    table->capacity = 0;
    table->entries  = NULL;
    table->keys     = NULL;
}

static i32 temp_table_find_entry(i32* keys, Scratch_Register* entries, i32 capacity, i32 key)
{
    i32 index = hash_int(key) % capacity;
    i32 tombstone = -1;
    for (;;)
    {
        i32 found_key = keys[index];
        if (found_key == -1)
        {
            if (entries[index] == REG_COUNT)
            {
                return tombstone != -1 ? tombstone : index;
            }
            else
            {
                if (tombstone == -1) tombstone = index;
            }
        }
        else if (found_key == key)
        {
            return index;
        }
        
        index = (index + 1) % capacity;
    }
}

#define TABLE_MAX_LOAD 0.75f

static void temp_table_adjust_capacity(Temp_Table* table, i32 capacity)
{
    i32 *new_keys = malloc(sizeof(i32) * capacity);
        Scratch_Register* new_entries = malloc(sizeof(Scratch_Register) * capacity);

        for (i32 i = 0; i < capacity; i++)
        {
            new_keys[i] = -1;
            new_entries[i] = REG_COUNT;
        }
        
        table->count = 0;
        for (i32 i = 0; i < table->capacity; i++)
        {
            i32 old_key = table->keys[i];
            Scratch_Register old_reg = table->entries[i];

            if (old_reg == REG_COUNT) continue;

            i32 index = temp_table_find_entry(new_keys, new_entries, capacity, old_key);
            new_keys[index] = table->keys[i];
            new_entries[index] = table->entries[i];
            table->count++;
        }

        table->capacity = capacity;
        table->entries  = new_entries;
        table->keys     = new_keys;
}

static bool temp_table_set(Temp_Table *table, i32 key, Scratch_Register reg)
{
    if (table->count + 1 > table->capacity * TABLE_MAX_LOAD)
    {
        i32 capacity = table->capacity < 8 ? 8 : table->capacity * 2;
        temp_table_adjust_capacity(table, capacity);
    }

    i32 index = temp_table_find_entry(table->keys, table->entries, table->capacity, key);
    bool new_entry = table->entries[index] == REG_COUNT;
    if (new_entry && table->entries[index] == REG_COUNT) table->count++;

    table->keys[index] = key;
    table->entries[index] = reg;
    return new_entry;
}

static bool temp_table_get(Temp_Table* table, i32 key, Scratch_Register* reg)
{
    if (table->count == 0) return false;

    i32 index = temp_table_find_entry(table->keys, table->entries, table->capacity, key);
    if (table->entries[index] == REG_COUNT) return false;

    *reg = table->entries[index];
    return true;
}

static bool temp_table_delete(Temp_Table* table, i32 key)
{
    if (table->count == 0) return false;

    i32 index = temp_table_find_entry(table->keys, table->entries, table->capacity, key);
    if (table->entries[index] == REG_COUNT) return false;

    table->keys[index] = -1;
    table->entries[index] = REG_RBX; // dummy value
    
    return true;
}

static Scratch_Register get_or_add_scratch_from_temp(Temp_Table* table, IR_Register ir_register, Scratch_Register_Table* scratch_table)
{
    i32 key = ir_register.index;
    Scratch_Register scratch_register;
    if (!temp_table_get(table, key, &scratch_register))
    {
        scratch_register = scratch_alloc(scratch_table);
        temp_table_set(table, key, scratch_register);
    }

    return scratch_register;
}

const char* scratch_name(Scratch_Register reg);
static void free_temp_scratch(Temp_Table* table, IR_Register ir_register, Scratch_Register_Table* scratch_table)
{
    i32 key = ir_register.index;
    Scratch_Register scratch_register = get_or_add_scratch_from_temp(table, ir_register, scratch_table);    
    temp_table_delete(table, key);
    scratch_free(scratch_table, scratch_register);
}

typedef enum
{
    INS_MOV,
    INS_PUSH,
    INS_POP,
    INS_ADD,
    INS_SUB,
    INS_MUL,
    INS_DIV,
    INS_RET,
    INS_NEG,
    INS_CQO,
    INS_COUNT
} Instruction;

const char* instruction_name[INS_COUNT] =
{
    [INS_MOV ] = "movq   ",
    [INS_PUSH] = "pushq  ",
    [INS_POP ] = "popq   ",
    [INS_ADD ] = "addq   ",
    [INS_SUB ] = "subq   ",
    [INS_MUL ] = "mulq   ",
    [INS_DIV ] = "divq   ",
    [INS_RET ] = "ret    ",
    [INS_NEG ] = "negq   ",
    [INS_CQO ] = "cqo    "
};

const char* scratch_name(Scratch_Register reg)
{
    return scratch_register_names[reg];
}

i32 label_count = 0;
i32 label_create()
{
    return label_count++;
}

String* label_name(i32 label, Allocator* allocator)
{
    return string_createf(allocator, ".L%d", label);
}

void x86_emit_move_reg_to_reg(String_Builder* sb, int src, int dst);
void x86_emit_move_lit_to_reg(String_Builder* sb, int num, int dst);
void x86_emit_move_name_to_reg(String_Builder* sb, const char* src, int dst);
void x86_emit_move_reg_to_name(String_Builder* sb, int src, const char* dst);
void x86_emit_move_name_to_name(String_Builder* sb, const char* src, const char* dst);

void x86_emit_unary(String_Builder* sb, int reg);
void x86_emit_div(String_Builder* sb, int src, int dst);
void x86_emit_mul(String_Builder* sb, int src, int dst);
void x86_emit_sub(String_Builder* sb, int src, int dst);
void x86_emit_add(String_Builder* sb, int src, int dst);

void x86_emit_label(String_Builder* sb, String* label)
{
    sb_appendf(sb, "%s:\n", label->str);
}

void x86_emit_add(String_Builder* sb, int src, int dst)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "addq    %s, %s\n", scratch_name(src), scratch_name(dst));
}

void x86_emit_sub(String_Builder* sb, int src, int dst)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "subq    %s, %s\n", scratch_name(dst), scratch_name(src));   
}

void x86_emit_mul(String_Builder* sb, int src, int dst)
{
    x86_emit_move_reg_to_name(sb, src, "%rax");

    const char* dst_name = scratch_name(dst);
    sb_indent(sb, 8);
    sb_appendf(sb, "imulq   %s\n", dst_name);

    x86_emit_move_name_to_name(sb, "%rax", dst_name);
}

void x86_emit_div(String_Builder* sb, int src, int dst) 
{
    x86_emit_move_reg_to_name(sb, src, "%rax");

    sb_indent(sb, 8);
    sb_append(sb, "cqo\n");

    sb_indent(sb, 8);
    const char* dst_name = scratch_name(dst);
    sb_appendf(sb, "idivq   %s\n", dst_name);

    x86_emit_move_name_to_name(sb, "%rax", dst_name);
}

void x86_emit_unary(String_Builder* sb, int src)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "negq    %s\n", scratch_name(src));
}

void x86_emit_move_reg_to_reg(String_Builder* sb, int src, int dst)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "movq    %s, %s\n", scratch_name(src), scratch_name(dst));
}

void x86_emit_move_lit_to_reg(String_Builder* sb, int num, int dst)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "movq    $%d, %s\n", num, scratch_name(dst));
}

void x86_emit_move_lit_to_name(String_Builder* sb, int num, const char* dst)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "movq    $%d, %s\n", num, dst);
}

void x86_emit_move_name_to_reg(String_Builder* sb, const char* src, int dst)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "movq    %s, %s\n", src, scratch_name(dst));
}

void x86_emit_move_reg_to_name(String_Builder* sb, int src, const char* dst)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "movq    %s, %s\n", scratch_name(src), dst);
}

void x86_emit_move_name_to_name(String_Builder* sb, const char* src, const char* dst)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "movq    %s, %s\n", src, dst);
}

Scratch_Register x86_codegen_expression(AST_Node*, String_Builder*, Scratch_Register_Table*);

Scratch_Register x86_codegen_expression(AST_Node* node, String_Builder* sb, Scratch_Register_Table* table)
{
    switch (node->type)
    {
    case AST_NODE_NUMBER:
    {
        Scratch_Register reg = scratch_alloc(table);
        x86_emit_move_lit_to_reg(sb, node->number, reg);
        return reg;
    }
    case AST_NODE_BINARY:
    {
        Scratch_Register left_reg = x86_codegen_expression(node->binary.left, sb, table);
        Scratch_Register right_reg = x86_codegen_expression(node->binary.right, sb, table);

        Token_Type operator = node->binary.operator;

        switch(operator)
        {
        case TOKEN_PLUS:
        {
            x86_emit_add(sb, left_reg, right_reg);
        }
        break;
        case TOKEN_MINUS:
        {
            // @Note: Subtract source from dest -> right from left
            x86_emit_sub(sb, left_reg, right_reg);
            i32 temp = right_reg;
            right_reg = left_reg;
            left_reg = temp;
        }
        break;
        case TOKEN_STAR:
        {
            x86_emit_mul(sb, left_reg, right_reg);
        }
        break;
        case TOKEN_SLASH:
        {
            x86_emit_div(sb, left_reg, right_reg);
        }
        break;
        default:
        assert("Invalid token type" && false);
        }
        
        scratch_free(table, left_reg);
        return right_reg;
    }
    case AST_NODE_UNARY:
    {
        Scratch_Register reg = x86_codegen_expression(node->unary.expression, sb, table);
        x86_emit_unary(sb, reg);
        return reg;
    }
    default:
    printf("%d\n", node->type);
    assert("Unsupported AST Node" && false);
    }

    return -1;
}

void x86_emit_ret(String_Builder* sb)
{
    sb_indent(sb, 8);
    sb_append(sb, "ret\n");
}

void x86_emit_pop_name(String_Builder* sb, const char* name)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "popq    %s\n", name);
}

void x86_emit_push_name(String_Builder* sb, const char* name)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "pushq   %s\n", name);
}

void x86_emit_asciz(String_Builder* sb, const char* name, const char* value)
{
    sb_appendf(sb, "%s:\n", name);
    sb_indent(sb, 8);
    sb_appendf(sb, ".asciz \"%s\"\n", value);
}

void x86_emit_call(String_Builder* sb, const char* function)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "call    %s\n", function);
}

void x86_emit_comment_line(String_Builder* sb, const char* comment)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "#;; %s\n", comment);
}

void x86_emit_header(String_Builder* sb)
{
    sb_append(sb, ".data\n");
    sb_append(sb, ".text\n");
}

String* x86_codegen_ir(IR_Program* program_node, Allocator* allocator)
{
    String_Builder sb;
    sb_init(&sb, 256);

    Scratch_Register_Table table;
    scratch_table_init(&table);

    Temp_Table temp_table;
    temp_table_init(&temp_table);
    
    x86_emit_header(&sb);

    Scratch_Register current_reg;

    for (i32 i = 0; i < program_node->exported_function_array.count; i++)
    {
        String_View name = program_node->exported_function_array.function_names[i];
        sb_appendf(&sb, ".global %s\n", name.string->str);
    }

    for (i32 i = 0; i < program_node->block_array.count; i++)
    {
        IR_Block* block = &program_node->block_array.blocks[i];

        for (i32 j = 0; j < block->node_array.count; j++)
        {
            IR_Node* node = &block->node_array.nodes[j];
            switch(node->type)
            {
            case IR_NODE_FUNCTION_DECL:
            {
                IR_Function_Decl* fun = &node->function;
                sb_appendf(&sb, "%s:\n", fun->name->str);
                x86_emit_push_name(&sb, "%rbp");
                x86_emit_move_name_to_name(&sb, "%rsp", "%rbp");
            }
            break;
            case IR_NODE_LABEL:
            {
                x86_emit_label(&sb, node->label.label_name);
            }
            break;
            case IR_NODE_INSTRUCTION:
            {
                IR_Instruction* instruction = &node->instruction;

                switch(instruction->type)
                {
                case IR_INS_RET:
                {
                    /* x86_emit_ret(&sb); */
                }
                break;
                case IR_INS_MOV:
                {
                    IR_Move* move = &instruction->move;

                    IR_Value* src = &move->src;
                    IR_Location* dst = &move->dst;

                    switch(src->type)
                    {
                    case VALUE_LOCATION:
                    {
                        if(dst->type == IR_LOCATION_REGISTER && src->loc.type == IR_LOCATION_REGISTER)
                        {
                            Scratch_Register src_reg = get_or_add_scratch_from_temp(&temp_table, src->loc.reg, &table);
                            Scratch_Register dst_reg = get_or_add_scratch_from_temp(&temp_table, dst->reg, &table);
                            x86_emit_move_reg_to_reg(&sb, src_reg, dst_reg);
                            current_reg = dst_reg;
                        }
                    }
                    break;
                    case VALUE_INT:
                    {
                        if(dst->type == IR_LOCATION_REGISTER)
                        {
                            Scratch_Register reg = get_or_add_scratch_from_temp(&temp_table, dst->reg, &table);
                            current_reg = reg;
                            x86_emit_move_lit_to_reg(&sb, src->integer, reg);
                        }
                    }
                    break;
                    case VALUE_VARIABLE:
                    {
                        
                    }
                    break;
                    }
                }
                break;
                case IR_INS_PUSH:
                {
                    IR_Push* push = &instruction->push;
                    IR_Value* value = &push->value;

                    switch(value->type)
                    {
                    case VALUE_LOCATION:
                    {
                        Scratch_Register reg = get_or_add_scratch_from_temp(&temp_table, value->loc.reg, &table);
                        current_reg = reg;
                        x86_emit_push_name(&sb, scratch_name(reg));
                    }
                    break;
                    case VALUE_VARIABLE:
                    {
                        
                    }
                    break;
                    default: break;
                    }
                }
                break;
                case IR_INS_POP:
                {
                    IR_Pop* pop = &instruction->pop;
                    IR_Value* value = &pop->value;

                    switch(value->type)
                    {
                    case VALUE_LOCATION:
                    {
                        Scratch_Register reg = get_or_add_scratch_from_temp(&temp_table, value->loc.reg, &table);
                        current_reg = reg;
                        x86_emit_push_name(&sb, scratch_name(reg));
                    }
                    break;
                    case VALUE_VARIABLE:
                    {
                        
                    }
                    break;
                    default: break;
                    }
                }
                break;
                case IR_INS_UNOP:
                {
                    IR_UnOp* unop = &instruction->unop;
                    IR_Value* value = &unop->value;

                    IR_Register ir_reg = value->loc.reg;

                    Scratch_Register reg = get_or_add_scratch_from_temp(&temp_table, ir_reg, &table);

                    x86_emit_unary(&sb, reg);
                    current_reg = reg;
                }
                break;
                case IR_INS_BINOP:
                {
                    IR_BinOp* binop = &instruction->binop;
                    IR_Value* left = &binop->left;
                    IR_Value* right = &binop->right;

                    IR_Register ir_left_reg = left->loc.reg;
                    IR_Register ir_right_reg = right->loc.reg;

                    Scratch_Register left_reg = get_or_add_scratch_from_temp(&temp_table, ir_left_reg, &table);
                    Scratch_Register right_reg = get_or_add_scratch_from_temp(&temp_table, ir_right_reg, &table);

                    switch(binop->operator)
                    {
                    case OP_ADD:
                    {
                        x86_emit_add(&sb, left_reg, right_reg);
                    }
                    break;
                    case OP_SUB:
                    {
                        x86_emit_sub(&sb, left_reg, right_reg);
                        i32 temp = right_reg;
                        right_reg = left_reg;
                        left_reg = temp;

                        IR_Register temp_ir = ir_right_reg;
                        ir_right_reg = ir_left_reg;
                        ir_left_reg = temp_ir;
                    }
                    break;
                    case OP_MUL:
                    {
                        x86_emit_mul(&sb, left_reg, right_reg);
                    }
                    break;
                    case OP_DIV:
                    {
                        x86_emit_div(&sb, left_reg, right_reg);
                    }
                    break;
                    }

                    current_reg = right_reg;
                    free_temp_scratch(&temp_table, ir_left_reg, &table);
                }
                break;
                default: break;
            }
            break;
            }
            }
        }
    }

    x86_emit_move_reg_to_name(&sb, current_reg, "%rax");
    scratch_free(&table, current_reg);

    sb_append(&sb, "\n");
    x86_emit_comment_line(&sb, "fprintf call to output result temporarily");
    x86_emit_move_name_to_name(&sb, "stderr", "%rax");
    x86_emit_move_reg_to_name(&sb, current_reg, "%rdx");
    x86_emit_move_name_to_name(&sb, "$format", "%rsi");
    x86_emit_move_name_to_name(&sb, "%rax", "%rdi");
    x86_emit_move_lit_to_name(&sb, 0, "%rax");
    x86_emit_call(&sb, "fprintf");
    x86_emit_move_lit_to_name(&sb, 0, "%rax");

    x86_emit_pop_name(&sb, "%rbp");

    x86_emit_ret(&sb);

    x86_emit_asciz(&sb, "format", "%d\\n");

    String* assembly = sb_get_result(&sb, allocator);
    return assembly;
}

void x86_codegen_program(AST_Node* program_node, String_Builder* sb, Scratch_Register_Table* table)
{
    sb_append(sb, ".data\n");
    sb_append(sb, ".text\n");
    sb_append(sb, ".global main\n");
    sb_append(sb, "main:\n");

    x86_emit_push_name(sb, "%rbp");
    x86_emit_move_name_to_name(sb, "%rsp", "%rbp");

    /* Scratch_Register final_reg = x86_codegen_expression(program_node->program.expression, sb, table); */

    /* x86_emit_move_reg_to_name(sb, final_reg, "%rax"); */
    /* scratch_free(table, final_reg); */

    // @Note: Emit instructions for fprintf call (used for now)
    /* sb_append(sb, "\n"); */
    /* x86_emit_comment_line(sb, "fprintf call to output result temporarily"); */
    /* x86_emit_move_name_to_name(sb, "stderr", "%rax"); */
    /* x86_emit_move_reg_to_name(sb, final_reg, "%rdx"); */
    /* x86_emit_move_name_to_name(sb, "$format", "%rsi"); */
    /* x86_emit_move_name_to_name(sb, "%rax", "%rdi"); */
    /* x86_emit_move_lit_to_name(sb, 0, "%rax"); */
    /* x86_emit_call(sb, "fprintf"); */
    /* x86_emit_move_lit_to_name(sb, 0, "%rax"); */

    /* x86_emit_pop_name(sb, "%rbp"); */

    /* x86_emit_ret(sb); */

    /* x86_emit_asciz(sb, "format", "%d\\n"); */
}

String* x86_codegen_ast(AST_Node* root_node, Allocator* allocator)
{
    String_Builder sb;
    sb_init(&sb, 256);

    Scratch_Register_Table register_table;
    scratch_table_init(&register_table);
    x86_codegen_program(root_node, &sb, &register_table);

    String* assembly = sb_get_result(&sb, allocator);

    return assembly;
}

void x86_codegen_ast_to_file(AST_Node* root_node, String* out_file, Allocator* allocator)
{
    String* assembly = x86_codegen_ast(root_node, allocator);

    FILE* file = NULL;
    if (out_file)
    {
        file = fopen(out_file->str, "w");
    }
    else
    {
        file = fopen("out.s", "w"); 
    }

    if (file)
    {
        string_fprintf(assembly, file);
        fclose(file);
    }
}

#endif
