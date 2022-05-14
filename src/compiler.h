#ifndef SKE_COMPILER_H
#define SKE_COMPILER_H

#define FILE_EXTENSION ".ske"

String* DEFAULT_EXECUTABLE_OUT_PATH = NULL;

typedef enum
{
    OPT_NONE            = 0,
    OPT_ASSEMBLY_OUTPUT = 1 << 1,
} Compiler_Options;

bool has_flag(Compiler_Options options, int flag)
{
    return options & flag;
}

typedef struct Compiler_Arguments Compiler_Arguments;
struct Compiler_Arguments
{
    Compiler_Options options;
    String* input_file; // @Incomplete: Should be a string array, but for now it is just a single string
    String* out_path;
    String* absolute_path;
};

bool is_source_file(String* string)
{
    return string_ends_with_cstr(string, FILE_EXTENSION);
}

Compiler_Arguments parse_args(int argc, char** argv, Allocator* allocator)
{
    Compiler_Arguments arguments;
    arguments.options = OPT_NONE;
    arguments.input_file = NULL;
    arguments.out_path = NULL;
    char *realpath(const char *restrict path,
                      char *restrict resolved_path);


    for (i32 i = 1; i < argc; i++)
    {
        char* arg = argv[i];
        String string = string_create(arg);

        if (string.length >= 2)
        {
            if (string_equal_cstr(&string, "--t") || string_equal_cstr(&string, "-test"))
            {
                printf("Running tests...\n");

                /* String* command = string_create_from_arena("", 1 , ALLOCATOR(&string_arena)); */
            }
            else if (string_equal_cstr(&string, "--o") || string_equal_cstr(&string, "-outpath"))
            {
                if(argc < i + 1)
                {
                    printf("No output file path provided for '%s' argument. Please provide a valid argument\n", string.str);
                    break;
                }
                arguments.out_path = string_allocate(argv[i + 1], allocator);
                i++;
            }
            else if (string_equal_cstr(&string, "--S") || string_equal_cstr(&string, "-asm"))
            {
                arguments.options |= OPT_ASSEMBLY_OUTPUT;
            }
            else if (string_equal_cstr(&string, "--h") || string_equal_cstr(&string, "-help"))
            {
                printf("Usage: ske [options] file...\n\n");
                printf("Options\n");

                printf("  --h or -help            Display this information\n");
                printf("  --o <file>              Place the output into <file>\n");
                printf("  --S or -asm             Compile only; do not assemble or link.\n");
                printf("  --c                     Compile and assembly, but do not link\n");
            }
            else if (is_source_file(&string))
            {
                arguments.input_file = string_copy(&string, allocator);
                String local = string_create(realpath(string.str, NULL));
                arguments.absolute_path = string_copy(&local, allocator);
            }
            else
            {
                printf("Unknown argument '%s'. Try --h or -help to see available options.\n", arg);
                break;
            }
        }
    }

    return arguments;
}

bool compiler_assemble_x86_with_input_file(String* file_path, String* output_path, Allocator* allocator)
{
    char *cmd[] = {"as", "-c", file_path->str, "-o", output_path->str, NULL};
    return run_subprocess(cmd);
}

bool compiler_link(String* input_file_path, String* output_file_path, Allocator* allocator)
{
    char *cmd[] = {"gcc", "-o", output_file_path->str, input_file_path->str, "-lm", "-no-pie", NULL};
    return run_subprocess(cmd); 
}

bool compile(String* source, Compiler_Arguments arguments, Allocator* allocator)
{
    if(source->length == 0)
    {
        log_error("Empty input\n");
        return false;
    }
    
    Token_List* tokens = lexer_tokenize(source, arguments.input_file, arguments.absolute_path);
    Parser parser;
    parser_init(&parser, arguments.absolute_path, tokens, allocator);

    bool result = false;
    if (parse(&parser, false, allocator))
    {
        IR_Program program = ir_translate_ast(parser.root, allocator);

        /* printf("AST -> assembly: \n"); */
        String* assembly = x86_codegen_ast(parser.root, allocator);
        /* string_print(assembly); */
        /* printf("\n"); */
        /* printf("IR -> assembly: \n"); */
        String* __ir_assembly = x86_codegen_ir(&program, allocator);
        /* string_print(__ir_assembly); */
        /* printf("\n"); */
        if (assembly)
        {
            String* out_path = NULL;
            if (has_flag(arguments.options, OPT_ASSEMBLY_OUTPUT))
            {
                out_path = arguments.out_path ? arguments.out_path : string_allocate("out.s", allocator);
            }
            else
            {
                out_path = create_temp_file(allocator);
            }
                
            if (out_path)
            {
                FILE* temp_file = fopen(out_path->str, "w");
                if (!temp_file)
                {
                    fprintf(stderr, "Unable to open temp file: %s\n", out_path->str);
                    exit(1);
                }

                string_write_to_file(assembly, temp_file);
                fclose(temp_file);

                if (has_flag(arguments.options, OPT_ASSEMBLY_OUTPUT))
                {
                    return true;
                }

                String* assembly_out = create_temp_file(allocator);
                result = compiler_assemble_x86_with_input_file(out_path, assembly_out, allocator);

                if (!result)
                {
                    fprintf(stderr, "Assembler failed\n");
                    exit(1);
                }

                if (!DEFAULT_EXECUTABLE_OUT_PATH)
                {
                    DEFAULT_EXECUTABLE_OUT_PATH = string_allocate("a.out", allocator);
                }
                
                String* executable_out = arguments.out_path ? arguments.out_path : DEFAULT_EXECUTABLE_OUT_PATH;

                result = compiler_link(assembly_out, executable_out, allocator);

                if (!result)
                {
                    fprintf(stderr, "Linking failed\n");
                    exit(1);
                }
            }
        }
    }
    else
    {
        exit(1);
    }
    
    parser_free(&parser);
    token_list_free(tokens);

    return result;
}

bool compile_file(Compiler_Arguments arguments, Allocator* allocator)
{
    if (!arguments.input_file)
    {
        return false;
    }
    
    FILE* file = fopen(arguments.input_file->str, "r");
    bool result = false;
    if (file)
    {
        String* source = string_create_from_file_with_allocator(file, allocator);
        result = compile(source, arguments, allocator);
        fclose(file);
        /* cleanup_temp_files(); */
    }
    return result;
}

#endif
