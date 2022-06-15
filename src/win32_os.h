#ifndef WIN32_OS_H
#define WIN32_OS_H

String* create_temp_file(Allocator* allocator)
{
    return NULL;
}

void cleanup_temp_files()
{

}

bool run_subprocess(char** argv)
{
    (void)argv;
    /* CreateProcessW(NULL, argv); */
    return false;
}

bool absolute_path(String* str, String* out)
{
    return false;
}

#endif
