#ifndef SKE_PARSE_H
#define SKE_PARSE_H

typedef enum
{
    AST_NODE_STATEMENT,
    AST_NODE_PROGRAM,
    AST_NODE_FUN_DECL,
    AST_NODE_CALL,
    AST_NODE_RETURN,
    AST_NODE_BLOCK,
    AST_NODE_NUMBER,
    AST_NODE_BINARY,
    AST_NODE_UNARY,
    AST_NODE_TYPE_SPECIFIER,
    AST_NODE_ERROR
} AST_Node_Type;

typedef enum
{
    TYPE_SPEC_INT,
    TYPE_SPEC_UNIT
} Type_Specifier;

typedef struct  AST_Node_List AST_Node_List;
struct AST_Node_List
{
    struct AST_Node** nodes;
    i32 capacity;
    i32 count;
};

typedef struct AST_Node AST_Node;
struct AST_Node
{
    AST_Node_Type type;

    union
    {
        i32 number; // @Incomplete: Should be expanded to other constant types (float, string, etc.)
        struct
        {
            AST_Node* expression;
            Token_Type operator;
        } unary;
        struct
        {
            AST_Node* left;
            AST_Node* right;

            Token_Type operator;
        } binary;
        struct
        {
            AST_Node_List declarations;
        } program;
        struct
        {
            AST_Node* expression;
        } expression;
        struct
        {
            AST_Node* statement;
        } statement;
        struct
        {
            AST_Node* expression;
        } return_statement;
        struct
        {
            String* name;
            AST_Node* type_specifier;
            AST_Node* arguments;
            AST_Node* body;
        } fun_decl;
        struct
        {
            String* name;
        } fun_call;
        struct
        {
            AST_Node_List declarations;
        } block;
        struct
        {
            Type_Specifier type;
        } type_specifier;
        struct
        {
            AST_Node* rest;
        } error;
    };
};

void ast_node_list_add(AST_Node_List* list, AST_Node* node)
{
    if (list->count + 1 > list->capacity)
    {
        list->capacity = list->capacity == 0 ? 2 : list->capacity * 2;
        list->nodes = realloc(list->nodes, list->capacity * sizeof(AST_Node*));
    }
    list->nodes[list->count++] = node;
}

typedef enum
{
    PREC_NONE,
    PREC_ASSIGNMENT,  // =
    PREC_OR,          // or
    PREC_AND,         // and
    PREC_EQUALITY,    // == !=
    PREC_COMPARISON,  // < > <= >=
    PREC_TERM,        // + -
    PREC_FACTOR,      // * /
    PREC_UNARY,       // ! -
    PREC_CALL,        // . ()
    PREC_PRIMARY
} Precedence;

typedef struct Parser Parser;
struct Parser
{
    Token current;
    Token previous;

    Token_List* token_stream;
    i32 current_token;

    String_View absolute_path;

    Allocator* allocator;

    bool had_error;
    bool panic_mode;

    AST_Node* root;
};

typedef AST_Node* (*Parse_Fn)(Parser*, AST_Node* left);
typedef struct
{
    Parse_Fn prefix;
    Parse_Fn infix;
    Precedence precedence;
} Parse_Rule;

static void parser_error_at(Parser* parser, Token* token, const char* message)
{
    if (parser->panic_mode) return;
    parser->panic_mode = true;

    fprintf(stderr, "\x1b[1;37m");
    fprintf(stderr, sv_null_terminated_string(parser->absolute_path));
    fprintf(stderr, ":%d:%d:\x1b[31m error: ", token->line, token->position);

    fprintf(stderr, "\x1b[0m");

    fprintf(stderr, "%s\n", message);
    parser->had_error = true;
}

void parser_error(Parser* parser, const char* message)
{
    parser_error_at(parser, &parser->previous, message);
}

void parser_error_at_current(Parser* parser, const char* message)
{
    parser_error_at(parser, &parser->current, message);
}

