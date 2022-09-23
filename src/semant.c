static u32 Sem_hash_string(String* string)
{
    u32 hash = 2166136261u;

    for (i32 i = 0; i < string->length; i++)
    {
        hash ^= string->str[i];
        hash += 16777619;
    }
    return hash;
}

static void Sem_check_error_at(Sem_Checker* checker, const char* file, i32 line, i32 position, const char* format, va_list arglist)
{
    fprintf(stderr, "\x1b[1;37m");
    fprintf(stderr, file);
    fprintf(stderr, ":%d:%d:\x1b[31m error: ", line, position);

    fprintf(stderr, "\x1b[0m");
    
    vfprintf(stderr, format, arglist);
    
    checker->had_error = true;
}

static void Sem_check_error(Sem_Checker* checker, const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);

    Sem_check_error_at(checker, checker->absolute_path.string->str, 0, 0, format, arglist);
}

static void Sem_error(Source_Location location, char* format, ...)
{
    va_list(ap);
    va_start(ap, format);
    output_error(location, "Semantic checker", format, ap);

    exit(1);
}

Sem_Scope* Sem_get_scope(Sem_Checker* checker, Sem_Scope_Handle handle)
{
    if (!SEM_HANDLE_VALID(handle) || checker->scope_list.count < handle.handle)
    {
        return NULL;
    }

    return &checker->scope_list.scopes[handle.handle];
}

static Sem_Scope* Sem_get_current_scope(Sem_Checker* checker)
{
    return Sem_get_scope(checker, checker->current_scope);
}

static Sem_Variable_Info* Sem_find_variable_entry(Sem_Variable_Info* entries, Sem_Variable_Key* keys, Sem_Variable_Key key, i32 capacity, i32* index)
{
    u32 hash_index = key.hash & (capacity - 1);

    Sem_Variable_Info* tombstone = NULL;

    for (;;)
    {
        Sem_Variable_Key found_key = keys[hash_index];

        if (found_key.key == NULL) // @Note: We found a tombstone
        {
            Sem_Variable_Info* entry = &entries[hash_index];
            if (entry->name == NULL)
            {
                return tombstone != NULL ? tombstone : entry;
            }
            else if (tombstone == NULL)
            {
                tombstone = entry;
            }
        }
        else if (found_key.key == key.key) // @Note: Pointer compare
        {
            *index = hash_index;
            return &entries[hash_index];
        }

        hash_index = (hash_index + 1) & (capacity - 1);
    }
    
    return NULL;
}

static Sem_Variable_Info* Sem_variable_get(Sem_Checker* checker, Sem_Variable_Key key)
{
    // @Note: Scope should always be valid, since there is always a global scope
    Sem_Scope* scope = Sem_get_scope(checker, checker->current_scope);

    i32 index = -1;
    do
    {
        Sem_Variable_Table* table = &scope->table;
        Sem_Variable_Info* info = Sem_find_variable_entry(table->entries, table->keys, key, table->capacity, &index);

        if (index == -1)
        {
            scope = Sem_get_scope(checker, scope->parent_handle);
        }
        else
        {
            return info;
        }
        
    } while (scope);
}

static void Sem_adjust_capacity(Sem_Variable_Table* table, i32 capacity, Allocator* allocator)
{
    Sem_Variable_Info* entries = malloc(sizeof(Sem_Variable_Info) * capacity);
    Sem_Variable_Key* keys = malloc(sizeof(Sem_Variable_Key) * capacity);
    for (i32 i = 0; i < capacity; i++)
    {
        entries[i].name = NULL;
        entries[i].type_info = SEM_MAKE_INVALID_TYPE;
    }
    
    table->count = 0;
    for (i32 i = 0; i < table->capacity; i++)
    {
        Sem_Variable_Key* key = &table->keys[i];
        if (key == NULL)
        {
            continue;
        }
        
        Sem_Variable_Info* entry = &table->entries[i];

        i32 index = -1;
        Sem_Variable_Info* dest = Sem_find_variable_entry(entries, keys, *key, capacity, &index);
        dest->name = entry->name;
        dest->type_info = entry->type_info;
        keys[index] = *key;
        table->count++;
    }

    free(table->entries);
    free(table->keys);

    table->entries = entries;
    table->keys = keys;
    table->capacity = capacity;
}

