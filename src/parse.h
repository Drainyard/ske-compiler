#ifndef PARSE_H
#define PARSE_H

typedef enum
{
    AST_NODE_STATEMENT,
    AST_NODE_EXPRESSION,
    AST_NODE_PROGRAM,
    AST_NODE_FUN_DECL,
    AST_NODE_CONSTANT,
    AST_NODE_BINARY,
    AST_NODE_UNARY,
    AST_NODE_TYPE_SPECIFIER,
    AST_NODE_ERROR
} AST_Node_Type;

typedef enum
{
    TYPE_SPEC_INT,
    TYPE_SPEC_VOID
} Type_Specifier;

struct AST_Node;
struct AST_Node
{
    AST_Node_Type type;

    union
    {
        i32 constant; // @Incomplete: Should be expanded to other constant types (float, string, etc.)
        struct
        {
            struct AST_Node* expression;
            Token_Type unary_token;
        } unary;
        struct
        {
            struct AST_Node* left;
            struct AST_Node* right;

            Token_Type operator;
        } binary;
        struct
        {
            struct AST_Node* expression;
        } expression;
        struct
        {
            struct AST_Node* statement;
        } statement;
        struct
        {
            const char* name;
            struct AST_Node* type_specifier;
            struct AST_Node* arguments;
        } fun_decl;
        struct
        {
            struct AST_Node* fun_decl;
        } program;
        struct
        {
            Type_Specifier type;
        } type_specifier;
        struct
        {
            struct AST_Node* rest;
        } error;
    };
};

typedef enum
{
    PREC_NONE,
    PREC_ASSIGNMENT,  // =
    PREC_OR,          // or
    PREC_AND,         // and
    PREC_EQUALITY,    // == !=
    PREC_COMPARISON,  // < > <= >=
    PREC_TERM,        // + -
    PREC_FACTOR,      // * /
    PREC_UNARY,       // ! -
    PREC_CALL,        // . ()
    PREC_PRIMARY
} Precedence;

struct Parser;
typedef struct AST_Node* (*Parse_Fn)(struct Parser*);
typedef struct
{
    Parse_Fn prefix;
    Parse_Fn infix;
    Precedence precedence;
} Parse_Rule;

typedef struct
{
    struct AST_Node* nodes;
    i32 capacity;
    i32 count;
} AST_Store;


struct Parser
{
    Token current;
    Token previous;

    Token* token_stream;
    i32 current_token;

    AST_Store ast_store;

    bool had_error;
    bool panic_mode;
};

static void error_at(struct Parser* parser, Token* token, const char* message)
{
    if (parser->panic_mode) return;
    parser->panic_mode = true;
    
    fprintf(stderr, "[line %d] Error", token->line);

    if (token->type == TOKEN_EOF)
    {
        fprintf(stderr, " at end");
    }
    else if (token->type == TOKEN_ERROR)
    {
        
    }
    else
    {
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    }
    fprintf(stderr, ": %s\n", message);
    parser->had_error = true;
}

void error(struct Parser* parser, const char* message)
{
    error_at(parser, &parser->previous, message);
}

void error_at_current(struct Parser* parser, const char* message)
{
    error_at(parser, &parser->current, message);
}

void advance_parser(struct Parser* parser)
{
    parser->previous = parser->current;

    for (;;)
    {
        parser->current = parser->token_stream[parser->current_token++];
        if (parser->current.type != TOKEN_ERROR) break;

        error_at_current(parser, parser->current.start);
    }
}

static void init_ast_store_with_capacity(AST_Store* store, i32 initial_capacity)
{
    store->capacity = initial_capacity;
    store->nodes = malloc(sizeof(struct AST_Node) * store->capacity);
    store->count = 0;
}

static void init_ast_store(AST_Store* store)
{
    init_ast_store_with_capacity(store, 32);
}

static struct AST_Node* add_node(AST_Store* store, AST_Node_Type type)
{
    if(store->capacity <= store->count + 1)
    {
        store->capacity *= 2;
        store->nodes = realloc(store->nodes, store->capacity);
    }

    struct AST_Node* new_node = &store->nodes[store->count++];
    new_node->type = type;
    return new_node;
}

void init_parser(struct Parser* parser, Token* tokens, i32 token_count)
{
    parser->current = tokens[0];
    parser->token_stream = tokens;
    parser->current_token = 0;
    parser->had_error = false;
    parser->panic_mode = false;

    init_ast_store(&parser->ast_store);
}

static void consume(struct Parser* parser, Token_Type token_type, const char* message)
{
    if (parser->current.type == token_type)
    {
        advance_parser(parser);
        return;
    }

    error_at_current(parser, message);
}

static Parse_Rule* get_rule(Token_Type type);
static struct AST_Node* parse_expression(struct Parser* parser);
static struct AST_Node* parse_precedence(struct Parser* parser, Precedence precedence);

static struct AST_Node* parse_precedence(struct Parser* parser, Precedence precedence)
{
    advance_parser(parser);
    Parse_Fn prefix_rule = get_rule(parser->previous.type)->prefix;
    if (prefix_rule == NULL)
    {
        error(parser, "Expect expression.");
        struct AST_Node* error_node = add_node(&parser->ast_store, AST_NODE_ERROR);
        return error_node;
    }

    struct AST_Node* prefix_node = prefix_rule(parser);

    while (precedence <= get_rule(parser->current.type)->precedence)
    {
        advance_parser(parser);
        Parse_Fn infix_rule = get_rule(parser->previous.type)->infix;
        struct AST_Node* infix = infix_rule(parser);

        if(infix)
        {
            switch(infix->type)
            {
            case AST_NODE_BINARY:
            {
                infix->binary.left = prefix_node;
            }
            break;
            }
        }
    }

