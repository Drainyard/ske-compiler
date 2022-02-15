#ifndef ARC_IR_H
#define ARC_IR_H

typedef enum
{
    IR_LABEL,
    IR_MOVE,
    IR_BIARY_NOP,
    IR_UNARY_OP,
    IR_MEM,
    IR_TEMP,
    IR_NAME,
    IR_CONST
} IR_Node_Type;

typedef struct Symbol Symbol;
struct Symbol
{
    String* name;
};

typedef struct Temp Temp;
struct Temp
{
    Symbol symbol;
};

typedef struct Label Label;
struct Label
{
    Symbol symbol;
};

typedef struct IR_Node IR_Node;
struct IR_Node
{
    IR_Node_Type type;

    union
    {
        struct
        {
            Symbol symbol;
        } label;
        struct
        {
            IR_Node* src;
            IR_Node* dst;
        } move;
        struct
        {
            IR_Node* left;
            IR_Node* right;
            Token_Type operator;
        } binary_op;
        struct
        {
            IR_Node* exp;
            Token_Type operator;
        } unary_op;
        struct
        {
            IR_Node* exp;
        } mem;
        struct
        {
            Temp temp;
        } temp;
        struct
        {
            Label label;
        } name;
        struct
        {
            i32 value;
        } const;
    };
};

IR_Tree* ir_codegen_ast(AST_Node* root_node, Allocator* allocator)
{
    
}


#endif
