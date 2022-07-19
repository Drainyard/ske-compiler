
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

AST_Node* parser_add_node(AST_Node_Type node_type, AST_Node* parent, Allocator* allocator)
{
    AST_Node* node = allocator->allocate(allocator, sizeof(AST_Node));
    node->type   = node_type;
    node->parent = parent;
    return node;
}

static AST_Node* parser_precedence(Parser* parser, Precedence precedence, AST_Node* parent)
{
    parser_advance(parser);
    Parse_Fn prefix_rule = parser_get_rule(parser->previous.type)->prefix;
    if (prefix_rule == NULL)
    {
        parser_error(parser, "expected expression");
        AST_Node* error_node = parser_add_node(AST_NODE_ERROR, parent, parser->allocator);
        return error_node;
    }

    AST_Node* left = prefix_rule(parser, NULL, parent);

    while (precedence <= parser_get_rule(parser->current.type)->precedence)
    {
        parser_advance(parser);
        Parse_Fn infix_rule = parser_get_rule(parser->previous.type)->infix;
        left = infix_rule(parser, left, parent);
    }

    return left;
}

static AST_Node* parser_number(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    i32 value = strtol(parser->previous.start, NULL, 10);
    AST_Node* number_node = parser_add_node(AST_NODE_NUMBER, parent, parser->allocator);
    number_node->number = value;

    return number_node;
}

static AST_Node* parser_variable(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    //Token identifier = parser->current;
    /* parser_advance(parser); */
    return NULL;
}

static AST_Node* parser_string(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    Token string = parser->current;
    AST_Node* string_node = parser_add_node(AST_NODE_STRING, parent, parser->allocator);
    string_node->string = string_allocate_empty(string.length, parser->allocator);
    sprintf(string_node->string->str, "%.*s", string.length, string.start);
    return string_node;
}

static AST_Node* parser_expression(Parser* parser, AST_Node* parent)
{
    return parser_precedence(parser, PREC_ASSIGNMENT, parent);
}

static AST_Node* parser_block(Parser* parser, AST_Node* parent)
{
    AST_Node* block = parser_add_node(AST_NODE_BLOCK, parent, parser->allocator);
    block->block.declarations.capacity = 0;
    block->block.declarations.count = 0;
    block->block.declarations.nodes = NULL;
    
    while (!parser_check(parser, TOKEN_RIGHT_BRACE) && !parser_check(parser, TOKEN_EOF))
    {
        ast_node_list_add(&block->block.declarations, parser_declaration(parser, parent));
    }

    parser_consume(parser, TOKEN_RIGHT_BRACE, "Expect '}' after block.");

    return block;
}

static AST_Node* parser_fun_declaration(Parser* parser, Token* identifier, AST_Node* parent)
{
    AST_Node* fun_node = parser_add_node(AST_NODE_FUN_DECL, parent, parser->allocator);

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

    fun_node->fun_decl.body = parser_block(parser, parent);
    
    return fun_node;
}

static AST_Node* parser_return_statement(Parser* parser, AST_Node* parent)
{
    if (parser_check(parser, TOKEN_SEMICOLON))
    {
        AST_Node* return_node = parser_add_node(AST_NODE_RETURN, parent, parser->allocator);
        return_node->return_statement.expression = NULL;
        parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
        return return_node;
    }
    else
    {
        AST_Node* return_node = parser_add_node(AST_NODE_RETURN, parent, parser->allocator);
        return_node->return_statement.expression = parser_expression(parser, return_node);
        parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
        return return_node;
    }
}

static AST_Node* parser_expression_statement(Parser* parser, AST_Node* parent)
{
    AST_Node* expression = parser_expression(parser, parent);
    parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
    return expression;
}

static AST_Node* parser_if_statement(Parser* parser, AST_Node* parent)
{
    AST_Node* if_node = parser_add_node(AST_NODE_IF, parent, parser->allocator);

    if_node->if_statement.condition = parser_expression(parser, if_node);
    
    if_node->if_statement.then_arm = parser_statement(parser, if_node);
    if_node->if_statement.else_arm = NULL;

    if (parser_match(parser, TOKEN_ELSE))
    {
        if_node->if_statement.else_arm = parser_statement(parser, if_node);
    }
    
    return if_node;
}

static AST_Node* parser_statement(Parser* parser, AST_Node* parent)
{
    if (parser_match(parser, TOKEN_RETURN))
    {
        return parser_return_statement(parser, parent);
    }
    else if (parser_match(parser, TOKEN_IF))
    {
        return parser_if_statement(parser, parent);
    }
    else if (parser_match(parser, TOKEN_LEFT_BRACE))
    {
        return parser_block(parser, parent);
    }
    else
    {
        return parser_expression_statement(parser, parent);
    }
}

