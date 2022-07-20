IR_Register ir_register_alloc(IR_Register_Table* table)
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


static void ir_error(char* format, ...)
{
    fprintf(stderr, "\x1b[1;31m");
    va_list(ap);
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fprintf(stderr, "\x1b[0m\n");

    exit(1);
}

static char* ir_type_to_string(IR_Node_Type type)
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

static char* ir_instruction_type_to_string(IR_Instruction* instruction)
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
    default: ir_error("Unknown instruction type.");
    }
    return NULL;
}

static char* ir_node_to_string(IR_Node* node)
{
    switch(node->type)
    {
    case IR_NODE_INSTRUCTION:
    {
        return ir_instruction_type_to_string(&node->instruction);
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

String* ir_generate_label_name(IR_Program* program, Allocator* allocator)
{
    return string_createf(allocator, ".Label_%d", program->label_counter++);
}

IR_Block* ir_allocate_block(IR_Program* program)
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

IR_Node* ir_emit_node(IR_Block* block, IR_Node_Type node_type)
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

void ir_add_function(IR_Program* program, String* name, bool exported)
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

i32 ir_find_function(IR_Program* program, String* name)
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

String_View* ir_get_function_name(IR_Program* program, i32 index)
{
    if (index == -1) return NULL;
    if (program->function_array.count <= index) return NULL;
    return &program->function_array.functions[index].name;
}

IR_Node* ir_emit_function_decl(IR_Block* block, String* name, bool export)
{
    IR_Node* function_decl = ir_emit_node(block, IR_NODE_FUNCTION_DECL);
    function_decl->function.export = export;
    function_decl->function.name   = name;
    ir_add_function(block->parent_program, name, export);

    return function_decl;
}

IR_Label* ir_emit_label(IR_Block* block, String* label_name, Allocator* allocator)
{
    if(block->has_label)
    {
        fprintf(stderr, "unable to add label to IR block. Already has a label\n");
        return NULL;
    }

    IR_Node* label = ir_emit_node(block, IR_NODE_LABEL);
    label->label.label_name = label_name; // @Study: Should the label have a string view, or should it be owning?
    return &label->label;
}

IR_Node* ir_emit_instruction(IR_Block* block, IR_Instruction_Type instruction_type)
{
    IR_Node* node = ir_emit_node(block, IR_NODE_INSTRUCTION);
    node->instruction.type = instruction_type;
    return node;
}

IR_Node* ir_emit_return(IR_Block* block, IR_Register* reg, Allocator* allocator)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_RET);
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

IR_UnOp* ir_emit_unop(IR_Block* block, IR_Register reg, IR_Op operator, Allocator* allocator)
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

IR_Push* ir_emit_push_int(IR_Block* block, i32 value, Allocator* allocator)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_PUSH);
    IR_Push* push = &node->instruction.push;

    IR_Value* ir_value = &push->value;
    ir_value->type = VALUE_INT;
    ir_value->integer = value;
    
    return push;
}

IR_Move* ir_emit_move_reg_to_reg(IR_Block* block, IR_Register src_reg, IR_Register dst_reg, Allocator* allocator)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_MOV);
    IR_Move* move = &node->instruction.move;

    IR_Value* src = &move->src;
    src->type = IR_LOCATION_REGISTER;
    src->loc.reg = src_reg;

    IR_Location* dst = &move->dst;
    dst->type = IR_LOCATION_REGISTER;
    dst->reg = dst_reg;

    return move;
}

IR_Move* ir_emit_move_lit_to_reg(IR_Block* block, i32 value, IR_Register reg, Allocator* allocator)
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

IR_BinOp* ir_emit_binop(IR_Block* block, IR_Register left, IR_Register right, IR_Op operator, IR_Register_Table* table, Allocator* allocator)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_BINOP);
    IR_BinOp* binop = &node->instruction.binop;

    binop->left = ir_create_value_location(ir_create_location_register(left));
    binop->right = ir_create_value_location(ir_create_location_register(right));
    binop->destination = binop->right.loc.reg;//ir_register_alloc(table);
    binop->operator = operator;

    return binop;
}

