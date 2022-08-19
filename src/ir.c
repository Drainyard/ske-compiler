IR_Register IR_register_alloc(IR_Register_Table* table)
{
    for (i32 i = 0; i < table->capacity; i++)
    {
        if (!table->inuse_table[i])
        {
            table->inuse_table[i] = true;
            IR_Register reg = { .gpr_index = i};
            return reg;
        }
    }

    i32 old_capacity = table->capacity;
    table->capacity = table->capacity == 0 ? 256 : table->capacity * 2;
    table->inuse_table = realloc(table->inuse_table, sizeof(bool) * table->capacity);
    for (i32 i = old_capacity; i < table->capacity; i++)
    {
        table->inuse_table[i] = false;
    }
    IR_Register reg = { .gpr_index = old_capacity };
    table->inuse_table[old_capacity] = true;
    return reg;
}

static void IR_error(char* format, ...)
{
    fprintf(stderr, "\x1b[1;31m");
    va_list(ap);
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fprintf(stderr, "\x1b[0m\n");

    exit(1);
}

static char* IR_type_to_string(IR_Node_Type type)
{
    switch(type)
    {
    case IR_NODE_INSTRUCTION:
    return "instruction";
    case IR_NODE_LABEL:
    return "label";
    case IR_NODE_FUNCTION_DECL:
    return "function declaration";
    }
    return NULL;
}

static char* IR_instruction_type_to_string(IR_Instruction* instruction)
{
    switch(instruction->type)
    {
    case IR_INS_MOV:
    return "mov";
    case IR_INS_PUSH:
    return "push";
    case IR_INS_POP:
    return "pop";
    case IR_INS_JUMP:
    return "jump";
    case IR_INS_BINOP:
    return "binop";
    case IR_INS_RET:
    return "return";
    case IR_INS_CALL:
    return "call";
    case IR_INS_UNOP:
    return "unop";
    case IR_INS_COMPARE:
    return "compare";
    default: IR_error("Unknown instruction type.");
    }
    return NULL;
}

static char* IR_node_to_string(IR_Node* node)
{
    switch(node->type)
    {
    case IR_NODE_INSTRUCTION:
    {
        return IR_instruction_type_to_string(&node->instruction);
    }
    break;
    case IR_NODE_LABEL:
    {
        return node->label.label_name->str;
    }
    break;
    case IR_NODE_FUNCTION_DECL:
    {
        return node->function.name->str;
    }
    break;
    }
    return NULL;
}

String* IR_generate_label_name(IR_Program* program, Allocator* allocator)
{
    return string_createf(allocator, ".Label_%d", program->label_counter++);
}

IR_Block* IR_allocate_block(IR_Program* program)
{
    IR_Block_Array* block_array = &program->block_array;
    if (block_array->count + 1 > block_array->capacity)
    {
        block_array->capacity = block_array->capacity == 0 ? 256 : block_array->capacity * 2;
        block_array->blocks = realloc(block_array->blocks, sizeof(IR_Block) * block_array->capacity);
    }

    IR_Block* block = &block_array->blocks[block_array->count++];
    block->parent_program      = program;
    block->block_address       = (IR_Block_Address) { .address = block_array->count - 1 };
    block->previous            = NULL;
    block->next                = NULL;
    block->has_label           = false;
    block->node_array.count    = 0;
    block->node_array.nodes    = NULL;
    block->node_array.capacity = 0;

    return block;
}

IR_Node* IR_emit_node(IR_Block* block, IR_Node_Type node_type)
{
    IR_Node_Array* node_array = &block->node_array;
    if (node_array->count + 1 > node_array->capacity)
    {
        node_array->capacity = node_array->capacity == 0 ? 256 : node_array->capacity * 2;
        node_array->nodes = realloc(node_array->nodes, sizeof(IR_Node) * node_array->capacity);
    }

    IR_Node* node = &node_array->nodes[node_array->count++];
    node->type = node_type;
    return node;
}

void IR_add_function(IR_Program* program, String* name, bool exported)
{
    IR_Function_Array* array = &program->function_array;
    if (array->count + 1 > array->capacity)
    {
        array->capacity = array->capacity == 0 ? 256 : array->capacity * 2;
        array->functions = realloc(array->functions, sizeof(IR_Function) * array->capacity);
    }

    IR_Function* function = &array->functions[array->count++];
    function->name = sv_create(name);
    function->exported = exported;
}

