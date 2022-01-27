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

const char* scratch_name(Scratch_Register reg)
{
    return scratch_register_names[reg];
}

i32 label_count = 0;
i32 label_create()
{
    return label_count++;
}

String* label_name(i32 label)
{
    return string_createf(".L%d", label);
}

Scratch_Register x86_codegen_expression(AST_Store*, AST_Node_Handle, String_Builder*, Scratch_Register_Table*);

Scratch_Register x86_codegen_expression(AST_Store* store, AST_Node_Handle node_handle, String_Builder* sb, Scratch_Register_Table* table)
{
    AST_Node* node = get_node(store, node_handle);

    switch (node->type)
    {
    case AST_NODE_NUMBER:
    {
        Scratch_Register reg = scratch_alloc(table);
        sb_indent(4, sb);
        sb_appendf(sb, "movq $%d, %s\n", node->number, scratch_name(reg));
        return reg;
    }
    case AST_NODE_BINARY:
    {
        Scratch_Register left_reg = x86_codegen_expression(store, node->binary.left, sb, table);
        Scratch_Register right_reg = x86_codegen_expression(store, node->binary.right, sb, table);

        sb_indent(4, sb);
        sb_appendf(sb, "addq %s, %s\n", scratch_name(left_reg), scratch_name(right_reg));
        scratch_free(table, left_reg);
        return right_reg;
    }
    case AST_NODE_UNARY:
    {
        Scratch_Register reg = x86_codegen_expression(store, node->unary.expression, sb, table);
        sb_indent(4, sb);
        sb_appendf(sb, "negq %s\n", scratch_name(reg));
        return reg;
    }
    default:
    printf("%d\n", node->type);
    assert("Unsupported AST Node" && false);
    }

    return -1;
}

void x86_codegen_program(AST_Store* store, AST_Node_Handle program_handle, String_Builder* sb, Scratch_Register_Table* table)
{
    sb_append(sb, ".data\n");
    sb_append(sb, ".text\n");
    sb_append(sb, ".global main\n");
    sb_append(sb, "main:\n");

    sb_indent(4, sb);
    sb_append(sb, "pushq %rbp\n");
    
    sb_indent(4, sb);
    sb_append(sb, "movq  %rsp, %rbp\n");

    AST_Node* program_node = get_node(store, program_handle);
    Scratch_Register final_reg = x86_codegen_expression(store, program_node->program.expression, sb, table);
    
    sb_indent(4, sb);
    sb_appendf(sb, "movq %s, %rax\n", scratch_name(final_reg));
    scratch_free(table, final_reg);

    sb_indent(4, sb);
    sb_append(sb, "popq %rbp\n");

    sb_indent(4, sb);
    sb_append(sb, "ret\n");
}

void x86_codegen_ast(AST_Store* store, AST_Node_Handle root)
{
    assert(store->count > 0);
    String_Builder sb;
    sb_init(&sb, 256);

    Scratch_Register_Table register_table;
    scratch_table_init(&register_table);
    x86_codegen_program(store, root, &sb, &register_table);

    String* assembly = sb_get_result(&sb);
    string_print(assembly);

    FILE* out_file = fopen("x86_out.s", "w");
    if (out_file)
    {
        string_fprintf(assembly, out_file);
        fclose(out_file);
    }
}


#endif
