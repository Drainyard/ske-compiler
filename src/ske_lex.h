#ifndef ARC_LEX_H
#define ARC_LEX_H


typedef enum
{
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,

    TOKEN_BANG,

    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,

    TOKEN_EOF,

    TOKEN_ERROR
} Token_Type;

typedef struct
{
    Token_Type type;
    char* start;
    i32 length;
    i32 line;
    i32 position;
} Token;

typedef struct
{
    char* start;
    char* current;

    i32 line;
    i32 position_on_line;

    String_View file_name;
    String_View absolute_path;
} Lexer;

static void lexer_init(Lexer* lexer, String* source, String_View file_name, String_View absolute_path)
{
    lexer->start = source->str;
    lexer->current = source->str;
    lexer->line = 1;
    lexer->file_name = file_name;
    lexer->absolute_path = absolute_path;
}

static void token_log(Token token)
{
    char *token_type;
    switch(token.type)
    {
    case TOKEN_PLUS:
    {
        token_type = "TOKEN_ADD";
    }
    break;
    case TOKEN_MINUS:
    {
        token_type = "TOKEN_SUB";
    }
    break;
    case TOKEN_STAR:
    {
        token_type = "TOKEN_MUL";
    }
    break;
    case TOKEN_SLASH:
    {
        token_type = "TOKEN_DIV";
    }
    break;
    case TOKEN_NUMBER:
    {
        token_type = "TOKEN_NUMBER";
    }
    break;
    case TOKEN_LEFT_PAREN:
    {
        token_type = "TOKEN_LEFT_PAREN";
    }
    break;
    case TOKEN_RIGHT_PAREN:
    {
        token_type = "TOKEN_RIGHT_PAREN";
    }
    break;
    case TOKEN_BANG:
    {
        token_type = "TOKEN_BANG";
    }
    break;
    case TOKEN_ERROR:
    {
        token_type = "TOKEN_ERROR";
    }
    case TOKEN_EOF:
    {
        token_type = "TOKEN_EOF";
    }
    break;
    }

    (void)token_type;

    char token_value[32];
    strncpy(token_value, token.start, token.length);
    token_value[token.length] = '\0';
    
    /* log_info("[%s] \t| start: %c \t| length: %d \t| value: %s\n", token_type, *token.start, token.length, token_value); */
}

static bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static bool lexer_is_at_end(Lexer* lexer)
{
    return *lexer->current == '\0';
}

static char lexer_advance(Lexer* lexer)
{
    lexer->current++;
    return lexer->current[-1];
}

static char lexer_peek_char(Lexer* lexer)
{
    return *lexer->current;
}

static char lexer_peek_next_char(Lexer* lexer)
{
    if (lexer_is_at_end(lexer)) return '\0';
    return lexer->current[1];
}

static bool lexer_match_character(Lexer* lexer, char expected)
{
    if (lexer_is_at_end(lexer)) return false;
    if (*lexer->current != expected) return false;

    lexer->current++;
    return true;
}

static Token lexer_make_token(Lexer* lexer, Token_Type type)
{
    i32 length = (i32)(lexer->current - lexer->start);
    Token token =
        {
            .type     = type,
            .start    = lexer->start,
            .line     = lexer->line,
            .length   = length,
            .position = lexer->position_on_line
        };
    lexer->position_on_line += length;
    return token;
}

static void lexer_verror_at(Lexer* lexer, char* location, char* fmt, va_list ap)
{
    fprintf(stderr, "\x1b[1;37m");
    i32 length = fprintf(stderr, sv_null_terminated_string(lexer->absolute_path));
    length += fprintf(stderr, ":%d:%d:\x1b[31m error: ", lexer->line, lexer->position_on_line);
    length++;
    
    fprintf(stderr, "\x1b[0m");

    fprintf(stderr, "\x1b[1;37m");
    fprintf(stderr, "'%s' ", lexer->start);
    fprintf(stderr, "\x1b[0m");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");

    /* fprintf(stderr, "%*s", length, ""); */
    /* fprintf(stderr, "%*s^ ", length, ""); */
}


