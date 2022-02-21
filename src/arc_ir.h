#ifndef ARC_IR_H
#define ARC_IR_H

typedef enum
{
    IR_PROGRAM,
    IR_SEQUENCE,
    IR_STATEMENT,
    IR_LABEL,
    IR_MOVE,
    IR_BIARY_OP,
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

typedef struct IR_Expression IR_Expression;
struct IR_Expression
{
    int i;
};

typedef struct IR_Node IR_Node;
struct IR_Node
{
    IR_Node_Type type;

    union
    {
        struct
        {
            IR_Expression* sequence;
        } program;
        struct
        {
            IR_Expression* statements;
            i32 count;
            i32 capacity;
        } sequence;
        struct
        {
            IR_Expression* node;
        } statement;
        struct
        {
            Symbol symbol;
        } label;
        struct
        {
            IR_Expression* src;
            IR_Expression* dst;
        } move;
        struct
        {
            IR_Expression* left;
            IR_Expression* right;
            Token_Type operator;
        } binary_op;
        struct
        {
            IR_Expression* exp;
            Token_Type operator;
        } unary_op;
        struct
        {
            IR_Expression* exp;
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

typedef struct IR_Block IR_Block;
struct IR_Block
{
    IR_Node* nodes;
    i32 count;
};

struct IR_Program
{
    IR_Block* blocks;
    i32 count;
};

IR_Node* ir_add_node(IR_Node_Type node_type, Allocator* allocator)
{
    IR_Node* node = allocator->allocate(allocator, sizeof(IR_Node));
    node->type = node_type;
    return node;
}

IR_Node* ir_codegen_ast(IR_Node* root_node, Allocator* allocator)
{
    IR_Node* program_node = ir_add_node(IR_PROGRAM, allocator);

    /* IR_Node* sequence = ir_add_node(IR_SEQUENCE, allocator); */

    
    
    return program_node;
}


#endif
