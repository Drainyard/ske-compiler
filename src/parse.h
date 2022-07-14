#ifndef SKE_PARSE_H
#define SKE_PARSE_H


typedef enum
{
    PREC_NONE,
    PREC_ASSIGNMENT,  // =
    PREC_OR,          // ||
    PREC_AND,         // &&
    PREC_BITWISE,     // | & ^
    PREC_EQUALITY,    // == !=
    PREC_COMPARISON,  // < > <= >=
    PREC_TERM,        // + -
    PREC_FACTOR,      // * /
    PREC_UNARY,       // ! -
    PREC_CALL,        // . ()
    PREC_PRIMARY
} Precedence;

typedef struct Parser Parser;
struct Parser
{
    Token current;
    Token previous;

    Token_List* token_stream;
    i32 current_token;

    String_View absolute_path;

    Allocator* allocator;

    bool had_error;
    bool panic_mode;

    AST_Node* root;
};

typedef AST_Node* (*Parse_Fn)(Parser*, AST_Node* left);
typedef struct
{
    Parse_Fn prefix;
    Parse_Fn infix;
    Precedence precedence;
} Parse_Rule;

static Parse_Rule* parser_get_rule(Token_Type type);
static AST_Node* parser_statement(Parser* parser);
static AST_Node* parser_expression(Parser* parser);
static AST_Node* parser_precedence(Parser* parser, Precedence precedence);
static AST_Node* parser_declaration(Parser* parser);
static AST_Node* parser_call(Parser* parser, AST_Node* previous);
static AST_Node* parser_grouping(Parser* parser, AST_Node* previous);
static AST_Node* parser_unary(Parser* parser, AST_Node* previous);
static AST_Node* parser_binary(Parser* parser, AST_Node* previous);
static AST_Node* parser_variable(Parser* parser, AST_Node* previous);
static AST_Node* parser_string(Parser* parser, AST_Node* previous);
static AST_Node* parser_number(Parser* parser, AST_Node* previous);


Parse_Rule rules[] = {
  [TOKEN_LEFT_PAREN]          = {parser_grouping, parser_call,   PREC_CALL},
  [TOKEN_RIGHT_PAREN]         = {NULL,            NULL,          PREC_NONE},
  [TOKEN_LEFT_BRACE]          = {NULL,            NULL,          PREC_NONE},
  [TOKEN_RIGHT_BRACE]         = {NULL,            NULL,          PREC_NONE},
  /* [TOKEN_COMMA]            = {NULL,            NULL,          PREC_NONE}, */
  /* [TOKEN_DOT]              = {NULL,            NULL,          PREC_NONE}, */
  [TOKEN_MINUS]               = {parser_unary,    parser_binary, PREC_TERM},
  [TOKEN_PLUS]                = {NULL,            parser_binary, PREC_TERM},
  [TOKEN_SEMICOLON]           = {NULL,            NULL,          PREC_NONE},
  [TOKEN_SLASH]               = {NULL,            parser_binary, PREC_FACTOR},
  [TOKEN_STAR]                = {NULL,            parser_binary, PREC_FACTOR},
  [TOKEN_BANG]                = {parser_unary,    NULL,          PREC_TERM},
  [TOKEN_BANG_EQUAL]          = {NULL,            parser_binary, PREC_COMPARISON},
  [TOKEN_EQUAL]               = {NULL,            parser_binary, PREC_COMPARISON},
  [TOKEN_EQUAL_EQUAL]         = {NULL,            parser_binary, PREC_EQUALITY},
  [TOKEN_GREATER]             = {NULL,            parser_binary, PREC_COMPARISON},
  [TOKEN_GREATER_EQUAL]       = {NULL,            parser_binary, PREC_COMPARISON},
  [TOKEN_LESS]                = {NULL,            parser_binary, PREC_COMPARISON},
  [TOKEN_LESS_EQUAL]          = {NULL,            parser_binary, PREC_COMPARISON},
  [TOKEN_IDENTIFIER]          = {parser_variable, NULL,          PREC_NONE},
  [TOKEN_STRING]              = {parser_string,   NULL,          PREC_NONE},
  [TOKEN_NUMBER]              = {parser_number,   NULL,          PREC_NONE},
  [TOKEN_ELSE]                = {NULL,            NULL,          PREC_NONE},
  [TOKEN_FALSE]               = {NULL,            NULL,          PREC_NONE},
  [TOKEN_FOR]                 = {NULL,            NULL,          PREC_NONE},
  [TOKEN_IF]                  = {NULL,            NULL,          PREC_NONE},
  [TOKEN_PIPE]                = {NULL,            parser_binary, PREC_BITWISE},
  [TOKEN_PIPE_PIPE]           = {NULL,            parser_binary, PREC_OR},
  [TOKEN_AMPERSAND]           = {NULL,            parser_binary, PREC_BITWISE},
  [TOKEN_AMPERSAND_AMPERSAND] = {NULL,            parser_binary, PREC_AND},
  [TOKEN_RETURN]              = {NULL,            NULL,          PREC_NONE},
  [TOKEN_TRUE]                = {NULL,            NULL,          PREC_NONE},
  [TOKEN_WHILE]               = {NULL,            NULL,          PREC_NONE},
  [TOKEN_ERROR]               = {NULL,            NULL,          PREC_NONE},
  [TOKEN_EOF]                 = {NULL,            NULL,          PREC_NONE},
};

#endif