static void lexer_error_at(Lexer* lexer, char* location, char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    lexer_verror_at(lexer, location, fmt, ap);
}

static void lexer_error_tok(Lexer* lexer, Token* token, char* fmt, ...)
{
    va_list(ap);
    va_start(ap, fmt);
    lexer_verror_at(lexer, token->start, fmt, ap);
}

static Token lexer_error_token(Lexer* lexer, char* message)
{
    Token token =
        {
            .type     = TOKEN_ERROR,
            .start    = lexer->current,
            .length   = strlen(message),
            .line     = lexer->line,
            .position = lexer->position_on_line
        };

    lexer_error_tok(lexer, &token, message);
    
    return token;
}

static void lexer_skip_whitespace(Lexer* lexer)
{
    for (;;)
    {
        char c = lexer_peek_char(lexer);
        switch(c)
        {
        case ' ':
        case '\r':
        case '\t':
        {
            lexer_advance(lexer);
        }
        break;
        case '\n':
        {
            lexer_advance(lexer);
            lexer->line++;
            lexer->position_on_line = 0;
        }
        break;
        default:
        {
            return;
        }
        }
    }
}

static Token lexer_number(Lexer* lexer)
{
    while (is_digit(lexer_peek_char(lexer))) lexer_advance(lexer);

    if (lexer_peek_char(lexer) == '.' && is_digit(lexer_peek_char(lexer)))
    {
        lexer_advance(lexer);
        while (is_digit(lexer_peek_char(lexer))) lexer_advance(lexer);
    }

    return lexer_make_token(lexer, TOKEN_NUMBER);
}

static Token lexer_scan_token(Lexer* lexer)
{
    lexer_skip_whitespace(lexer);
    lexer->start = lexer->current;

    if (lexer_is_at_end(lexer)) return lexer_make_token(lexer, TOKEN_EOF);

    char c = lexer_advance(lexer);

    if (is_digit(c)) return lexer_number(lexer);

    switch(c)
    {
    case '+': return lexer_make_token(lexer, TOKEN_PLUS);
    case '-': return lexer_make_token(lexer, TOKEN_MINUS);
    case '*': return lexer_make_token(lexer, TOKEN_STAR);
    case '/': return lexer_make_token(lexer, TOKEN_SLASH);
    case '(': return lexer_make_token(lexer, TOKEN_LEFT_PAREN);
    case ')': return lexer_make_token(lexer, TOKEN_RIGHT_PAREN);
    }

    return lexer_error_token(lexer, "unexpected token");
}

typedef struct
{
    Token* tokens;
    i32 capacity;
    i32 count;
} Token_List;

typedef struct
{
    Token* tokens;
    i32 current;
    i32 count;
} Token_Stream;

void token_list_init(Token_List* list, i32 initial_capacity)
{
    list->capacity = initial_capacity;
    list->tokens = malloc(sizeof(Token) * initial_capacity);
    list->count = 0;
}

void token_list_free(Token_List* list)
{
    free(list->tokens);
    free(list);
}

void token_list_maybe_expand(Token_List* list)
{
    if (list->count + 1 >= list->count)
    {
        list->capacity *= 2;
        list->tokens = realloc(list->tokens, list->capacity);
    }
}

void token_list_add(Token_List* list, Token token)
{
    token_list_maybe_expand(list);
    list->tokens[list->count++] = token;
}

Token_List* lexer_tokenize(String* input, String* file_name, String* absolute_path)
{
    Token_List* list = malloc(sizeof(Token_List));
    token_list_init(list, 128);
    
    Lexer lexer;
    lexer_init(&lexer, input, sv_create(file_name), sv_create(absolute_path));

    Token token = lexer_scan_token(&lexer);

    while (token.type != TOKEN_EOF)
    {
        token_list_add(list, token);
        token = lexer_scan_token(&lexer);
    }

    token_list_add(list, token);

    return list;
}


#endif
