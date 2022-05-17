#ifndef NB_SHELL
#define NB_SHELL

String_Array* temp_files;
#define MAX_TEMP_FILES 32

String* create_temp_file(Allocator* allocator)
{
    if (!temp_files)
    {
        temp_files = string_array_allocate(MAX_TEMP_FILES, allocator);
    }

    String* path = string_allocate("/tmp/ske-XXXXXX", allocator);
    i32 fd = mkstemp(path->str);
    if (fd == 1)
    {
        log_error("mkstemp failed: %s\n", strerror(errno));
    }
    close(fd);
    string_array_push(temp_files, path);
    return path;
}

void cleanup_temp_files()
{
    if (temp_files)
    {
        for (i32 i = 0; i < temp_files->count; i++)
        {
            unlink(temp_files->strings[i]->str);
        }
        temp_files->count = 0;
    }
}

#ifdef __linux__
bool run_subprocess(char** argv)
{
    if (fork() == 0)
    {
        execvp(argv[0], argv);
        log_error("exec failed: %s: %s\n", argv[0], strerror(errno));
        exit(1);
    }

    i32 status;
    while (wait(&status) > 0);
    if (status != 0)
    {
        exit(1);
    }
    return true;
}
#elif _WIN32
bool run_subprocess(char** argv)
{
    CreateProcess(NULL, argv);
    return true;
}
#endif

#endif
