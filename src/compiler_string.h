#ifndef COMPILER_STRING_H
#define COMPILER_STRING_H

typedef struct
{
    i32 length;
    unsigned char str[1];
} String;

typedef struct
{
    String* string;
    i32 current_index;
} String_Builder;

static String* allocate_string(i32 input_string_length)
{
    String* new_string = malloc(sizeof(i32) * input_string_length + 1);
    new_string->length = input_string_length;
    return new_string;
}

static String* expand_string(String* string, i32 new_size)
{
    assert(new_size > string->length);
    string->length = new_size;
    String* new_string = allocate_string(new_size);
    for (i32 i = 0; i < new_size; i++)
    {
    }
    return realloc(string, new_size);
}

static void free_string(String* string)
{
    free(string);
}

static String* create_string(const char* input_string)
{
    i32 length = strlen(input_string);
    String* string = allocate_string(length);
    string->length = length;
    for (i32 i = 0; i < length; i++)
    {
        string->str[i] = input_string[i];
    }
    string->str[length] = '\0';
    return string;
}

static void append(String_Builder* builder, const char* app)
{
    i32 len = strlen(app);
    if(len == 0)
    {
        return;
    }
    
    if (!builder->string)
    {
        builder->string = create_string(app);
        builder->current_index = len;
    }
    else if (builder->current_index + len > builder->string->length)
    {
        i32 new_length = builder->string->length * 2;
        expand_string(builder->string, new_length);
    }

    i32 c = 0;
    for (i32 i = builder->current_index; i < builder->current_index + len; i++)
    {
        builder->string->str[i] = app[c++];
    }
    builder->current_index = len;
    builder->string->str[builder->current_index] = '\0';
}

#endif
