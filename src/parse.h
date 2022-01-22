#ifndef PARSE_H
#define PARSE_H

typedef enum
{
    AST_NODE_STATEMENT,
    /* AST_NODE_EXPRESSION, */
    AST_NODE_PROGRAM,
    AST_NODE_FUN_DECL,
    AST_NODE_NUMBER,
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

typedef struct
{
    i32 handle;
} AST_Node_Handle;
static AST_Node_Handle INVALID_HANDLE = { .handle = -1 };
#define AST_HANDLE_VALID(handle) (handle.handle != -1)

typedef struct
{
    AST_Node_Type type;

    union
    {
        i32 number; // @Incomplete: Should be expanded to other constant types (float, string, etc.)
        struct
        {
            AST_Node_Handle expression;
            Token_Type operator;
        } unary;
        struct
        {
            AST_Node_Handle left;
            AST_Node_Handle right;

            Token_Type operator;
        } binary;
        struct
        {
            AST_Node_Handle expression;
        } program;
        struct
        {
            AST_Node_Handle expression;
        } expression;
        struct
        {
            AST_Node_Handle statement;
        } statement;
        struct
        {
            const char* name;
            AST_Node_Handle type_specifier;
            AST_Node_Handle arguments;
        } fun_decl;
        /* struct */
        /* { */
        /*     AST_Node_Handle fun_decl; */
        /* } program; */
        struct
        {
            Type_Specifier type;
        } type_specifier;
        struct
        {
            AST_Node_Handle rest;
        } error;
    };
} AST_Node;

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

typedef struct
{
    AST_Node* nodes;
    i32 capacity;
    i32 count;
} AST_Store;

typedef struct
{
    Token current;
    Token previous;

    Token* token_stream;
    i32 current_token;

    AST_Store ast_store;

    bool had_error;
    bool panic_mode;

    AST_Node_Handle root;
} Parser;

typedef AST_Node_Handle (*Parse_Fn)(Parser*, AST_Node_Handle left_handle);
typedef struct
{
    Parse_Fn prefix;
    Parse_Fn infix;
    Precedence precedence;
} Parse_Rule;

static void error_at(Parser* parser, Token* token, const char* message)
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

void error(Parser* parser, const char* message)
{
    error_at(parser, &parser->previous, message);
}

void error_at_current(Parser* parser, const char* message)
{
    error_at(parser, &parser->current, message);
}

void advance_parser(Parser* parser)
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
    store->nodes = malloc(sizeof(AST_Node) * store->capacity);
    store->count = 0;
}

static void init_ast_store(AST_Store* store)
{
    init_ast_store_with_capacity(store, 32);
}

static AST_Node_Handle add_node(AST_Store* store, AST_Node_Type type)
{
    if(store->capacity <= store->count + 1)
    {
        store->capacity *= 2;
        store->nodes = realloc(store->nodes, store->capacity);
    }

    AST_Node* new_node = &store->nodes[store->count++];
    new_node->type = type;
    AST_Node_Handle handle = { .handle = store->count - 1 };
    return handle;
}

static AST_Node* get_node(AST_Store* store, AST_Node_Handle handle)
{
    assert(AST_HANDLE_VALID(handle));
    return &store->nodes[handle.handle];
}

void init_parser(Parser* parser, Token* tokens, i32 token_count)
{
    parser->current = tokens[0];
    parser->token_stream = tokens;
    parser->current_token = 0;
    parser->had_error = false;
    parser->panic_mode = false;

    init_ast_store(&parser->ast_store);
}

void free_parser(Parser* parser)
{
    parser->ast_store.count = 0;
    parser->token_stream = NULL;
    parser->had_error = false;
    parser->panic_mode = false;
}

static void consume(Parser* parser, Token_Type token_type, const char* message)
{
    if (parser->current.type == token_type)
    {
        advance_parser(parser);
        return;
    }

    error_at_current(parser, message);
}

static bool check(Parser* parser, Token_Type type)
{
    return parser->current.type == type;
}

static bool match(Parser* parser, Token_Type type)
{
    if (!check(parser, type)) return false;
    advance_parser(parser);
    return true;
}

static Parse_Rule* get_rule(Token_Type type);
static AST_Node_Handle parse_expression(Parser* parser);
static AST_Node_Handle parse_precedence(Parser* parser, Precedence precedence);

static AST_Node_Handle parse_precedence(Parser* parser, Precedence precedence)
{
    advance_parser(parser);
    Parse_Fn prefix_rule = get_rule(parser->previous.type)->prefix;
    if (prefix_rule == NULL)
    {
        error(parser, "Expect expression.");
        AST_Node_Handle error_node = add_node(&parser->ast_store, AST_NODE_ERROR);
        return error_node;
    }

    AST_Node_Handle left = prefix_rule(parser, INVALID_HANDLE);

    while (precedence <= get_rule(parser->current.type)->precedence)
    {
        advance_parser(parser);
        Parse_Fn infix_rule = get_rule(parser->previous.type)->infix;
        left = infix_rule(parser, left);
    }

    return left;
}

static AST_Node_Handle parse_number(Parser* parser, AST_Node_Handle _)
{
    i32 value = strtol(parser->previous.start, NULL, 10);
    AST_Node_Handle handle = add_node(&parser->ast_store, AST_NODE_NUMBER);
    AST_Node* number_node = get_node(&parser->ast_store, handle);
    number_node->number = value;

    return handle;
}

static AST_Node_Handle parse_expression(Parser* parser)
{
    /* AST_Node_Handle handle = add_node(&parser->ast_store, AST_NODE_EXPRESSION); */
    /* AST_Node* expression = get_node(&parser->ast_store, handle); */
    /* expression->expression.expression = parse_precedence(parser, PREC_ASSIGNMENT); */
    return parse_precedence(parser, PREC_ASSIGNMENT);
}