void parser_advance(Parser* parser)
{
    parser->previous = parser->current;

    for (;;)
    {
        parser->current = parser->token_stream->tokens[parser->current_token++];
        if (parser->current.type != TOKEN_ERROR) break;

        char err[32];
        sprintf(err, "unknown token \x1b[1;37m'%s'\x1b[0m", parser->current.start);
        parser_error_at(parser, &parser->current, err);
    }
}

void parser_init(Parser* parser, String* absolute_path, Token_List* tokens, Allocator* allocator)
{
    parser->current = tokens->tokens[0];
    parser->token_stream = tokens;
    parser->current_token = 0;
    parser->had_error = false;
    parser->panic_mode = false;
    parser->absolute_path = sv_create(absolute_path);

    parser->allocator = allocator;
}

void parser_free(Parser* parser)
{
    parser->allocator->free_all(parser->allocator);
    parser->token_stream = NULL;
    parser->had_error = false;
    parser->panic_mode = false;
}

static void parser_consume(Parser* parser, Token_Type token_type, const char* message)
{
    if (parser->current.type == token_type)
    {
        parser_advance(parser);
        return;
    }

    parser_error_at_current(parser, message);
}

static bool parser_check(Parser* parser, Token_Type type)
{
    return parser->current.type == type;
}

static bool parser_match(Parser* parser, Token_Type type)
{
    if (!parser_check(parser, type)) return false;
    parser_advance(parser);
    return true;
}

AST_Node* parser_add_node(AST_Node_Type node_type, Allocator* allocator)
{
    AST_Node* node = allocator->allocate(allocator, sizeof(AST_Node));
    node->type = node_type;
    return node;
}

static Parse_Rule* parser_get_rule(Token_Type type);
static AST_Node* parser_expression(Parser* parser);
static AST_Node* parser_precedence(Parser* parser, Precedence precedence);
static AST_Node* parser_declaration(Parser* parser);
static AST_Node* parser_call(Parser* parser, AST_Node* previous);

static AST_Node* parser_precedence(Parser* parser, Precedence precedence)
{
    parser_advance(parser);
    Parse_Fn prefix_rule = parser_get_rule(parser->previous.type)->prefix;
    if (prefix_rule == NULL)
    {
        parser_error(parser, "expected expression");
        AST_Node* error_node = parser_add_node(AST_NODE_ERROR, parser->allocator);
        return error_node;
    }

    AST_Node* left = prefix_rule(parser, NULL);

    while (precedence <= parser_get_rule(parser->current.type)->precedence)
    {
        parser_advance(parser);
        Parse_Fn infix_rule = parser_get_rule(parser->previous.type)->infix;
        left = infix_rule(parser, left);
    }

    return left;
}

static AST_Node* parser_number(Parser* parser, AST_Node* _)
{
    (void)_;
    i32 value = strtol(parser->previous.start, NULL, 10);
    AST_Node* number_node = parser_add_node(AST_NODE_NUMBER, parser->allocator);
    number_node->number = value;

    return number_node;
}

static AST_Node* parser_variable(Parser* parser, AST_Node* previous)
{
    //Token identifier = parser->current;
    /* parser_advance(parser); */
    return NULL;
}

static AST_Node* parser_expression(Parser* parser)
{
    return parser_precedence(parser, PREC_ASSIGNMENT);
}

static AST_Node* parser_block(Parser* parser)
{
    AST_Node* block = parser_add_node(AST_NODE_BLOCK, parser->allocator);
    block->block.declarations.capacity = 0;
    block->block.declarations.count = 0;
    block->block.declarations.nodes = NULL;
    
    while (!parser_check(parser, TOKEN_RIGHT_BRACE) && !parser_check(parser, TOKEN_EOF))
    {
        ast_node_list_add(&block->block.declarations, parser_declaration(parser));
    }

    parser_consume(parser, TOKEN_RIGHT_BRACE, "Expect '}' after block.");

    return block;
}

