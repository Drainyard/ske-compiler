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
    IR_INS_UNOP,
    IR_INS_COUNT
} IR_Instruction_Type;

typedef struct IR_Register IR_Register;
struct IR_Register
{
    char name[4];
};

typedef struct IR_Mem IR_Mem;
struct IR_Mem
{
    i32 dummy;
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

    const char name[32];
};

typedef struct
{
    IR_Data_Value* data;
    i32 count;
    i32 capacity;
} IR_Data_Array;

typedef struct IR_Value IR_Value;
struct IR_Value
{
    enum Value_Type
    {
        VALUE_LOCATION,
        VALUE_INT,
        VALUE_DATA_VALUE
    } type;

    union
    {
        i32           integer;
        IR_Data_Value data_value;
        IR_Location   loc;
    };
};

typedef struct IR_Move IR_Move;
struct IR_Move
{
    IR_Value src;
    IR_Location dst;
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
        IR_UnOp  unop;
    };
};

typedef struct IR_Label IR_Label;
struct IR_Label
{
    String* label_name;
};

typedef enum
{
    IR_NODE_INSTRUCTION,
    IR_NODE_LABEL,
} IR_Node_Type;

typedef struct IR_Node IR_Node;
struct IR_Node
{
    IR_Node_Type type;
    union
    {
        IR_Instruction instruction;
        IR_Label label;
    };
};

typedef struct
{
    IR_Node* nodes;
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

void ir_pretty_print_location(String_Builder* sb, IR_Location* location)
{
    switch(location->type)
    {
    case IR_LOCATION_REGISTER:
    {
        sb_appendf(sb, "%%s", location->reg.name);    
    }
    break;
    case IR_LOCATION_MEMORY:
    {
        
    }
    break;
    }
}

void ir_pretty_print_value(String_Builder* sb, IR_Value* value)
{
    switch(value->type)
    {
    case VALUE_LOCATION:
    {
        ir_pretty_print_location(sb, &value->loc);
    }
    break;
    case VALUE_INT:
    {
        sb_appendf(sb, "%d", value->integer);
    }
    break;
    case VALUE_DATA_VALUE:
    {
        sb_appendf(sb, "\"%s\"", value->data_value.name);
    }
    break;
    }
}

void ir_pretty_print(IR_Program* program, Allocator* allocator)
{
    String_Builder sb;
    sb_init(&sb, 256);

    // @Incomplete:
    // - Print data section

    // Print blocks
    for (i32 i = 0; i < program->block_array.count; i++)
    {
        sb_indent(&sb, 4);
        IR_Block* block = &program->block_array.blocks[i];

        for (i32 j = 0; j < block->node_array.count; j++)
        {
            IR_Node* node = &block->node_array.nodes[i];

            switch(node->type)
            {
            case IR_NODE_LABEL:
            {
                IR_Label* label = &node->label;
                sb_appendf(&sb, "%s:", label->label_name->str);
                sb_newline(&sb);
            }
            break;
            case IR_NODE_INSTRUCTION:
            {
                IR_Instruction* instruction = &node->instruction;
                sb_indent(&sb, 4);
                
                switch(instruction->type)
                {
                case IR_INS_MOV:
                {
                    IR_Move* move = &instruction->move;

                    IR_Value* src = &move->src;
                    IR_Location* dst = &move->dst;
                    
                    sb_append(&sb, "MOVE    ");

                    ir_pretty_print_value(&sb, src);
                    sb_append(&sb, ", ");
                    ir_pretty_print_location(&sb, dst);

                    sb_newline(&sb);
                }
                break;
                case IR_INS_PUSH:
                {
                    IR_Push* push = &instruction->push;
                    sb_append(&sb, "PUSH    ");
                    ir_pretty_print_value(&sb, &push->value);
                    sb_newline(&sb);
                }
                break;
                case IR_INS_POP:
                {
                    IR_Pop* pop = &instruction->pop;
                    sb_append(&sb, "POP     ");
                    ir_pretty_print_value(&sb, &pop->value);
                    sb_newline(&sb);
                }
                break;
                case IR_INS_BINOP:
                {
                    IR_BinOp* binop = &instruction->binop;

                    switch(binop->operator)
                    {
                    case OP_ADD:
                    {
                        sb_append(&sb, "ADD     ");
                    }
                    break;
                    case OP_SUB:
                    {
                        sb_append(&sb, "SUB     ");
                    }
                    break;
                    case OP_MUL:
                    {
                        sb_append(&sb, "MUL     ");
                    }
                    break;
                    case OP_DIV:
                    {
                        sb_append(&sb, "DIV     ");
                    }
                    break;
                    }

                    ir_pretty_print_value(&sb, &binop->left);
                    sb_append(&sb, ", ");
                    ir_pretty_print_value(&sb, &binop->right);
                    sb_newline(&sb);
                }
                break;
                case IR_INS_RET:
                {
                    sb_append(&sb, "RET");
                    sb_newline(&sb);
                }
                break;
                case IR_INS_UNOP:
                {
                    IR_UnOp* unop = &instruction->unop;
                    switch(unop->operator)
                    {
                    case OP_SUB:
                    {
                        sb_append(&sb, "NEG     ");
                    }
                    break;
                    default:
                    sb_append(&sb, "UNOP ERR");
                    sb_newline(&sb);
                    }

                    ir_pretty_print_value(&sb, &unop->value);
                }
                break;
                default:
                break;
                }
            }
            break;
            }
        }
    }
   
    String* string = sb_get_result(&sb, allocator);
    string_print(string);
}

#endif