i32 IR_find_function(IR_Program* program, String* name)
{
    IR_Function_Array functions = program->function_array;
    for (i32 i = 0; i < functions.count; i++)
    {
        String_View fun_name = functions.functions[i].name;
        if (string_equal(name, fun_name.string))
        {
            return i;
        }
    }
    return -1;
}

String_View* IR_get_function_name(IR_Program* program, i32 index)
{
    if (index == -1) return NULL;
    if (program->function_array.count <= index) return NULL;
    return &program->function_array.functions[index].name;
}

IR_Node* IR_emit_function_decl(IR_Block* block, String* name, bool export)
{
    IR_Node* function_decl = IR_emit_node(block, IR_NODE_FUNCTION_DECL);
    function_decl->function.export = export;
    function_decl->function.name   = name;
    IR_add_function(block->parent_program, name, export);

    return function_decl;
}

IR_Label* IR_emit_label(IR_Block* block, String* label_name, Allocator* allocator)
{
    if(block->has_label)
    {
        fprintf(stderr, "unable to add label to IR block. Already has a label\n");
        return NULL;
    }

    IR_Node* label = IR_emit_node(block, IR_NODE_LABEL);
    label->label.label_name = label_name; // @Study: Should the label have a string view, or should it be owning?
    return &label->label;
}

IR_Node* IR_emit_instruction(IR_Block* block, IR_Instruction_Type instruction_type)
{
    IR_Node* node = IR_emit_node(block, IR_NODE_INSTRUCTION);
    node->instruction.type = instruction_type;
    return node;
}

IR_Node* IR_emit_return(IR_Block* block, IR_Register* reg, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_RET);
    IR_Return* ret = &node->instruction.ret;

    if (reg)
    {
        ret->return_register = *reg;
        ret->has_return_value = true;
    }
    else
    {
        ret->has_return_value = false;
    }

    return node;
}

IR_UnOp* IR_emit_unop(IR_Block* block, IR_Register reg, IR_Op operator, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_UNOP);
    IR_UnOp* unop = &node->instruction.unop;

    IR_Value* value = &unop->value;
    value->type = VALUE_LOCATION;

    IR_Location* location = &value->loc;
    location->type = IR_LOCATION_REGISTER;
    location->reg = reg;

    unop->operator = operator;

    return unop;
}

IR_Push* IR_emit_push_int(IR_Block* block, i32 value, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_PUSH);
    IR_Push* push = &node->instruction.push;

    IR_Value* IR_value = &push->value;
    IR_value->type = VALUE_INT;
    IR_value->integer = value;
    
    return push;
}

IR_Move* IR_emit_move_reg_to_reg(IR_Block* block, IR_Register src_reg, IR_Register dst_reg, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_MOV);
    IR_Move* move = &node->instruction.move;

    IR_Value* src = &move->src;
    src->type = IR_LOCATION_REGISTER;
    src->loc.reg = src_reg;

    IR_Location* dst = &move->dst;
    dst->type = IR_LOCATION_REGISTER;
    dst->reg = dst_reg;

    return move;
}

IR_Move* IR_emit_move_lit_to_reg(IR_Block* block, i32 value, IR_Register reg, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_MOV);
    IR_Move* move = &node->instruction.move;

    IR_Value* IR_src = &move->src;
    IR_src->type = VALUE_INT;
    IR_src->integer = value;

    IR_Location* dst = &move->dst;
    dst->type = IR_LOCATION_REGISTER;
    dst->reg = reg;

    return move;
}

IR_Location IR_create_location_register(IR_Register reg)
{
    IR_Location location = { .type = IR_LOCATION_REGISTER };
    location.reg = reg;
    return location;
}

IR_Value IR_create_value_location(IR_Location location)
{
    IR_Value value = {.type = VALUE_LOCATION};
    value.loc = location;
    return value;
}

IR_Value IR_create_value_register(IR_Register reg)
{
    return IR_create_value_location(IR_create_location_register(reg));
}

IR_Value IR_create_value_number(i32 number)
{
    IR_Value value = { .type = VALUE_INT };
    value.integer = number;
    return value;
}