static AST_Node* parser_fun_declaration(Parser* parser, Token* identifier)
{
    AST_Node* fun_node = parser_add_node(AST_NODE_FUN_DECL, parser->allocator);

    fun_node->fun_decl.name = string_allocate_empty(identifier->length, parser->allocator);
    sprintf(fun_node->fun_decl.name->str, "%.*s", identifier->length, identifier->start);

    parser_consume(parser, TOKEN_LEFT_PAREN, "Expect '(' after '::' in function declaration.");

    if (!parser_check(parser, TOKEN_RIGHT_PAREN))
    {
        // @Incomplete: Handle arguments here
        assert(false);
    }

    parser_consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after parameters.");
    parser_consume(parser, TOKEN_LEFT_BRACE, "Expect '{' function body.");

    fun_node->fun_decl.body = parser_block(parser);
    
    return fun_node;
}

static AST_Node* parser_return_statement(Parser* parser)
{
    if (parser_match(parser, TOKEN_SEMICOLON))
    {
        AST_Node* return_node = parser_add_node(AST_NODE_RETURN, parser->allocator);
        return_node->return_statement.expression = NULL;
        parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
        return return_node;
    }
    else
    {
        AST_Node* return_node = parser_add_node(AST_NODE_RETURN, parser->allocator);
        return_node->return_statement.expression = parser_expression(parser);
        parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
        return return_node;
    }
}

static AST_Node* parser_expression_statement(Parser* parser)
{
    AST_Node* expression = parser_expression(parser);
    parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
    return expression;
}

static AST_Node* parser_statement(Parser* parser)
{
    if (parser_match(parser, TOKEN_RETURN))
    {
        return parser_return_statement(parser);
    }
    else
    {
        return parser_expression_statement(parser);
    }
}

static AST_Node* parser_const_declaration(Parser* parser, Token* identifier)
{
    if (parser_check(parser, TOKEN_LEFT_PAREN))
    {
        return parser_fun_declaration(parser, identifier);
    }
    return NULL;
}

static AST_Node* parser_declaration(Parser* parser)
{
    if (parser_check(parser, TOKEN_IDENTIFIER))
    {
        Token identifier = parser->current;
        parser_advance(parser);
        if (parser_check(parser, TOKEN_COLON_COLON))
        {
            parser_advance(parser);
            return parser_const_declaration(parser, &identifier);
        }
        else if (parser_check(parser, TOKEN_LEFT_PAREN))
        {
            AST_Node* call_node = parser_call(parser, NULL);
            parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after function call.");
            return call_node;
        }
        return parser_statement(parser);
    }
    else
    {
        return parser_statement(parser);
    }
    return NULL;
}

static AST_Node* parser_binary(Parser* parser, AST_Node* left)
{
    Token_Type operator_type = parser->previous.type;
    Parse_Rule* rule = parser_get_rule(operator_type);

    AST_Node* binary_expression = parser_add_node(AST_NODE_BINARY, parser->allocator);

    binary_expression->binary.left = left;
    binary_expression->binary.right = parser_precedence(parser, rule->precedence + 1);

    switch (operator_type)
    {
    case TOKEN_PLUS:
    case TOKEN_MINUS:
    case TOKEN_STAR:
    case TOKEN_SLASH: 
    {
        binary_expression->binary.operator = operator_type;
    }
    break;    
    default:
    binary_expression->binary.operator = TOKEN_ERROR;
    }
    return binary_expression;
}

