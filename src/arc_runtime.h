#ifndef ARC_RUNTIME_H
#define ARC_RUNTIME_H

void repl(Allocator* allocator)
{
    String* buffer = string_allocate(1024, allocator);
    for(;;)
    {
        printf("> ");

        if(!fgets(buffer->str, 1024, stdin))
        {
            printf("\n");
            break;
        }

        bool result = compile(buffer, NULL, NULL, allocator);
        if (!result)
        {
            log_error("Compilation failed with errors\n");
        }
    }
}
    



#endif
