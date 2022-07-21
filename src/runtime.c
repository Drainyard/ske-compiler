
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

        bool result = Compiler_compile(&buffer, args, allocator);
        if (!result)
        {
            // TODO: Output errors?
            compiler_bug("Compilation failed with errors\n");
        }
    }
}