static AST_Node_Handle parse_binary(Parser* parser, AST_Node_Handle left)
{
    Token_Type operator_type = parser->previous.type;
    Parse_Rule* rule = get_rule(operator_type);

    AST_Node_Handle handle = add_node(&parser->ast_store, AST_NODE_BINARY);
    AST_Node* binary_expression = get_node(&parser->ast_store, handle);

    binary_expression->binary.left = left;
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
    return handle;
}

static AST_Node_Handle parse_unary(Parser* parser, AST_Node_Handle rest)
{
    Token_Type operator_type = parser->previous.type;
    AST_Node_Handle handle = add_node(&parser->ast_store, AST_NODE_UNARY);
    AST_Node* unary_expression = get_node(&parser->ast_store, handle);

    unary_expression->unary.expression = parse_precedence(parser, PREC_UNARY);

    switch (operator_type)
    {
    case TOKEN_MINUS:
    {
        unary_expression->unary.operator = TOKEN_MINUS;
    }
    break;
    case TOKEN_BANG:
    {
        unary_expression->unary.operator = TOKEN_BANG;
    }
    break;
    default:
    {
        unary_expression->unary.operator = TOKEN_ERROR;
    }
    break;
    }
    return handle;
}

static AST_Node_Handle parse_grouping(Parser* parser, AST_Node_Handle previous)
{
    AST_Node_Handle handle = parse_expression(parser);
    consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
    return handle;
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

static char* type_string(AST_Node_Type type)
{
    switch(type)
    {
    case AST_NODE_STATEMENT:
    return "AST_NODE_STATEMENT";
    /* case AST_NODE_EXPRESSION: */
    /* return "AST_NODE_EXPRESSION"; */
    case AST_NODE_PROGRAM:
    return "AST_NODE_PROGRAM";
    case AST_NODE_FUN_DECL:
    return "AST_NODE_FUN_DECL";
    case AST_NODE_NUMBER:
    return "AST_NODE_NUMBER";
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

static void indent(i32 indentation)
{
    for(i32 i = 0; i < indentation; i++)
    {
        printf("  ");
    }
}

static void pretty_print_unary(AST_Store* store, AST_Node* node, i32 indentation);
static void pretty_print_binary(AST_Store* store, AST_Node* binary, i32 indentation);
static void pretty_print_expression(AST_Store* store, AST_Node* node, i32 indentation);

static void pretty_print_unary(AST_Store* store, AST_Node* node, i32 indentation)
{
    indent(indentation);
    printf("(Unary\t\n ");
    indentation++;
    indent(indentation);
    printf(" (Op: ");
    switch (node->unary.operator)
    {
    case TOKEN_PLUS: printf("+"); break;
    case TOKEN_MINUS: printf("-"); break;
    case TOKEN_BANG: printf("*"); break;
    case TOKEN_ERROR: printf("ERROR"); break;
    default: assert(false);
    }
    printf(",\n ");
    pretty_print_expression(store, get_node(store, node->unary.expression), indentation);
    printf(")");
}

static void pretty_print_binary(AST_Store* store, AST_Node* binary, i32 indentation)
{
    indent(indentation);
    printf("(Binary\t\n ");
    indentation++;
    pretty_print_expression(store, get_node(store, binary->binary.left), indentation);
    printf(",\n");
    indent(indentation);
    printf(" (Op: ");
    switch (binary->binary.operator)
    {
    case TOKEN_PLUS: printf("+"); break;
    case TOKEN_MINUS: printf("-"); break;
    case TOKEN_STAR: printf("*"); break;
    case TOKEN_SLASH: printf("/"); break;
    case TOKEN_ERROR: printf("ERROR"); break;
    default: assert(false);
    }
    printf("),\n ");
    pretty_print_expression(store, get_node(store, binary->binary.right), indentation);
    printf(")");
}

static void pretty_print_number(AST_Store* store, AST_Node* number, i32 indentation)
{
    indent(indentation);
    printf("(Number: %d)", number->number);
}

static void pretty_print_expression(AST_Store* store, AST_Node* node, i32 indentation)
{
    switch(node->type)
    {
    case AST_NODE_UNARY:
    {
        pretty_print_unary(store, node, indentation);
    }
    break;
    case AST_NODE_BINARY:
    {
        pretty_print_binary(store, node, indentation);
    }
    break;
    case AST_NODE_NUMBER:
    {
        pretty_print_number(store, node, indentation);
    }
    break;
    default:
    {
        log_error("Unsupported node type %s\n", type_string(node->type));
        assert(false);
    }
    break;
    }
}

static void pretty_print_program(AST_Store* store, AST_Node* program_node, i32 indentation)
{
    printf("(Program\t\n ");
    indentation++;
    pretty_print_expression(store, get_node(store, program_node->program.expression), indentation);
    printf(")");
}

static void pretty_print_ast(AST_Store* store)
{
    assert(store->count > 0);
    AST_Node* root = &store->nodes[0];

    assert(root->type == AST_NODE_PROGRAM);
    pretty_print_program(store, root, 0);
    /* pretty_print_expression(store, get_node(store, root->program.expression), 0); */
    printf("\n");
}

bool parse(Parser* parser)
{
    advance_parser(parser);

    if (!match(parser, TOKEN_EOF))
    {
        parser->root = add_node(&parser->ast_store, AST_NODE_PROGRAM);
        AST_Node* root = get_node(&parser->ast_store, parser->root);
    
        root->program.expression = parse_expression(parser);
    }
    
    consume(parser, TOKEN_EOF, "Expect end of expression");

    if (!parser->had_error)
    {
        pretty_print_ast(&parser->ast_store);
    }

    return !parser->had_error;
}


#endif
