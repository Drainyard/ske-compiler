#ifndef AST_H
#define AST_H

typedef enum
{
    AST_NODE_STATEMENT,
    AST_NODE_PROGRAM,
    AST_NODE_FUN_DECL,
    AST_NODE_CALL,
    AST_NODE_ARGUMENT_LIST,
    AST_NODE_IF,
    AST_NODE_RETURN,
    AST_NODE_BLOCK,
    AST_NODE_NUMBER,
    AST_NODE_STRING,
    AST_NODE_BINARY,
    AST_NODE_UNARY,
    AST_NODE_TYPE_SPECIFIER,
    AST_NODE_ERROR
} AST_Node_Type;

typedef enum
{
    TYPE_SPEC_INT,
    TYPE_SPEC_UNIT
} Type_Specifier;

typedef struct  AST_Node_List AST_Node_List;
struct AST_Node_List
{
    struct AST_Node** nodes;
    i32 capacity;
    i32 count;
};

typedef struct AST_Node AST_Node;
struct AST_Node
{
    AST_Node_Type type;

    union
    {
        i32 number; // @Incomplete: Should be expanded to other constant types (float, string, etc.)
        String* string;
        struct
        {
            AST_Node* expression;
            Token_Type operator;
        } unary;
        struct
        {
            AST_Node* left;
            AST_Node* right;

            Token_Type operator;
        } binary;
        struct
        {
            AST_Node_List declarations;
        } program;
        struct
        {
            AST_Node* expression;
        } expression;
        struct
        {
            AST_Node* statement;
        } statement;
        struct
        {
            AST_Node* expression;
        } return_statement;
        struct
        {
            AST_Node* condition;
            AST_Node* then_arm;
            AST_Node* else_arm;
        } if_statement;
        struct
        {
            String* name;
            AST_Node* type_specifier;
            AST_Node* arguments;
            AST_Node* body;
        } fun_decl;
        struct
        {
            AST_Node** arguments;
            i32 count;
        } argument_list;
        struct
        {
            String* name;
            AST_Node* arguments;
        } fun_call;
        struct
        {
            AST_Node_List declarations;
        } block;
        struct
        {
            Type_Specifier type;
        } type_specifier;
        struct
        {
            AST_Node* rest;
        } error;
    };
};

void ast_node_list_add(AST_Node_List* list, AST_Node* node)
{
    if (list->count + 1 > list->capacity)
    {
        list->capacity = list->capacity == 0 ? 2 : list->capacity * 2;
        list->nodes = realloc(list->nodes, list->capacity * sizeof(AST_Node*));
    }
    list->nodes[list->count++] = node;
}


static char* parser_type_string(AST_Node_Type type)
{
    switch(type)
    {
    case AST_NODE_STATEMENT:
    return "AST_NODE_STATEMENT";
    case AST_NODE_PROGRAM:
    return "AST_NODE_PROGRAM";
    case AST_NODE_FUN_DECL:
    return "AST_NODE_FUN_DECL";
    case AST_NODE_ARGUMENT_LIST:
    return "AST_NODE_ARGUMENT_LIST";
    case AST_NODE_CALL:
    return "AST_NODE_CALL";
    case AST_NODE_RETURN:
    return "AST_NODE_RETURN";
    case AST_NODE_IF:
    return "AST_NODE_IF";
    case AST_NODE_BLOCK:
    return "AST_NODE_BLOCK";
    case AST_NODE_NUMBER:
    return "AST_NODE_NUMBER";
    case AST_NODE_STRING:
    return "AST_NODE_STRING";
    case AST_NODE_BINARY:
    return "AST_NODE_BINARY";
    case AST_NODE_UNARY:
    return "AST_NODE_UNARY";
    case AST_NODE_TYPE_SPECIFIER:
    return "AST_NODE_TYPE_SPECIFIER";
    case AST_NODE_ERROR:
    return "AST_NODE_ERROR";
    }
    return "";
}

