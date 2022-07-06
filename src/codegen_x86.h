#ifndef SKE_X86_CODEGEN_H
#define SKE_X86_CODEGEN_H

#define SKE_CODEGEN_INTEL 1

typedef enum
{
    SCRATCH_RBX,
    SCRATCH_R10,
    SCRATCH_R11,
    SCRATCH_R12,
    SCRATCH_R13,
    SCRATCH_R14,
    SCRATCH_R15,
    SCRATCH_COUNT
} Scratch_Register;

typedef enum
{
    REG_RAX,
    REG_RBX,
    REG_RCX,
    REG_RDX,
    REG_RSI,
    REG_RDI,
    REG_RBP,
    REG_RSP,
    REG_R8,
    REG_R9,
    REG_R10,
    REG_R11,
    REG_R12,
    REG_R13,
    REG_R14,
    REG_R15,
    REG_COUNT
} Register;

typedef struct
{
    bool inuse_table[SCRATCH_COUNT];
} Scratch_Register_Table;

void scratch_table_init(Scratch_Register_Table* table)
{
    table->inuse_table[SCRATCH_RBX] = false;
    table->inuse_table[SCRATCH_R10] = false;
    table->inuse_table[SCRATCH_R11] = false;
    table->inuse_table[SCRATCH_R12] = false;
    table->inuse_table[SCRATCH_R13] = false;
    table->inuse_table[SCRATCH_R14] = false;
    table->inuse_table[SCRATCH_R15] = false;
}

Scratch_Register scratch_alloc(Scratch_Register_Table* table)
{
    for (i32 i = 0; i < SCRATCH_COUNT; i++)
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

#ifdef SKE_CODEGEN_INTEL
const char* register_names[REG_COUNT] =
{
    [REG_RAX] = "rax",
    [REG_RBX] = "rbx",
    [REG_RCX] = "rcx",
    [REG_RDX] = "rdx",
    [REG_RSI] = "rsi",
    [REG_RDI] = "rdi",
    [REG_RBP] = "rbp",
    [REG_RSP] = "rsp",
    [REG_R8 ] = "r8",
    [REG_R9 ] = "r9",
    [REG_R10] = "r10",
    [REG_R11] = "r11",
    [REG_R12] = "r12",
    [REG_R13] = "r13",
    [REG_R14] = "r14",
    [REG_R15] = "r15",
};

const char* scratch_register_names[SCRATCH_COUNT] =
{
    [SCRATCH_RBX] = "rbx",
    [SCRATCH_R10] = "r10",
    [SCRATCH_R11] = "r11",
    [SCRATCH_R12] = "r12",
    [SCRATCH_R13] = "r13",
    [SCRATCH_R14] = "r14",
    [SCRATCH_R15] = "r15",
};

#elif SKE_CODEGEN_AT_T

const char* register_names[REG_COUNT] =
{
    [REG_RAX] = "%rax",
    [REG_RBX] = "%rbx",
    [REG_RCX] = "%rcx",
    [REG_RDX] = "%rdx",
    [REG_RSI] = "%rsi",
    [REG_RDI] = "%rdi",
    [REG_RBP] = "%rbp",
    [REG_RSP] = "%rsp",
    [REG_R8 ] = "%r8",
    [REG_R9 ] = "%r9",
    [REG_R10] = "%r10",
    [REG_R11] = "%r11",
    [REG_R12] = "%r12",
    [REG_R13] = "%r13",
    [REG_R14] = "%r14",
    [REG_R15] = "%r15",
};

const char* scratch_register_names[SCRATCH_COUNT] =
{
    [SCRATCH_RBX] = "%rbx",
    [SCRATCH_R10] = "%r10",
    [SCRATCH_R11] = "%r11",
    [SCRATCH_R12] = "%r12",
    [SCRATCH_R13] = "%r13",
    [SCRATCH_R14] = "%r14",
    [SCRATCH_R15] = "%r15",
};
#endif


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
            if (entries[index] == SCRATCH_COUNT)
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
            new_entries[i] = SCRATCH_COUNT;
        }
        
        table->count = 0;
        for (i32 i = 0; i < table->capacity; i++)
        {
            i32 old_key = table->keys[i];
            Scratch_Register old_reg = table->entries[i];

            if (old_reg == SCRATCH_COUNT) continue;

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
    bool new_entry = table->entries[index] == SCRATCH_COUNT;
    if (new_entry && table->entries[index] == SCRATCH_COUNT) table->count++;

    table->keys[index] = key;
    table->entries[index] = reg;
    return new_entry;
}