static b32 Sem_variable_set(Sem_Scope* scope, Sem_Variable_Key key, Sem_Variable_Info value, Allocator* allocator)
{
    Sem_Variable_Table* table = &scope->table;

    if (table->count + 1 > table->capacity * SEM_TABLE_MAX_LOAD)
    {
        i32 capacity = table->capacity < 8 ? 8 : table->capacity * 2;
        Sem_adjust_capacity(table, capacity, allocator);
    }

    i32 index = -1;
    Sem_Variable_Info* entry = Sem_find_variable_entry(table->entries, table->keys, key, table->capacity, &index);

    b32 is_new_key = index == -1;
    if (is_new_key && entry->name == NULL)
    {
        table->count++;
    }

    *entry = value;
    table->keys[key.hash & (table->capacity - 1)] = key;

    return is_new_key;
}

#define SEM_ERROR(format, ...) (Sem_error(MAKE_LOCATION(), format, ##__VA_ARGS__))

void Sem_init_checker(Sem_Checker* checker, String* absolute_path, Allocator* allocator)
{
    checker->current_scope = (Sem_Scope_Handle){ .handle = -1 };
    checker->had_error = false;
    checker->allocator = allocator;
    checker->scope_list.scopes   = NULL;
    checker->scope_list.count    = 0;
    checker->scope_list.capacity = 0;
    checker->absolute_path = sv_create(absolute_path);
}

Sem_Type Sem_create_type(AST_Node* type_node)
{
    Sem_Type type = {0};

    Type_Specifier spec = type_node->type_specifier.type;
    type.kind = TYPE_KIND_BUILTIN;
    switch(spec)
    {
    case TYPE_SPEC_INT:
    {
        type.builtin = BUILTIN_INT;
    }
    break;
    case TYPE_SPEC_UNIT:
    {
        type.builtin = BUILTIN_UNIT;
    }
    break;
    case TYPE_SPEC_INVALID:
    {
        SEM_ERROR("Invalid type %s", type_spec_to_string(spec));
    }
    break;
    }
           
    return type;
}

Sem_Variable_Info Sem_create_variable_info(String* name, Sem_Type type_info)
{
    Sem_Variable_Info info =
        {
            .name = name,
            .type_info = type_info
        };

    return info;
}


Sem_Function_Decl Sem_create_function_decl(AST_Node* fun_decl, Allocator* allocator)
{
    Sem_Function_Decl decl = {0};

    decl.name = fun_decl->fun_decl.name;
    Sem_Type* return_type = allocator->allocate(allocator, sizeof(Sem_Type));

    *return_type = Sem_create_type(fun_decl->fun_decl.return_type);

    AST_Node_List args = fun_decl->fun_decl.arguments;

    decl.arguments = allocator->allocate(allocator, sizeof(Sem_Variable_Info) * args.count);

    for (i32 i = 0; i < args.count; i++)
    {
        AST_Node* arg = args.nodes[i];

        Sem_Variable_Info var = Sem_create_variable_info(fun_decl->fun_argument.name, Sem_create_type(arg->fun_argument.type));

        decl.arguments[decl.argument_count++] = var;
    }
        
    return decl;
}

