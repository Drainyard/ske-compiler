#ifndef ARC_COMPILER_H
#define ARC_COMPILER_H

#define FILE_EXTENSION ".ar"

bool compile(String* source, String* out_path, Allocator* allocator)
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
        x86_codegen_ast(parser.root, out_path, allocator);
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
        String* source = string_create_from_file_with_arena(file, allocator);
        String_Array* array = string_split(path, '.', allocator);
        assert(array->count > 0);
        result = compile(source, string_concat_cstr(array->strings[0], ".s", allocator), allocator);
        fclose(file);
    }
    return result;
}

#endif
