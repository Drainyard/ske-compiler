#ifndef LOG_H
#define LOG_H

#define BLACK_FOREGROUND "\033[30m"
#define BLACK_BACKGROUND "\033[40m"

#define RED_FOREGROUND "\033[31m"
#define RED_BACKGROUND "\033[41m"

#define GREEN_FOREGROUND "\033[32m"
#define GREEN_BACKGROUND "\033[42m"

#define DISTRO_DEFAULT_FOREGROUND "\033[39m"
#define DISTRO_DEFAULT_BACKGROUND "\033[49m"

static void log_info(char* format, ...)
{
    fprintf(stderr, GREEN_FOREGROUND);
    fprintf(stderr, "[info]: ");
    fprintf(stderr, DISTRO_DEFAULT_FOREGROUND);
    va_list arglist;
    va_start(arglist, format);
    vfprintf(stderr, format, arglist);
    va_end(arglist);
}

static void log_error(char* format, ...)
{
    fprintf(stderr, RED_FOREGROUND);
    fprintf(stderr, "[error]: ");
    fprintf(stderr, DISTRO_DEFAULT_FOREGROUND);
    va_list arglist;
    va_start(arglist, format);
    vfprintf(stderr, format, arglist);
    va_end(arglist);
}

#endif
