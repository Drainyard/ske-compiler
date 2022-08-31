void AST_node_list_add(AST_Node_List* list, AST_Node* node)
{
    if (list->count + 1 > list->capacity)
    {
        list->capacity = list->capacity == 0 ? 2 : list->capacity * 2;
        list->nodes = realloc(list->nodes, list->capacity * sizeof(AST_Node*));
    }
    list->nodes[list->count++] = node;
}

static char* AST_type_string(AST_Node_Type type)
{
    switch(type)
    {
    case AST_NODE_STATEMENT:
    return "AST statement";
    case AST_NODE_PROGRAM:
    return "AST program";
    case AST_NODE_FUN_DECL:
    return "AST function declaration";
    case AST_NODE_ARGUMENT_LIST:
    return "AST argument list";
    case AST_NODE_FUNCTION_ARGUMENT:
    return "AST function argument";
    case AST_NODE_VARIABLE:
    return "AST variable";
    case AST_NODE_CALL:
    return "AST call";
    case AST_NODE_RETURN:
    return "AST return";
    case AST_NODE_IF:
    return "AST if";
    case AST_NODE_BLOCK:
    return "AST block";
    case AST_NODE_LITERAL:
    return "AST literal";
    case AST_NODE_STRING:
    return "AST string";
    case AST_NODE_BINARY:
    return "AST binary";
    case AST_NODE_UNARY:
    return "AST unary";
    case AST_NODE_TYPE_SPECIFIER:
    return "AST type specifier";
    case AST_NODE_ERROR:
    return "AST error";
    }
    return "";
}

static void pretty_print_operator(Token_Type operator, String_Builder* builder)
{
    /* sb_append(builder, "("); */
    /* sb_append(builder, "Op: "); */
    switch (operator)
    {
    case TOKEN_PLUS:                    sb_append(builder, "+"); break;
    case TOKEN_MINUS:                   sb_append(builder, "-"); break;
    case TOKEN_STAR:                    sb_append(builder, "*"); break;
    case TOKEN_SLASH:                   sb_append(builder, "/"); break;
    case TOKEN_EQUAL_EQUAL:             sb_append(builder, "=="); break;
    case TOKEN_EQUAL:                   sb_append(builder, "="); break;
    case TOKEN_BANG_EQUAL:              sb_append(builder, "!="); break;
    case TOKEN_PIPE:                    sb_append(builder, "|"); break;
    case TOKEN_PIPE_PIPE:               sb_append(builder, "||"); break;
    case TOKEN_AMPERSAND:               sb_append(builder, "&"); break;
    case TOKEN_AMPERSAND_AMPERSAND:     sb_append(builder, "&&"); break;
    case TOKEN_LESS:                    sb_append(builder, "<"); break;
    case TOKEN_LESS_EQUAL:              sb_append(builder, "<="); break;
    case TOKEN_GREATER:                 sb_append(builder, ">"); break;
    case TOKEN_GREATER_EQUAL:           sb_append(builder, ">="); break;
    case TOKEN_ERROR: sb_append(builder, "ERROR"); break;
    default: COMPILER_BUG("AST pretty printer: Unknown operator: %s", token_type_to_string(operator));
    }
}

static void pretty_print_unary(AST_Node* node, i32 indentation, String_Builder* builder)
{
    /* indentation++; */
    sb_indent(builder, indentation);

    sb_append(builder, "(");
    pretty_print_operator(node->unary.operator, builder);

    pretty_print_expression(node->unary.expression, indentation, builder);
    sb_append(builder, ")");
}

static void pretty_print_binary(AST_Node* binary, i32 indentation, String_Builder* builder)
{
    /* sb_append(builder, "Binary\t\n "); */

    sb_indent(builder, indentation);
    sb_append(builder, "(");
    pretty_print_operator(binary->binary.operator, builder);
    sb_append(builder, " ");    
    
    pretty_print_expression(binary->binary.left, 0, builder);
    /* sb_indent(builder, indentation); */
    sb_append(builder, " ");   

    pretty_print_expression(binary->binary.right, 0, builder);
    sb_append(builder, ")");
}

static void pretty_print_literal(AST_Node* node, i32 indentation, String_Builder* builder)
{
    switch(node->literal.type)
    {
    case LIT_INT:
    {
        sb_appendf(builder, "%d", node->literal.i);
    }
    break;
    case LIT_FLOAT:
    {
        sb_appendf(builder, "%f", node->literal.f);
    }
    break;
    case LIT_STRING:
    {
        sb_appendf(builder, "%s", node->literal.s);
    }
    break;
    }
}

static void pretty_print_string(AST_Node* string, i32 indentation, String_Builder* builder)
{
    sb_appendf(builder, "%.*s", string->string->length, string->string->str);
}

static void pretty_print_call(AST_Node* call, i32 indentation, String_Builder* builder)
{
    sb_indent(builder, indentation);
    sb_appendf(builder, "(call %s ", call->fun_call.name->str);

    AST_Node_List* arguments = &call->fun_call.arguments;
    for (i32 i = 0; i < arguments->count; i++)
    {
        AST_Node* argument = arguments->nodes[i];
        pretty_print_expression(argument, 0, builder);

        if (i == arguments->count - 1)
        {
            break;
        }
        sb_append(builder, " ");
    }
    sb_append(builder, ")");
}

