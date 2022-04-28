#ifndef NB_STRING_H
#define NB_STRING_H

typedef struct String String;
struct String
{
    int length;
    char* str;    
};

typedef struct String_View String_View;
struct String_View
{
    String* string;
};

String_View sv_create(String* string)
{
    String_View view =
    {
        .string = string
    };
    return view;
}

int sv_len(String_View view)
{
    return view.string->length;
}

char* sv_null_terminated_string(String_View view)
{
    return view.string->str;
}

String string_create(char* nt_str)
{
    String string =
    {
        .length = strlen(nt_str),
        .str = nt_str
    };
    return string;
}

void string_set(String* string, char* value)
{
    size_t length = strlen(value);
    for(int i = 0; i < length; i++)
    {
        string->str[i] = value[i];
    }
    string->str[length] = '\0';
}

#define STRING_SIZE(length) (sizeof(String) + length + 1)

String* string_allocate_empty(size_t size, Allocator* allocator)
{
    String* string = (String*)allocator->allocate(allocator, STRING_SIZE(size));
    string->length = size;
    string->str = (char*)((umm)string) + sizeof(String);
    return string;
}

String* string_allocate(char* nt_str, Allocator* allocator)
{
    size_t size = strlen(nt_str);
    String* string = string_allocate_empty(size, allocator);
    string_set(string, nt_str);
    return string;
}

String* string_copy(String* input, Allocator* allocator)
{
    String* string = string_allocate_empty(input->length, allocator);
    string_set(string, input->str);
    return string;
}

typedef struct
{
    char* string;
    i32 current_index;
    i32 capacity;
} String_Builder;

String* string_create_from_file_with_allocator(FILE* file, Allocator* allocator)
{
    fseek(file, 0, SEEK_END);
    i32 file_size = ftell(file);
    if(file_size <= 0)
    {
        return NULL;
    }
    
    fseek(file, 0, SEEK_SET);

    String* new_string = string_allocate_empty(file_size, allocator);
    fread(new_string->str, file_size, 1, file);
    new_string->str[file_size] = '\0';

    return new_string;
}

void string_print(String* string);

void string_write_to_file(String* string, FILE* file)
{
    fwrite(string->str, string->length, 1, file);
}

String* string_createf(Allocator* allocator, const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    i32 format_length = vsnprintf(NULL, 0, format, arglist);
    if (format_length == 0)
    {
        va_end(arglist);
        return NULL;
    }

    String* result = string_allocate_empty(format_length, allocator);
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

bool string_ends_with_cstr(String* lhs, const char* rhs)
{
    i32 len = strlen(rhs);
    if (len > lhs->length) return false;

    i32 start = lhs->length - len;
    for (i32 i = 0; i < len; i++)
    {
        if (lhs->str[start + i] != rhs[i]) return false;
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

String* string_substring(String* string, i32 start, i32 length, Allocator* allocator)
{
    if (start < 0) start = 0;
    if (length <= 0) return NULL;
    if (length > string->length) length = string->length;
    if (length + start > string->length)
    {
        length = string->length - start;
    }

    String* substr = string_allocate_empty(length, allocator);
    i32 index = start;
    for (i32 i = 0; i < length; i++)
    {
        substr->str[i] = string->str[index++];
    }
    substr->str[substr->length] = '\0';
    return substr;
}

String* string_concat_str(String* lhs, String* rhs, Allocator* allocator)
{
    if (lhs->length == 0) return string_allocate(rhs->str, allocator);
    if (rhs->length == 0) return string_allocate(lhs->str, allocator);

    String* new_string = string_allocate_empty(lhs->length + rhs->length, allocator);

    for (i32 i = 0; i < lhs->length; i++)
    {
        new_string->str[i] = lhs->str[i];
    }

    i32 index = 0;
    for (i32 i = lhs->length; i < lhs->length + rhs->length; i++)
    {
        new_string->str[i] = rhs->str[index++];
    }

    return new_string;
}

String* string_concat_cstr(String* lhs, char* rhs, Allocator* allocator)
{
    i32 rhs_len = strlen(rhs);
    if(lhs->length == 0) return string_allocate(rhs, allocator);
    if(rhs_len == 0) return string_allocate(lhs->str, allocator);
    String* new_string = string_allocate_empty(lhs->length + rhs_len, allocator);

    for (i32 i = 0; i < lhs->length; i++)
    {
        new_string->str[i] = lhs->str[i];
    }

    i32 index = 0;
    for (i32 i = lhs->length; i < lhs->length + rhs_len; i++)
    {
        new_string->str[i] = rhs[index++];
    }

    return new_string;
}

typedef struct
{
    String** strings;
    i32 count;
    i32 capacity;
} String_Array;

String_Array* string_array_allocate(i32 capacity, Allocator* allocator)
{
    String_Array* array = allocator->allocate(allocator, sizeof(String_Array));
    array->strings = allocator->allocate(allocator, sizeof(String*) * capacity);
    array->capacity = capacity;
    array->count = 0;
    return array;
}

void string_array_push(String_Array* array, String* string)
{
    if(array->count + 1 >= array->capacity)
    {
        log_error("String array out of space: %d/%d\n", array->count, array->capacity);
        assert(false);
    }

    array->strings[array->count++] = string;
}

String_Array* string_split(String* string, char delim, Allocator* allocator)
{
    i32 count = 1;
    for (i32 i = 0; i < string->length; i++)
    {
        if(string->str[i] == delim)
        {
            count++;
        }
    }
    
    String_Array* array = string_array_allocate(count, allocator);
    array->count = count;
    i32 current_index = 0;
    for (i32 i = 0; i < array->count; i++)
    {
        i32 start = current_index;
        for (; current_index < string->length; current_index++)
        {
            if (string->str[current_index] == delim) break;
        }
        array->strings[i] = string_substring(string, start, current_index, allocator);
    }
    return array;
}

void sb_init(String_Builder* builder, i32 initial_capacity)
{
    builder->capacity = initial_capacity;
    builder->string = calloc(builder->capacity, 1);
    builder->current_index = 0;
}

void sb_init_with_allocator(String_Builder* builder, i32 initial_capacity, Allocator* allocator)
{
    builder->capacity = initial_capacity;
    builder->string = allocator->allocate(allocator, builder->capacity);
    for (i32 i = 0; i < initial_capacity; i++)
    {
        builder->string[i] = 0;
    }
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

String* sb_get_result(String_Builder* builder, Allocator* allocator)
{
    if (!builder->string || builder->current_index == 0)
    {
        log_error("Trying to create the empty string.");
        return NULL;
    }

    String* result = string_allocate_empty(builder->current_index, allocator);
    string_set(result, builder->string);
    return result;
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