static bool temp_table_get(Temp_Table* table, i32 key, Scratch_Register* reg)
{
    if (table->count == 0) return false;

    i32 index = temp_table_find_entry(table->keys, table->entries, table->capacity, key);
    if (table->entries[index] == SCRATCH_COUNT) return false;

    *reg = table->entries[index];
    return true;
}

static bool temp_table_delete(Temp_Table* table, i32 key)
{
    if (table->count == 0) return false;

    i32 index = temp_table_find_entry(table->keys, table->entries, table->capacity, key);
    if (table->entries[index] == SCRATCH_COUNT) return false;

    table->keys[index] = -1;
    table->entries[index] = SCRATCH_RBX; // dummy value
    
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
    INS_XOR,
    INS_CALL,
    INS_COUNT
} Instruction;


const char* instruction_names[INS_COUNT] =
{
    [INS_MOV ] = "mov",
    [INS_PUSH] = "push",
    [INS_POP]  = "pop",
    [INS_ADD]  = "add",
    [INS_SUB]  = "sub",
    [INS_MUL]  = "mul",
    [INS_DIV]  = "div",
    [INS_RET]  = "ret",
    [INS_NEG]  = "neg",
    [INS_CQO]  = "cqo",
    [INS_XOR]  = "xor",
    [INS_CALL] = "call"
};

typedef enum
{
    SUFFIX_BYTE,
    SUFFIX_WORD,
    SUFFIX_LONG,
    SUFFIX_QUAD,
    SUFFIX_COUNT
} Type_Suffix;

const char instruction_suffix[SUFFIX_COUNT] =
{
    [SUFFIX_BYTE] = 'b',
    [SUFFIX_WORD] = 'w',
    [SUFFIX_LONG] = 'l',
    [SUFFIX_QUAD] = 'q',
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

void x86_emit_move_reg_to_reg(String_Builder* sb, Scratch_Register src, Scratch_Register dst);
void x86_emit_move_lit_to_reg(String_Builder* sb, i32 num, Scratch_Register dst);
void x86_emit_move_name_to_reg(String_Builder* sb, const char* src, Scratch_Register dst);
void x86_emit_move_reg_to_name(String_Builder* sb, Scratch_Register src, const char* dst);
void x86_emit_move_name_to_name(String_Builder* sb, const char* src, const char* dst);

void x86_emit_unary(String_Builder* sb, Scratch_Register reg);
void x86_emit_div(String_Builder* sb, Scratch_Register src, Scratch_Register dst);
void x86_emit_mul(String_Builder* sb, Scratch_Register src, Scratch_Register dst);
void x86_emit_sub(String_Builder* sb, Scratch_Register src, Scratch_Register dst);
void x86_emit_add(String_Builder* sb, Scratch_Register src, Scratch_Register dst);

void x86_emit_label(String_Builder* sb, const char* label)
{
    sb_appendf(sb, "%s:\n", label);
}

void x86_emit_add(String_Builder* sb, Scratch_Register src, Scratch_Register dst)
{
    sb_indent(sb, 8);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_ADD], scratch_name(dst), scratch_name(src));
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_ADD], scratch_name(src), scratch_name(dst));
#endif
    
}

void x86_emit_sub(String_Builder* sb, Scratch_Register src, Scratch_Register dst)
{
    sb_indent(sb, 8);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_SUB], scratch_name(dst), scratch_name(src));
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_SUB], scratch_name(src), scratch_name(dst));
#endif
}

void x86_emit_mul(String_Builder* sb, Scratch_Register src, Scratch_Register dst)
{
    x86_emit_move_reg_to_name(sb, src, register_names[REG_RAX]);

    const char* dst_name = scratch_name(dst);
    sb_indent(sb, 8);
    sb_appendf(sb, "%s     %s\n", instruction_names[INS_MUL], dst_name);

    x86_emit_move_name_to_name(sb, register_names[REG_RAX], dst_name);
}

