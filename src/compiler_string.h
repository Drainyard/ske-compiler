#ifndef COMPILER_STRING_H
#define COMPILER_STRING_H

typedef struct
{
    i32 length;
    char str[1];
} String;

typedef struct
{
    char* string;
    i32 current_index;
    i32 capacity;
} String_Builder;

String* string_allocate(i32 input_string_length)
{
    String* new_string = malloc(sizeof(i32) * input_string_length + 1);
    new_string->length = input_string_length;
    return new_string;
}

void string_free(String* string)
{
    free(string);
}

String* string_create_with_length(const char* input_string, i32 length)
{
    String* string = string_allocate(length);
    string->length = length;
    for (i32 i = 0; i < length; i++)
    {
        string->str[i] = input_string[i];
    }
    string->str[length] = '\0';
    return string;
}

String* string_create(const char* input_string)
{
    i32 length = strlen(input_string);
    return string_create_with_length(input_string, length);
}

String* string_createf(const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    i32 format_length = vsnprintf(NULL, 0, format, arglist);
    if (format_length == 0)
    {
        va_end(arglist);
        return NULL;
    }

    String* result = string_allocate(format_length);
    va_start(arglist, format);
    vsnprintf(result->str, format_length + 1, format, arglist);
    result->str[format_length] = '\0';

    return result;
}

bool string_equal_cstr(String* lhs, const char* rhs)
{
    i32 len = strlen(rhs);
    if(len != lhs->length) return false;

    for (i32 i = 0; i < lhs->length; i++)
    {
        if (lhs->str[i] != rhs[i]) return false;
    }
    return true;
}

void string_print(String* string)
{
    printf("%s", string->str);
}

void string_fprintf(String* string, FILE* file)
{
    fprintf(file, "%s", string->str);
}

void sb_init(String_Builder* builder, i32 initial_capacity)
{
    builder->capacity = initial_capacity;
    builder->string = calloc(builder->capacity, 1);
    builder->current_index = 0;
}

static unsigned int next_power_of_two(i32 n)
{
    i32 power = 1;
    if (n && !(n & (n - 1)))
    {
        return n;
    }
 
    while (power < n)
    {
        power <<= 1;
    }
     
    return power;
}

#define LOAD_FACTOR 2
static void sb_maybe_expand(String_Builder* builder, i32 extra_length)
{
    if (!builder->string)
    {
        sb_init(builder, next_power_of_two(extra_length));
    }
 
    if(builder->current_index + extra_length >= builder->capacity)
    {
        i32 old_capacity = builder->capacity;
        builder->capacity *= LOAD_FACTOR;
        builder->string = realloc(builder->string, builder->capacity);
        for (i32 i = old_capacity; i < builder->capacity; i++)
        {
            builder->string[i] = '\0';
        }
    }
}

void sb_append(String_Builder* builder, const char* str)
{
    i32 len = strlen(str);
    if(len == 0)
    {
        return;
    }
    
    sb_maybe_expand(builder, len);

    i32 c = 0;
    for (i32 i = builder->current_index; i < builder->current_index + len; i++)
    {
        builder->string[i] = str[c++];
    }
    builder->current_index += len;
}

void sb_appendf(String_Builder* builder, const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    i32 format_length = vsnprintf(NULL, 0, format, arglist);
    if (format_length == 0)
    {
        va_end(arglist);
        return;
    }
    
    sb_maybe_expand(builder, format_length);
    
    va_start(arglist, format);
    vsnprintf(&builder->string[builder->current_index], format_length + 1, format, arglist);
    va_end(arglist);

    builder->current_index += format_length;
}

String* sb_get_result(String_Builder* builder)
{
    if (!builder->string || builder->current_index == 0)
    {
        log_error("Trying to create the empty string.");
        return NULL;
    }

    return string_create_with_length(builder->string, builder->current_index);
}

void sb_free(String_Builder* builder)
{
    free(builder->string);
}

static void sb_indent(String_Builder* builder, i32 indentation)
{
    for(i32 i = 0; i < indentation; i++)
    {
        sb_append(builder, "  ");
    }
}

#endif
