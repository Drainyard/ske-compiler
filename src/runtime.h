#ifndef RUNTIME_H
#define RUNTIME_H

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

        bool result = compile(buffer, NULL);
        if (!result)
        {
            log_error("Compilation failed with errors\n");
        }
    }
}
    



#endif