void x86_emit_div(String_Builder* sb, Scratch_Register src, Scratch_Register dst) 
{
    x86_emit_move_reg_to_name(sb, src, register_names[REG_RAX]);

    sb_indent(sb, 8);
    sb_appendf(sb, "%s\n", instruction_names[INS_CQO]); 

    sb_indent(sb, 8);
    const char* dst_name = scratch_name(dst);
    sb_appendf(sb, "%s    %s\n", instruction_names[INS_DIV], dst_name);

    x86_emit_move_name_to_name(sb, register_names[REG_RAX], dst_name);
}

void x86_emit_unary(String_Builder* sb, Scratch_Register src)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "%s     %s\n", instruction_names[INS_NEG], scratch_name(src));
}

void x86_emit_move_reg_to_reg(String_Builder* sb, Scratch_Register src, Scratch_Register dst)
{
    sb_indent(sb, 8);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_MOV], scratch_name(dst), scratch_name(src));
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_MOV], scratch_name(src), scratch_name(dst));
#endif
}

static char literal_prefix()
{
#ifdef SKE_CODEGEN_INTEL
    return ' ';
#elif SKE_CODEGEN_AT_T
    return '$';
#endif
    return ' ';
}

void x86_emit_move_lit_to_reg(String_Builder* sb, i32 num, Scratch_Register dst)
{
    sb_indent(sb, 8);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %c%d\n", instruction_names[INS_MOV], scratch_name(dst), literal_prefix(), num);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %c%d, %s\n", instruction_names[INS_MOV], literal_prefix(), num, scratch_name(dst));
#endif
}

void x86_emit_move_lit_to_name(String_Builder* sb, i32 num, const char* dst)
{
    sb_indent(sb, 8);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %c%d\n", instruction_names[INS_MOV], dst, literal_prefix(), num);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %c%d, %s\n", instruction_names[INS_MOV], literal_prefix(), num, dst);
#endif
}

void x86_emit_move_name_to_reg(String_Builder* sb, const char* src, Scratch_Register dst)
{
    sb_indent(sb, 8);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_MOV], scratch_name(dst), src);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_MOV], src,  scratch_name(dst));
#endif
}

void x86_emit_move_reg_to_name(String_Builder* sb, Scratch_Register src, const char* dst)
{
    sb_indent(sb, 8);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_MOV], dst, scratch_name(src));
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_MOV], scratch_name(src),  dst);
#endif
}

void x86_emit_move_name_to_name(String_Builder* sb, const char* src, const char* dst)
{
    sb_indent(sb, 8);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_MOV], dst, src);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_MOV], src,  dst);
#endif
}

void x86_emit_ret(String_Builder* sb)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "%s\n", instruction_names[INS_RET]);
}

void x86_emit_pop_name(String_Builder* sb, const char* name)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "%s     %s\n", instruction_names[INS_POP], name);
}

void x86_emit_push_name(String_Builder* sb, const char* name)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "%s     %s\n", name, instruction_names[INS_PUSH]);
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
    sb_appendf(sb, "%s    %s\n", instruction_names[INS_CALL], function);
}

void x86_emit_comment_line(String_Builder* sb, const char* comment)
{
    sb_indent(sb, 8);
    sb_appendf(sb, "# %s\n", comment);
}

void x86_emit_xor_name_name(String_Builder* sb, const char* n1, const char* n2)
{
    sb_indent(sb, 8);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_XOR], n2, n1);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_names[INS_XOR], n1, n2);
#endif

}

typedef enum
{
    LINUX_SC_EXIT = 60
} Linux_Syscall;

void x86_emit_syscall(String_Builder* sb, Linux_Syscall syscall)
{
    x86_emit_move_lit_to_name(sb, (i32)syscall, register_names[REG_RAX]);
    sb_indent(sb, 8);
    sb_append(sb, "syscall\n");
}

