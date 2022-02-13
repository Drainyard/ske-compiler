#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef int32_t    i32;
typedef int64_t    i64;
typedef uint64_t   u32;
typedef uint32_t   u64;
typedef uintptr_t  umm;

#include "log.h"
#include "nb_memory.h"
#include "nb_string.h"
#include "nb_file.h"
#include "lex.h"
#include "parse.h"
#include "x86_codegen.h"
#include "compiler.h"
#include "runtime.h"

#define LINE_BUFFER_SIZE 256

bool is_source_file(String* string)
{
    return string_ends_with_cstr(string, FILE_EXTENSION);
}

int main(int argc, char** argv)
{
    Arena string_arena;
    size_t buffer_length = 1024 * 1024;
    void* arena_buffer = malloc(buffer_length);
    arena_init(&string_arena, arena_buffer, buffer_length);

    char* str = "file.ar_. . + 3..";
    String* test = string_create_from_arena(str, strlen(str), ALLOCATOR(&string_arena));
    String* substr1 = string_substring(test, 0, 4, ALLOCATOR(&string_arena));
    String* substr2 = string_substring(test, 2, 4, ALLOCATOR(&string_arena));
    String* substr3 = string_substring(test, 10, 2, ALLOCATOR(&string_arena));
    
    String* test2 = string_create("file.test.ar", ALLOCATOR(&string_arena));
    String* substr4 = string_substring(test2, 0, 13, ALLOCATOR(&string_arena));

    assert(string_equal_cstr(substr1, "file"));
    assert(string_equal_cstr(substr2, "le.a"));
    assert(string_equal_cstr(substr3, ". "));
    assert(string_equal_cstr(substr4, "file.test.ar"));
    string_print(substr1);
    printf("\n");
    string_print(substr2);
    printf("\n");
    string_print(substr3);
    printf("\n");
    string_print(substr4);
    printf("\n");

    String_Array* split = string_split(test2, '.', ALLOCATOR(&string_arena));
    assert(split->count == 3);

    
    /* if(argc == 1) */
    /* { */
    /*     repl(); */
    /* } */
    /* else if(argc > 1) */
    /* { */
    /*     String* file_path = NULL; */
    /*     for (i32 i = 1; i < argc; i++) */
    /*     { */
    /*         char* arg = argv[i]; */
    /*         String* string = string_create(arg); */

    /*         if (string->length >= 2) */
    /*         { */
    /*             if (string_equal_cstr(string, "--t") || string_equal_cstr(string, "-test")) */
    /*             { */
    /*                 printf("Running tests...\n"); */
    /*                 string_free(string); */
    /*             } */
    /*             else if (string_equal_cstr(string, "--h") || string_equal_cstr(string, "-help")) */
    /*             { */
    /*                 printf("Usage: arc [options] file...\n\n"); */
    /*                 printf("OPTIONS\n"); */

    /*                 printf("--h or -help            Display this information\n"); */
    /*                 string_free(string); */
    /*             } */
    /*             else if (is_source_file(string)) */
    /*             { */
    /*                 log_info("Source file: %s\n", string->str); */
    /*                 file_path = string; */
    /*             } */
    /*             else */
    /*             { */
    /*                 printf("Unknown argument '%s'. Try --h or -help to see available options.\n", arg); */
    /*                 string_free(string); */
    /*                 break; */
    /*             } */
    /*         } */
    /*     } */

    /*     if (file_path) */
    /*     { */
    /*         compile_file(file_path); */
    /*     } */
    /* } */
    
    return 0;
}