Sem_Scope* Sem_push_scope(Sem_Checker* checker, Allocator* allocator)
{
    i32 capacity = checker->scope_list.capacity;
    i32 count = checker->scope_list.count;
    
    if (count + 1 > capacity)
    {
        checker->scope_list.capacity = capacity < 8 ? 8 : capacity * 2;
        checker->scope_list.scopes = realloc(checker->scope_list.scopes, sizeof(Sem_Scope) * checker->scope_list.capacity);
    }

    Sem_Scope* new_scope = &checker->scope_list.scopes[checker->scope_list.count++];
    new_scope->parent_handle = checker->current_scope;
    new_scope->table =
        (Sem_Variable_Table){
            .entries  = NULL,
            .keys     = NULL,
            .count    = 0,
            .capacity = 0
        };

    checker->current_scope = (Sem_Scope_Handle) { checker->scope_list.count - 1 };
    
    return new_scope;
}

void Sem_add_variable_to_scope(Sem_Scope* scope, String* name, Sem_Type type_info, Allocator* allocator)
{
    Sem_Variable_Info info = Sem_create_variable_info(name, type_info);
    Sem_Variable_Key key =
        {
            .key = name,
            .hash = Sem_hash_string(name)
        };

    Sem_variable_set(scope, key, info, allocator);
}

void Sem_pop_scope(Sem_Checker* checker)
{
    if (!SEM_HANDLE_VALID(checker->current_scope))
    {
        return;
    }

    Sem_Scope* scope = Sem_get_scope(checker, checker->current_scope);
    checker->current_scope = scope->parent_handle;
}

const char* Sem_type_to_string(Sem_Type type)
{
    switch(type.kind)
    {
    case TYPE_KIND_BUILTIN:
    return "builtin";
    case TYPE_KIND_ALIAS:
    return "alias";
    case TYPE_KIND_STRUCT:
    return "struct";
    case TYPE_KIND_ENUM:
    return "enum";
    case TYPE_KIND_FUNCTION:
    return "function";
    case TYPE_KIND_INVALID:
    return "invalid";
    }
}

void Sem_compare_types(Sem_Checker* checker, Sem_Type left, Sem_Type right)
{
    if (left.kind != right.kind)
    {
        checker->had_error = true;
        return;
    }

    switch(left.kind)
    {
    case TYPE_KIND_BUILTIN:
    {
        if (left.builtin != right.builtin)
        {
            Sem_check_error(checker, "");
            checker->had_error = true;
            return;
        }
    }
    break;
    default:
    {
        NOT_IMPLEMENTED("Type checking not yet implemented for %s", Sem_type_to_string(left));
    }
    break;
    }
}

void Sem_check_binary(Sem_Checker* checker, AST_Node* binary, Allocator* allocator)
{
    AST_Node* left = binary->binary.left;
    AST_Node* right = binary->binary.right;

    Sem_Type left_type = Sem_check_expression(checker, left, allocator);
    Sem_Type right_type = Sem_check_expression(checker, right, allocator);

    Sem_compare_types(checker, left_type, right_type);
}

Sem_Type Sem_check_expression(Sem_Checker* checker, AST_Node* expression, Allocator* allocator)
{
    switch(expression->type)
    {
    case AST_NODE_CALL:
    {
        String* name = expression->fun_call.name;
        AST_Node_List arguments = expression->fun_call.arguments;
    }
    break;
    case AST_NODE_VARIABLE:
    {
        
    }
    break;
    case AST_NODE_LITERAL:
    {
        AST_Literal literal = expression->literal;
        Sem_Type type;
        switch(literal.type)
        {
        case LIT_INT:
        {
            type.kind = TYPE_KIND_BUILTIN;
            type.builtin = BUILTIN_INT;
        }
        break;
        case LIT_FLOAT:
        {
            type.kind = TYPE_KIND_BUILTIN;
            type.builtin = BUILTIN_FLOAT;
        }
        break;
        case LIT_STRING:
        {
            type.kind = TYPE_KIND_BUILTIN;
            type.builtin = BUILTIN_STRING;
        }
        break;
        }
        return type;
    }
    break;
    case AST_NODE_BINARY:
    {
        Sem_check_binary(checker, expression, allocator);
    }
    break;
    case AST_NODE_UNARY:
    {
        AST_Node* expression = expression->unary.expression;
        Sem_check_expression(checker, expression, allocator);
    }
    break;
    default:
    SEM_ERROR("Not a valid expression node type: %s", AST_type_string(expression->type));
    break;
    }
}

