void Lex_init(Lexer* lexer, String* source, String_View file_name, String_View absolute_path)
{
    lexer->start = source->str;
    lexer->current = source->str;
    lexer->line = 1;
    lexer->file_name = file_name;
    lexer->absolute_path = absolute_path;
    lexer->position_on_line = 0;
}

char* token_type_to_string(Token_Type token)
{
    switch(token)
    {
    case TOKEN_NUMBER:              return "number";
    case TOKEN_PLUS:                return "+";
    case TOKEN_MINUS:               return "-";
    case TOKEN_STAR:                return "*";
    case TOKEN_SLASH:               return "/";
    case TOKEN_SEMICOLON:           return ";";
    case TOKEN_COMMA:               return ",";
    case TOKEN_ARROW:               return "->";
    case TOKEN_BANG:                return "!";
    case TOKEN_BANG_EQUAL:          return "!=";
    case TOKEN_LESS:                return "<";
    case TOKEN_GREATER:             return ">";
    case TOKEN_LESS_EQUAL:          return "<=";
    case TOKEN_GREATER_EQUAL:       return ">=";
    case TOKEN_PIPE:                return "|";
    case TOKEN_PIPE_PIPE:           return "||";
    case TOKEN_AMPERSAND:           return "&";
    case TOKEN_AMPERSAND_AMPERSAND: return "&&";
    case TOKEN_LEFT_PAREN:          return "(";
    case TOKEN_RIGHT_PAREN:         return ")";
    case TOKEN_LEFT_BRACE:          return "{";
    case TOKEN_RIGHT_BRACE:         return "}";
    case TOKEN_COLON:               return ":";
    case TOKEN_COLON_COLON:         return "::";
    case TOKEN_COLON_EQUAL:         return ":=";
    case TOKEN_EQUAL:               return "=";
    case TOKEN_EQUAL_EQUAL:         return "==";
    case TOKEN_IF:                  return "if";
    case TOKEN_ELSE:                return "else";
    case TOKEN_WHILE:               return "while";
    case TOKEN_RETURN:              return "return";
    case TOKEN_FALSE:               return "false";
    case TOKEN_TRUE:                return "true";
    case TOKEN_FOR:                 return "for";
    case TOKEN_IDENTIFIER:          return "identifier";
    case TOKEN_STRING:              return "string";
    case TOKEN_EOF:                 return "eof";
    case TOKEN_ERROR:               return "error";
    }
    return NULL;
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

static bool Lex_is_at_end(Lexer* lexer)
{
    return *lexer->current == '\0';
}

static char Lex_advance(Lexer* lexer)
{
    lexer->current++;
    return lexer->current[-1];
}

static char Lex_peek_char(Lexer* lexer)
{
    return *lexer->current;
}

#ifdef __GNUC__
__attribute__((unused))
#endif
static char Lex_peek_next_char(Lexer* lexer)
{
    if (Lex_is_at_end(lexer)) return '\0';
    return lexer->current[1];
}

#ifdef __GNUC__
__attribute__((unused))
#endif
static bool Lex_match_character(Lexer* lexer, char expected)
{
    if (Lex_is_at_end(lexer)) return false;
    if (*lexer->current != expected) return false;

    lexer->current++;
    return true;
}

static Token Lex_make_token(Lexer* lexer, Token_Type type)
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

static void Lex_verror_at(Lexer* lexer, char* location, char* fmt, va_list ap)
{
    (void)location;
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

static void Lex_error_tokenf(Lexer* lexer, Token* token, char* fmt, ...)
{
    va_list(ap);
    va_start(ap, fmt);
    Lex_verror_at(lexer, token->start, fmt, ap);

    va_end(ap);
}

static Token Lex_error_token(Lexer* lexer, char* message)
{
    Token token =
        {
            .type     = TOKEN_ERROR,
            .start    = lexer->current,
            .length   = (i32)strlen(message),
            .line     = lexer->line,
            .position = lexer->position_on_line
        };

    Lex_error_tokenf(lexer, &token, message);
    
    return token;
}

static Token Lex_string(Lexer* lexer)
{
    while (Lex_peek_char(lexer) != '"' && !Lex_is_at_end(lexer))
    {
        if (Lex_peek_char(lexer) == '\n') lexer->line++;
        Lex_advance(lexer);
    }

    if (Lex_is_at_end(lexer)) return Lex_error_token(lexer, "Unterminated string.");
    Lex_advance(lexer);
    return Lex_make_token(lexer, TOKEN_STRING);
}

static void Lex_skip_whitespace(Lexer* lexer)
{
    for (;;)
    {
        char c = Lex_peek_char(lexer);
        switch(c)
        {
        case ' ':
        case '\r':
        case '\t':
        {
            Lex_advance(lexer);
        }
        break;
        case '\n':
        {
            Lex_advance(lexer);
            lexer->line++;
            lexer->position_on_line = 0;
        }
        break;
        case '/':
        {
            char next = Lex_peek_next_char(lexer);
            if (next == '/')
            {
                while (Lex_peek_char(lexer) != '\n' && !Lex_is_at_end(lexer)) Lex_advance(lexer);
            }
            else
            {
                return;
            }
        }
        break;
        default:
        {
            return;
        }
        }
    }
}

static Token_Type Lex_check_keyword(Lexer* lexer, i32 start, i32 length, const char* rest, Token_Type type) {
  if (lexer->current - lexer->start == start + length &&
      memcmp(lexer->start + start, rest, length) == 0) {
    return type;
  }

  return TOKEN_IDENTIFIER;
}

static Token_Type Lex_identifier_type(Lexer* lexer)
{
    switch (lexer->start[0]) {
    case 'i': return Lex_check_keyword(lexer, 1, 1, "f", TOKEN_IF);
    case 'e': return Lex_check_keyword(lexer, 1, 3, "lse", TOKEN_ELSE);
    case 'r': return Lex_check_keyword(lexer, 1, 5, "eturn", TOKEN_RETURN);
    case 'w': return Lex_check_keyword(lexer, 1, 4, "hile", TOKEN_WHILE);
    case 't': return Lex_check_keyword(lexer, 1, 3, "rue", TOKEN_TRUE);
    case 'f':
    {
        if (lexer->current - lexer->start > 1)
        {
            switch (lexer->start[1])
            {
            case 'a': return Lex_check_keyword(lexer, 2, 3, "lse", TOKEN_FALSE);
            case 'o': return Lex_check_keyword(lexer, 2, 2, "or", TOKEN_FOR);
            }
        }
    }

    }
    return TOKEN_IDENTIFIER;
}

static Token Lex_identifier(Lexer* lexer)
{
    while (is_alpha(Lex_peek_char(lexer)) || is_digit(Lex_peek_char(lexer))) Lex_advance(lexer);
    return Lex_make_token(lexer, Lex_identifier_type(lexer));
}

static Token Lex_number(Lexer* lexer)
{
    while (is_digit(Lex_peek_char(lexer))) Lex_advance(lexer);

    if (Lex_peek_char(lexer) == '.' && is_digit(Lex_peek_char(lexer)))
    {
        Lex_advance(lexer);
        while (is_digit(Lex_peek_char(lexer))) Lex_advance(lexer);
    }

    return Lex_make_token(lexer, TOKEN_NUMBER);
}

Token Lex_scan_token(Lexer* lexer)
{
    Lex_skip_whitespace(lexer);
    lexer->start = lexer->current;

    if (Lex_is_at_end(lexer)) return Lex_make_token(lexer, TOKEN_EOF);

    char c = Lex_advance(lexer);

    if (is_alpha(c)) return Lex_identifier(lexer);
    if (is_digit(c)) return Lex_number(lexer);

    switch(c)
    {
    case '+': return Lex_make_token(lexer, TOKEN_PLUS);
    case '-':
    {
        if (Lex_match_character(lexer, '>')) return Lex_make_token(lexer, TOKEN_ARROW);
        return Lex_make_token(lexer, TOKEN_MINUS);
    }
    case '*': return Lex_make_token(lexer, TOKEN_STAR);
    case '/': return Lex_make_token(lexer, TOKEN_SLASH);
    case '|':
    {
        if (Lex_match_character(lexer, '|')) return Lex_make_token(lexer, TOKEN_PIPE_PIPE);
        return Lex_make_token(lexer, TOKEN_PIPE);
    }
    case '&':
    {
        if (Lex_match_character(lexer, '&')) return Lex_make_token(lexer, TOKEN_AMPERSAND_AMPERSAND);
        return Lex_make_token(lexer, TOKEN_AMPERSAND);
    }
    
    case '!':
    {
        if (Lex_match_character(lexer, '=')) return Lex_make_token(lexer, TOKEN_BANG_EQUAL);
        return Lex_make_token(lexer, TOKEN_BANG);
    }
    case '=':
    {
        if (Lex_match_character(lexer, '=')) return Lex_make_token(lexer, TOKEN_EQUAL_EQUAL);
        return Lex_make_token(lexer, TOKEN_EQUAL);
    }
    case '<':
    {
        if (Lex_match_character(lexer, '=')) return Lex_make_token(lexer, TOKEN_LESS_EQUAL);
        return Lex_make_token(lexer, TOKEN_LESS);
    }
    case '>':
    {
        if (Lex_match_character(lexer, '=')) return Lex_make_token(lexer, TOKEN_GREATER_EQUAL);
        return Lex_make_token(lexer, TOKEN_GREATER_EQUAL);
    }
    
    case '(': return Lex_make_token(lexer, TOKEN_LEFT_PAREN);
    case ')': return Lex_make_token(lexer, TOKEN_RIGHT_PAREN);
    case '{': return Lex_make_token(lexer, TOKEN_LEFT_BRACE);
    case '}': return Lex_make_token(lexer, TOKEN_RIGHT_BRACE);
    case ':':
    {
        if (Lex_match_character(lexer, ':')) return Lex_make_token(lexer, TOKEN_COLON_COLON);
        if (Lex_match_character(lexer, '=')) return Lex_make_token(lexer, TOKEN_COLON_EQUAL);
        return Lex_make_token(lexer, TOKEN_COLON);
    }
    case ';': return Lex_make_token(lexer, TOKEN_SEMICOLON);
    case '"': return Lex_string(lexer);
    case ',': return Lex_make_token(lexer, TOKEN_COMMA);
    }

    return Lex_error_token(lexer, "unexpected token");
}

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
    if (list->count + 1 >= list->capacity)
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

Token_List* Lex_tokenize(String* input, String* file_name, String* absolute_path)
{
    Token_List* list = malloc(sizeof(Token_List));
    token_list_init(list, 128);
    
    Lexer lexer;
    Lex_init(&lexer, input, sv_create(file_name), sv_create(absolute_path));

    Token token = Lex_scan_token(&lexer);

    while (token.type != TOKEN_EOF)
    {
        token_list_add(list, token);
        token = Lex_scan_token(&lexer);
    }

    token_list_add(list, token);

    return list;
}

String* Lex_pretty_print(Token_List* list, Allocator* allocator)
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
        case TOKEN_ARROW:
        {
            sb_append(&sb, "ARROW('->')\n");
        }
        break;
        case TOKEN_PIPE:
        {
            sb_append(&sb, "PIPE('|')\n");
        }
        break;
        case TOKEN_PIPE_PIPE:
        {
            sb_append(&sb, "PIPE_PIPE('||')\n");
        }
        break;
        case TOKEN_AMPERSAND:
        {
            sb_append(&sb, "AMPERSAND('&')\n");
        }
        break;
        case TOKEN_AMPERSAND_AMPERSAND:
        {
            sb_append(&sb, "AMPERSAND_AMPERSAND('&&')\n");
        }
        break;
        case TOKEN_SEMICOLON:
        {
            sb_append(&sb, "SEMICOLON(';')\n");
        }
        break;
        case TOKEN_COMMA:
        {
            sb_append(&sb, "COMMA(',')\n");
        }
        break;
        case TOKEN_BANG:
        {
            sb_append(&sb, "BANG('!')\n");
        }
        break;
        case TOKEN_BANG_EQUAL:
        {
            sb_append(&sb, "BANG_EQUAL('!=')\n");
        }
        break;
        case TOKEN_LESS:
        {
            sb_append(&sb, "LESS('<')\n");
        }
        break;        
        case TOKEN_LESS_EQUAL:
        {
            sb_append(&sb, "LESS_EQUAL('<=')\n");
        }
        break;
        case TOKEN_GREATER:
        {
            sb_append(&sb, "GREATER('>')\n");
        }
        break;
        case TOKEN_GREATER_EQUAL:
        {
            sb_append(&sb, "LESS_EQUAL('>=')\n");
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
        case TOKEN_EQUAL_EQUAL:
        {
            sb_append(&sb, "EQUAL_EQUAL('==')\n");
        }
        break;
        case TOKEN_COLON:
        {
            sb_append(&sb, "COLON('::')\n");
        }
        break;
        case TOKEN_COLON_COLON:
        {
            sb_append(&sb, "COLON_COLON('::')\n");
        }
        break;
        case TOKEN_COLON_EQUAL:
        {
            sb_append(&sb, "COLON_EQUAL(':=')\n");
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
        case TOKEN_IDENTIFIER:
        {
            sb_appendf(&sb, "IDENT('%.*s')\n", token.length, token.start);
        }
        break;
        case TOKEN_STRING:
        {
            sb_appendf(&sb, "STRING('%.*s')\n", token.length, token.start);
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
