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

typedef struct IR_Register_Table IR_Register_Table;
struct IR_Register_Table
{
    bool *inuse_table;
    i32 capacity;
};

typedef struct IR_Register IR_Register;
struct IR_Register
{
    i32 index;
};

IR_Register ir_register_alloc(IR_Register_Table* table)
{
    for (i32 i = 0; i < table->capacity; i++)
    {
        if (!table->inuse_table[i])
        {
            table->inuse_table[i] = true;
            IR_Register reg = { .index = i};
            return reg;
        }
    }

    i32 old_capacity = table->capacity;
    table->capacity *= 2;
    table->inuse_table = realloc(table->inuse_table, sizeof(i32) * table->capacity);
    for (i32 i = old_capacity; i < table->capacity; i++)
    {
        table->inuse_table[i] = false;
    }
    IR_Register reg = { .index = table->inuse_table[old_capacity] };
    return reg;
}


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

    bool has_label;
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

void ir_pretty_print(IR_Program* program, Allocator* allocator);

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

IR_Node* ir_emit_node(IR_Block* block, IR_Node_Type node_type)
{
    IR_Node_Array* node_array = &block->node_array;
    if (node_array->count + 1 >= node_array->capacity)
    {
        node_array->capacity = node_array->capacity == 0 ? 2 : node_array->capacity * 2;
        node_array->nodes = realloc(node_array->nodes, sizeof(IR_Node) * node_array->capacity);
    }

    IR_Node* node = &node_array->nodes[node_array->count++];
    node->type = node_type;
    return node;
}

IR_Node* ir_emit_label(IR_Block* block, String* label_name)
{
    if(block->has_label)
    {
        fprintf(stderr, "unable to add label to IR block. Already has a label");
        return NULL;
    }

    IR_Node* label = ir_emit_node(block, IR_NODE_LABEL);
    label->label.label_name = label_name; // @Study: Should the label habe a string view, or should it be owning?
    return label;
}

IR_Node* ir_emit_instruction(IR_Block* block, IR_Instruction_Type instruction_type)
{
    IR_Node* node = ir_emit_node(block, IR_NODE_INSTRUCTION);
    node->instruction.type = instruction_type;
    return node;
}

IR_UnOp* ir_emit_unop(IR_Block* block, IR_Register reg, IR_Op operator)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_UNOP);
    IR_UnOp* unop = &node->instruction.unop;

    IR_Value* value = &unop->value;
    value->type = VALUE_LOCATION;

    IR_Location* location = &value->loc;
    location->type = IR_LOCATION_REGISTER;
    location->reg = reg;

    unop->operator = operator;

    return unop;
}

IR_Push* ir_emit_push_int(IR_Block* block, i32 value)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_PUSH);
    IR_Push* push = &node->instruction.push;

    IR_Value* ir_value = &push->value;
    ir_value->type = VALUE_INT;
    ir_value->integer = value;
    
    return push;
}

IR_Move* ir_emit_move_lit_to_reg(IR_Block* block, i32 value, IR_Register reg)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_MOV);
    IR_Move* move = &node->instruction.move;

    IR_Value* ir_src = &move->src;
    ir_src->type = VALUE_INT;
    ir_src->integer = value;

    IR_Location* dst = &move->dst;
    dst->type = IR_LOCATION_REGISTER;
    dst->reg = reg;

    return move;
}

IR_Location ir_create_location_register(IR_Register reg)
{
    IR_Location location = { .type = IR_LOCATION_REGISTER };
    location.reg = reg;
    return location;
}

IR_Value ir_create_value_location(IR_Location location)
{
    IR_Value value = {.type = VALUE_LOCATION};
    value.loc = location;
    return value;
}

IR_BinOp* ir_emit_add(IR_Block* block, IR_Register left, IR_Register right)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_BINOP);
    IR_BinOp* binop = &node->instruction.binop;

    binop->left = ir_create_value_location(ir_create_location_register(left));
    binop->right = ir_create_value_location(ir_create_location_register(right));

    return binop;
}

IR_BinOp* ir_emit_sub(IR_Block* block, IR_Register left, IR_Register right)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_BINOP);
    IR_BinOp* binop = &node->instruction.binop;

    return binop;
}

