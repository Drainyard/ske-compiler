#ifndef SKE_RUNTIME_H
#define SKE_RUNTIME_H

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

        Compiler_Arguments args =
            {
                .options    = OPT_NONE,
                .input_file = NULL,
                .out_path   = NULL
            };

        bool result = compile(&buffer, args, allocator);
        if (!result)
        {
            log_error("Compilation failed with errors\n");
        }
    }
}
    



#endif