static AST_Node* parser_unary(Parser* parser, AST_Node* rest)
{
    Token_Type operator_type = parser->previous.type;
    AST_Node* unary_expression = parser_add_node(AST_NODE_UNARY, parser->allocator);

    unary_expression->unary.expression = parser_precedence(parser, PREC_UNARY);

    switch (operator_type)
    {
    case TOKEN_MINUS:
    {
        unary_expression->unary.operator = TOKEN_MINUS;
    }
    break;
    case TOKEN_BANG:
    {
        unary_expression->unary.operator = TOKEN_BANG;
    }
    break;
    default:
    {
        unary_expression->unary.operator = TOKEN_ERROR;
    }
    break;
    }
    return unary_expression;
}

static AST_Node* parser_grouping(Parser* parser, AST_Node* previous)
{
    AST_Node* grouping = parser_expression(parser);
    parser_consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
    return grouping;
}

static AST_Node* parser_call(Parser* parser, AST_Node* previous)
{
    AST_Node* call = parser_add_node(AST_NODE_CALL, parser->allocator);
    Token prev = parser->previous;
    call->fun_call.name = string_allocate_empty(prev.length, parser->allocator);
    sprintf(call->fun_call.name->str, "%.*s", prev.length, prev.start);
    parser_advance(parser);
    parser_consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after argument list of function call.");
    return call;
}

Parse_Rule rules[] = {
  [TOKEN_LEFT_PAREN]       = {parser_grouping, parser_call,   PREC_CALL},
  [TOKEN_RIGHT_PAREN]      = {NULL,            NULL,          PREC_NONE},
  [TOKEN_LEFT_BRACE]       = {NULL,            NULL,          PREC_NONE},
  [TOKEN_RIGHT_BRACE]      = {NULL,            NULL,          PREC_NONE},
  /* [TOKEN_COMMA]         = {NULL,            NULL,          PREC_NONE}, */
  /* [TOKEN_DOT]           = {NULL,            NULL,          PREC_NONE}, */
  [TOKEN_MINUS]            = {parser_unary,    parser_binary, PREC_TERM},
  [TOKEN_PLUS]             = {NULL,            parser_binary, PREC_TERM},
  [TOKEN_SEMICOLON]        = {NULL,            NULL,          PREC_NONE},
  [TOKEN_SLASH]            = {NULL,            parser_binary, PREC_FACTOR},
  [TOKEN_STAR]             = {NULL,            parser_binary, PREC_FACTOR},
  [TOKEN_BANG]             = {NULL,            NULL,          PREC_NONE},
  /* [TOKEN_BANG_EQUAL]    = {NULL,            NULL,          PREC_NONE}, */
  [TOKEN_EQUAL]            = {NULL,            NULL,          PREC_NONE},
  /* [TOKEN_EQUAL_EQUAL]   = {NULL,            NULL,          PREC_NONE}, */
  /* [TOKEN_GREATER]       = {NULL,            NULL,          PREC_NONE}, */
  /* [TOKEN_GREATER_EQUAL] = {NULL,            NULL,          PREC_NONE}, */
  /* [TOKEN_LESS]          = {NULL,            NULL,          PREC_NONE}, */
  /* [TOKEN_LESS_EQUAL]    = {NULL,            NULL,          PREC_NONE}, */
  [TOKEN_IDENTIFIER]       = {parser_variable, NULL,          PREC_NONE},
  [TOKEN_NUMBER]           = {parser_number,   NULL,          PREC_NONE},
  [TOKEN_ELSE]             = {NULL,            NULL,          PREC_NONE},
  [TOKEN_FALSE]            = {NULL,            NULL,          PREC_NONE},
  [TOKEN_FOR]              = {NULL,            NULL,          PREC_NONE},
  [TOKEN_IF]               = {NULL,            NULL,          PREC_NONE},
  /* [TOKEN_NIL]           = {NULL,            NULL,          PREC_NONE}, */
  [TOKEN_RETURN]           = {NULL,            NULL,          PREC_NONE},
  /* [TOKEN_THIS]          = {NULL,            NULL,          PREC_NONE}, */
  [TOKEN_TRUE]             = {NULL,            NULL,          PREC_NONE},
  [TOKEN_WHILE]            = {NULL,            NULL,          PREC_NONE},
  [TOKEN_ERROR]            = {NULL,            NULL,          PREC_NONE},
  [TOKEN_EOF]              = {NULL,            NULL,          PREC_NONE},
};

