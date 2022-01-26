#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef int32_t i32;
typedef int64_t i64;
typedef uint64_t u32;
typedef uint32_t u64;

#include "compiler_string.h"
#include "log.h"
#include "lex.h"
#include "parse.h"
#include "runtime.h"

#define LINE_BUFFER_SIZE 256


int main(int argc, char** argv)
{
    String_Builder builder =
        {
            .string = NULL,
            .current_index = 0
        };

    append(&builder, "Hello");

    printf("%s\n", builder.string->str);
    append(&builder, ", ");
    printf("%s\n", builder.string->str);
    append(&builder, "World");
    printf("%s\n", builder.string->str);
    append(&builder, "!");
    printf("%s\n", builder.string->str);
    append(&builder, "\n");

    String* result = builder.string;
    
    printf("%d %s\n", result->length, result->str);
    
    if(argc == 1)
    {
        /* repl(); */
    }
    else if(argc == 2)
    {
        // @Incomplete: Run file here
    }
    
    return 0;
}