IR_Op ir_map_operator(Token_Type source)
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
    default: ir_error("Invalid operator %s.", token_type_to_string(source)); exit(1);
    }
}

IR_Jump* ir_emit_jump(IR_Block* block, IR_Label label, IR_Jump_Type jump_type, IR_Block_Address block_address, Allocator* allocator)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_JUMP);
    IR_Jump* jump = &node->instruction.jump;

    jump->type = jump_type;
    jump->address = block_address;

    return jump;
}

IR_Compare* ir_emit_comparison(IR_Block* block, IR_Value left, IR_Location right, IR_Op operator, IR_Register_Table* table, Allocator* allocator)
{
    IR_Node* node = ir_emit_instruction(block, IR_INS_COMPARE);
    IR_Compare* compare = &node->instruction.compare;

    compare->left = left;
    compare->right = right;
    compare->operator = operator;
    compare->destination = compare->right.reg;//ir_register_alloc(table);

    return compare;
}

IR_Register ir_translate_expression(AST_Node* node, IR_Block* block, Allocator* allocator, IR_Register_Table* table)
{
    switch(node->type)
    {
    case  AST_NODE_NUMBER:
    {
        IR_Register reg = ir_register_alloc(table);
        ir_emit_move_lit_to_reg(block, node->number, reg, allocator);
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
        case TOKEN_MINUS:
        case TOKEN_STAR:
        case TOKEN_SLASH:
        case TOKEN_BANG:
        case TOKEN_EQUAL:
        case TOKEN_PIPE:
        case TOKEN_AMPERSAND:
        {
            IR_BinOp* binop = ir_emit_binop(block, left_reg, right_reg, ir_map_operator(operator), table, allocator);
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
            IR_Value left_val = ir_create_value_location(ir_create_location_register(left_reg));
            IR_Location right_loc = ir_create_location_register(right_reg);

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
                    jump_type = JMP_EQUAL;
                }
            }
            break;
            case TOKEN_LESS:
            case TOKEN_GREATER:
            case TOKEN_LESS_EQUAL:
            case TOKEN_GREATER_EQUAL:
            case TOKEN_BANG_EQUAL:
            {
                if (left_is_zero)
                {
                    jump_type = JMP_NOT_ZERO;
                }
                else
                {
                    jump_type = JMP_NOT_EQUAL;
                }
            }
            break;
            default: ir_error("Invalid comparison operator %s", token_type_to_string(operator));
            }

            (void)jump_type;
            
            IR_Compare* compare = ir_emit_comparison(block, left_val, right_loc, ir_map_operator(operator), table, allocator);

            if (node->parent->type == AST_NODE_IF)
            {
             
            }

            // @Incomplete: Create jumps based on which type of comparison we have here... (short circuiting?)
            /* assert(false); */
            return compare->destination;
        }
        default:
        ir_error("Unsupported operator for binary operations %s\n", token_type_to_string(operator));
        break;
        }
    }
    case AST_NODE_UNARY:
    {
        IR_Register reg = ir_translate_expression(node->unary.expression, block, allocator, table);
        Token_Type operator = node->unary.operator;
        switch(operator)
        {
        case TOKEN_MINUS:
        {
            ir_emit_unop(block, reg, OP_SUB, allocator);
        }
        break;
        case TOKEN_BANG:
        {
            ir_emit_unop(block, reg, OP_NOT, allocator);
        }
        break;
        default: ir_error("Unsupported operator for unary operations %s\n", token_type_to_string(operator));
        }
        
        return reg;
    }
    default:
    assert("Unsupported AST Node" && false);
    }
}

