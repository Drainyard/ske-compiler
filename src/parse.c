
static void Parser_error_at(Parser* parser, Token* token, const char* message)
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

void Parser_error(Parser* parser, const char* message)
{
    Parser_error_at(parser, &parser->previous, message);
}

void Parser_error_at_current(Parser* parser, const char* message)
{
    Parser_error_at(parser, &parser->current, message);
}

void Parser_advance(Parser* parser)
{
    parser->previous = parser->current;

    for (;;)
    {
        parser->current = parser->token_stream->tokens[parser->current_token++];
        if (parser->current.type != TOKEN_ERROR) break;

        char err[32];
        sprintf(err, "unknown token \x1b[1;37m'%s'\x1b[0m", parser->current.start);
        Parser_error_at(parser, &parser->current, err);
    }
}

void Parser_init(Parser* parser, String* absolute_path, Token_List* tokens, Allocator* allocator)
{
    parser->current = tokens->tokens[0];
    parser->token_stream = tokens;
    parser->current_token = 0;
    parser->had_error = false;
    parser->panic_mode = false;
    parser->absolute_path = sv_create(absolute_path);

    parser->allocator = allocator;
}

void Parser_free(Parser* parser)
{
    parser->allocator->free_all(parser->allocator);
    parser->token_stream = NULL;
    parser->had_error = false;
    parser->panic_mode = false;
}

static void Parser_consume(Parser* parser, Token_Type token_type, const char* message)
{
    if (parser->current.type == token_type)
    {
        Parser_advance(parser);
        return;
    }

    Parser_error_at_current(parser, message);
}

static bool Parser_check(Parser* parser, Token_Type type)
{
    return parser->current.type == type;
}

static bool Parser_match(Parser* parser, Token_Type type)
{
    if (!Parser_check(parser, type)) return false;
    Parser_advance(parser);
    return true;
}

AST_Node* Parser_add_node(AST_Node_Type node_type, AST_Node* parent, Allocator* allocator)
{
    AST_Node* node = allocator->allocate(allocator, sizeof(AST_Node));
    node->type   = node_type;
    node->parent = parent;
    return node;
}

static AST_Node* Parser_precedence(Parser* parser, Precedence precedence, AST_Node* parent)
{
    Parser_advance(parser);
    Parse_Fn prefix_rule = Parser_get_rule(parser->previous.type)->prefix;
    if (prefix_rule == NULL)
    {
        Parser_error(parser, "expected expression");
        AST_Node* error_node = Parser_add_node(AST_NODE_ERROR, parent, parser->allocator);
        return error_node;
    }

    AST_Node* left = prefix_rule(parser, NULL, parent);

    while (precedence <= Parser_get_rule(parser->current.type)->precedence)
    {
        Parser_advance(parser);
        Parse_Fn infix_rule = Parser_get_rule(parser->previous.type)->infix;
        left = infix_rule(parser, left, parent);
    }

    return left;
}

static AST_Node* Parser_number(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    i32 value = strtol(parser->previous.start, NULL, 10);
    AST_Node* number_node = Parser_add_node(AST_NODE_LITERAL, parent, parser->allocator);
    AST_Literal* lit = &number_node->literal;
    lit->i = value;
    lit->type = LIT_INT;

    return number_node;
}

static AST_Node* Parser_variable(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    //Token identifier = parser->current;
    /* Parser_advance(parser); */
    return NULL;
}

static AST_Node* Parser_string(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    Token string = parser->current;
    AST_Node* string_node = Parser_add_node(AST_NODE_STRING, parent, parser->allocator);
    string_node->string = string_allocate_empty(string.length, parser->allocator);
    sprintf(string_node->string->str, "%.*s", string.length, string.start);
    return string_node;
}

static AST_Node* Parser_expression(Parser* parser, AST_Node* parent)
{
    return Parser_precedence(parser, PREC_ASSIGNMENT, parent);
}