static Parse_Rule* parser_get_rule(Token_Type type)
{
    return &rules[type];
}

static char* parser_type_string(AST_Node_Type type)
{
    switch(type)
    {
    case AST_NODE_STATEMENT:
    return "AST_NODE_STATEMENT";
    /* case AST_NODE_EXPRESSION: */
    /* return "AST_NODE_EXPRESSION"; */
    case AST_NODE_PROGRAM:
    return "AST_NODE_PROGRAM";
    case AST_NODE_FUN_DECL:
    return "AST_NODE_FUN_DECL";
    case AST_NODE_CALL:
    return "AST_NODE_CALL";
    case AST_NODE_RETURN:
    return "AST_NODE_RETURN";
    case AST_NODE_BLOCK:
    return "AST_NODE_BLOCK";
    case AST_NODE_NUMBER:
    return "AST_NODE_NUMBER";
    case AST_NODE_BINARY:
    return "AST_NODE_BINARY";
    case AST_NODE_UNARY:
    return "AST_NODE_UNARY";
    case AST_NODE_TYPE_SPECIFIER:
    return "AST_NODE_TYPE_SPECIFIER";
    case AST_NODE_ERROR:
    return "AST_NODE_ERROR";
    }
    return "";
}

static void pretty_print_unary(AST_Node* node, i32 indentation, String_Builder* builder);
static void pretty_print_binary(AST_Node* binary, i32 indentation, String_Builder* builder);
static void pretty_print_expression(AST_Node* node, i32 indentation, String_Builder* builder);

typedef void (*Pretty_Print_Fn)(AST_Node*, i32, String_Builder*);

static void paren(String_Builder* builder, Pretty_Print_Fn print_fn, AST_Node* node, i32 indentation)
{
    sb_indent(builder, indentation);
    sb_append(builder, "(");
    print_fn(node, indentation, builder);
    sb_append(builder, ")");
}

static void pretty_print_operator(Token_Type operator, String_Builder* builder)
{
    /* sb_append(builder, "("); */
    /* sb_append(builder, "Op: "); */
    switch (operator)
    {
    case TOKEN_PLUS: sb_append(builder, "+"); break;
    case TOKEN_MINUS: sb_append(builder, "-"); break;
    case TOKEN_STAR:  sb_append(builder, "*"); break;
    case TOKEN_SLASH: sb_append(builder, "/"); break;
    case TOKEN_ERROR: sb_append(builder, "ERROR"); break;
    default: assert(false);
    }
    /* sb_append(builder, ")"); */
}

static void pretty_print_unary(AST_Node* node, i32 indentation, String_Builder* builder)
{
    sb_append(builder, "Unary\t\n ");
    
    indentation++;
    sb_indent(builder, indentation);

    pretty_print_operator(node->unary.operator, builder);

    sb_append(builder, ",\n ");
    pretty_print_expression(node->unary.expression, indentation, builder);
    sb_append(builder, ")");
}

static void pretty_print_binary(AST_Node* binary, i32 indentation, String_Builder* builder)
{
    /* sb_append(builder, "Binary\t\n "); */

    sb_indent(builder, indentation);
    sb_append(builder, "(");
    pretty_print_operator(binary->binary.operator, builder);
    sb_append(builder, " ");    
    
    pretty_print_expression(binary->binary.left, 0, builder);
    /* sb_indent(builder, indentation); */
    sb_append(builder, " ");   

    pretty_print_expression(binary->binary.right, 0, builder);
    sb_append(builder, ")");
}

static void pretty_print_number(AST_Node* number, i32 indentation, String_Builder* builder)
{
    sb_appendf(builder, "%d", number->number);
}

