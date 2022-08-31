#ifndef SEMANT_H
#define SEMANT_H

/* @Note:
   We want to implement some basic semantic checker. In this case it will consist of:
   - Basic type checking
   - Check if a variable is in scope

   ### Type Checking
   Type checking needs to be done both for expressions (binop, unop, assignments) and function arguments.

   ### Scopes
   We need to have a global scope (function declarations for now only) and a local scope (within functions and blocks).
   So for type checking we need a 
 */

typedef enum
{
    BUILTIN_INT,
    BUILTIN_FLOAT,
    BUILTIN_STRING,
    BUILTIN_UNIT,
} Sem_Builtin_Type;

typedef enum
{
    TYPE_KIND_BUILTIN,
    TYPE_KIND_ALIAS,
    TYPE_KIND_STRUCT,
    TYPE_KIND_ENUM
} Sem_Type_Kind;

typedef struct Sem_Type_Alias Sem_Type_Alias;
struct Sem_Type_Alias
{
    String* alias_name;
    Sem_Type
};

typedef struct Sem_Type Sem_Type;
struct Sem_Type
{
    Sem_Type_Kind kind;

    union
    {
        Sem_Builtin_Type builtin;
        
    };
};

typedef struct Sem_Variable_Info Sem_Variable_Info;
struct Sem_Variable_Info
{
    
};

typedef struct Sem_Variable_Table Sem_Variable_Table;
struct Sem_Variable_Table
{
    
};

Sem_Variable_Table Sem_Check(AST_Node* root, Allocator* allocator)
{
    Sem_Variable_Table table = {0};
    
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

                
                
            }
            break;
        }
    }

    return table;
}

#endif
