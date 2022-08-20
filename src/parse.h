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

typedef AST_Node* (*Parse_Fn)(Parser*, AST_Node* left, AST_Node* parent);
typedef struct
{
    Parse_Fn prefix;
    Parse_Fn infix;
    Precedence precedence;
} Parse_Rule;

static Parse_Rule* Parser_get_rule(Token_Type type);
static AST_Node* Parser_statement(Parser* parser, AST_Node* parent);
static AST_Node* Parser_expression(Parser* parser, AST_Node* parent);
static AST_Node* Parser_precedence(Parser* parser, Precedence precedence, AST_Node* parent);
static AST_Node* Parser_declaration(Parser* parser, AST_Node* parent);
static AST_Node* Parser_call(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_grouping(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_unary(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_binary(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_variable(Parser* parser, AST_Node* previous, AST_Node* parent, const char* error_message);
static AST_Node* Parser_named_variable(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_string(Parser* parser, AST_Node* previous, AST_Node* parent);
static AST_Node* Parser_number(Parser* parser, AST_Node* previous, AST_Node* parent);


Parse_Rule rules[] = {
  [TOKEN_LEFT_PAREN]          = {Parser_grouping,       Parser_call,   PREC_CALL},
  [TOKEN_RIGHT_PAREN]         = {NULL,                  NULL,          PREC_NONE},
  [TOKEN_LEFT_BRACE]          = {NULL,                  NULL,          PREC_NONE},
  [TOKEN_RIGHT_BRACE]         = {NULL,                  NULL,          PREC_NONE},
  /* [TOKEN_COMMA]            = {NULL,                  NULL,          PREC_NONE}, */
  /* [TOKEN_DOT]              = {NULL,                  NULL,          PREC_NONE}, */
  [TOKEN_MINUS]               = {Parser_unary,          Parser_binary, PREC_TERM},
  [TOKEN_PLUS]                = {NULL,                  Parser_binary, PREC_TERM},
  [TOKEN_SEMICOLON]           = {NULL,                  NULL,          PREC_NONE},
  [TOKEN_SLASH]               = {NULL,                  Parser_binary, PREC_FACTOR},
  [TOKEN_STAR]                = {NULL,                  Parser_binary, PREC_FACTOR},
  [TOKEN_BANG]                = {Parser_unary,          NULL,          PREC_TERM},
  [TOKEN_BANG_EQUAL]          = {NULL,                  Parser_binary, PREC_COMPARISON},
  [TOKEN_EQUAL]               = {NULL,                  Parser_binary, PREC_COMPARISON},
  [TOKEN_EQUAL_EQUAL]         = {NULL,                  Parser_binary, PREC_EQUALITY},
  [TOKEN_GREATER]             = {NULL,                  Parser_binary, PREC_COMPARISON},
  [TOKEN_GREATER_EQUAL]       = {NULL,                  Parser_binary, PREC_COMPARISON},
  [TOKEN_LESS]                = {NULL,                  Parser_binary, PREC_COMPARISON},
  [TOKEN_LESS_EQUAL]          = {NULL,                  Parser_binary, PREC_COMPARISON},
  [TOKEN_IDENTIFIER]          = {Parser_named_variable, NULL,          PREC_NONE},
  [TOKEN_STRING]              = {Parser_string,         NULL,          PREC_NONE},
  [TOKEN_NUMBER]              = {Parser_number,         NULL,          PREC_NONE},
  [TOKEN_ELSE]                = {NULL,                  NULL,          PREC_NONE},
  [TOKEN_FALSE]               = {NULL,                  NULL,          PREC_NONE},
  [TOKEN_FOR]                 = {NULL,                  NULL,          PREC_NONE},
  [TOKEN_IF]                  = {NULL,                  NULL,          PREC_NONE},
  [TOKEN_PIPE]                = {NULL,                  Parser_binary, PREC_BITWISE},
  [TOKEN_PIPE_PIPE]           = {NULL,                  Parser_binary, PREC_OR},
  [TOKEN_AMPERSAND]           = {NULL,                  Parser_binary, PREC_BITWISE},
  [TOKEN_AMPERSAND_AMPERSAND] = {NULL,                  Parser_binary, PREC_AND},
  [TOKEN_RETURN]              = {NULL,                  NULL,          PREC_NONE},
  [TOKEN_TRUE]                = {NULL,                  NULL,          PREC_NONE},
  [TOKEN_WHILE]               = {NULL,                  NULL,          PREC_NONE},
  [TOKEN_ERROR]               = {NULL,                  NULL,          PREC_NONE},
  [TOKEN_EOF]                 = {NULL,                  NULL,          PREC_NONE},
};

#endif