static AST_Node* parser_const_declaration(Parser* parser, Token* identifier, AST_Node* parent)
{
    if (parser_check(parser, TOKEN_LEFT_PAREN))
    {
        return parser_fun_declaration(parser, identifier, parent);
    }
    return NULL;
}

static AST_Node* parser_declaration(Parser* parser, AST_Node* parent)
{
    if (parser_check(parser, TOKEN_IDENTIFIER))
    {
        Token identifier = parser->current;
        parser_advance(parser);
        if (parser_check(parser, TOKEN_COLON_COLON))
        {
            parser_advance(parser);
            return parser_const_declaration(parser, &identifier, parent);
        }
        else if (parser_check(parser, TOKEN_LEFT_PAREN))
        {
            AST_Node* call_node = parser_call(parser, NULL, parent);
            parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after function call.");
            return call_node;
        }
        return parser_statement(parser, parent);
    }
    else
    {
        return parser_statement(parser, parent);
    }
    return NULL;
}

static AST_Node* parser_binary(Parser* parser, AST_Node* left, AST_Node* parent)
{
    Token_Type operator_type = parser->previous.type;
    Parse_Rule* rule = parser_get_rule(operator_type);

    AST_Node* binary_expression = parser_add_node(AST_NODE_BINARY, parent, parser->allocator);

    binary_expression->binary.left = left;
    binary_expression->binary.right = parser_precedence(parser, rule->precedence + 1, binary_expression);

    switch (operator_type)
    {
    case TOKEN_PLUS:
    case TOKEN_MINUS:
    case TOKEN_STAR:
    case TOKEN_SLASH:
    case TOKEN_EQUAL_EQUAL:
    case TOKEN_EQUAL:
    case TOKEN_BANG_EQUAL:
    case TOKEN_PIPE:
    case TOKEN_PIPE_PIPE:
    case TOKEN_AMPERSAND:
    case TOKEN_AMPERSAND_AMPERSAND:
    case TOKEN_LESS:
    case TOKEN_LESS_EQUAL:
    case TOKEN_GREATER:
    case TOKEN_GREATER_EQUAL:
    {
        binary_expression->binary.operator = operator_type;
    }
    break;    
    default:
    binary_expression->binary.operator = TOKEN_ERROR;
    }
    return binary_expression;
}

static AST_Node* parser_unary(Parser* parser, AST_Node* rest, AST_Node* parent)
{
    Token_Type operator_type = parser->previous.type;
    AST_Node* unary_expression = parser_add_node(AST_NODE_UNARY, parent, parser->allocator);

    unary_expression->unary.expression = parser_precedence(parser, PREC_UNARY, parent);

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

static AST_Node* parser_grouping(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    AST_Node* grouping = parser_expression(parser, parent);
    parser_consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
    return grouping;
}

static AST_Node* parser_argument_list(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    u8 arg_count = 0;
    AST_Node* argument_list = parser_add_node(AST_NODE_ARGUMENT_LIST, parent, parser->allocator);
    argument_list->argument_list.arguments = parser->allocator->allocate(parser->allocator, sizeof(AST_Node) * 16);
    
    if (!parser_check(parser, TOKEN_RIGHT_PAREN))
    {
        do
        {
            argument_list->argument_list.arguments[arg_count] = parser_expression(parser, parent);
            if (arg_count == 255)
            {
                parser_error(parser, "Can't have more than 255 arguments.");
            }
            arg_count++;
        } while (parser_match(parser, TOKEN_COMMA));
    }
    argument_list->argument_list.count = arg_count;
    parser_consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after arguments.");

    return argument_list;
}

static AST_Node* parser_call(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    AST_Node* call = parser_add_node(AST_NODE_CALL, parent, parser->allocator);
    Token prev = parser->previous;
    call->fun_call.name = string_allocate_empty(prev.length, parser->allocator);
    sprintf(call->fun_call.name->str, "%.*s", prev.length, prev.start);
    parser_advance(parser);
    call->fun_call.arguments = parser_argument_list(parser, NULL, call);
    return call;
}

static Parse_Rule* parser_get_rule(Token_Type type)
{
    return &rules[type];
}

bool parse(Parser* parser, bool print_ast, Allocator* allocator)
{
    parser_advance(parser);

    if (!parser_match(parser, TOKEN_EOF))
    {
        parser->root = parser_add_node(AST_NODE_PROGRAM, NULL, parser->allocator);
        parser->root->program.declarations.count = 0;
        parser->root->program.declarations.capacity = 0;
        parser->root->program.declarations.nodes = NULL;

        while (!parser_match(parser, TOKEN_EOF))
        {
            ast_node_list_add(&parser->root->program.declarations, parser_declaration(parser, parser->root));
        }
        /* parser->root->program.expression = parser_expression(parser); */
    }
    
    if (!parser->had_error && print_ast)
    {
        pretty_print_ast(parser->root, allocator);
    }

    return !parser->had_error;
}
