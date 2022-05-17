#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#else #ifdef _WIN32

#endif

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
#include "nb_shell.h"
#include "lex.h"
#include "parse.h"
#include "ir.h"
#include "codegen_x86.h"
#include "compiler.h"
#include "runtime.h"

#define LINE_BUFFER_SIZE 256

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
        Compiler_Arguments arguments = parse_args(argc, argv, ALLOCATOR(&string_arena));

        if (arguments.input_file)
        {
            compile_file(arguments, ALLOCATOR(&string_arena));
        }
    }

    return 0;
}