IR_BinOp* IR_emit_binop(IR_Block* block, IR_Register left, IR_Register right, IR_Op operator, IR_Register_Table* table, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_BINOP);
    IR_BinOp* binop = &node->instruction.binop;

    binop->left = IR_create_value_location(IR_create_location_register(left));
    binop->right = IR_create_value_location(IR_create_location_register(right));

    switch(operator)
    {
    case OP_SUB:
    {
        binop->destination = binop->left.loc.reg;
    }
    break;
    default:
    {
        binop->destination = binop->right.loc.reg;
    }
    break;
    }

    binop->operator = operator;

    return binop;
}

IR_Op IR_map_operator(Token_Type source)
{
    switch(source)
    {
    case TOKEN_PLUS:
    return OP_ADD;
    case TOKEN_MINUS:
    return OP_SUB;
    case TOKEN_STAR:
    return OP_MUL;
    case TOKEN_SLASH:
    return OP_DIV;
    case TOKEN_BANG:
    return OP_NOT;
    case TOKEN_EQUAL_EQUAL:
    return OP_EQUAL;
    case TOKEN_EQUAL:
    return OP_ASSIGN;
    case TOKEN_BANG_EQUAL:
    return OP_NOT_EQUAL;
    case TOKEN_PIPE:
    return OP_BIT_OR;
    case TOKEN_PIPE_PIPE:
    return OP_OR;
    case TOKEN_AMPERSAND:
    return OP_BIT_AND;
    case TOKEN_AMPERSAND_AMPERSAND:
    return OP_AND;
    case TOKEN_LESS:
    return OP_LESS;
    case TOKEN_LESS_EQUAL:
    return OP_LESS_EQUAL;
    case TOKEN_GREATER:
    return OP_GREATER;
    case TOKEN_GREATER_EQUAL:
    return OP_GREATER_EQUAL;
    default: IR_error("Invalid operator %s.", token_type_to_string(source)); exit(1);
    }
}

IR_Jump* IR_emit_jump(IR_Block* block, IR_Label label, IR_Jump_Type jump_type, IR_Block_Address block_address, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_JUMP);
    IR_Jump* jump = &node->instruction.jump;

    jump->type = jump_type;
    jump->address = block_address;

    return jump;
}

IR_Compare* IR_emit_comparison(IR_Block* block, IR_Value left, IR_Location right, IR_Op operator, IR_Register_Table* table, Allocator* allocator)
{
    IR_Node* node = IR_emit_instruction(block, IR_INS_COMPARE);
    IR_Compare* compare = &node->instruction.compare;

    compare->left = left;
    compare->right = right;
    compare->operator = operator;
    compare->destination = compare->right.reg;

    return compare;
}

IR_Block* IR_get_block(IR_Program* program, IR_Block_Address address)
{
    IR_Block_Array* blocks = &program->block_array;
    if (address.address >= 0 && address.address < blocks->count)
    {
        return &blocks->blocks[address.address];
    }
    return NULL;
}

IR_Node* IR_get_node(IR_Block* block, i32 index)
{
    if (index >= 0 && index < block->node_array.count)
    {
        return &block->node_array.nodes[index];
    }
    return NULL;
}

IR_Block* IR_get_current_block(IR_Program* program)
{
    if (program->block_array.count == 0)
    {
        return NULL;
    }

    return &program->block_array.blocks[program->block_array.count - 1];
}


