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
    
    x86_emit_header(&sb);

    Scratch_Register final_reg;

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
                // @Incomplete: Currently ignoring lables
            }
            break;
            case IR_NODE_INSTRUCTION:
            {
                IR_Instruction* instruction = &node->instruction;
                /* sb_indent(sb, 8); */

                switch(instruction->type)
                {
                case IR_INS_RET:
                {}
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
                        if(dst->type == IR_LOCATION_REGISTER)
                        {
                            if (src->loc.type == IR_LOCATION_REGISTER)
                            {
                                Scratch_Register src = scratch_alloc(&table);
                                final_reg = scratch_alloc(&table);
                                x86_emit_move_reg_to_reg(&sb, src, final_reg);
                                scratch_free(&table, src);
                            }
                        }
                    }
                    break;
                    case VALUE_INT:
                    {
                        if(dst->type == IR_LOCATION_REGISTER)
                        {
                            final_reg = scratch_alloc(&table);
                            x86_emit_move_lit_to_reg(&sb, src->integer, final_reg);
                        }
                    }
                    break;
                    case VALUE_VARIABLE:
                    {}
                    break;
                    }
                    
                    /* sb_append(sb, "move    "); */

                    /* ir_pretty_print_value(sb, src); */
                    /* sb_append(sb, ", "); */
                    /* ir_pretty_print_location(sb, dst); */

                    /* sb_newline(&sb); */
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
                        /* Scratch_Register reg = scratch_alloc(table); */
                        /* x86_emit_push_name(sb, scratch_name(reg)); */
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
                        Scratch_Register reg = scratch_alloc(&table);
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
                {}
                break;
                case IR_INS_BINOP:
                {
                    IR_BinOp* binop = &instruction->binop;
                    /* IR_Value* left = &binop->left; */
                    /* IR_Value* right = &binop->right; */

                    /* Scratch_Register left_reg = scratch_alloc(table); */
                    /* Scratch_Register right_reg = scratch_alloc(table); */

                    switch(binop->operator)
                    {
                    case OP_ADD:
                    {
                        
                    }
                    break;
                    case OP_SUB:
                    {
                        
                    }
                    break;
                    case OP_MUL:
                    {
                        
                    }
                    break;
                    case OP_DIV:
                    {
                        
                    }
                    break;
                    }
                }
                break;
                default: break;
            }
            break;
            }
            }
        }
    }

    sb_append(&sb, "\n");
    x86_emit_comment_line(&sb, "fprintf call to output result temporarily");
    x86_emit_move_name_to_name(&sb, "stderr", "%rax");
    x86_emit_move_reg_to_name(&sb, final_reg, "%rdx");
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

    Scratch_Register final_reg = x86_codegen_expression(program_node->program.expression, sb, table);

    x86_emit_move_reg_to_name(sb, final_reg, "%rax");
    scratch_free(table, final_reg);

    // @Note: Emit instructions for fprintf call (used for now)
    sb_append(sb, "\n");
    x86_emit_comment_line(sb, "fprintf call to output result temporarily");
    x86_emit_move_name_to_name(sb, "stderr", "%rax");
    x86_emit_move_reg_to_name(sb, final_reg, "%rdx");
    x86_emit_move_name_to_name(sb, "$format", "%rsi");
    x86_emit_move_name_to_name(sb, "%rax", "%rdi");
    x86_emit_move_lit_to_name(sb, 0, "%rax");
    x86_emit_call(sb, "fprintf");
    x86_emit_move_lit_to_name(sb, 0, "%rax");

    x86_emit_pop_name(sb, "%rbp");

    x86_emit_ret(sb);

    x86_emit_asciz(sb, "format", "%d\\n");
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
