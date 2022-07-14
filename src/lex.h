#ifndef SKE_LEX_H
#define SKE_LEX_H


typedef enum
{
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    
    TOKEN_BANG,
    TOKEN_BANG_EQUAL,

    TOKEN_LESS,
    TOKEN_GREATER,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER_EQUAL,

    TOKEN_PIPE,
    TOKEN_PIPE_PIPE,

    TOKEN_AMPERSAND,
    TOKEN_AMPERSAND_AMPERSAND,

    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,

    TOKEN_COLON, // type specifier
    TOKEN_COLON_COLON, // constant decl
    TOKEN_COLON_EQUAL, // mutable decl
    TOKEN_EQUAL, // asignment
    TOKEN_EQUAL_EQUAL, // equality

    TOKEN_IF, TOKEN_ELSE, TOKEN_WHILE,
    TOKEN_RETURN, 
    TOKEN_FALSE, TOKEN_TRUE, TOKEN_FOR,
    
    TOKEN_IDENTIFIER,
    TOKEN_STRING,

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

void lexer_init(Lexer* lexer, String* source, String_View file_name, String_View absolute_path);
Token lexer_scan_token(Lexer* lexer);

void token_list_init(Token_List* list, i32 initial_capacity);
void token_list_free(Token_List* list);
void token_list_maybe_expand(Token_List* list);
void token_list_add(Token_List* list, Token token);

Token_List* lexer_tokenize(String* input, String* file_name, String* absolute_path);
String* lexer_pretty_print(Token_List* list, Allocator* allocator);

#endif
