#ifndef ARC_COMPILER_H
#define ARC_COMPILER_H

#define FILE_EXTENSION ".ar"

#define READ_END 0
#define WRITE_END 1
char DEFAULT_ASSEMBLY_OUT_FILE[] = "__out.o"; // TODO: Should be passed in as arguments as well
char DEFAULT_EXECUTABLE_OUT_FILE[] = "a.out"; // TODO: Should be passed in as arguments as well

FILE* compiler_assemble_x86(String* x86_assembly, Allocator* allocator)
{
    char* first_command = "./assemble.sh ";
    
    String_Builder sb;
    sb_init_with_allocator(&sb, 32 + x86_assembly->length, allocator);
    sb_append(&sb, first_command);
    sb_appendf(&sb, "'%s'", x86_assembly->str);

    sb_append(&sb, " ");
    sb_append(&sb, DEFAULT_ASSEMBLY_OUT_FILE);

    String* final_command = sb_get_result(&sb, allocator);

    FILE* fp;
    fp = popen(final_command->str, "r");
    if (!fp)
    {
        log_error("Failed to run assembler\n");
        return NULL;
    }

    char path[1035];
    while (fgets(path, sizeof(path), fp) != NULL)
    {
        log_info("%s", path);
    }
    pclose(fp);
    
    /* system(final_command->str); */
    
    /* if(output) */
    /* { */
    /*     String* result = string_create_from_file_with_allocator(output, allocator); */
    /*     if (!result) */
    /*     { */
    /*         log_error("Unable to assemble file\n"); */
    /*         pclose(output); */
    /*         return NULL; */
    /*     } */
    /*     string_print(result); */
    /*     pclose(output); */
    /* } */
    /* return output; */
    return NULL;
}

bool compiler_link()
{
    return false;
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
            FILE* object_file = compiler_assemble_x86(assembly, allocator);
        }
        result = true;
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
