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

#include "log.h"
#include "compiler_string.h"
#include "lex.h"
#include "parse.h"
#include "x86_codegen.h"
#include "runtime.h"

#define LINE_BUFFER_SIZE 256


int main(int argc, char** argv)
{
    if(argc == 1)
    {
        repl();
    }
    else if(argc > 1)
    {
        for (i32 i = 1; i < argc; i++)
        {
            char* arg = argv[i];
            String* string = string_create(arg);

            if (string->length >= 2)
            {
                if (string_equal_cstr(string, "--t") || string_equal_cstr(string, "-test"))
                {
                    printf("Running tests...\n");
                }
                else if (string_equal_cstr(string, "--h") || string_equal_cstr(string, "-help"))
                {
                    
                }
                else
                {
                    printf("Unknown argument '%s'. Try --h or -help to see available options.\n", arg);
                    break;
                }
            }
        }

        
        
        // @Incomplete: Run file here
    }
    
    return 0;
}
