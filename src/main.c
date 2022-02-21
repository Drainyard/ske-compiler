#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>

typedef int16_t    i16;
typedef int32_t    i32;
typedef int64_t    i64;
typedef uint64_t   u32;
typedef uint32_t   u64;
typedef uintptr_t  umm;

#include "log.h"
#include "nb_memory.h"
#include "nb_string.h"
#include "nb_file.h"
#include "arc_lex.h"
#include "arc_parse.h"
#include "arc_ir.h"
#include "arc_x86_codegen.h"
#include "arc_compiler.h"
#include "arc_runtime.h"

#define LINE_BUFFER_SIZE 256

bool is_source_file(String* string)
{
    return string_ends_with_cstr(string, FILE_EXTENSION);
}

int main(int argc, char** argv)
{
    Arena base_allocator;
    size_t buffer_length = 1024 * 1024;
    void* base_buffer = malloc(buffer_length);
    arena_init(&base_allocator, base_buffer, buffer_length);

    Arena string_arena;
    size_t string_buffer_length = 1024 * 1024;
    void* string_buffer = malloc(string_buffer_length);
    arena_init(&string_arena, string_buffer, string_buffer_length);
    
    if(argc == 1)
    {
        repl(ALLOCATOR(&base_allocator));
    }
    else if(argc > 1)
    {
        String* file_path = NULL;
        for (i32 i = 1; i < argc; i++)
        {
            char* arg = argv[i];
            String* string = string_create(arg, ALLOCATOR(&string_arena));

            if (string->length >= 2)
            {
                if (string_equal_cstr(string, "--t") || string_equal_cstr(string, "-test"))
                {
                    printf("Running tests...\n");
                }
                else if (string_equal_cstr(string, "--h") || string_equal_cstr(string, "-help"))
                {
                    printf("Usage: arc [options] file...\n\n");
                    printf("OPTIONS\n");

                    printf("--h or -help            Display this information\n");
                }
                else if (is_source_file(string))
                {
                    log_info("Source file: %s\n", string->str);
                    file_path = string;
                }
                else
                {
                    printf("Unknown argument '%s'. Try --h or -help to see available options.\n", arg);
                    break;
                }
            }
        }

        if (file_path)
        {
            compile_file(file_path, ALLOCATOR(&string_arena));
        }
    }
    
    return 0;
}
