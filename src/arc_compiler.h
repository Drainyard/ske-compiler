#ifndef ARC_COMPILER_H
#define ARC_COMPILER_H

#define FILE_EXTENSION ".ar"

#define READ_END 0
#define WRITE_END 1

char DEFAULT_ASSEMBLY_OUT_FILE[] = "__out.o"; // TODO: Should be passed in as arguments as well
char DEFAULT_EXECUTABLE_OUT_FILE[] = "a.out"; // TODO: Should be passed in as arguments as well

bool run_command(String* command, const char* error_message)
{
    FILE* fp;
    fp = popen(command->str, "r");
    if (!fp)
    {
        log_error(error_message);
        return false;
    }

    char path[1048];
    while (fgets(path, sizeof(path), fp) != NULL)
    {
        log_info("%s", path);
    }
    pclose(fp);

    return true;
}

bool compiler_assemble_x86_with_output_path(String* x86_assembly, const char* output_path, Allocator* allocator)
{
    String_Builder sb;
    sb_init_with_allocator(&sb, 32 + x86_assembly->length, allocator);

    sb_appendf(&sb, "echo '%s' | as -o %s", x86_assembly->str, output_path);

    String* command = sb_get_result(&sb, allocator);

    return run_command(command, "Failed to run assembler\n");
}


bool compiler_assemble_x86(String* x86_assembly, Allocator* allocator)
{
    return compiler_assemble_x86_with_output_path(x86_assembly, DEFAULT_ASSEMBLY_OUT_FILE, allocator);
}

bool compiler_link_with_output_file(const char* input_file_path, const char* output_file_path, Allocator* allocator)
{
    String_Builder sb;
    sb_init_with_allocator(&sb, 1024, allocator);

    sb_appendf(&sb, "gcc -o %s %s -lm && rm -rf %s", output_file_path, input_file_path, input_file_path);

    String* command = sb_get_result(&sb, allocator);
    return run_command(command, "Linking failed\n");
}

bool compiler_link(const char* input_file_path, Allocator* allocator)
{
    return compiler_link_with_output_file(input_file_path, DEFAULT_EXECUTABLE_OUT_FILE, allocator);
}

bool compile(String* source, Allocator* allocator)
{
    if(source->length == 0)
    {
        log_error("Empty input\n");
        return false;
    }
    
    Token_List* tokens = lexer_tokenize(source);
    Parser parser;
    parser_init(&parser, tokens, allocator);

    bool result = false;
    if (parse(&parser, allocator))
    {
        log_info("Parsing succeeded\n\n");
        String* assembly = x86_codegen_ast(parser.root, allocator);

        if (assembly)
        {
            result = compiler_assemble_x86_with_output_path(assembly, DEFAULT_ASSEMBLY_OUT_FILE, allocator);

            if (!result)
            {
                log_error("Assembler failed\n");
                exit(1);
            }

            result = compiler_link_with_output_file(DEFAULT_ASSEMBLY_OUT_FILE, DEFAULT_EXECUTABLE_OUT_FILE, allocator);

            if (!result)
            {
                log_error("Linking failed\n");
                exit(1);
            }
        }
    }
    else
    {
        log_error("Parsing failed with errors\n");        
    }
    
    parser_free(&parser);
    token_list_free(tokens);

    return result;
}

bool compile_file(String* path, Allocator* allocator)
{
    FILE* file = fopen(path->str, "r");
    bool result = false;
    if (file)
    {
        String* source = string_create_from_file_with_allocator(file, allocator);
        result = compile(source, allocator);
        fclose(file);
    }
    return result;
}

#endif
