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

#define LINE_BUFFER_SIZE 256

typedef struct
{
    Token* current;
    Token* previous;
} Parser;

void parse(Token* tokens, i32 token_count)
{
    Parser parser = {};
    parser.current = &tokens[0];
    parser.previous = NULL;

    
}

int main(int argc, char** argv)
{
    char line_buffer[LINE_BUFFER_SIZE];
    char* input = fgets(line_buffer, LINE_BUFFER_SIZE, stdin);
    size_t input_length = strlen(input);

    log_info("%s %d\n", input, input_length);
    i32 token_count = 0;
    Token* tokens = tokenize(input, input_length, &token_count);

    return 0;
}
