#ifndef SKE_LEX_H
#define SKE_LEX_H


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
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,

    TOKEN_EQUAL,

    TOKEN_IF, TOKEN_ELSE, TOKEN_WHILE,
    TOKEN_RETURN, TOKEN_LET, TOKEN_MUT,

    TOKEN_FALSE, TOKEN_TRUE, TOKEN_FOR,

    TOKEN_FN,
    
    TOKEN_IDENTIFIER,

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
    lexer->position_on_line = 0;
}

static bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
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

#ifdef __GNUC__
__attribute__((unused))
#endif
static char lexer_peek_next_char(Lexer* lexer)
{
    if (lexer_is_at_end(lexer)) return '\0';
    return lexer->current[1];
}

#ifdef __GNUC__
__attribute__((unused))
#endif
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

static Token_Type lexer_check_keyword(Lexer* lexer, i32 start, i32 length, const char* rest, Token_Type type) {
  if (lexer->current - lexer->start == start + length &&
      memcmp(lexer->start + start, rest, length) == 0) {
    return type;
  }

  return TOKEN_IDENTIFIER;
}

static Token_Type lexer_identifier_type(Lexer* lexer)
{
    switch (lexer->start[0]) {
    case 'i': return lexer_check_keyword(lexer, 1, 1, "f", TOKEN_IF);
    case 'e': return lexer_check_keyword(lexer, 1, 3, "lse", TOKEN_ELSE);
    case 'r': return lexer_check_keyword(lexer, 1, 5, "eturn", TOKEN_RETURN);
    case 'l': return lexer_check_keyword(lexer, 1, 2, "et", TOKEN_LET);
    case 'm': return lexer_check_keyword(lexer, 1, 2, "ut", TOKEN_MUT);
    case 'w': return lexer_check_keyword(lexer, 1, 4, "hile", TOKEN_WHILE);
    case 't': return lexer_check_keyword(lexer, 1, 3, "rue", TOKEN_TRUE);
    case 'f':
    {
        if (lexer->current - lexer->start > 1)
        {
            switch (lexer->start[1])
            {
            case 'n': return TOKEN_FN;
            case 'a': return lexer_check_keyword(lexer, 2, 3, "lse", TOKEN_FALSE);
            case 'o': return lexer_check_keyword(lexer, 2, 1, "or", TOKEN_FOR);
            }
        }
    }

    }
    return TOKEN_IDENTIFIER;
}

static Token lexer_identifier(Lexer* lexer)
{
    while (is_alpha(lexer_peek_char(lexer)) || is_digit(lexer_peek_char(lexer))) lexer_advance(lexer);

    return lexer_make_token(lexer, lexer_identifier_type(lexer));
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

    if (is_alpha(c)) return lexer_identifier(lexer);
    if (is_digit(c)) return lexer_number(lexer);

    switch(c)
    {
    case '+': return lexer_make_token(lexer, TOKEN_PLUS);
    case '-': return lexer_make_token(lexer, TOKEN_MINUS);
    case '*': return lexer_make_token(lexer, TOKEN_STAR);
    case '/': return lexer_make_token(lexer, TOKEN_SLASH);
    case '=': return lexer_make_token(lexer, TOKEN_EQUAL);
    case '(': return lexer_make_token(lexer, TOKEN_LEFT_PAREN);
    case ')': return lexer_make_token(lexer, TOKEN_RIGHT_PAREN);
    case '{': return lexer_make_token(lexer, TOKEN_LEFT_BRACE);
    case '}': return lexer_make_token(lexer, TOKEN_RIGHT_BRACE);
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

String* lexer_pretty_print(Token_List* list, Allocator* allocator)
{
    String_Builder sb;
    sb_init(&sb, 256);

    for (i32 i = 0; i < list->count; i++)
    {
        Token token = list->tokens[i];

        switch (token.type)
        {
        case TOKEN_NUMBER:
        {
            i32 value = strtol(token.start, NULL, 10);
            sb_appendf(&sb, "NUMBER('%d')\n", value);
        }
        break;
        case TOKEN_PLUS:
        {
            sb_append(&sb, "PLUS('+')\n");
        }
        break;
        case TOKEN_MINUS:
        {
            sb_append(&sb, "MINUS('-')\n");
        }
        break;
        case TOKEN_STAR:
        {
            sb_append(&sb, "STAR('*')\n");
        }
        break;
        case TOKEN_SLASH:
        {
            sb_append(&sb, "SLASH('/')\n");
        }
        break;
        case TOKEN_BANG:
        {
            sb_append(&sb, "BANG('!')\n");
        }
        break;
        case TOKEN_LEFT_PAREN:
        {
            sb_append(&sb, "LPAREN('(')\n");
        }
        break;
        case TOKEN_RIGHT_PAREN:
        {
            sb_append(&sb, "RPAREN(')')\n");
        }
        break;
        case TOKEN_LEFT_BRACE:
        {
            sb_append(&sb, "LBRACE('{')\n");
        }
        break;
        case TOKEN_RIGHT_BRACE:
        {
            sb_append(&sb, "RBRACE('}')\n");
        }
        break;
        case TOKEN_EQUAL:
        {
            sb_append(&sb, "EQUAL('=')\n");
        }
        break;
        case TOKEN_IF:
        {
            sb_append(&sb, "IF('if')\n");
        }
        break;
        case TOKEN_ELSE:
        {
            sb_append(&sb, "ELSE('else')\n");
        }
        break;
        case TOKEN_WHILE:
        {
            sb_append(&sb, "WHILE('while')\n");
        }
        break;
        case TOKEN_RETURN:
        {
            sb_append(&sb, "RETURN('return')\n");
        }
        break;
        case TOKEN_LET:
        {
            sb_append(&sb, "LET('let')\n");
        }
        break;
        case TOKEN_MUT:
        {
            sb_append(&sb, "MUT('mut')\n");
        }
        break;
        case TOKEN_FALSE:
        {
            sb_append(&sb, "FALSE('false')\n");
        }
        break;
        case TOKEN_TRUE:
        {
            sb_append(&sb, "TRUE('true')\n");
        }
        break;
        case TOKEN_FOR:
        {
            sb_append(&sb, "FOR('for')\n");
        }
        break;
        case TOKEN_FN:
        {
            sb_append(&sb, "FN('fn')\n");
        }
        break;
        case TOKEN_IDENTIFIER:
        {
            sb_appendf(&sb, "IDENT('%.*s')\n", token.length, token.start);
        }
        break;
        case TOKEN_EOF:
        {
            sb_append(&sb, "EOF\n");
        }
        break;
        case TOKEN_ERROR: break;
        }
    }
    
    return sb_get_result(&sb, allocator);
}


#endif
