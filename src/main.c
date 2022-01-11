#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

typedef int32_t i32;
typedef int64_t i64;
typedef uint64_t u32;
typedef uint32_t u64;

#include "log.h"
#include "lex.h"
#include "runtime.h"

#define LINE_BUFFER_SIZE 256

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

static void parse_precedence(Parser* parser, Precedence precedence)
{
    
}

static AST_Node* parse_number(Parser* parser)
{
    i32 value = strtol(parser->previous.start, NULL, 10);
    // @Incomplete: Allocate an int constant here

    return NULL;
}

static void parse_expression(Parser* parser, AST_Node* ast)
{
    parse_precedence(parser, PREC_ASSIGNMENT);
}

static void parse_unary(Parser* parser, AST_Node* ast)
{
    Token_Type operator_type = parser->previous.type;

    parse_expression(parser, ast);

    switch (operator_type)
    {
    case TOKEN_SUB: break;// @Incomplete: Return AST_Node* negation
    default: return;
    }
}

static void parse_grouping(Parser* parser, AST_Node* ast)
{
    parse_expression(parser, ast);
    consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

bool parse(Token* tokens, i32 token_count, AST_Node* ast)
{
    Parser parser = {};
    init_parser(&parser, tokens, token_count);

    advance_parser(&parser);
    parse_expression(&parser, ast);
    consume(&parser, TOKEN_EOF, "Expect end of expression");

    return !parser.had_error;
}

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        repl();
    }
    else if(argc == 2)
    {
        // @Incomplete: Run file here
    }
    
    return 0;
}