IR_Register IR_translate_expression(AST_Node* node, IR_Block* block, IR_Block* end_block, Allocator* allocator, IR_Register_Table* table)
{
    switch(node->type)
    {
    case  AST_NODE_LITERAL:
    {
        IR_Register reg = IR_register_alloc(table);
        AST_Literal* literal = &node->literal;
        switch(node->literal.type)
        {
        case LIT_INT:
        {
            IR_emit_move_lit_to_reg(block, literal->i, reg, allocator);            
        }
        break;
        case LIT_FLOAT:
        {}
        break;
        case LIT_STRING:
        {}
        break;
        }

        return reg;
    }
    case AST_NODE_BINARY:
    {
        IR_Register left_reg = IR_translate_expression(node->binary.left, block, NULL, allocator, table);
        IR_Register right_reg = IR_translate_expression(node->binary.right, block, NULL, allocator, table);

        Token_Type operator = node->binary.operator;

        switch(operator)
        {
        case TOKEN_PLUS:
        case TOKEN_MINUS:
        case TOKEN_STAR:
        case TOKEN_SLASH:
        case TOKEN_BANG:
        case TOKEN_EQUAL:
        case TOKEN_PIPE:
        case TOKEN_AMPERSAND:
        {
            IR_BinOp* binop = IR_emit_binop(block, left_reg, right_reg, IR_map_operator(operator), table, allocator);
            return binop->destination;
        }
        case TOKEN_EQUAL_EQUAL:
        case TOKEN_PIPE_PIPE:
        case TOKEN_AMPERSAND_AMPERSAND:
        case TOKEN_LESS:
        case TOKEN_GREATER:
        case TOKEN_LESS_EQUAL:
        case TOKEN_GREATER_EQUAL:
        case TOKEN_BANG_EQUAL:
        {
            IR_Value left_val = IR_create_value_location(IR_create_location_register(left_reg));
            IR_Location right_loc = IR_create_location_register(right_reg);

            bool left_is_zero = left_val.type == VALUE_INT && left_val.integer;
            
            IR_Jump_Type jump_type = JMP_ALWAYS;
            switch(operator)
            {
            case TOKEN_EQUAL_EQUAL:
            {
                if (left_is_zero)
                {
                    jump_type = JMP_ZERO;
                }
                else
                {
                    jump_type = JMP_NOT_EQUAL;
                }
            }
            break;
            case TOKEN_LESS:
            {
                jump_type = JMP_GREATER_EQUAL;
                /* jump_type = JMP_LESS; */
            }
            break;
            case TOKEN_GREATER:
            {
                jump_type = JMP_LESS_EQUAL;
                /* jump_type = JMP_GREATER; */
            }
            break;
            case TOKEN_LESS_EQUAL:
            {
                jump_type = JMP_GREATER;
                /* jump_type = JMP_LESS_EQUAL; */
            }
            break;
            case TOKEN_GREATER_EQUAL:
            {
                jump_type = JMP_LESS;
                /* jump_type = JMP_GREATER_EQUAL; */
            }
            break;
            case TOKEN_BANG_EQUAL:
            {
                if (left_is_zero)
                {
                    jump_type = JMP_NOT_ZERO;
                }
                else
                {
                    jump_type = JMP_EQUAL;
                }
            }
            break;
            default: IR_error("Invalid comparison operator %s", token_type_to_string(operator));
            }

            IR_Compare* compare = IR_emit_comparison(block, left_val, right_loc, IR_map_operator(operator), table, allocator);

            // @Incomplete: Do some kind of short circuiting? Right now this won't work with &&, ||

            if (end_block)
            {
                IR_Node* node = IR_get_node(end_block, 0);
                IR_Label* end_label = &node->label;
                IR_emit_jump(block, *end_label, jump_type, end_block->block_address, allocator);
            }
            else
            {
                // @Incomplete: Emit set instruction (setcc in x86_64)
            }

            return compare->destination;
        }
        default:
        IR_error("Unsupported operator for binary operations %s\n", token_type_to_string(operator));
        break;
        }
    }
    case AST_NODE_UNARY:
    {
        IR_Register reg = IR_translate_expression(node->unary.expression, block, NULL, allocator, table);
        Token_Type operator = node->unary.operator;
        switch(operator)
        {
        case TOKEN_MINUS:
        {
            IR_emit_unop(block, reg, OP_SUB, allocator);
        }
        break;
        case TOKEN_BANG:
        {
            IR_emit_unop(block, reg, OP_NOT, allocator);
        }
        break;
        default: IR_error("Unsupported operator for unary operations %s\n", token_type_to_string(operator));
        }
        
        return reg;
    }
    default:
    assert("Unsupported AST Node" && false);
    }
}

IR_Block* IR_translate_block(IR_Block* block, AST_Node* body, Allocator* allocator, IR_Register_Table* register_table);

