#ifndef COMPILER_H
#define COMPILER_H

#define FILE_EXTENSION ".ar"

bool compile(String* source, String* out_path)
{
    if(source->length == 0)
    {
        log_error("Empty input\n");
        return false;
    }
    
    Token_List* tokens = lexer_tokenize(source);
    Parser parser;
    parser_init(&parser, tokens);

    bool result = false;
    if (parse(&parser))
    {
        log_info("Parsing succeeded\n\n");
        x86_codegen_ast(&parser.ast_store, parser.root, out_path);
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

bool compile_file(String* path)
{
    FILE* file = fopen(path->str, "r");
    bool result = false;
    if (file)
    {
        String* source = string_create_from_file(file);
        String_Array* array = string_split(path, '.');
        assert(array->count > 0);
        result = compile(source, string_concat_cstr(array->strings[0], ".s"));
        fclose(file);
    }
    return result;
}

#endif