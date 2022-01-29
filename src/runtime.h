#ifndef RUNTIME_H
#define RUNTIME_H

bool compile(String* source)
{
    Token_List* tokens = lexer_tokenize(source);
    Parser parser;
    parser_init(&parser, tokens);

    bool result = false;
    if (parse(&parser))
    {
        log_info("Parsing succeeded\n");
        x86_codegen_ast(&parser.ast_store, parser.root);
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

void repl()
{
    String* buffer = string_allocate(1024);
    for(;;)
    {
        printf("> ");

        if(!fgets(buffer->str, buffer->length, stdin))
        {
            printf("\n");
            break;
        }

        bool result = compile(buffer);
        if (!result)
        {
            log_error("Compilation failed with errors\n");
        }
    }
}

bool compile_file(const char* path)
{
    FILE* file = fopen(path, "r");
    bool result = false;
    if (file)
    {
        String* source = string_create_from_file(file);
        result = compile(source);
        fclose(file);
    }
    return result;
}
    



#endif