IR_Block* IR_translate_statement(IR_Block* block, AST_Node* statement, Allocator* allocator, IR_Register_Table* register_table)
{
    switch(statement->type)
    {
    case AST_NODE_RETURN:
    {
        if (statement->return_statement.expression)
        {
            IR_Register reg = IR_translate_expression(statement->return_statement.expression, block, NULL, allocator, register_table);
            IR_Register dst = IR_register_alloc(register_table);
                
            IR_emit_move_reg_to_reg(block, reg, dst, allocator);
            IR_emit_return(block, &dst, allocator);
        }
        else
        {
            IR_emit_return(block, NULL, allocator);
        }
        return block;
    }
    break;
    case AST_NODE_IF:
    {
        AST_Node* ast_condition = statement->if_statement.condition;

        AST_Node* ast_then_arm = statement->if_statement.then_arm;
        if (ast_then_arm->type != AST_NODE_BLOCK)
        {
            IR_error("Then arm for if statement has to be a block, was %s", AST_type_string(ast_then_arm->type));
        }

        IR_Block* then_block = IR_allocate_block(block->parent_program);
        IR_Block* end_block = IR_allocate_block(block->parent_program);

        IR_Label* end_label = IR_emit_label(end_block, IR_generate_label_name(block->parent_program, allocator), allocator);

        IR_Register cond_register = IR_translate_expression(ast_condition, block, end_block, allocator, register_table);
        IR_Block* new_block = end_block;

        if (ast_condition->type == AST_NODE_LITERAL)
        {
            IR_emit_comparison(block, IR_create_value_number(0), IR_create_location_register(cond_register), OP_EQUAL, register_table, allocator);
            IR_emit_jump(block, *end_label, JMP_EQUAL, end_block->block_address, allocator);

            IR_translate_block(then_block, ast_then_arm, allocator, register_table);     
        }
        else if (ast_condition->type == AST_NODE_BINARY)
        {
            IR_translate_block(then_block, ast_then_arm, allocator, register_table);
        }

        AST_Node* ast_else_arm = statement->if_statement.else_arm;
        if (ast_else_arm)
        {
            // @Incomplete: This will not be enough if the else arm is an if-statement, in that case, we need to re-translate some other way.
            // In this case, we probably just need a IR_translate_statement function, that does whatever this function does instead,
            // and then explicitly call IR_translate_block on blocks instead of what we are currently doing.
            switch(ast_else_arm->type)
            {
            case AST_NODE_BLOCK:
            {
                new_block = IR_translate_block(end_block, ast_else_arm, allocator, register_table);                
            }
            break;
            case AST_NODE_IF:
            {
                new_block = IR_translate_statement(end_block, ast_else_arm, allocator, register_table);
            }
            break;
            default: compiler_bug("Invalid statement type for else statement %s.", AST_type_string(ast_else_arm->type));
            }
        }
        return new_block;                    
    }
    break;
    case AST_NODE_CALL:
    {
        String* fun_name = statement->fun_call.name;
        i32 index = IR_find_function(block->parent_program, fun_name);
            
        if (index != -1)
        {
            IR_Node* call = IR_emit_instruction(block, IR_INS_CALL);
            call->instruction.call.function_index = index;
        }
        else
        {
            compiler_bug("Unknown function %s.", fun_name->str);
        }
    }
    break;
    case AST_NODE_LITERAL:
    case AST_NODE_BINARY:
    case AST_NODE_UNARY:
    {
        IR_translate_expression(statement, block, NULL, allocator, register_table);
    }
    break;
    default: compiler_bug("Invalid AST node type %s.", AST_type_string(statement->type));
    }

    return block;
}

IR_Block* IR_translate_block(IR_Block* block, AST_Node* body, Allocator* allocator, IR_Register_Table* register_table)
{
    AST_Node_List list = body->block.declarations;

    IR_Block* used_block = block;

    for (i32 i = 0; i < list.count; i++)
    {
        AST_Node* node = list.nodes[i];
        used_block = IR_translate_statement(used_block, node, allocator, register_table);
    }
    return used_block;
}

void IR_translate_program(IR_Program* program, AST_Node* ast_program, Allocator* allocator, IR_Register_Table* register_table)
{
    AST_Node_List declarations = ast_program->program.declarations;

    for (i32 i = 0; i < declarations.count; i++)
    {
        AST_Node* node = declarations.nodes[i];

        switch(node->type)
        {
        case AST_NODE_FUN_DECL:
        {
            IR_Block* block = IR_allocate_block(program);
            IR_emit_function_decl(block, node->fun_decl.name, true);

            IR_translate_block(block, node->fun_decl.body, allocator, register_table);
        }
        break;
        case AST_NODE_LITERAL:
        case AST_NODE_BINARY:
        case AST_NODE_UNARY:
        {
            IR_Block* block = IR_get_current_block(program);
            
            String* name = string_allocate("main", allocator);
            IR_emit_function_decl(block, name, true);
            IR_translate_expression(node, block, NULL, allocator, register_table);
            IR_emit_instruction(block, IR_INS_RET);
        }
        break;
        default: compiler_bug("Invalid AST node type %s.", AST_type_string(node->type));
        }
    }
}

