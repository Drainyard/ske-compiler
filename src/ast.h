#ifndef AST_H
#define AST_H

typedef enum
{
    AST_NODE_STATEMENT,
    AST_NODE_PROGRAM,
    AST_NODE_FUN_DECL,
    AST_NODE_CALL,
    AST_NODE_ARGUMENT_LIST,
    AST_NODE_FUNCTION_ARGUMENT,
    AST_NODE_VARIABLE,
    AST_NODE_IF,
    AST_NODE_RETURN,
    AST_NODE_BLOCK,
    AST_NODE_LITERAL,
    AST_NODE_BINARY,
    AST_NODE_UNARY,
    AST_NODE_TYPE_SPECIFIER,
    AST_NODE_ERROR
} AST_Node_Type;

typedef enum
{
    TYPE_SPEC_INT,
    TYPE_SPEC_UNIT,
    TYPE_SPEC_INVALID
} Type_Specifier;

typedef struct AST_Node AST_Node;

typedef struct  AST_Node_List AST_Node_List;
struct AST_Node_List
{
    AST_Node** nodes;
    i32 capacity;
    i32 count;
};

typedef struct AST_Literal AST_Literal;
struct AST_Literal
{
    enum AST_Literal_Type
    {
        LIT_INT,
        LIT_FLOAT,
        LIT_STRING
    } type;

    union
    {
        i64 i; // @Incomplete: Should be different int sizes at some point
        f64 f;
        String* s;
    };
};

typedef struct AST_Node AST_Node;
struct AST_Node
{
    AST_Node_Type type;
    AST_Node* parent;

    union
    {
        AST_Literal literal; // @Incomplete: Should be expanded to other constant types (float, string, etc.)
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
            String* variable_name;
        } variable;
        struct
        {
            String* name;
            AST_Node* return_type;
            AST_Node_List arguments;
            AST_Node* body;
        } fun_decl;
        struct
        {
            String* name;
            AST_Node* type; // @Incomplete: Should this be something typesafe (hah)?
        } fun_argument;
        struct
        {
            String* name;
            AST_Node_List arguments;
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

typedef void (*Pretty_Print_Fn)(AST_Node*, i32, String_Builder*);

static void pretty_print_unary(AST_Node* node, i32 indentation, String_Builder* builder);
static void pretty_print_binary(AST_Node* binary, i32 indentation, String_Builder* builder);
static void pretty_print_string(AST_Node* string, i32 indentation, String_Builder* builder);
static void pretty_print_expression(AST_Node* node, i32 indentation, String_Builder* builder);
static void pretty_print_block(AST_Node* block, i32 indentation, String_Builder* builder);
static void pretty_print_statement(AST_Node* statement, i32 indentation, String_Builder* builder);
static void pretty_print_expression(AST_Node* expression, i32 indentation, String_Builder* builder);


#endif