void x86_emit_exit_syscall(String_Builder* sb)
{
    x86_emit_move_name_to_name(sb, register_names[REG_RAX], register_names[REG_RDI]);  
    x86_emit_move_lit_to_name(sb, LINUX_SC_EXIT, register_names[REG_RAX]);

    sb_indent(sb, 8);
    sb_append(sb, "syscall\n");
}

void x86_emit_start(String_Builder* sb)
{
    sb_append(sb, ".global _start\n");

    sb_append(sb, ".text\n");

    x86_emit_label(sb, "_start");

    x86_emit_xor_name_name(sb, register_names[REG_RBP], register_names[REG_RBP]);

    x86_emit_call(sb, "main");
    x86_emit_move_name_to_name(sb, register_names[REG_RAX], register_names[REG_RDI]);
    
    x86_emit_syscall(sb, LINUX_SC_EXIT);
}

String* x86_codegen_ir(IR_Program* program_node, Allocator* allocator)
{
    String_Builder sb;
    sb_init(&sb, 256);

    Scratch_Register_Table table;
    scratch_table_init(&table);

    Temp_Table temp_table;
    temp_table_init(&temp_table);

    sb_append(&sb, ".intel_syntax noprefix\n\n");
    
    for (i32 i = 0; i < program_node->function_array.count; i++)
    {
        IR_Function function = program_node->function_array.functions[i];
        if (function.exported)
        {
            String_View name = program_node->function_array.functions[i].name;
            sb_appendf(&sb, ".global %s\n", name.string->str);
        }
    }
    
    x86_emit_start(&sb);

    Scratch_Register current_reg;

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
                /* x86_emit_push_name(&sb, "%rbp"); */
                /* x86_emit_move_name_to_name(&sb, "%rsp", "%rbp"); */
            }
            break;
            case IR_NODE_LABEL:
            {
                x86_emit_label(&sb, node->label.label_name->str);
            }
            break;
            case IR_NODE_INSTRUCTION:
            {
                IR_Instruction* instruction = &node->instruction;

                switch(instruction->type)
                {
                case IR_INS_RET:
                {
                    IR_Return* ret = &instruction->ret;
                    if (ret->has_return_value)
                    {
                        Scratch_Register return_reg = get_or_add_scratch_from_temp(&temp_table, ret->return_register, &table);
                        x86_emit_move_reg_to_name(&sb, return_reg, register_names[REG_RAX]); // calling convention defined return
                    }
                    x86_emit_ret(&sb);
                }
                break;
                case IR_INS_CALL:
                {
                    IR_Call* call = &instruction->call;
                    String_View* name = ir_get_function_name(program_node, call->function_index);
                    x86_emit_call(&sb, name->string->str);
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
                default: compiler_bug("Unhandled IR instruction."); break;
            }
            break;
            }
            default: break;
            }
        }
    }

    /* sb_append(&sb, "\n"); */
    /* x86_emit_comment_line(&sb, "fprintf call to output result temporarily"); */
    /* x86_emit_move_name_to_name(&sb, "stderr", "%rax"); */
    /* x86_emit_move_reg_to_name(&sb, current_reg, "%rdx"); */
    /* x86_emit_move_name_to_name(&sb, "$format", "%rsi"); */
    /* x86_emit_move_name_to_name(&sb, "%rax", "%rdi"); */
    /* x86_emit_move_lit_to_name(&sb, 0, "%rax"); */
    /* x86_emit_call(&sb, "fprintf"); */
    /* x86_emit_move_lit_to_name(&sb, 0, "%rax"); */

    /* x86_emit_pop_name(&sb, "%rbp"); */

    /* x86_emit_ret(&sb); */

    /* x86_emit_asciz(&sb, "format", "%d\\n"); */

    String* assembly = sb_get_result(&sb, allocator);
    return assembly;
}

void x86_codegen_program(AST_Node* program_node, String_Builder* sb, Scratch_Register_Table* table)
{
    sb_append(sb, ".data\n");
    sb_append(sb, ".text\n");
    sb_append(sb, ".global _start\n");
    sb_append(sb, "_start:\n");

    x86_emit_push_name(sb, register_names[REG_RBP]);
    x86_emit_move_name_to_name(sb, register_names[REG_RSP], register_names[REG_RBP]);

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