void ir_translate_block(IR_Block* block, AST_Node* body, Allocator* allocator, IR_Register_Table* register_table)
{
    AST_Node_List list = body->block.declarations;

    for (i32 i = 0; i < list.count; i++)
    {
        AST_Node* node = list.nodes[i];

        switch(node->type)
        {
        case AST_NODE_RETURN:
        {
            if (node->return_statement.expression)
            {
                IR_Register reg = ir_translate_expression(node->return_statement.expression, block, allocator, register_table);
                IR_Register dst = ir_register_alloc(register_table);
                
                ir_emit_move_reg_to_reg(block, reg, dst, allocator);
                ir_emit_return(block, &dst, allocator);
            }
            else
            {
                ir_emit_return(block, NULL, allocator);
            }
        }
        break;
        case AST_NODE_IF:
        {
            AST_Node* ast_condition = node->if_statement.condition;

            IR_Register cond_register = ir_translate_expression(ast_condition, block, allocator, register_table);
            
            AST_Node* ast_then_arm = node->if_statement.then_arm;
            if (ast_then_arm->type != AST_NODE_BLOCK)
            {
                ir_error("Then arm for if statement has to be a block, was %s", ast_type_string(ast_then_arm->type));
            }

            if (ast_condition->type == AST_NODE_NUMBER)
            {
                i32 number = ast_condition->number;
                /* @Incomplete:
                   - Generate a compare instruction with 0
                   - Generate a jump_equals (patch label later)
                */

                IR_Block* then_block = ir_allocate_block(block->parent_program);
                IR_Block* end_block = ir_allocate_block(block->parent_program);
                IR_Label* end_label = ir_emit_label(end_block, ir_generate_label_name(block->parent_program, allocator), allocator);

                ir_emit_jump(block, *end_label, JMP_EQUAL, end_block->block_address, allocator);
            }
            else if (ast_condition->type == AST_NODE_BINARY)
            {
                /* @Incomplete:
                   - Generate a jump that matches the compare (patch label later)
                */
            }
            
            AST_Node* ast_else_arm = node->if_statement.else_arm;
            if (ast_else_arm)
            {
                
            }

            /* IR_Node* prev = &node_array->nodes[node_array->count - 1]; */
            /* if (prev->type != IR_NODE_INSTRUCTION) */
            /* { */
            /*     ir_error("Node before if has to be an instruction, was %s.", ir_type_to_string(prev->type)); */
            /* } */

            /* IR_Instruction* prev_instruction = &prev->instruction; */
            /* if (prev_instruction->type != IR_INS_COMPARE) */
            /* { */
            /*     ir_error("Instruction before if has to be a compare, was %s.", ir_type_to_string(prev->type)); */
            /* }             */
        }
        break;
        case AST_NODE_CALL:
        {
            String* fun_name = node->fun_call.name;
            i32 index = ir_find_function(block->parent_program, fun_name);
            assert(index != -1 && "Unknown function.");
            if (index != -1)
            {
                IR_Node* call = ir_emit_instruction(block, IR_INS_CALL);
                call->instruction.call.function_index = index;
            }
        }
        break;
        case AST_NODE_NUMBER:
        case AST_NODE_BINARY:
        case AST_NODE_UNARY:
        {
            ir_translate_expression(node, block, allocator, register_table);
        }
        break;
        default: assert(false && "Invalid AST node type.");
        }
    }
}

IR_Block* ir_get_current_block(IR_Program* program)
{
    if (program->block_array.count == 0)
    {
        return NULL;
    }

    return &program->block_array.blocks[program->block_array.count - 1];
}

void ir_translate_program(IR_Program* program, AST_Node* ast_program, Allocator* allocator, IR_Register_Table* register_table)
{
    AST_Node_List declarations = ast_program->program.declarations;

    for (i32 i = 0; i < declarations.count; i++)
    {
        AST_Node* node = declarations.nodes[i];

        switch(node->type)
        {
        case AST_NODE_FUN_DECL:
        {
            IR_Block* block = ir_allocate_block(program);
            ir_emit_function_decl(block, node->fun_decl.name, true);

            ir_translate_block(block, node->fun_decl.body, allocator, register_table);
        }
        break;
        case AST_NODE_NUMBER:
        case AST_NODE_BINARY:
        case AST_NODE_UNARY:
        {
            IR_Block* block = ir_get_current_block(program);
            
            String* name = string_allocate("main", allocator);
            ir_emit_function_decl(block, name, true);
            ir_translate_expression(node, block, allocator, register_table);
            ir_emit_instruction(block, IR_INS_RET);
        }
        break;
        default: assert(false && "Invalid AST node type");
        }
    }
}