void Sem_check_statement(Sem_Checker* checker, AST_Node* statement, Allocator* allocator)
{
    switch(statement->type)
    {
    case AST_NODE_RETURN:
    {
        NOT_IMPLEMENTED("Semantic checker: Return statement not yet implemented.");
        AST_Node* return_expression = statement->return_statement.expression;
        
    }
    break;
    case AST_NODE_IF:
    {
        NOT_IMPLEMENTED("Semantic checker: If statement not yet implemented.");
    }
    break;
    default: // @Note: Expression statement
    {
        NOT_IMPLEMENTED("Semantic checker: Expression statement not yet implemented.");
    }
    break;
    }
}

void Sem_check_block(Sem_Checker* checker, AST_Node* block, Allocator* allocator)
{
    /* NOT_IMPLEMENTED("Semantic block checking not yet implemented"); */

    Sem_Scope* current_scope = Sem_get_current_scope(checker);

    AST_Node_List declarations = block->block.declarations;

    for (i32 i = 0; i < declarations.count; i++)
    {
        AST_Node* node = declarations.nodes[i];
        Sem_check_statement(checker, node, allocator);
    }
}

void Sem_check(AST_Node* root, String* absolute_path, Allocator* allocator)
{
    Sem_Checker checker = {0};
    Sem_init_checker(&checker, absolute_path, allocator);
    
    Sem_Scope* global_scope = Sem_push_scope(&checker, allocator);
    
    AST_Node_List declarations = root->program.declarations;

    for (i32 i = 0; i < declarations.count; i++)
    {
        AST_Node* node = declarations.nodes[i];

        switch(node->type)
        {
        case AST_NODE_FUN_DECL:
        {
            
            Sem_Type fun_type =
                {
                    .kind = TYPE_KIND_FUNCTION,
                    .fun_decl = Sem_create_function_decl(node, allocator)
                };
            Sem_add_variable_to_scope(global_scope, node->fun_decl.name, fun_type, allocator);
        }
        break;
        default: break;
        }
    }
    
    for (i32 i = 0; i < declarations.count; i++)
    {
        AST_Node* node = declarations.nodes[i];

        switch(node->type)
        {
            case AST_NODE_FUN_DECL:
            {
                /* @Incomplete:
                   - Create a new scope
                   - Add arguments to current scope
                   - Type check block
                   - Get return type of block and compare to function return type
                */

                Sem_Scope* function_scope = Sem_push_scope(&checker, allocator);

                AST_Node_List* arguments = &node->fun_decl.arguments;
                for (i32 i = 0; i < arguments->count; i++)
                {
                    AST_Node* argument = arguments->nodes[i];
                    String* name = argument->fun_argument.name;
                    AST_Node* ast_type = argument->fun_argument.type;

                    Type_Specifier type_spec = ast_type->type_specifier.type;
                    Sem_Type type = {0};

                    switch(type_spec)
                    {
                    case TYPE_SPEC_INT:
                    {
                        type.kind = TYPE_KIND_BUILTIN;
                        type.builtin = BUILTIN_INT;
                    }
                    break;
                    case TYPE_SPEC_UNIT:
                    {
                        type.kind = TYPE_KIND_BUILTIN;
                        type.builtin = BUILTIN_UNIT;
                    }
                    break;
                    case TYPE_SPEC_INVALID:
                    {
                        type.kind = TYPE_KIND_INVALID;
                    }
                    break;
                    }

                    Sem_add_variable_to_scope(function_scope, name, type, allocator);
                }

                Sem_check_block(&checker, node->fun_decl.body, allocator);

                Sem_pop_scope(&checker);
            }
            break;
        default:
        {
            SEM_ERROR("Invalid AST node type in top level.");
        }
        break;
        }
    }
}
