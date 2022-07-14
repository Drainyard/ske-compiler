#ifndef SKE_COMPILER_H
#define SKE_COMPILER_H

#define FILE_EXTENSION ".ske"

String* DEFAULT_EXECUTABLE_OUT_PATH = NULL;

typedef enum
{
    OPT_NONE            = 0,
    OPT_ASSEMBLY_OUTPUT = 1 << 1,
    OPT_IR_OUTPUT       = 1 << 2,
    OPT_TOK_OUTPUT      = 1 << 3,
    OPT_AST_OUTPUT      = 1 << 4
} Compiler_Options;

typedef struct Compiler_Arguments Compiler_Arguments;
struct Compiler_Arguments
{
    Compiler_Options options;
    String* input_file; // @Incomplete: Should be a string array, but for now it is just a single string
    String* out_path; // Out path for the chosen output 
    String* absolute_path;
};

#endif