IR_Program IR_translate_ast(AST_Node* root_node, Allocator* allocator)
{
    IR_Program program =
        {
            .data_array  = {0},
            .block_array = {0},
            .function_array = {0},
            .label_counter = 0
        };

    IR_Register_Table* register_table = malloc(sizeof(IR_Register_Table));
    register_table->capacity = 0;
    register_table->inuse_table = NULL;

    IR_translate_program(&program, root_node, allocator, register_table);

    return program;
}

void IR_pretty_print_register(String_Builder* sb, IR_Register* reg)
{
    switch(reg->type)
    {
    case IR_GPR:
    {
        sb_appendf(sb, "%r%d", reg->gpr_index);
    }
    break;
    case IR_SPECIAL:
    {
        switch(reg->special_register)
        {
        case SPECIAL_STACK_POINTER:
        {
            sb_append(sb, "rsp");
        }
        break;
        case SPECIAL_STACK_BASE:
        {
            sb_append(sb, "rsb");
        }
        break;
        case SPECIAL_INSTRUCTION_POINTER:
        {
            sb_append(sb, "rip");
        }
        break;
        }
    }
    break;
    }
}

void IR_pretty_print_location(String_Builder* sb, IR_Location* location)
{
    switch(location->type)
    {
    case IR_LOCATION_REGISTER:
    {
        IR_pretty_print_register(sb, &location->reg);
    }
    break;
    case IR_LOCATION_MEMORY:
    {
        
    }
    break;
    }
}

