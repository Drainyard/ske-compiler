#ifndef SKE_IR_H
#define SKE_IR_H

// @Study: Should we make our IR structs into mega structs?
typedef enum
{
    IR_INS_MOV,
    IR_INS_PUSH,
    IR_INS_POP,
    IR_INS_JMP,
    IR_INS_BINOP,
    IR_INS_RET,
    IR_INS_CALL,
    IR_INS_UNOP,
    IR_INS_COMPARE,
    IR_INS_COUNT
} IR_Instruction_Type;

typedef struct IR_Register_Table IR_Register_Table;
struct IR_Register_Table
{
    bool *inuse_table;
    i32 capacity;
};

/*
An IR register is simply a virtual register, so it contains just an index (for now)
 */
typedef struct IR_Register IR_Register;
struct IR_Register
{
    i32 index;
};

typedef struct IR_Mem IR_Mem;
struct IR_Mem
{
    enum IR_Mem_Type
    {
        IR_MEM_REGISTER,
        IR_MEM_OFFSET,
        IR_MEM_SCALED,
        IR_MEM_BASE_SCALED
    } type;

    union
    {
        IR_Register reg;
        struct
        {
            IR_Register reg;
            i32         offset;
        } offset;
        struct
        {
            IR_Register reg;
            IR_Register register_offset;
            i32         scale;
        } scaled;
    };
};

typedef struct IR_Location IR_Location;
struct IR_Location
{
    enum IR_Location_Type
    {
        IR_LOCATION_REGISTER,
        IR_LOCATION_MEMORY
    } type;

    union
    {
        IR_Register reg;
        IR_Mem      mem;
    };
};

typedef struct IR_Data_Value IR_Data_Value;
struct IR_Data_Value
{
    enum
    {
        IR_DATA_STRING,
        IR_DATA_INT
    } type;

    union
    {
        String* string;
        i32     integer;
    };

    char name[32];
};

typedef struct
{
    IR_Data_Value* data;
    i32 count;
    i32 capacity;
} IR_Data_Array;

typedef struct IR_Variable IR_Variable;
struct IR_Variable
{
    char name[32];
};

typedef struct IR_Value IR_Value;
struct IR_Value
{
    enum Value_Type
    {
        VALUE_LOCATION,
        VALUE_INT,
        VALUE_VARIABLE
    } type;

    union
    {
        i32           integer;
        IR_Variable   variable;
        IR_Location   loc;
    };
};

typedef struct IR_Move IR_Move;
struct IR_Move
{
    IR_Value src;
    IR_Location dst;
};

typedef struct IR_Return IR_Return;
struct IR_Return
{
    IR_Register return_register;
    bool has_return_value;
};

typedef struct IR_Call IR_Call;
struct IR_Call
{
    i32 function_index;
};

typedef struct IR_Label IR_Label;
struct IR_Label
{
    String* label_name;
};

typedef struct IR_Jump IR_Jump;
struct IR_Jump
{
    IR_Label label;
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
    OP_NOT,
    OP_EQUAL,
    OP_ASSIGN,
    OP_BIT_OR,
    OP_BIT_AND,
    OP_OR,
    OP_AND,
    OP_LESS,
    OP_GREATER,
    OP_LESS_EQUAL,
    OP_GREATER_EQUAL,
    OP_NOT_EQUAL
} IR_Op;

typedef struct IR_BinOp IR_BinOp;
struct IR_BinOp
{
    IR_Value left;
    IR_Value right;

    IR_Register destination;

    IR_Op operator;
};

typedef struct IR_Compare IR_Compare;
struct IR_Compare
{
    IR_Value left;
    IR_Location right; // @Note: This is an x86 restriction, should we really conform to that in the IR?

    IR_Register destination;

    IR_Op operator;
};

typedef struct IR_UnOp IR_UnOp;
struct IR_UnOp
{
    IR_Value value;
    IR_Register destination;
    
    IR_Op operator;
};

typedef struct IR_Instruction IR_Instruction;
struct IR_Instruction
{
    IR_Instruction_Type type;
    union
    {
        IR_Move    move;
        IR_Return  ret;
        IR_Call    call;
        IR_Jump    jump;
        IR_Push    push;
        IR_Pop     pop;
        IR_BinOp   binop;
        IR_UnOp    unop;
        IR_Compare compare;
    };
};

typedef enum
{
    IR_NODE_INSTRUCTION,
    IR_NODE_LABEL,
    IR_NODE_FUNCTION_DECL,
} IR_Node_Type;

typedef struct IR_Function_Decl IR_Function_Decl;
struct IR_Function_Decl
{
    String* name;
    bool export;
};

typedef struct IR_Node IR_Node;
struct IR_Node
{
    IR_Node_Type type;
    union
    {
        IR_Instruction instruction;
        IR_Label label;
        IR_Function_Decl function;
    };
};

typedef struct IR_Node_Array IR_Node_Array;
struct IR_Node_Array
{
    IR_Node* nodes;
    i32 count;
    i32 capacity;
};

typedef struct IR_Block IR_Block;
struct IR_Block
{
    IR_Block* previous;
    IR_Block* next;

    IR_Node_Array node_array;

    bool has_label;

    struct IR_Program* parent_program;
};

typedef struct
{
    IR_Block* blocks;
    i32 count;
    i32 capacity;
} IR_Block_Array;

typedef struct IR_Function IR_Function;
struct IR_Function
{
    String_View name;
    bool exported;
};

typedef struct IR_Function_Array IR_Function_Array;
struct IR_Function_Array
{
    IR_Function* functions;
    i32 count;
    i32 capacity;
};

typedef struct IR_Program IR_Program;
struct IR_Program
{
    IR_Data_Array data_array;
    IR_Block_Array block_array;
    IR_Function_Array function_array;
};

String* ir_pretty_print(IR_Program* program, Allocator* allocator);


#endif
