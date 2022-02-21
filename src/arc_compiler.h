#ifndef ARC_COMPILER_H
#define ARC_COMPILER_H

#define FILE_EXTENSION ".ar"

#define READ_END 0
#define WRITE_END 1


FILE* compiler_assemble_x86(String* x86_assembly, Allocator* allocator)
{
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();

    char first_command[] = "echo";
    char* first_argument = x86_assembly->str;
    printf("%s\n", x86_assembly->str);
    char second_command[] = "as";
    char second_argument[] = "-o a.out";

    if(pid==0)
    {
        dup2(fd[WRITE_END], STDOUT_FILENO);
        close(fd[READ_END]);
        close(fd[WRITE_END]);
        execlp(first_command, first_command, first_argument, (char*) NULL);
        fprintf(stderr, "Failed to execute '%s'\n", first_command);
        exit(1);
    }
    else
    { 
        pid=fork();

        if(pid==0)
        {
            dup2(fd[READ_END], STDIN_FILENO);
            close(fd[WRITE_END]);
            close(fd[READ_END]);
            execlp(second_command, second_command, second_argument,(char*) NULL);
            fprintf(stderr, "Failed to execute '%s'\n", second_command);
            exit(1);
        }
        else
        {
            int status;
            close(fd[READ_END]);
            close(fd[WRITE_END]);
            waitpid(pid, &status, 0);
        }
    }
    
    /* if(output) */
    /* { */
    /*     String* result = string_create_from_file_with_allocator(output, allocator); */
    /*     if (!result) */
    /*     { */
    /*         log_error("Unable to assemble file\n"); */
    /*         pclose(output); */
    /*         return NULL; */
    /*     } */
    /*     string_print(result); */
    /*     pclose(output); */
    /* } */
    /* return output; */
    return NULL;
}

bool compiler_link()
{
    return false;
}

bool compile(String* source, Allocator* allocator)
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
        String* assembly = x86_codegen_ast(parser.root, allocator);

        if (assembly)
        {
            FILE* object_file = compiler_assemble_x86(assembly, allocator);
            
        }
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
        String* source = string_create_from_file_with_allocator(file, allocator);
        result = compile(source, allocator);
        fclose(file);
    }
    return result;
}

#endif