    return prefix_node;
}

static struct AST_Node* parse_number(struct Parser* parser)
{
    i32 value = strtol(parser->previous.start, NULL, 10);
    // @Incomplete: Allocate an int constant here

    return NULL;
}

static struct AST_Node* parse_expression(struct Parser* parser)
{
    struct AST_Node* expression = add_node(&parser->ast_store, AST_NODE_EXPRESSION);
    expression->expression.expression = parse_precedence(parser, PREC_ASSIGNMENT);
    return expression;
}

static struct AST_Node* parse_binary(struct Parser* parser)
{
    Token_Type operator_type = parser->previous.type;
    Parse_Rule* rule = get_rule(operator_type);

    struct AST_Node* binary_expression = add_node(&parser->ast_store, AST_NODE_BINARY);
    
    binary_expression->binary.right = parse_precedence(parser, rule->precedence + 1);

    switch (operator_type)
    {
    case TOKEN_PLUS:
    case TOKEN_MINUS:
    case TOKEN_STAR:
    case TOKEN_SLASH: 
    {
        binary_expression->binary.operator = operator_type;
    }
    break;    
    default:
    binary_expression->binary.operator = TOKEN_ERROR;
    }
    return binary_expression;
}

static struct AST_Node* parse_unary(struct Parser* parser)
{
    Token_Type operator_type = parser->previous.type;
    struct AST_Node* unary_expression = add_node(&parser->ast_store, AST_NODE_UNARY);

    unary_expression->unary.expression = parse_precedence(parser, PREC_UNARY);

    switch (operator_type)
    {
    case TOKEN_MINUS:
    {
        unary_expression->unary.unary_token = TOKEN_MINUS;
    }
    break;
    case TOKEN_BANG:
    {
        unary_expression->unary.unary_token = TOKEN_BANG;
    }
    break;
    default:
    {
        unary_expression->unary.unary_token = TOKEN_ERROR;
    }
    break;
    }
    return unary_expression;
}

static struct AST_Node* parse_grouping(struct Parser* parser)
{
    struct AST_Node* node = parse_expression(parser);
    consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
    return node;
}

Parse_Rule rules[] = {
  [TOKEN_LEFT_PAREN]       = {parse_grouping, NULL,         PREC_NONE},
  [TOKEN_RIGHT_PAREN]      = {NULL,           NULL,         PREC_NONE},
  /* [TOKEN_LEFT_BRACE]    = {NULL,           NULL,         PREC_NONE},  */
  /* [TOKEN_RIGHT_BRACE]   = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_COMMA]         = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_DOT]           = {NULL,           NULL,         PREC_NONE}, */
  [TOKEN_MINUS]            = {parse_unary,    parse_binary, PREC_TERM},
  [TOKEN_PLUS]             = {NULL,           parse_binary, PREC_TERM},
  /* [TOKEN_SEMICOLON]     = {NULL,           NULL,         PREC_NONE}, */
  [TOKEN_SLASH]            = {NULL,           parse_binary, PREC_FACTOR},
  [TOKEN_STAR]             = {NULL,           parse_binary, PREC_FACTOR},
  /* [TOKEN_BANG]          = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_BANG_EQUAL]    = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_EQUAL]         = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_EQUAL_EQUAL]   = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_GREATER]       = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_GREATER_EQUAL] = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_LESS]          = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_LESS_EQUAL]    = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_IDENTIFIER]    = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_STRING]        = {NULL,           NULL,         PREC_NONE}, */
  [TOKEN_NUMBER]           = {parse_number,   NULL,         PREC_NONE},
  /* [TOKEN_AND]           = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_CLASS]         = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_ELSE]          = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_FALSE]         = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_FOR]           = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_FUN]           = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_IF]            = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_NIL]           = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_OR]            = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_PRINT]         = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_RETURN]        = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_SUPER]         = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_THIS]          = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_TRUE]          = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_VAR]           = {NULL,           NULL,         PREC_NONE}, */
  /* [TOKEN_WHILE]         = {NULL,           NULL,         PREC_NONE}, */
  [TOKEN_ERROR]            = {NULL,           NULL,         PREC_NONE},
  [TOKEN_EOF]              = {NULL,           NULL,         PREC_NONE},
};

static Parse_Rule* get_rule(Token_Type type)
{
    return &rules[type];
}

static void pretty_print_unary(struct AST_Node* node, i32 indentation)
{
    
}

static void pretty_print_binary(struct AST_Node* node, i32 indentation)
{
    for(i32 i = 0; i < indentation; i++)
    {
        printf("\t");
    }

    
}

static void pretty_print_expression(struct AST_Node* node, i32 indentation)
{
    printf("Expression(\n");
    indentation++;

    struct AST_Node* child = node->expression.expression;

    switch(child->type)
    {
    case AST_NODE_UNARY:
    {
        pretty_print_unary(child, indentation);
    }
    break;
    case AST_NODE_BINARY:
    {
        pretty_print_binary(child, indentation);
    }
    break;
    }
}

static void pretty_print_ast(AST_Store* store)
{
    assert(store->count > 0);
    struct AST_Node* root = &store->nodes[0];

    assert(root->type == AST_NODE_EXPRESSION);
    pretty_print_expression(root, 0);
}

bool parse(Token* tokens, i32 token_count)
{
    struct Parser parser = {};
    init_parser(&parser, tokens, token_count);

    advance_parser(&parser);
    struct AST_Node* expression_node = parse_expression(&parser);
    consume(&parser, TOKEN_EOF, "Expect end of expression");

    pretty_print_ast(&parser.ast_store);

    return !parser.had_error;
}


#endif
