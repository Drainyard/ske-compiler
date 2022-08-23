#ifndef COMMON_H
#define COMMON_H

typedef struct Source_Location Source_Location;
struct Source_Location
{
    const char* file_name;
    i32 line_number;

    // @Incomplete: Add column?
};

void generic_error(Source_Location location, const char* format, ...);
#define GENERIC_ERR(format, ...) (generic_error(MAKE_LOCATION(), format, ##__VA_ARGS__))
void compiler_bug(Source_Location location, const char* format, ...);
#define COMPILER_BUG(format, ...) (compiler_bug(MAKE_LOCATION(), format, ##__VA_ARGS__))
void not_implemented(Source_Location location, const char* format, ...);
#define NOT_IMPLEMENTED(format, ...) (not_implemented(MAKE_LOCATION(), format, ##__VA_ARGS__))

Source_Location make_location(const char* file, i32 line);
#define MAKE_LOCATION() (make_location(__FILE__, __LINE__))

void output_error(Source_Location location, const char* type, const char* format, va_list arglist);

#endif
