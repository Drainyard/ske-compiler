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
#elif _WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRA_LEAN
#include "windows.h"
#endif

typedef int16_t    i16;
typedef int32_t    i32;
typedef int64_t    i64;
typedef uint8_t    u8;
typedef uint16_t   u16;
typedef uint32_t   u32;
typedef uint64_t   u64;
typedef uintptr_t  umm;

#include "log.h"
#include "nb_memory.h"
#include "nb_string.h"
#include "nb_file.h"
//#include "nb_shell.h"
#include "os.h"

#ifdef __linux__
#include "linux_os.h"
#elif _WIN32
#include "win32_os.h"
#endif

static void compiler_bug(const char* message)
{
    fprintf(stderr, "\x1b[1;31m");
    fprintf(stderr, "Compiler bug: %s\n", message);
    fprintf(stderr, "\x1b[0m\n");

    assert(false);
}

#include "lex.h"
#include "ast.h"
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