void IR_pretty_print_value(String_Builder* sb, IR_Value* value)
{
    switch(value->type)
    {
    case VALUE_LOCATION:
    {
        IR_pretty_print_location(sb, &value->loc);
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

void IR_pretty_print_instruction(String_Builder* sb, IR_Instruction* instruction, IR_Program* program)
{
    sb_indent(sb, 8);
                
    switch(instruction->type)
    {
    case IR_INS_MOV:
    {
        IR_Move* move = &instruction->move;

        IR_Value* src = &move->src;
        IR_Location* dst = &move->dst;

        IR_pretty_print_location(sb, dst);
        sb_append(sb, " := ");
        IR_pretty_print_value(sb, src);

        sb_newline(sb);
    }
    break;
    case IR_INS_PUSH:
    {
        IR_Push* push = &instruction->push;
        sb_append(sb, "push(");
        IR_pretty_print_value(sb, &push->value);
        sb_append(sb, ")");
        sb_newline(sb);
    }
    break;
    case IR_INS_POP:
    {
        IR_Pop* pop = &instruction->pop;
        sb_append(sb, "pop(");
        IR_pretty_print_value(sb, &pop->value);
        sb_append(sb, ")");
        sb_newline(sb);
    }
    break;
    case IR_INS_JUMP:
    {
        IR_Jump* jump = &instruction->jump;
        switch(jump->type)
        {
        case JMP_ALWAYS:
        {
            sb_append(sb, "jmp ");
        }
        break;
        case JMP_EQUAL:
        {
            sb_append(sb, "je ");
        }
        break;
        case JMP_ZERO:
        {
            sb_append(sb, "jz ");
        }
        break;
        case JMP_NOT_EQUAL:
        {
            sb_append(sb, "jne ");
        }
        break;
        case JMP_NOT_ZERO:
        {
            sb_append(sb, "jnz ");
        }
        break;
        case JMP_LESS:
        {
            sb_append(sb, "jl ");
        }
        break;
        case JMP_LESS_EQUAL:
        {
            sb_append(sb, "jle ");
        }
        break;
        case JMP_GREATER:
        {
            sb_append(sb, "jg ");
        }
        break;
        case JMP_GREATER_EQUAL:
        {
            sb_append(sb, "jge ");
        }
        break;
        }

        IR_Block_Address address = jump->address;
        if (program)
        {
            IR_Block* block = &program->block_array.blocks[address.address];
            IR_Node* first_node = &block->node_array.nodes[0];
            IR_Label* label = &first_node->label;
            sb_append(sb, label->label_name->str);
        }
        
        sb_newline(sb);
    }
    break;
    case IR_INS_BINOP:
    {
        IR_BinOp* binop = &instruction->binop;

        IR_pretty_print_register(sb, &binop->destination);
        sb_append(sb, " := ");
        IR_pretty_print_value(sb, &binop->left);

        switch(binop->operator)
        {
        case OP_ADD:
        {
            sb_append(sb, " + ");
        }
        break;
        case OP_SUB:
        {
            sb_append(sb, " - ");
        }
        break;
        case OP_MUL:
        {
            sb_append(sb, " * ");
        }
        break;
        case OP_DIV:
        {
            sb_append(sb, " / ");
        }
        break;
        case OP_NOT_EQUAL:
        {
            sb_append(sb, " != ");
        }
        break;
        case OP_EQUAL:
        {
            sb_append(sb, " == ");
        }
        break;
        case OP_ASSIGN:
        {
            sb_append(sb, " = ");
        }
        break;
        case OP_BIT_OR:
        {
            sb_append(sb, " | ");
        }
        break;
        case OP_BIT_AND:
        {
            sb_append(sb, " & ");
        }
        break;
        default: IR_error("Unsupported operator for binary operation\n");
        }
        IR_pretty_print_value(sb, &binop->right);

        sb_newline(sb);
    }
    break;
    case IR_INS_RET:
    {
        IR_Return* ret = &instruction->ret;
        sb_append(sb, "ret");
        if (ret->has_return_value)
        {
            sb_append(sb, " ");
            IR_pretty_print_register(sb, &ret->return_register);
        }
                    
        sb_newline(sb);
    }
    break;
    case IR_INS_CALL:
    {
        IR_Call* call = &instruction->call;
        String_View name = program->function_array.functions[call->function_index].name;
        sb_appendf(sb, "call %s\n", name.string->str);
    }
    break;
    case IR_INS_UNOP:
    {
        IR_UnOp* unop = &instruction->unop;

        IR_pretty_print_value(sb, &unop->value);
        sb_append(sb, " := ");
        switch(unop->operator)
        {
        case OP_SUB:
        {
            sb_append(sb, "-");
        }
        break;
        case OP_NOT:
        {
            sb_append(sb, "!");
        }
        break;
        default: IR_error("Unsupported operator for unary operation\n");
        }
        IR_pretty_print_value(sb, &unop->value);
        sb_append(sb, "");
        sb_newline(sb);
    }
    break;
    case IR_INS_COMPARE:
    {
        IR_Compare* compare = &instruction->compare;

        IR_pretty_print_register(sb, &compare->destination);
        sb_append(sb, " := ");
        IR_pretty_print_value(sb, &compare->left);
                    
        switch(compare->operator)
        {
        case OP_OR:
        {
            sb_append(sb, " || ");
        }
        break;
        case OP_AND:
        {
            sb_append(sb, " && ");
        }
        break;
        case OP_LESS:
        {
            sb_append(sb, " < ");
        }
        break;
        case OP_GREATER:
        {
            sb_append(sb, " > ");
        }
        break;
        case OP_LESS_EQUAL:
        {
            sb_append(sb, " <= ");
        }
        break;
        case OP_GREATER_EQUAL:
        {
            sb_append(sb, " >= ");
        }
        break;
        case OP_EQUAL:
        {
            sb_append(sb, " == ");
        }
        break;
        case OP_NOT_EQUAL:
        {
            sb_append(sb, " != ");
        }
        break;
        default: IR_error("Unsupported operator for compare operation\n");
        }
        IR_pretty_print_location(sb, &compare->right);
        sb_newline(sb);
    }
    break;
    default: IR_error("IR pretty printer: Unhandled instruction %s", IR_instruction_type_to_string(instruction));
    break;
    }
}

String* IR_pretty_print(IR_Program* program, Allocator* allocator)
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
            case IR_NODE_FUNCTION_DECL:
            {
                IR_Function_Decl* fun = &node->function;
                if(fun->export)
                {
                    sb_append(&sb, "export ");
                }
                sb_appendf(&sb, "fun %s()\n", fun->name->str);
            }
            break;
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
                IR_pretty_print_instruction(&sb, instruction, program);
            }
            break;
            }
        }
    }
   
    return sb_get_result(&sb, allocator);
}