static void pretty_print_expression(AST_Node* node, i32 indentation, String_Builder* builder)
{
    switch(node->type)
    {
    case AST_NODE_UNARY:
    {
        pretty_print_unary(node, 0, builder);
        /* paren(builder, pretty_print_unary, node, 0); */
    }
    break;
    case AST_NODE_BINARY:
    {
        pretty_print_binary(node, 0, builder);
        /* paren(builder, pretty_print_binary, node, 0); */
    }
    break;
    case AST_NODE_NUMBER:
    {
        pretty_print_number(node, 0, builder);
        /* paren(builder, pretty_print_number, node, 0); */
    }
    break;
    default:
    {
        log_error("Unsupported node type %s\n", parser_type_string(node->type));
        assert(false);
    }
    break;
    }
}

static void pretty_print_statement(AST_Node* statement, i32 indentation, String_Builder* builder)
{
    switch(statement->type)
    {
    case AST_NODE_RETURN:
    {
        sb_indent(builder, indentation);
        sb_append(builder, "(return \n");
        sb_indent(builder, indentation + 1);
        pretty_print_expression(statement->return_statement.expression, indentation, builder);
        sb_append(builder, ")");
    }
    break;
    case AST_NODE_CALL:
    {
        sb_indent(builder, indentation);
        sb_appendf(builder, "(call %s)", statement->fun_call.name->str);
    }
    break;
    default: assert(false && "Not a valid statement type"); break;
    }
}

static void pretty_print_declaration(AST_Node* declaration, i32 indentation, String_Builder* builder)
{
    switch(declaration->type)
    {
    case AST_NODE_FUN_DECL:
    {
        sb_indent(builder, indentation);
        sb_appendf(builder, "(fun %s ()", declaration->fun_decl.name->str);

        AST_Node_List block = declaration->fun_decl.body->block.declarations;

        if (block.count > 0)
        {
            sb_append(builder, ",\n");
        }

        for (i32 i = 0; i < block.count; i++)
        {
            AST_Node* node = block.nodes[i];
            pretty_print_statement(node, indentation + 1, builder);
        }

        sb_append(builder, ")\n");
    }
    break;
    default: assert(false && "Not a declaration."); break;
    }
}

static void pretty_print_program(AST_Node* program_node, i32 indentation, String_Builder* builder)
{
    sb_append(builder, "(");
    sb_append(builder, "program\t\n");
    indentation++;

    AST_Node_List list = program_node->program.declarations;

    for (i32 i = 0; i < list.count; i++)
    {
        AST_Node* declaration = list.nodes[i];
        pretty_print_declaration(declaration, indentation, builder);
    }
    
    /* pretty_print_expression(program_node->program.expression, indentation, builder); */
    sb_append(builder, ")");
}

static String* pretty_print_ast(AST_Node* root, Allocator* allocator)
{
    assert(root->type == AST_NODE_PROGRAM);
    String_Builder builder;
    sb_init(&builder, 256);
    pretty_print_program(root, 0, &builder);
    sb_append(&builder, "\n");

    return sb_get_result(&builder, allocator);
}

bool parse(Parser* parser, bool print_ast, Allocator* allocator)
{
    parser_advance(parser);

    if (!parser_match(parser, TOKEN_EOF))
    {
        parser->root = parser_add_node(AST_NODE_PROGRAM, parser->allocator);
        parser->root->program.declarations.count = 0;
        parser->root->program.declarations.capacity = 0;
        parser->root->program.declarations.nodes = NULL;

        while (!parser_match(parser, TOKEN_EOF))
        {
            ast_node_list_add(&parser->root->program.declarations, parser_declaration(parser));
        }
        /* parser->root->program.expression = parser_expression(parser); */
    }
    
    if (!parser->had_error && print_ast)
    {
        pretty_print_ast(parser->root, allocator);
    }

    return !parser->had_error;
}


#endif
