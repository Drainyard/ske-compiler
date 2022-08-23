void output_error(Source_Location location, const char* type, const char* format, va_list arglist)
{
    fprintf(stderr, "\x1b[1;31m");
    fprintf(stderr, "%s error in file %s - line %d: ", type, location.file_name, location.line_number);
    vfprintf(stderr, format, arglist);
    fprintf(stderr, "\x1b[0m\n");

    exit(1);
}

void generic_error(Source_Location location, const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    output_error(location, "Generic", format, arglist);

    exit(1);
}

void compiler_bug(Source_Location location, const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    output_error(location, "Compiler bug", format, arglist);

    exit(1);
}

void not_implemented(Source_Location location, const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    output_error(location, "Not implemented", format, arglist);
        
    exit(1);
}

Source_Location make_location(const char* file, i32 line)
{
    return (Source_Location)
        {
            .file_name   = file,
            .line_number = line
        };
}

