#ifndef X86_CODEGEN_H
#define X86_CODEGEN_H

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
    sb_indent(sb, 4);
    sb_appendf(sb, "addq    %s, %s\n", scratch_name(src), scratch_name(dst));
}

void x86_emit_sub(String_Builder* sb, int src, int dst)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "subq    %s, %s\n", scratch_name(dst), scratch_name(src));   
}

void x86_emit_mul(String_Builder* sb, int src, int dst)
{
    x86_emit_move_reg_to_name(sb, src, "%rax");

    const char* dst_name = scratch_name(dst);
    sb_indent(sb, 4);
    sb_appendf(sb, "imulq   %s\n", dst_name);

    x86_emit_move_name_to_name(sb, "%rax", dst_name);
}

void x86_emit_div(String_Builder* sb, int src, int dst) 
{
    x86_emit_move_reg_to_name(sb, src, "%rax");

    sb_indent(sb, 4);
    sb_append(sb, "cqo\n");

    sb_indent(sb, 4);
    const char* dst_name = scratch_name(dst);
    sb_appendf(sb, "idivq   %s\n", dst_name);

    x86_emit_move_name_to_name(sb, "%rax", dst_name);
}

void x86_emit_unary(String_Builder* sb, int src)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "negq    %s\n", scratch_name(src));
}

void x86_emit_move_reg_to_reg(String_Builder* sb, int src, int dst)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "movq    %s, %s\n", scratch_name(src), scratch_name(dst));
}

void x86_emit_move_lit_to_reg(String_Builder* sb, int num, int dst)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "movq    $%d, %s\n", num, scratch_name(dst));
}

void x86_emit_move_name_to_reg(String_Builder* sb, const char* src, int dst)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "movq    %s, %s\n", src, scratch_name(dst));
}

void x86_emit_move_reg_to_name(String_Builder* sb, int src, const char* dst)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "movq    %s, %s\n", scratch_name(src), dst);
}

void x86_emit_move_name_to_name(String_Builder* sb, const char* src, const char* dst)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "movq    %s, %s\n", src, dst);
}

Scratch_Register x86_codegen_expression(AST_Store*, AST_Node_Handle, String_Builder*, Scratch_Register_Table*);

Scratch_Register x86_codegen_expression(AST_Store* store, AST_Node_Handle node_handle, String_Builder* sb, Scratch_Register_Table* table)
{
    AST_Node* node = ast_store_get_node(store, node_handle);

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
        Scratch_Register left_reg = x86_codegen_expression(store, node->binary.left, sb, table);
        Scratch_Register right_reg = x86_codegen_expression(store, node->binary.right, sb, table);

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
        Scratch_Register reg = x86_codegen_expression(store, node->unary.expression, sb, table);
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
    sb_indent(sb, 4);
    sb_append(sb, "ret\n");
}

void x86_emit_pop_name(String_Builder* sb, const char* name)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "popq    %s\n", name);
}

void x86_emit_push_name(String_Builder* sb, const char* name)
{
    sb_indent(sb, 4);
    sb_appendf(sb, "pushq   %s\n", name);
}

void x86_codegen_program(AST_Store* store, AST_Node_Handle program_handle, String_Builder* sb, Scratch_Register_Table* table)
{
    sb_append(sb, ".data\n");
    sb_append(sb, ".text\n");
    sb_append(sb, ".global main\n");
    sb_append(sb, "main:\n");

    x86_emit_push_name(sb, "%rbp");

    x86_emit_move_name_to_name(sb, "%rsp", "%rbp");

    AST_Node* program_node = ast_store_get_node(store, program_handle);
    Scratch_Register final_reg = x86_codegen_expression(store, program_node->program.expression, sb, table);

    x86_emit_move_reg_to_name(sb, final_reg, "%rax");
    scratch_free(table, final_reg);

    x86_emit_pop_name(sb, "%rbp");

    x86_emit_ret(sb);    
}

void x86_codegen_ast(AST_Store* store, AST_Node_Handle root, String* out_file, Allocator* allocator)
{
    assert(store->count > 0);
    String_Builder sb;
    sb_init(&sb, 256);

    Scratch_Register_Table register_table;
    scratch_table_init(&register_table);
    x86_codegen_program(store, root, &sb, &register_table);

    String* assembly = sb_get_result(&sb, allocator);
    string_print(assembly);

    if (out_file)
    {
        FILE* file = fopen(out_file->str, "w");
        string_fprintf(assembly, file);
        fclose(file);
    }
}

#endif
