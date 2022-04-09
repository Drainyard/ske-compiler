#ifndef ARC_RUNTIME_H
#define ARC_RUNTIME_H

void repl(Allocator* allocator)
{
    char str[1024];
    String buffer = string_create(str);
    for(;;)
    {
        printf("> ");

        if(!fgets(buffer.str, 1024, stdin))
        {
            printf("\n");
            break;
        }

        bool result = compile(&buffer, NULL, NULL, allocator);
        if (!result)
        {
            log_error("Compilation failed with errors\n");
        }
    }
}
    



#endif
