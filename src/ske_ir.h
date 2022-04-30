#ifndef ARC_IR_H
#define ARC_IR_H


// @Study: Should we make our IR structs into mega structs?
typedef enum
{
    IR_INS_MOV,
    IR_INS_PUSH,
    IR_INS_POP,
    IR_INS_BINOP,
    IR_INS_RET,
    IR_INS_UnOp,
    IR_INS_COUNT
} IR_Instruction_Type;

typedef struct IR_Register IR_Register;
struct IR_Register
{
    char name[4];
};

typedef struct IR_Value IR_Value;
struct IR_Value
{
    enum Value_Type
    {
        VALUE_REGISTER,
        VALUE_INT,
        VALUE_STRING
    } Type;

    union
    {
        i32 value;
        IR_Register reg;
    };
};

typedef struct IR_Move IR_Move;
struct IR_Move
{
    IR_Value src;
    IR_Register dst;
};

typedef struct IR_Push IR_Push;
struct IR_Push
{
    IR_Value value;
};

typedef struct IR_Pop IR_Pop;
struct IR_Pop
{
    IR_Value value;
};

typedef enum
{
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
} IR_Op;

typedef struct IR_BinOp IR_BinOp;
struct IR_BinOp
{
    IR_Value left;
    IR_Value right;

    IR_Op operator;
};

typedef struct IR_UnOp IR_UnOp;
struct IR_UnOp
{
    IR_Value value;
    IR_Op operator;
};


typedef struct IR_Instruction IR_Instruction;
struct IR_Instruction
{
    IR_Instruction_Type type;
    union
    {
        IR_Move  move;
        IR_Push  push;
        IR_Pop   pop;
        IR_BinOp binop;
        IR_UnOp   neg;
    };
};

typedef struct IR_Label IR_Label;
struct IR_Label
{
    String* label_name;
};

typedef struct
{
    struct IR_Node* nodes;
    i32 count;
    i32 capacity;
} IR_Node_Array;

typedef struct IR_Block IR_Block;
struct IR_Block
{
    struct IR_Block* previous;
    struct IR_Block* next;

    IR_Node_Array node_array;
};

typedef enum
{
    IR_NODE_INSTRUCTION,
    IR_NODE_LABEL,
    IR_NODE_BLOCK
} IR_Node_Type;

typedef struct IR_Node IR_Node;
struct IR_Node
{
    IR_Node_Type type;
    union
    {
        IR_Instruction instruction;
        IR_Label lable;
    };
};

typedef enum
{
    IR_DATA_STRING,
    IR_DATA_INT
} IR_Data_Type;


typedef struct IR_Data_Value IR_Data_Value;
struct IR_Data_Value
{
    IR_Data_Type type;
    union
    {
        String* string;
        i32     integer;
    };
};

typedef struct
{
    IR_Data_Value* data;
    i32 count;
    i32 capacity;
} IR_Data_Array;

typedef struct
{
    IR_Block* blocks;
    i32 count;
    i32 capacity;
} IR_Block_Array;

typedef struct IR_Program IR_Program;
struct IR_Program
{
    IR_Data_Array data_array;
    IR_Block_Array block_array;
};

IR_Block* ir_allocate_block(IR_Block_Array* block_array)
{
    if (block_array->count + 1 >= block_array->capacity)
    {
        block_array->capacity = block_array->capacity == 0 ? 2 : block_array->capacity * 2;
        block_array->blocks = realloc(block_array->blocks, sizeof(IR_Block) * block_array->capacity);
    }
    
    IR_Block* block = &block_array->blocks[block_array->count++];
    block->previous            = NULL;
    block->next                = NULL;
    block->node_array.count    = 0;
    block->node_array.nodes    = NULL;
    block->node_array.capacity = 0;

    return block;
}

IR_Node* ir_add_instruction_to_block(IR_Block* block, IR_Instruction_Type instruction_type)
{
    IR_Node_Array* node_array = &block->node_array;
    if (node_array->count + 1 >= node_array->capacity)
    {
        node_array->capacity = node_array->capacity == 0 ? 2 : node_array->capacity * 2;
        node_array->nodes = realloc(node_array->nodes, sizeof(IR_Node) * node_array->capacity);
    }

    IR_Node* node = &node_array->nodes[node_array->count++];
    node->type = IR_NODE_INSTRUCTION;
    node->instruction.type = instruction_type;
    return node;
}

IR_Program ir_translate_ast(AST_Node* root_node)
{
    IR_Program program =
        {
            .data_array  = {0},
            .block_array = {0},
        };

    return program;
}

/* IR_Node* ir_add_node(IR_Node_Type node_type, Allocator* allocator) */
/* { */
/*     IR_Node* node = allocator->allocate(allocator, sizeof(IR_Node)); */
/*     node->type = node_type; */
/*     return node; */
/* } */

/* IR_Node* ir_codegen_ast(IR_Node* root_node, Allocator* allocator) */
/* { */
/*     IR_Node* program_node = ir_add_node(IR_PROGRAM, allocator); */

/*     /\* IR_Node* sequence = ir_add_node(IR_SEQUENCE, allocator); *\/ */

    
    
/*     return program_node; */
/* } */


#endif