static AST_Node* Parser_block(Parser* parser, AST_Node* parent)
{
    AST_Node* block = Parser_add_node(AST_NODE_BLOCK, parent, parser->allocator);
    block->block.declarations.capacity = 0;
    block->block.declarations.count = 0;
    block->block.declarations.nodes = NULL;
    
    while (!Parser_check(parser, TOKEN_RIGHT_BRACE) && !Parser_check(parser, TOKEN_EOF))
    {
        AST_node_list_add(&block->block.declarations, Parser_declaration(parser, parent));
    }

    Parser_consume(parser, TOKEN_RIGHT_BRACE, "Expect '}' after block.");

    return block;
}

static AST_Node* Parser_fun_declaration(Parser* parser, Token* identifier, AST_Node* parent)
{
    AST_Node* fun_node = Parser_add_node(AST_NODE_FUN_DECL, parent, parser->allocator);

    fun_node->fun_decl.name = string_allocate_empty(identifier->length, parser->allocator);
    sprintf(fun_node->fun_decl.name->str, "%.*s", identifier->length, identifier->start);

    Parser_consume(parser, TOKEN_LEFT_PAREN, "Expect '(' after '::' in function declaration.");

    if (!Parser_check(parser, TOKEN_RIGHT_PAREN))
    {
        // @Incomplete: Handle arguments here
        assert(false);
    }

    Parser_consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after parameters.");
    Parser_consume(parser, TOKEN_LEFT_BRACE, "Expect '{' function body.");

    fun_node->fun_decl.body = Parser_block(parser, parent);
    
    return fun_node;
}

static AST_Node* Parser_return_statement(Parser* parser, AST_Node* parent)
{
    if (Parser_check(parser, TOKEN_SEMICOLON))
    {
        AST_Node* return_node = Parser_add_node(AST_NODE_RETURN, parent, parser->allocator);
        return_node->return_statement.expression = NULL;
        Parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
        return return_node;
    }
    else
    {
        AST_Node* return_node = Parser_add_node(AST_NODE_RETURN, parent, parser->allocator);
        return_node->return_statement.expression = Parser_expression(parser, return_node);
        Parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
        return return_node;
    }
}

static AST_Node* Parser_expression_statement(Parser* parser, AST_Node* parent)
{
    AST_Node* expression = Parser_expression(parser, parent);
    Parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after expression.");
    return expression;
}

static AST_Node* Parser_if_statement(Parser* parser, AST_Node* parent)
{
    AST_Node* if_node = Parser_add_node(AST_NODE_IF, parent, parser->allocator);

    if_node->if_statement.condition = Parser_expression(parser, if_node);
    
    if_node->if_statement.then_arm = Parser_statement(parser, if_node);
    if_node->if_statement.else_arm = NULL;

    if (Parser_match(parser, TOKEN_ELSE))
    {
        if_node->if_statement.else_arm = Parser_statement(parser, if_node);
    }
    
    return if_node;
}

static AST_Node* Parser_statement(Parser* parser, AST_Node* parent)
{
    if (Parser_match(parser, TOKEN_RETURN))
    {
        return Parser_return_statement(parser, parent);
    }
    else if (Parser_match(parser, TOKEN_IF))
    {
        return Parser_if_statement(parser, parent);
    }
    else if (Parser_match(parser, TOKEN_LEFT_BRACE))
    {
        return Parser_block(parser, parent);
    }
    else
    {
        return Parser_expression_statement(parser, parent);
    }
}

static AST_Node* Parser_const_declaration(Parser* parser, Token* identifier, AST_Node* parent)
{
    if (Parser_check(parser, TOKEN_LEFT_PAREN))
    {
        return Parser_fun_declaration(parser, identifier, parent);
    }
    return NULL;
}