IR_Program ir_translate_ast(AST_Node* root_node, Allocator* allocator)
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
    /* IR_Block* block = ir_allocate_block(&program); */
    
    /* String* name = string_allocate("main", allocator); */
    /* ir_emit_function_decl(block, name, true, allocator); */

    ir_translate_program(&program, root_node, allocator, register_table);
    
    /* ir_translate_expression(root_node->program.expression, block, allocator, register_table); */

    /* ir_pretty_print(&program, true, allocator); */

    return program;
}

void ir_pretty_print_register(String_Builder* sb, IR_Register* reg)
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

void ir_pretty_print_location(String_Builder* sb, IR_Location* location)
{
    switch(location->type)
    {
    case IR_LOCATION_REGISTER:
    {
        ir_pretty_print_register(sb, &location->reg);
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

String* ir_pretty_print(IR_Program* program, Allocator* allocator)
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
                sb_indent(&sb, 8);
                
                switch(instruction->type)
                {
                case IR_INS_MOV:
                {
                    IR_Move* move = &instruction->move;

                    IR_Value* src = &move->src;
                    IR_Location* dst = &move->dst;

                    ir_pretty_print_location(&sb, dst);
                    sb_append(&sb, " := ");
                    ir_pretty_print_value(&sb, src);

                    sb_newline(&sb);
                }
                break;
                case IR_INS_PUSH:
                {
                    IR_Push* push = &instruction->push;
                    sb_append(&sb, "push(");
                    ir_pretty_print_value(&sb, &push->value);
                    sb_append(&sb, ")");
                    sb_newline(&sb);
                }
                break;
                case IR_INS_POP:
                {
                    IR_Pop* pop = &instruction->pop;
                    sb_append(&sb, "pop(");
                    ir_pretty_print_value(&sb, &pop->value);
                    sb_append(&sb, ")");
                    sb_newline(&sb);
                }
                break;
                case IR_INS_JUMP:
                {
                    IR_Jump* jump = &instruction->jump;
                    switch(jump->type)
                    {
                    case JMP_ALWAYS:
                    {
                        sb_append(&sb, "jmp(");
                    }
                    break;
                    case JMP_EQUAL:
                    {
                        sb_append(&sb, "je(");
                    }
                    break;
                    case JMP_ZERO:
                    {
                        sb_append(&sb, "jz(");
                    }
                    break;
                    case JMP_NOT_EQUAL:
                    {
                        sb_append(&sb, "jne(");
                    }
                    break;
                    case JMP_NOT_ZERO:
                    {
                        sb_append(&sb, "jnz(");
                    }
                    break;
                    case JMP_LESS:
                    {
                        sb_append(&sb, "jl(");
                    }
                    break;
                    case JMP_LESS_EQUAL:
                    {
                        sb_append(&sb, "jle(");
                    }
                    break;
                    case JMP_GREATER:
                    {
                        sb_append(&sb, "jg(");
                    }
                    break;
                    case JMP_GREATER_EQUAL:
                    {
                        sb_append(&sb, "jge(");
                    }
                    break;
                    }

                    IR_Block_Address address = jump->address;
                    IR_Block* block = &program->block_array.blocks[address.address];
                    IR_Node* first_node = &block->node_array.nodes[0];
                    IR_Label* label = &first_node->label;
                    sb_append(&sb, label->label_name->str);
                    sb_append(&sb, ")");
                    sb_newline(&sb);
                }
                break;
                case IR_INS_BINOP:
                {
                    IR_BinOp* binop = &instruction->binop;

                    ir_pretty_print_register(&sb, &binop->destination);
                    sb_append(&sb, " := ");
                    ir_pretty_print_value(&sb, &binop->left);

                    switch(binop->operator)
                    {
                    case OP_ADD:
                    {
                        sb_append(&sb, " + ");
                    }
                    break;
                    case OP_SUB:
                    {
                        sb_append(&sb, " - ");
                    }
                    break;
                    case OP_MUL:
                    {
                        sb_append(&sb, " * ");
                    }
                    break;
                    case OP_DIV:
                    {
                        sb_append(&sb, " / ");
                    }
                    break;
                    case OP_NOT_EQUAL:
                    {
                        sb_append(&sb, " != ");
                    }
                    break;
                    case OP_EQUAL:
                    {
                        sb_append(&sb, " == ");
                    }
                    break;
                    case OP_ASSIGN:
                    {
                        sb_append(&sb, " = ");
                    }
                    break;
                    case OP_BIT_OR:
                    {
                        sb_append(&sb, " | ");
                    }
                    break;
                    case OP_BIT_AND:
                    {
                        sb_append(&sb, " & ");
                    }
                    break;
                    default: ir_error("Unsupported operator for binary operation\n");
                    }
                    ir_pretty_print_value(&sb, &binop->right);

                    sb_newline(&sb);
                }
                break;
                case IR_INS_RET:
                {
                    IR_Return* ret = &instruction->ret;
                    sb_append(&sb, "ret");
                    if (ret->has_return_value)
                    {
                        sb_append(&sb, " ");
                        ir_pretty_print_register(&sb, &ret->return_register);
                    }
                    
                    sb_newline(&sb);
                }
                break;
                case IR_INS_CALL:
                {
                    IR_Call* call = &instruction->call;
                    String_View name = program->function_array.functions[call->function_index].name;
                    sb_appendf(&sb, "call %s\n", name.string->str);
                }
                break;
                case IR_INS_UNOP:
                {
                    IR_UnOp* unop = &instruction->unop;

                    ir_pretty_print_value(&sb, &unop->value);
                    sb_append(&sb, " := ");
                    switch(unop->operator)
                    {
                    case OP_SUB:
                    {
                        sb_append(&sb, "-");
                    }
                    break;
                    case OP_NOT:
                    {
                        sb_append(&sb, "!");
                    }
                    break;
                    default: ir_error("Unsupported operator for unary operation\n");
                    }
                    ir_pretty_print_value(&sb, &unop->value);
                    sb_append(&sb, "");
                    sb_newline(&sb);
                }
                break;
                case IR_INS_COMPARE:
                {
                    IR_Compare* compare = &instruction->compare;

                    ir_pretty_print_register(&sb, &compare->destination);
                    sb_append(&sb, " := ");
                    ir_pretty_print_value(&sb, &compare->left);
                    
                    switch(compare->operator)
                    {
                    case OP_OR:
                    {
                        sb_append(&sb, " || ");
                    }
                    break;
                    case OP_AND:
                    {
                        sb_append(&sb, " && ");
                    }
                    break;
                    case OP_LESS:
                    {
                        sb_append(&sb, " < ");
                    }
                    break;
                    case OP_GREATER:
                    {
                        sb_append(&sb, " > ");
                    }
                    break;
                    case OP_LESS_EQUAL:
                    {
                        sb_append(&sb, " <= ");
                    }
                    break;
                    case OP_GREATER_EQUAL:
                    {
                        sb_append(&sb, " >= ");
                    }
                    break;
                    case OP_EQUAL:
                    {
                        sb_append(&sb, " == ");
                    }
                    break;
                    case OP_NOT_EQUAL:
                    {
                        sb_append(&sb, " != ");
                    }
                    break;
                    default: ir_error("Unsupported operator for compare operation\n");
                    }
                    ir_pretty_print_location(&sb, &compare->right);
                    sb_newline(&sb);
                }
                break;
                default: ir_error("IR pretty printer: Unhandled instruction %s", ir_instruction_type_to_string(instruction));
                break;
                }
            }
            break;
            }
        }
    }
   
    return sb_get_result(&sb, allocator);
}
