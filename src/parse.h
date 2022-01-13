#ifndef PARSE_H
#define PARSE_H

typedef struct
{
    Token current;
    Token previous;

    Token* token_stream;
    i32 current_token;

    bool had_error;
    bool panic_mode;
} Parser;

typedef enum
{
    AST_NODE_STATEMENT,
    AST_NODE_EXPRESSION,
    AST_NODE_PROGRAM,
    AST_NODE_FUN_DECL,
    AST_NODE_CONSTANT,
    AST_NODE_BINARY,
    AST_NODE_TYPE_SPECIFIER
} AST_Node_Type;

typedef enum
{
    TYPE_SPEC_INT,
    TYPE_SPEC_VOID
} Type_Specifier;

typedef struct 
{
    AST_Node_Type type;

    union
    {
        i32 constant; // @Incomplete: Should be expanded to other constant types (float, string, etc.)
        struct
        {
            struct AST_Node* negation;
        } unary;
        struct
        {
            struct AST_Node* left;
            struct AST_Node* right;
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
    };
} AST_Node;

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

void init_parser(Parser* parser, Token* tokens, i32 token_count)
{
    parser->current = tokens[0];
    parser->token_stream = tokens;
    parser->current_token = 0;
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

typedef AST_Node* (*Parse_Fn)(Parser*);
typedef struct
{
    Parse_Fn prefix;
    Parse_Fn infix;
    Precedence precedence;
} Parse_Rule;

static Parse_Rule* get_rule(Token_Type type);
static AST_Node* parse_expression(Parser* parser);
static AST_Node* parse_precedence(Parser* parser, Precedence precedence);

static AST_Node* parse_precedence(Parser* parser, Precedence precedence)
{
    advance_parser(parser);
    Parse_Fn prefix_rule = get_rule(parser->previous.type)->prefix;
    if (prefix_rule == NULL)
    {
        error(parser, "Expect expression.");
        return NULL;
    }

    AST_Node* prefix_node = prefix_rule(parser);

    while (precedence <= get_rule(parser->current.type)->precedence)
    {
        advance_parser(parser);
        Parse_Fn infix_rule = get_rule(parser->previous.type)->infix;
        AST_Node* infix = infix_rule(parser);
    }

    return NULL;
}

static AST_Node* parse_number(Parser* parser)
{
    i32 value = strtol(parser->previous.start, NULL, 10);
    // @Incomplete: Allocate an int constant here

    return NULL;
}

static AST_Node* parse_expression(Parser* parser)
{
    parse_precedence(parser, PREC_ASSIGNMENT);
}

static AST_Node* parse_binary(Parser* parser)
{
    Token_Type operator_type = parser->previous.type;
    Parse_Rule* rule = get_rule(operator_type);
    parse_precedence(parser, rule->precedence + 1);

    switch (operator_type)
    {
    case TOKEN_PLUS: break;
    case TOKEN_MINUS: break;
    case TOKEN_STAR: break;
    case TOKEN_SLASH: break;
    default: return NULL;
    }
    return NULL;
}

static AST_Node* parse_unary(Parser* parser)
{
    Token_Type operator_type = parser->previous.type;

    parse_precedence(parser, PREC_UNARY);

    switch (operator_type)
    {
    case TOKEN_MINUS: break;// @Incomplete: Return AST_Node* negation
    default: return NULL;
    }
}

static AST_Node* parse_grouping(Parser* parser)
{
    AST_Node* node = parse_expression(parser);
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


bool parse(Token* tokens, i32 token_count)
{
    Parser parser = {};
    init_parser(&parser, tokens, token_count);

    advance_parser(&parser);
    AST_Node* program_node = parse_expression(&parser);
    consume(&parser, TOKEN_EOF, "Expect end of expression");

    return !parser.had_error;
}


#endif
