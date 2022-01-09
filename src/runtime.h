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
        free(tokens);
    }
}



#endif