IR_BinOp* ir_emit_mul(IR_Block* block, IR_Register left, IR_Register right)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_BINOP);
    IR_BinOp* binop = &node->instruction.binop;

    return binop;
}

IR_BinOp* ir_emit_div(IR_Block* block, IR_Register left, IR_Register right)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_BINOP);
    IR_BinOp* binop = &node->instruction.binop;

    return binop;
}

IR_Register ir_translate_expression(AST_Node* node, IR_Block* block, Allocator* allocator, IR_Register_Table* table)
{
    switch(node->type)
    {
    case  AST_NODE_NUMBER:
    {
        IR_Register reg = ir_register_alloc(table);
        ir_emit_move_lit_to_reg(block, node->number, reg);
        return reg;
    }
    case AST_NODE_BINARY:
    {
        IR_Register left_reg = ir_translate_expression(node->binary.left, block, allocator, table);
        IR_Register right_reg = ir_translate_expression(node->binary.right, block, allocator, table);

        Token_Type operator = node->binary.operator;

        switch(operator)
        {
        case TOKEN_PLUS:
        {
            IR_BinOp* binop = ir_emit_add(block, left_reg, right_reg);
        }
        break;
        case TOKEN_MINUS:
        {
            IR_BinOp* binop = ir_emit_sub(block, left_reg, right_reg);
        }
        break;
        case TOKEN_STAR:
        {
            IR_BinOp* binop = ir_emit_mul(block, left_reg, right_reg);
        }
        break;
        case TOKEN_SLASH:
        {
            IR_BinOp* binop = ir_emit_div(block, left_reg, right_reg);
        }
        break;
        }
    }
    case AST_NODE_UNARY:
    {
        IR_Register reg = ir_translate_expression(node->unary.expression, block, allocator, table);
        ir_emit_unop(block, reg, OP_SUB);
        return reg;
    }
    default:
    printf("%d\n", node->type);
    assert("Unsupported AST Node" && false);
    }
}

IR_Program ir_translate_ast(AST_Node* root_node, Allocator* allocator)
{
    IR_Program program =
        {
            .data_array  = {0},
            .block_array = {0},
        };

    IR_Register_Table register_table;
    IR_Block* block = ir_allocate_block(&program.block_array);
    
    String* name = string_allocate("MAIN", allocator);
    ir_emit_label(block, name);
    
    ir_translate_expression(root_node->program.expression, block, allocator, &register_table);

    ir_emit_instruction(block, IR_INS_RET);

    ir_pretty_print(&program, allocator);

    return program;
}

void ir_pretty_print_location(String_Builder* sb, IR_Location* location)
{
    switch(location->type)
    {
    case IR_LOCATION_REGISTER:
    {
        sb_appendf(sb, "%r%d", location->reg.index);    
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
    case VALUE_VARIABLE:
    {
        sb_appendf(sb, "\"%s\"", value->variable.name);
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
        IR_Block* block = &program->block_array.blocks[i];

        for (i32 j = 0; j < block->node_array.count; j++)
        {
            IR_Node* node = &block->node_array.nodes[j];

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
                    
                    sb_append(&sb, "move    ");

                    ir_pretty_print_value(&sb, src);
                    sb_append(&sb, ", ");
                    ir_pretty_print_location(&sb, dst);

                    sb_newline(&sb);
                }
                break;
                case IR_INS_PUSH:
                {
                    IR_Push* push = &instruction->push;
                    sb_append(&sb, "push    ");
                    ir_pretty_print_value(&sb, &push->value);
                    sb_newline(&sb);
                }
                break;
                case IR_INS_POP:
                {
                    IR_Pop* pop = &instruction->pop;
                    sb_append(&sb, "pop     ");
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
                        sb_append(&sb, "add     ");
                    }
                    break;
                    case OP_SUB:
                    {
                        sb_append(&sb, "sub     ");
                    }
                    break;
                    case OP_MUL:
                    {
                        sb_append(&sb, "mul     ");
                    }
                    break;
                    case OP_DIV:
                    {
                        sb_append(&sb, "div     ");
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
                    sb_append(&sb, "ret");
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
                        sb_append(&sb, "neg     ");
                    }
                    break;
                    default:
                    sb_append(&sb, "unop err");
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
