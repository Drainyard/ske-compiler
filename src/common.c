void generic_error(const char* format, ...)
{
    fprintf(stderr, "\x1b[1;31m");
    fprintf(stderr, "Generic error: ");
    va_list arglist;
    va_start(arglist, format);
    vfprintf(stderr, format, arglist);
    va_end(arglist);
    fprintf(stderr, "\x1b[0m\n");

    assert(false);
}

void compiler_bug(const char* format, ...)
{
    fprintf(stderr, "\x1b[1;31m");
    fprintf(stderr, "Compiler bug: ");
    va_list arglist;
    va_start(arglist, format);
    vfprintf(stderr, format, arglist);
    va_end(arglist);
    fprintf(stderr, "\x1b[0m\n");

    assert(false);
}

void not_implemented(const char* format, ...)
{
    fprintf(stderr, "\x1b[1;31m");
    fprintf(stderr, "Not implemented: ");
    va_list arglist;
    va_start(arglist, format);
    vfprintf(stderr, format, arglist);
    va_end(arglist);
    fprintf(stderr, "\x1b[0m\n");

    assert(false);
}

