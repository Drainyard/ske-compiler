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

void expression(Parser* parser)
{
}

void consume(Parser* parser, Token_Type token_type, const char* message)
{
    if (parser->current.type == token_type)
    {
        advance_parser(parser);
        return;
    }

    error_at_current(parser, message);
}

bool parse(Token* tokens, i32 token_count)
{
    Parser parser = {};
    init_parser(&parser, tokens, token_count);

    advance_parser(&parser);
    expression(&parser);
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
