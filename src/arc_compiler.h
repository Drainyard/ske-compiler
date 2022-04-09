#ifndef ARC_COMPILER_H
#define ARC_COMPILER_H

#define FILE_EXTENSION ".ar"

String* DEFAULT_EXECUTABLE_OUT_PATH = NULL;

bool compiler_assemble_x86_with_output_path(String* x86_assembly, const char* output_path, Allocator* allocator)
{
    String_Builder sb;
    sb_init_with_allocator(&sb, 32 + x86_assembly->length, allocator);

    sb_appendf(&sb, "echo '%s' | as -o %s", x86_assembly->str, output_path);

    String* command = sb_get_result(&sb, allocator);

    return run_command(command, "Failed to run assembler\n");
}

bool compiler_assemble_x86_with_input_file(String* file_path, String* output_path, Allocator* allocator)
{
    char *cmd[] = {"as", "-c", file_path->str, "-o", output_path->str, NULL};
    return run_subprocess(cmd);
}

bool compiler_link(String* input_file_path, String* output_file_path, Allocator* allocator)
{
    char *cmd[] = {"gcc", "-o", output_file_path->str, input_file_path->str, "-lm", NULL};
    return run_subprocess(cmd); 
}

bool compile(String* source, String* assembly_out_path, String* executable_out_path, Allocator* allocator)
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
    if (parse(&parser, false, allocator))
    {
        log_info("Parsing succeeded\n\n");
        String* assembly = x86_codegen_ast(parser.root, allocator);
        String* assembly_out = assembly_out_path ? assembly_out_path : create_temp_file(allocator);
        if (assembly)
        {
            String* temp_path = create_temp_file(allocator);
            if (temp_path)
            {
                FILE* temp_file = fopen(temp_path->str, "w");
                if (!temp_file)
                {
                    log_error("Unable to open temp file: %s\n", temp_file);
                    exit(1);
                }

                string_write_to_file(assembly, temp_file);
                fclose(temp_file);
                
                result = compiler_assemble_x86_with_input_file(temp_path, assembly_out, allocator);

                if (!result)
                {
                    log_error("Assembler failed\n");
                    exit(1);
                }

                if (!DEFAULT_EXECUTABLE_OUT_PATH)
                {
                    DEFAULT_EXECUTABLE_OUT_PATH = string_allocate("a.out", allocator);
                }
                
                String* executable_out = executable_out_path ? executable_out_path : DEFAULT_EXECUTABLE_OUT_PATH;

                result = compiler_link(assembly_out, executable_out, allocator);

                if (!result)
                {
                    log_error("Linking failed\n");
                    exit(1);
                }
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

bool compile_file(String* path, String* assembly_out_path, String* executable_out_path, Allocator* allocator)
{
    FILE* file = fopen(path->str, "r");
    bool result = false;
    if (file)
    {
        String* source = string_create_from_file_with_allocator(file, allocator);
        result = compile(source, assembly_out_path, executable_out_path, allocator);
        fclose(file);
        /* cleanup_temp_files(); */
    }
    return result;
}

#endif
