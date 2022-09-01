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

static Sem_Variable_Info* Sem_find_variable_entry(Sem_Scope* scope, Sem_Variable_Key key, i32* index)
{
    Sem_Variable_Table* table = &scope->table;

    u32 hash_index = key.hash & (table->capacity - 1);

    Sem_Variable_Info* tombstone = NULL;

    for (;;)
    {
        Sem_Variable_Key found_key = table->keys[hash_index];

        if (found_key.key == NULL)
        {
            
        }
        else if (found_key.key == key.key) // @Note: Pointer compare
        {
            *index = hash_index;
            return &table->entries[hash_index];
        }
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
        Sem_Variable_Info* info = Sem_find_variable_entry(scope, key, &index);

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

#define SEM_ERROR(format, ...) (Sem_error(MAKE_LOCATION(), format, ##__VA_ARGS__))

void Sem_init_checker(Sem_Checker* checker)
{
    checker->current_scope = (Sem_Scope_Handle){ .handle = -1 };
    checker->had_error = false;
    checker->scope_list.scopes   = NULL;
    checker->scope_list.count    = 0;
    checker->scope_list.capacity = 0;
}

Sem_Scope* Sem_create_scope(Sem_Checker* checker, Allocator* allocator)
{
    NOT_IMPLEMENTED("Scope creation not yet implemented");
    return NULL;
}

void Sem_add_variable_to_scope(Sem_Scope* scope, String* name, Sem_Type type_info, Allocator* allocator)
{
    
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

void Sem_check_block(Sem_Checker* checker, AST_Node* body, Allocator* allocator)
{
    
}

void Sem_check(AST_Node* root, Allocator* allocator)
{
    Sem_Checker checker = {0};
    Sem_init_checker(&checker);
    
    Sem_Scope* global_scope = Sem_create_scope(&checker, allocator);
    
    AST_Node_List declarations = root->program.declarations;
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

                Sem_Scope* function_scope = Sem_create_scope(&checker, allocator);

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