static AST_Node* Parser_declaration(Parser* parser, AST_Node* parent)
{
    if (Parser_check(parser, TOKEN_IDENTIFIER))
    {
        Token identifier = parser->current;
        Parser_advance(parser);
        if (Parser_check(parser, TOKEN_COLON_COLON))
        {
            Parser_advance(parser);
            return Parser_const_declaration(parser, &identifier, parent);
        }
        else if (Parser_check(parser, TOKEN_LEFT_PAREN))
        {
            AST_Node* call_node = Parser_call(parser, NULL, parent);
            Parser_consume(parser, TOKEN_SEMICOLON, "Expect ';' after function call.");
            return call_node;
        }
        return Parser_statement(parser, parent);
    }
    else
    {
        return Parser_statement(parser, parent);
    }
    return NULL;
}

static AST_Node* Parser_binary(Parser* parser, AST_Node* left, AST_Node* parent)
{
    Token_Type operator_type = parser->previous.type;
    Parse_Rule* rule = Parser_get_rule(operator_type);

    AST_Node* binary_expression = Parser_add_node(AST_NODE_BINARY, parent, parser->allocator);

    binary_expression->binary.left = left;
    binary_expression->binary.right = Parser_precedence(parser, rule->precedence + 1, binary_expression);

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

static AST_Node* Parser_unary(Parser* parser, AST_Node* rest, AST_Node* parent)
{
    Token_Type operator_type = parser->previous.type;
    AST_Node* unary_expression = Parser_add_node(AST_NODE_UNARY, parent, parser->allocator);

    unary_expression->unary.expression = Parser_precedence(parser, PREC_UNARY, parent);

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

static AST_Node* Parser_grouping(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    AST_Node* grouping = Parser_expression(parser, parent);
    Parser_consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
    return grouping;
}

static AST_Node* Parser_argument_list(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    u8 arg_count = 0;
    AST_Node* argument_list = Parser_add_node(AST_NODE_ARGUMENT_LIST, parent, parser->allocator);
    argument_list->argument_list.arguments = parser->allocator->allocate(parser->allocator, sizeof(AST_Node) * 16);
    
    if (!Parser_check(parser, TOKEN_RIGHT_PAREN))
    {
        do
        {
            argument_list->argument_list.arguments[arg_count] = Parser_expression(parser, parent);
            if (arg_count == 255)
            {
                Parser_error(parser, "Can't have more than 255 arguments.");
            }
            arg_count++;
        } while (Parser_match(parser, TOKEN_COMMA));
    }
    argument_list->argument_list.count = arg_count;
    Parser_consume(parser, TOKEN_RIGHT_PAREN, "Expect ')' after arguments.");

    return argument_list;
}

static AST_Node* Parser_call(Parser* parser, AST_Node* previous, AST_Node* parent)
{
    AST_Node* call = Parser_add_node(AST_NODE_CALL, parent, parser->allocator);
    Token prev = parser->previous;
    call->fun_call.name = string_allocate_empty(prev.length, parser->allocator);
    sprintf(call->fun_call.name->str, "%.*s", prev.length, prev.start);
    Parser_advance(parser);
    call->fun_call.arguments = Parser_argument_list(parser, NULL, call);
    return call;
}

static Parse_Rule* Parser_get_rule(Token_Type type)
{
    return &rules[type];
}

bool Parser_parse(Parser* parser, bool print_ast, Allocator* allocator)
{
    Parser_advance(parser);

    if (!Parser_match(parser, TOKEN_EOF))
    {
        parser->root = Parser_add_node(AST_NODE_PROGRAM, NULL, parser->allocator);
        parser->root->program.declarations.count = 0;
        parser->root->program.declarations.capacity = 0;
        parser->root->program.declarations.nodes = NULL;

        while (!Parser_match(parser, TOKEN_EOF))
        {
            AST_node_list_add(&parser->root->program.declarations, Parser_declaration(parser, parser->root));
        }
        /* parser->root->program.expression = Parser_expression(parser); */
    }
    
    if (!parser->had_error && print_ast)
    {
        pretty_print_ast(parser->root, allocator);
    }

    return !parser->had_error;
}
