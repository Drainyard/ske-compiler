#ifndef LEX_H
#define LEX_H


typedef enum
{
    TOKEN_NUMBER,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,

    TOKEN_EOF,

    TOKEN_ERROR
} Token_Type;

typedef struct
{
    Token_Type type;
    char* start;
    i32 length;
} Token;

typedef struct
{
    char* start;
    char* current;
} Lexer;

static void init_lexer(Lexer* lexer, char* source)
{
    lexer->start = source;
    lexer->current = source;
}

static void log_token(Token token)
{
    char *token_type;
    switch(token.type)
    {
    case TOKEN_ADD:
    {
        token_type = "TOKEN_ADD";
    }
    break;
    case TOKEN_SUB:
    {
        token_type = "TOKEN_SUB";
    }
    break;
    case TOKEN_MUL:
    {
        token_type = "TOKEN_MUL";
    }
    break;
    case TOKEN_DIV:
    {
        token_type = "TOKEN_DIV";
    }
    break;
    case TOKEN_NUMBER:
    {
        token_type = "TOKEN_NUMBER";
    }
    break;
    case TOKEN_ERROR:
    {
        token_type = "TOKEN_ERROR";
    }
    }

    char token_value[32];
    strncpy(token_value, token.start, token.length);
    token_value[token.length] = '\0';
    
    log_info("[%s] \t| start: %c \t| length: %d \t| value: %s\n", token_type, *token.start, token.length, token_value);
}


static bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static bool is_at_end(Lexer* lexer)
{
    return *lexer->current == '\0';
}

static char advance(Lexer* lexer)
{
    lexer->current++;
    return lexer->current[-1];
}

static char peek(Lexer* lexer)
{
    return *lexer->current;
}

static char peek_next(Lexer* lexer)
{
    if (is_at_end(lexer)) return '\0';
    return lexer->current[1];
}

static bool match(Lexer* lexer, char expected)
{
    if (is_at_end(lexer)) return false;
    if (*lexer->current != expected) return false;

    lexer->current++;
    return true;
}

static Token make_token(Lexer* lexer, Token_Type type)
{
    Token token = {};
    token.type = type;
    token.start = lexer->current;
    token.length = (i32)(lexer->current - lexer->start);
    return token;
}

static Token error_token(Lexer* lexer, char* message)
{
    Token token = {};
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = strlen(message);
    return token;
}

static void skip_whitespace(Lexer* lexer)
{
    for (;;)
    {
        char c = peek(lexer);
        switch(c)
        {
        case ' ':
        case '\r':
        case '\t':
        {
            advance(lexer);
        }
        break;
        default:
        {
            return;
        }
        }
    }
}

static Token number(Lexer* lexer)
{
    while (is_digit(peek(lexer))) advance(lexer);

    if (peek(lexer) == '.' && is_digit(peek(lexer)))
    {
        advance(lexer);
        while (is_digit(peek(lexer))) advance(lexer);
    }

    return make_token(lexer, TOKEN_NUMBER);
}

static Token scan_token(Lexer* lexer)
{
    skip_whitespace(lexer);
    lexer->start = lexer->current;

    if (is_at_end(lexer)) return make_token(lexer, TOKEN_EOF);

    char c = advance(lexer);

    if (is_digit(c)) return number(lexer);

    switch(c)
    {
    case '+': return make_token(lexer, TOKEN_ADD);
    case '-': return make_token(lexer, TOKEN_SUB);
    case '*': return make_token(lexer, TOKEN_MUL);
    case '/': return make_token(lexer, TOKEN_DIV);
    }

    return error_token(lexer, "Unexpected token.");
}

Token* tokenize(char* input, size_t input_length, i32 *token_count)
{
    Token* tokens = malloc(sizeof(Token) * input_length); //@Note(niels): String length might be too long
    *token_count = 0;

    Lexer lexer = {};
    init_lexer(&lexer, input);

    Token token = scan_token(&lexer);

    while (token.type != TOKEN_EOF)
    {
        tokens[(*token_count)++] = token;
        token = scan_token(&lexer);
    }

    log_info("Tokens: %d\n", *token_count);

    for(int i = 0; i < *token_count; i++)
    {
        log_token(tokens[i]);
    }

    return tokens;
}


#endif