static void pretty_print_unary(AST_Node* node, i32 indentation, String_Builder* builder);
static void pretty_print_binary(AST_Node* binary, i32 indentation, String_Builder* builder);
static void pretty_print_string(AST_Node* string, i32 indentation, String_Builder* builder);
static void pretty_print_expression(AST_Node* node, i32 indentation, String_Builder* builder);

typedef void (*Pretty_Print_Fn)(AST_Node*, i32, String_Builder*);

/* static void paren(String_Builder* builder, Pretty_Print_Fn print_fn, AST_Node* node, i32 indentation) */
/* { */
/*     sb_indent(builder, indentation); */
/*     sb_append(builder, "("); */
/*     print_fn(node, indentation, builder); */
/*     sb_append(builder, ")"); */
/* } */

static void pretty_print_operator(Token_Type operator, String_Builder* builder)
{
    /* sb_append(builder, "("); */
    /* sb_append(builder, "Op: "); */
    switch (operator)
    {
    case TOKEN_PLUS: sb_append(builder, "+"); break;
    case TOKEN_MINUS: sb_append(builder, "-"); break;
    case TOKEN_STAR:  sb_append(builder, "*"); break;
    case TOKEN_SLASH: sb_append(builder, "/"); break;
    case TOKEN_ERROR: sb_append(builder, "ERROR"); break;
    default: assert(false);
    }
    /* sb_append(builder, ")"); */
}

static void pretty_print_unary(AST_Node* node, i32 indentation, String_Builder* builder)
{
    sb_append(builder, "Unary\t\n ");
    
    indentation++;
    sb_indent(builder, indentation);

    pretty_print_operator(node->unary.operator, builder);

    sb_append(builder, ",\n ");
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

static void pretty_print_number(AST_Node* number, i32 indentation, String_Builder* builder)
{
    sb_appendf(builder, "%d", number->number);
}

static void pretty_print_string(AST_Node* string, i32 indentation, String_Builder* builder)
{
    sb_appendf(builder, "%.*s", string->string->length, string->string->str);
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
    case AST_NODE_NUMBER:
    {
        pretty_print_number(node, 0, builder);
    }
    break;
    case AST_NODE_STRING:
    {
        pretty_print_string(node, 0, builder);
    }
    break;
    default:
    {
        log_error("Unsupported node type %s\n", parser_type_string(node->type));
        assert(false);
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
        sb_append(builder, " ");
        pretty_print_statement(statement->if_statement.then_arm, indentation, builder);

        if (statement->if_statement.else_arm)
        {
            sb_append(builder, " ");
            pretty_print_statement(statement->if_statement.else_arm, indentation, builder);
        }
        
        sb_append(builder, ")");
    }
    break;
    case AST_NODE_CALL:
    {
        sb_indent(builder, indentation);
        sb_appendf(builder, "(call %s", statement->fun_call.name->str);

        AST_Node* arguments = statement->fun_call.arguments;
        for (i32 i = 0; i < arguments->argument_list.count; i++)
        {
            AST_Node* argument = arguments->argument_list.arguments[i];
            pretty_print_expression(argument, 0, builder);
            sb_append(builder, " ");
        }
        sb_append(builder, ")");
    }
    break;
    default: assert(false && "Not a valid statement type"); break;
    }
}

static void pretty_print_declaration(AST_Node* declaration, i32 indentation, String_Builder* builder)
{
    switch(declaration->type)
    {
    case AST_NODE_FUN_DECL:
    {
        sb_indent(builder, indentation);
        sb_appendf(builder, "(fun %s ()", declaration->fun_decl.name->str);

        AST_Node_List block = declaration->fun_decl.body->block.declarations;

        if (block.count > 0)
        {
            sb_append(builder, ",\n");
        }

        for (i32 i = 0; i < block.count; i++)
        {
            AST_Node* node = block.nodes[i];
            pretty_print_statement(node, indentation + 1, builder);
        }

        sb_append(builder, ")\n");
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

#endif