static void pretty_print_expression(AST_Node* node, i32 indentation, String_Builder* builder)
{
    switch(node->type)
    {
    case AST_NODE_UNARY:
    {
        pretty_print_unary(node, 0, builder);
    }
    break;
    case AST_NODE_BINARY:
    {
        pretty_print_binary(node, 0, builder);
    }
    break;
    case AST_NODE_LITERAL:
    {
        pretty_print_literal(node, 0, builder);
    }
    break;
    case AST_NODE_STRING:
    {
        pretty_print_string(node, 0, builder);
    }
    break;
    case AST_NODE_VARIABLE:
    {
        sb_appendf(builder, "%s", node->variable.variable_name->str);
    }
    break;
    case AST_NODE_CALL:
    {
        pretty_print_call(node, 0, builder);
    }
    break;
    default:
    {
        COMPILER_BUG("AST pretty printer: Unsupported node type %s\n", AST_type_string(node->type));
    }
    break;
    }
}

static void pretty_print_statement(AST_Node* statement, i32 indentation, String_Builder* builder)
{
    switch(statement->type)
    {
    case AST_NODE_RETURN:
    {
        sb_indent(builder, indentation);
        sb_append(builder, "(return");
        if (statement->return_statement.expression)
        {
            sb_append(builder, "\n");
            sb_indent(builder, indentation + 1);
            pretty_print_expression(statement->return_statement.expression, indentation, builder);
        }
        sb_append(builder, ")");
    }
    break;
    case AST_NODE_IF:
    {
        sb_indent(builder, indentation);
        sb_append(builder, "(if ");
        pretty_print_expression(statement->if_statement.condition, indentation, builder);
        sb_append(builder, " \n");
        pretty_print_block(statement->if_statement.then_arm, indentation, builder);
        sb_append(builder, "\n");

        if (statement->if_statement.else_arm)
        {
            sb_indent(builder, indentation);
            sb_append(builder, "(else \n");
            pretty_print_statement(statement->if_statement.else_arm, indentation + 1, builder);
            sb_append(builder, ")");
        }
        
        sb_append(builder, ")");
    }
    break;
    case AST_NODE_CALL:
    {
        pretty_print_call(statement, indentation, builder);
    }
    break;
    case AST_NODE_BLOCK:
    {
        pretty_print_block(statement, indentation, builder);
    }
    break;
    default: COMPILER_BUG("Not a valid statement type %s.", AST_type_string(statement->type)); break;
    }
}

static void pretty_print_block(AST_Node* block, i32 indentation, String_Builder* builder)
{
    AST_Node_List* list = &block->block.declarations;
    for (i32 i = 0; i < list->count; i++)
    {
        AST_Node* node = list->nodes[i];
        pretty_print_statement(node, indentation + 1, builder);
    }
}

static char* type_spec_to_string(Type_Specifier type)
{
    switch(type)
    {
    case TYPE_SPEC_INT:
    {
        return "int";
    }
    break;
    case TYPE_SPEC_UNIT:
    {
        return "()";
    }
    break;
    case TYPE_SPEC_INVALID:
    {
        return "invalid";
    }
    break;
    }
}

static void pretty_print_type_spec(AST_Node* type_spec, i32 indentation, String_Builder* builder)
{
    Type_Specifier spec = type_spec->type_specifier.type;
    sb_append(builder, type_spec_to_string(spec));
}

static void pretty_print_declaration(AST_Node* declaration, i32 indentation, String_Builder* builder)
{
    switch(declaration->type)
    {
    case AST_NODE_FUN_DECL:
    {
        sb_indent(builder, indentation);
        sb_appendf(builder, "(fun %s ", declaration->fun_decl.name->str);

        sb_append(builder, "[");
        
        AST_Node_List* argument_list = &declaration->fun_decl.arguments;
        for (i32 i = 0; i < argument_list->count; i++)
        {
            AST_Node* argument = argument_list->nodes[i];
            sb_appendf(builder, "%s : ", argument->fun_argument.name->str);
            pretty_print_type_spec(argument->fun_argument.type, indentation, builder);

            if (i < argument_list->count - 1)
            {
                sb_append(builder, ", ");
            }
        }
        
        sb_append(builder, "]");


        sb_append(builder, " -> ");

        if (declaration->fun_decl.return_type)
        {
            pretty_print_type_spec(declaration->fun_decl.return_type, indentation, builder);
        }
        else
        {
            sb_append(builder, "()");
        }

        AST_Node_List block = declaration->fun_decl.body->block.declarations;

        if (block.count > 0)
        {
            sb_append(builder, "\n");
        }

        pretty_print_block(declaration->fun_decl.body, indentation, builder);

        sb_append(builder, ")");
    }
    break;
    default: assert(false && "Not a declaration."); break;
    }
}

static void pretty_print_program(AST_Node* program_node, i32 indentation, String_Builder* builder)
{
    sb_append(builder, "(");
    sb_append(builder, "program\t\n");
    indentation++;

    AST_Node_List list = program_node->program.declarations;

    for (i32 i = 0; i < list.count; i++)
    {
        AST_Node* declaration = list.nodes[i];
        pretty_print_declaration(declaration, indentation, builder);

        if (i < list.count - 1)
        {
            sb_append(builder, "\n");
        }
    }
    
    /* pretty_print_expression(program_node->program.expression, indentation, builder); */
    sb_append(builder, ")");
}

static String* pretty_print_ast(AST_Node* root, Allocator* allocator)
{
    assert(root->type == AST_NODE_PROGRAM);
    String_Builder builder;
    sb_init(&builder, 256);
    pretty_print_program(root, 0, &builder);
    sb_append(&builder, "\n");

    return sb_get_result(&builder, allocator);
}
