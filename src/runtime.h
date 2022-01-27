#ifndef RUNTIME_H
#define RUNTIME_H

void repl()
{
    char line_buffer[1024];
    for(;;)
    {
        printf("> ");

        if(!fgets(line_buffer, sizeof(line_buffer), stdin))
        {
            printf("\n");
            break;
        }
        i32 token_count;
        Token* tokens = tokenize(line_buffer, sizeof(line_buffer), &token_count);
        Parser parser;
        init_parser(&parser, tokens, token_count);
        if(parse(&parser))
        {
            log_info("Parsing succeeded\n");

            x86_codegen_ast(&parser.ast_store, parser.root);
        }
        else
        {
            log_error("Parsing failed with errors\n");
        }
        free_parser(&parser);
        free(tokens);
    }
}



#endif
