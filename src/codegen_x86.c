static void scratch_table_init(Scratch_Register_Table* table)
{
    table->inuse_table[SCRATCH_RBX] = false;
    table->inuse_table[SCRATCH_R10] = false;
    table->inuse_table[SCRATCH_R11] = false;
    table->inuse_table[SCRATCH_R12] = false;
    table->inuse_table[SCRATCH_R13] = false;
    table->inuse_table[SCRATCH_R14] = false;
    table->inuse_table[SCRATCH_R15] = false;
}

static Scratch_Register scratch_alloc(Scratch_Register_Table* table)
{
    for (i32 i = 0; i < SCRATCH_COUNT; i++)
    {
        if (!table->inuse_table[i])
        {
            table->inuse_table[i] = true;
            return i;
        }
    }
    assert("No available scratch registers" && false);
    return -1;
}

static void scratch_free(Scratch_Register_Table* table, Scratch_Register reg)
{
    table->inuse_table[reg] = false;
}

static i32 hash_int(i32 a)
{
      a ^= (a << 13);
      a ^= (a >> 17);        
      a ^= (a << 5);
      return a;   
}

static void temp_table_init(Temp_Table* table)
{
    table->count    = 0;
    table->capacity = 0;
    table->entries  = NULL;
    table->keys     = NULL;
}

static i32 temp_table_find_entry(i32* keys, Scratch_Register* entries, i32 capacity, i32 key)
{
    i32 index = hash_int(key) % capacity;
    i32 tombstone = -1;
    for (;;)
    {
        i32 found_key = keys[index];
        if (found_key == -1)
        {
            if (entries[index] == SCRATCH_COUNT)
            {
                return tombstone != -1 ? tombstone : index;
            }
            else
            {
                if (tombstone == -1) tombstone = index;
            }
        }
        else if (found_key == key)
        {
            return index;
        }
        
        index = (index + 1) % capacity;
    }
}


static void temp_table_adjust_capacity(Temp_Table* table, i32 capacity)
{
    i32 *new_keys = malloc(sizeof(i32) * capacity);
        Scratch_Register* new_entries = malloc(sizeof(Scratch_Register) * capacity);

        for (i32 i = 0; i < capacity; i++)
        {
            new_keys[i] = -1;
            new_entries[i] = SCRATCH_COUNT;
        }
        
        table->count = 0;
        for (i32 i = 0; i < table->capacity; i++)
        {
            i32 old_key = table->keys[i];
            Scratch_Register old_reg = table->entries[i];

            if (old_reg == SCRATCH_COUNT) continue;

            i32 index = temp_table_find_entry(new_keys, new_entries, capacity, old_key);
            new_keys[index] = table->keys[i];
            new_entries[index] = table->entries[i];
            table->count++;
        }

        table->capacity = capacity;
        table->entries  = new_entries;
        table->keys     = new_keys;
}

static bool temp_table_set(Temp_Table *table, i32 key, Scratch_Register reg)
{
    if (table->count + 1 > table->capacity * TABLE_MAX_LOAD)
    {
        i32 capacity = table->capacity < 8 ? 8 : table->capacity * 2;
        temp_table_adjust_capacity(table, capacity);
    }

    i32 index = temp_table_find_entry(table->keys, table->entries, table->capacity, key);
    bool new_entry = table->entries[index] == SCRATCH_COUNT;
    if (new_entry && table->entries[index] == SCRATCH_COUNT) table->count++;

    table->keys[index] = key;
    table->entries[index] = reg;
    return new_entry;
}

static bool temp_table_get(Temp_Table* table, i32 key, Scratch_Register* reg)
{
    if (table->count == 0) return false;

    i32 index = temp_table_find_entry(table->keys, table->entries, table->capacity, key);
    if (table->entries[index] == SCRATCH_COUNT) return false;

    *reg = table->entries[index];
    return true;
}

static bool temp_table_delete(Temp_Table* table, i32 key)
{
    if (table->count == 0) return false;

    i32 index = temp_table_find_entry(table->keys, table->entries, table->capacity, key);
    if (table->entries[index] == SCRATCH_COUNT) return false;

    table->keys[index] = -1;
    table->entries[index] = SCRATCH_RBX; // dummy value
    
    return true;
}

static Scratch_Register get_or_add_scratch_from_temp(Temp_Table* table, IR_Register ir_register, Scratch_Register_Table* scratch_table)
{
    i32 key = ir_register.index;
    Scratch_Register scratch_register;
    if (!temp_table_get(table, key, &scratch_register))
    {
        scratch_register = scratch_alloc(scratch_table);
        temp_table_set(table, key, scratch_register);
    }

    return scratch_register;
}

static void free_temp_scratch(Temp_Table* table, IR_Register ir_register, Scratch_Register_Table* scratch_table)
{
    i32 key = ir_register.index;
    Scratch_Register scratch_register = get_or_add_scratch_from_temp(table, ir_register, scratch_table);    
    temp_table_delete(table, key);
    scratch_free(scratch_table, scratch_register);
}

static const char* instruction_name(Instruction instruction, Register dst_reg)
{
    Reg_Size size = register_sizes[dst_reg];

#ifdef SKE_CODEGEN_INTEL
    not_implemented("Instruction names for Intel not yet implemented.");
    return NULL;
#elif SKE_CODEGEN_AT_T
    switch(instruction)
    {
    case INS_MOV:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return INS_NAME_MOV REG_SUFFIX_BYTE;
        case REG_SIZE_WORD: return INS_NAME_MOV REG_SUFFIX_WORD;
        case REG_SIZE_LONG: return INS_NAME_MOV REG_SUFFIX_LONG;
        case REG_SIZE_QUAD: return INS_NAME_MOV REG_SUFFIX_QUAD;
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_PUSH:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return INS_NAME_PUSH REG_SUFFIX_BYTE;
        case REG_SIZE_WORD: return INS_NAME_PUSH REG_SUFFIX_WORD;
        case REG_SIZE_LONG: return INS_NAME_PUSH REG_SUFFIX_LONG;
        case REG_SIZE_QUAD: return INS_NAME_PUSH REG_SUFFIX_QUAD;
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_POP:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return INS_NAME_POP REG_SUFFIX_BYTE;
        case REG_SIZE_WORD: return INS_NAME_POP REG_SUFFIX_WORD;
        case REG_SIZE_LONG: return INS_NAME_POP REG_SUFFIX_LONG;
        case REG_SIZE_QUAD: return INS_NAME_POP REG_SUFFIX_QUAD;
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_ADD:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return INS_NAME_ADD REG_SUFFIX_BYTE;
        case REG_SIZE_WORD: return INS_NAME_ADD REG_SUFFIX_WORD;
        case REG_SIZE_LONG: return INS_NAME_ADD REG_SUFFIX_LONG;
        case REG_SIZE_QUAD: return INS_NAME_ADD REG_SUFFIX_QUAD;
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_SUB:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return INS_NAME_SUB REG_SUFFIX_BYTE;
        case REG_SIZE_WORD: return INS_NAME_SUB REG_SUFFIX_WORD;
        case REG_SIZE_LONG: return INS_NAME_SUB REG_SUFFIX_LONG;
        case REG_SIZE_QUAD: return INS_NAME_SUB REG_SUFFIX_QUAD;
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_MUL:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return INS_NAME_MUL REG_SUFFIX_BYTE;
        case REG_SIZE_WORD: return INS_NAME_MUL REG_SUFFIX_WORD;
        case REG_SIZE_LONG: return INS_NAME_MUL REG_SUFFIX_LONG;
        case REG_SIZE_QUAD: return INS_NAME_MUL REG_SUFFIX_QUAD;
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_DIV:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return INS_NAME_DIV REG_SUFFIX_BYTE;
        case REG_SIZE_WORD: return INS_NAME_DIV REG_SUFFIX_WORD;
        case REG_SIZE_LONG: return INS_NAME_DIV REG_SUFFIX_LONG;
        case REG_SIZE_QUAD: return INS_NAME_DIV REG_SUFFIX_QUAD;
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_CMP:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return INS_NAME_CMP REG_SUFFIX_BYTE;
        case REG_SIZE_WORD: return INS_NAME_CMP REG_SUFFIX_WORD;
        case REG_SIZE_LONG: return INS_NAME_CMP REG_SUFFIX_LONG;
        case REG_SIZE_QUAD: return INS_NAME_CMP REG_SUFFIX_QUAD;
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_RET:
    {
        return INS_NAME_RET;
    }
    case INS_NEG:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return INS_NAME_NEG REG_SUFFIX_BYTE;
        case REG_SIZE_WORD: return INS_NAME_NEG REG_SUFFIX_WORD;
        case REG_SIZE_LONG: return INS_NAME_NEG REG_SUFFIX_LONG;
        case REG_SIZE_QUAD: return INS_NAME_NEG REG_SUFFIX_QUAD;
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_CQO:
    {
        return INS_NAME_CQO;
    }
    case INS_XOR:
    {
        switch(size)
        {
        case REG_SIZE_BYTE: return INS_NAME_XOR REG_SUFFIX_BYTE;
        case REG_SIZE_WORD: return INS_NAME_XOR REG_SUFFIX_WORD;
        case REG_SIZE_LONG: return INS_NAME_XOR REG_SUFFIX_LONG;
        case REG_SIZE_QUAD: return INS_NAME_XOR REG_SUFFIX_QUAD;
        default: compiler_bug("Should not happen.");
        }
    }
    case INS_CALL:
    {
        return INS_NAME_CALL;
    }
    default: compiler_bug("Invalid instruction.");
    
    }
#endif

    return NULL;
}

const char instruction_suffix[REG_SIZE_COUNT] =
{
    [REG_SIZE_BYTE] = 'b',
    [REG_SIZE_WORD] = 'w',
    [REG_SIZE_LONG] = 'l',
    [REG_SIZE_QUAD] = 'q',
};

static Register scratch_to_register(Scratch_Register reg)
{
    switch(reg)
    {
    case SCRATCH_RBX:
    return REG_RBX;
    case SCRATCH_R10:
    return REG_R10;
    case SCRATCH_R11:
    return REG_R11;
    case SCRATCH_R12:
    return REG_R12;
    case SCRATCH_R13:
    return REG_R13;
    case SCRATCH_R14:
    return REG_R14;
    case SCRATCH_R15:
    return REG_R15;
    default: compiler_bug("Invalid scratch register.");
    }

    assert(false && "Should not happend.");
}

i32 label_count = 0;
i32 label_create()
{
    return label_count++;
}

String* label_name(i32 label, Allocator* allocator)
{
    return string_createf(allocator, ".L%d", label);
}

void x86_emit_label(String_Builder* sb, const char* label)
{
    sb_appendf(sb, "%s:\n", label);
}

void x86_emit_add(String_Builder* sb, Register src, Register dst)
{
    sb_indent(sb, ASM_OUT_INDENT);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_ADD, dst), register_names[dst], register_names[src]);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_ADD, dst), register_names[src], register_names[dst]);
#endif
}

void x86_emit_sub(String_Builder* sb, Register src, Register dst)
{
    sb_indent(sb, ASM_OUT_INDENT);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_SUB, dst), register_names[dst], register_names[src]);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_SUB, dst), register_names[src], register_names[dst]);
#endif
}

void x86_emit_mul(String_Builder* sb, Register src, Register dst)
{
    x86_emit_move_reg_to_reg(sb, src, REG_RAX);

    sb_indent(sb, ASM_OUT_INDENT);
    sb_appendf(sb, "%s    %s\n", instruction_name(INS_MUL, dst), register_names[dst]);

    x86_emit_move_reg_to_reg(sb, REG_RAX, dst);
}

void x86_emit_div(String_Builder* sb, Register src, Register dst) 
{
    x86_emit_move_reg_to_reg(sb, src, REG_RAX);

    sb_indent(sb, ASM_OUT_INDENT);
    sb_appendf(sb, "%s\n", instruction_name(INS_CQO, REG_RAX)); 

    sb_indent(sb, ASM_OUT_INDENT);
    sb_appendf(sb, "%s    %s\n", instruction_name(INS_DIV, dst), register_names[dst]);

    x86_emit_move_reg_to_reg(sb, REG_RAX, dst);
    /* x86_emit_move_name_to_name(sb, register_names[REG_RAX], dst_name); */
}

static char literal_prefix()
{
#ifdef SKE_CODEGEN_INTEL
    return ' ';
#elif SKE_CODEGEN_AT_T
    return '$';
#endif
    return ' ';
}

void x86_emit_cmp_lit_to_loc(String_Builder* sb, i32 lhs, IR_Location rhs, Scratch_Register_Table* table, Temp_Table* temp_table)
{
    sb_indent(sb, ASM_OUT_INDENT);

    assert(rhs.type == IR_LOCATION_REGISTER);
    Scratch_Register s_right_reg = get_or_add_scratch_from_temp(temp_table, rhs.reg, table);
    Register right_reg = scratch_to_register(s_right_reg);

#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %c%d\n", instruction_name(INS_CMP, right_reg), register_names[right_reg], literal_prefix(), lhs);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %c%d, %s\n", instruction_name(INS_CMP, right_reg), literal_prefix(), lhs, register_names[right_reg]);
#endif
}

void x86_emit_cmp_loc_to_loc(String_Builder* sb, IR_Location lhs, IR_Location rhs, Scratch_Register_Table* table, Temp_Table* temp_table)
{
    sb_indent(sb, ASM_OUT_INDENT);

    assert(lhs.type == IR_LOCATION_REGISTER && rhs.type == IR_LOCATION_REGISTER);
    Scratch_Register s_left_reg = get_or_add_scratch_from_temp(temp_table, lhs.reg, table);
    Scratch_Register s_right_reg = get_or_add_scratch_from_temp(temp_table, rhs.reg, table);

    Register left_reg = scratch_to_register(s_left_reg);
    Register right_reg = scratch_to_register(s_right_reg);

#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_CMP, right_reg), register_names[left_reg], register_names[right_reg]);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_CMP, right_reg), register_names[right_reg], register_names[left_reg]);
#endif
}

void x86_emit_cmp_reg_to_reg(String_Builder* sb, Register s_lhs, Register s_rhs, IR_Op operator)
{
    Register lhs = scratch_to_register(s_lhs);
    Register rhs = scratch_to_register(s_rhs);
    
    x86_emit_move_reg_to_reg(sb, lhs, REG_RAX);

    sb_indent(sb, ASM_OUT_INDENT);

#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_CMP, REG_RAX), register_names[REG_RAX], register_names[rhs]);
#elif SKE_CODEGEN_AT_T
sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_CMP, REG_RAX), register_names[rhs], register_names[REG_RAX]);
#endif
}

void x86_emit_setcc(String_Builder* sb, IR_Op operator, Register result_reg)
{
    sb_indent(sb, ASM_OUT_INDENT);

    char* instruction = NULL;
    switch(operator)
    {
    case OP_NOT_EQUAL:
    {
        instruction = "setne";
    }
    break;
    case OP_EQUAL:
    {
        instruction = "sete ";
    }
    break;
    case OP_OR:
    {
        not_implemented("Binary or (||)");
    }
    break;
    case OP_AND:
    {
        not_implemented("Binary and (&&)");
    }
    break;
    case OP_LESS:
    {
        instruction = "setl ";
    }
    break;
    case OP_GREATER:
    {
        instruction = "setg ";
    }
    break;
    case OP_LESS_EQUAL:
    {
        instruction = "setle";
    }
    break;
    case OP_GREATER_EQUAL:
    {
        instruction = "setge";
    }
    break;
    default: compiler_bug("Comparison: Invalid operator.");
    }

    sb_appendf(sb, "%s   %s\n", instruction, register_names[REG_AL]);

    x86_emit_move_reg_to_reg(sb, REG_AL, result_reg);
}

void x86_emit_unary(String_Builder* sb, Register src)
{
    sb_indent(sb, ASM_OUT_INDENT);
    sb_appendf(sb, "%s     %s\n", instruction_name(INS_NEG, src), register_names[src]);
}

void x86_emit_move_reg_to_reg(String_Builder* sb, Register src, Register dst)
{
    sb_indent(sb, ASM_OUT_INDENT);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_MOV, dst), register_names[dst], register_names[src]);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_MOV, dst), register_names[src], register_names[dst]);
#endif
}

void x86_emit_move_reg_to_mem(String_Builder* sb, Register src, IR_Mem dst, 
                              Scratch_Register_Table* table, Temp_Table* temp_table)
{
    not_implemented("x86: Move reg to mem");
}

void x86_emit_move_mem_to_reg(String_Builder* sb, IR_Mem src, Register dst, 
                              Scratch_Register_Table* table, Temp_Table* temp_table)
{
    not_implemented("x86: Move mem to reg");
}

void x86_emit_move_mem_to_mem(String_Builder* sb, IR_Mem src, IR_Mem dst, 
                              Scratch_Register_Table* table, Temp_Table* temp_table)
{
    not_implemented("x86: Move mem to mem");
}

void x86_emit_move_loc_to_loc(String_Builder* sb, IR_Location src, IR_Location dst, 
                             Scratch_Register_Table* table, Temp_Table* temp_table)
{
    assert(src.type == IR_LOCATION_REGISTER && dst.type == IR_LOCATION_REGISTER);
    if (src.type == IR_LOCATION_REGISTER)
    {
        Scratch_Register s_left_reg = get_or_add_scratch_from_temp(temp_table, src.reg, table);
        Register left_reg = scratch_to_register(s_left_reg);
        if (dst.type == IR_LOCATION_REGISTER)
        {
            Scratch_Register s_right_reg = get_or_add_scratch_from_temp(temp_table, src.reg, table);
            Register right_reg = scratch_to_register(s_right_reg);

            x86_emit_move_reg_to_reg(sb, left_reg, right_reg);
        }
        else if (dst.type == IR_LOCATION_MEMORY)
        {
            x86_emit_move_reg_to_mem(sb, left_reg, dst.mem, table, temp_table);
        }
    }
    else if (src.type == IR_LOCATION_MEMORY)
    {
        if (dst.type == IR_LOCATION_REGISTER)
        {
            Scratch_Register s_right_reg = get_or_add_scratch_from_temp(temp_table, dst.reg, table);
            Register right_reg = scratch_to_register(s_right_reg);
            
            x86_emit_move_mem_to_reg(sb, src.mem, right_reg, table, temp_table);
        }
        else if(dst.type == IR_LOCATION_MEMORY)
        {
            x86_emit_move_mem_to_mem(sb, src.mem, dst.mem, table, temp_table);
        }
    }
}

void x86_emit_move_lit_to_reg(String_Builder* sb, i32 num, Register dst)
{
    sb_indent(sb, ASM_OUT_INDENT);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %c%d\n", instruction_name(INS_MOV, dst), register_names[dst), literal_prefix(), num);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %c%d, %s\n", instruction_name(INS_MOV, dst), literal_prefix(), num, register_names[dst]);
#endif
}

void x86_emit_ret(String_Builder* sb)
{
    sb_indent(sb, ASM_OUT_INDENT);
    sb_appendf(sb, "%s\n", instruction_name(INS_RET, REG_RAX));
}

void x86_emit_pop_reg(String_Builder* sb, Register reg)
{
    sb_indent(sb, ASM_OUT_INDENT);
    sb_appendf(sb, "%s     %s\n", instruction_name(INS_POP, reg), register_names[reg]);
}

void x86_emit_push_reg(String_Builder* sb, Register reg)
{
    sb_indent(sb, ASM_OUT_INDENT);
    sb_appendf(sb, "%s    %s\n", instruction_name(INS_PUSH, reg), register_names[reg]);
}

void x86_emit_asciz(String_Builder* sb, const char* name, const char* value)
{
    sb_appendf(sb, "%s:\n", name);
    sb_indent(sb, ASM_OUT_INDENT);
    sb_appendf(sb, ".asciz \"%s\"\n", value);
}

void x86_emit_call(String_Builder* sb, const char* function)
{
    sb_indent(sb, ASM_OUT_INDENT);
    sb_appendf(sb, "%s     %s\n", instruction_name(INS_CALL, REG_RAX), function);
}

void x86_emit_comment_line(String_Builder* sb, const char* comment)
{
    sb_indent(sb, ASM_OUT_INDENT);
    sb_appendf(sb, "# %s\n", comment);
}

void x86_emit_xor_reg_to_reg(String_Builder* sb, Register lhs, Register rhs)
{
    sb_indent(sb, ASM_OUT_INDENT);
#ifdef SKE_CODEGEN_INTEL
    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_XOR, rhs), register_names[rhs], register_names[rhs]);
#elif SKE_CODEGEN_AT_T
    sb_appendf(sb, "%s     %s, %s\n", instruction_name(INS_XOR, rhs), register_names[lhs], register_names[rhs]);
#endif
}

void x86_emit_syscall(String_Builder* sb, Linux_Syscall syscall)
{
    x86_emit_move_lit_to_reg(sb, (i32)syscall, REG_RAX);
    sb_indent(sb, ASM_OUT_INDENT);
    sb_append(sb, "syscall\n");
}

void x86_emit_exit_syscall(String_Builder* sb)
{
    x86_emit_move_reg_to_reg(sb, REG_RAX, REG_RDI);  
    x86_emit_move_lit_to_reg(sb, LINUX_SC_EXIT, REG_RAX);

    sb_indent(sb, ASM_OUT_INDENT);
    sb_append(sb, "syscall\n");
}

void x86_emit_start(String_Builder* sb)
{
    sb_append(sb, ".global _start\n");

    sb_append(sb, ".text\n");

    x86_emit_label(sb, "_start");

    x86_emit_xor_reg_to_reg(sb, REG_RBP, REG_RBP);

    x86_emit_call(sb, "main");
    
    x86_emit_move_reg_to_reg(sb, REG_RAX, REG_RDI);
    
    x86_emit_syscall(sb, LINUX_SC_EXIT);
}

String* x86_codegen_ir(IR_Program* program_node, Allocator* allocator)
{
    String_Builder sb;
    sb_init(&sb, 256);

    Scratch_Register_Table table;
    scratch_table_init(&table);

    Temp_Table temp_table;
    temp_table_init(&temp_table);

#ifdef SKE_CODEGEN_INTEL
    sb_append(&sb, ".intel_syntax noprefix\n\n");
#endif
    
    for (i32 i = 0; i < program_node->function_array.count; i++)
    {
        IR_Function function = program_node->function_array.functions[i];
        if (function.exported)
        {
            String_View name = program_node->function_array.functions[i].name;
            sb_appendf(&sb, ".global %s\n", name.string->str);
        }
    }
    
    x86_emit_start(&sb);

    Scratch_Register current_reg;

    for (i32 i = 0; i < program_node->block_array.count; i++)
    {
        IR_Block* block = &program_node->block_array.blocks[i];

        for (i32 j = 0; j < block->node_array.count; j++)
        {
            IR_Node* node = &block->node_array.nodes[j];
            switch(node->type)
            {
            case IR_NODE_FUNCTION_DECL:
            {
                IR_Function_Decl* fun = &node->function;
                sb_appendf(&sb, "%s:\n", fun->name->str);

                x86_emit_push_reg(&sb, REG_RBP);
                x86_emit_move_reg_to_reg(&sb, REG_RSP, REG_RBP);
            }
            break;
            case IR_NODE_LABEL:
            {
                x86_emit_label(&sb, node->label.label_name->str);
            }
            break;
            case IR_NODE_INSTRUCTION:
            {
                IR_Instruction* instruction = &node->instruction;

                switch(instruction->type)
                {
                case IR_INS_RET:
                {
                    IR_Return* ret = &instruction->ret;
                    if (ret->has_return_value)
                    {
                        Scratch_Register return_reg = get_or_add_scratch_from_temp(&temp_table, ret->return_register, &table);
                        x86_emit_move_reg_to_reg(&sb, scratch_to_register(return_reg), REG_RAX); // calling convention defined return
                    }
                    x86_emit_pop_reg(&sb, REG_RBP);
                    x86_emit_ret(&sb);
                }
                break;
                case IR_INS_CALL:
                {
                    IR_Call* call = &instruction->call;
                    String_View* name = ir_get_function_name(program_node, call->function_index);
                    x86_emit_call(&sb, name->string->str);
                }
                break;
                case IR_INS_MOV:
                {
                    IR_Move* move = &instruction->move;

                    IR_Value* src = &move->src;
                    IR_Location* dst = &move->dst;

                    switch(src->type)
                    {
                    case VALUE_LOCATION:
                    {
                        if(dst->type == IR_LOCATION_REGISTER && src->loc.type == IR_LOCATION_REGISTER)
                        {
                            Scratch_Register src_reg = get_or_add_scratch_from_temp(&temp_table, src->loc.reg, &table);
                            Scratch_Register dst_reg = get_or_add_scratch_from_temp(&temp_table, dst->reg, &table);
                            x86_emit_move_reg_to_reg(&sb, scratch_to_register(src_reg), scratch_to_register(dst_reg));
                            current_reg = dst_reg;
                        }
                    }
                    break;
                    case VALUE_INT:
                    {
                        if(dst->type == IR_LOCATION_REGISTER)
                        {
                            Scratch_Register reg = get_or_add_scratch_from_temp(&temp_table, dst->reg, &table);
                            current_reg = reg;
                            x86_emit_move_lit_to_reg(&sb, src->integer, scratch_to_register(reg));
                        }
                    }
                    break;
                    case VALUE_VARIABLE:
                    {
                        
                    }
                    break;
                    }
                }
                break;
                case IR_INS_PUSH:
                {
                    IR_Push* push = &instruction->push;
                    IR_Value* value = &push->value;

                    switch(value->type)
                    {
                    case VALUE_LOCATION:
                    {
                        Scratch_Register reg = get_or_add_scratch_from_temp(&temp_table, value->loc.reg, &table);
                        current_reg = reg;
                        x86_emit_push_reg(&sb, scratch_to_register(reg));
                    }
                    break;
                    case VALUE_VARIABLE:
                    {
                        
                    }
                    break;
                    default: break;
                    }
                }
                break;
                case IR_INS_POP:
                {
                    IR_Pop* pop = &instruction->pop;
                    IR_Value* value = &pop->value;

                    switch(value->type)
                    {
                    case VALUE_LOCATION:
                    {
                        Scratch_Register reg = get_or_add_scratch_from_temp(&temp_table, value->loc.reg, &table);
                        current_reg = reg;
                        x86_emit_push_reg(&sb, scratch_to_register(reg));
                    }
                    break;
                    case VALUE_VARIABLE:
                    {
                        
                    }
                    break;
                    default: break;
                    }
                }
                break;
                case IR_INS_UNOP:
                {
                    IR_UnOp* unop = &instruction->unop;
                    IR_Value* value = &unop->value;

                    IR_Register ir_reg = value->loc.reg;

                    Scratch_Register reg = get_or_add_scratch_from_temp(&temp_table, ir_reg, &table);

                    x86_emit_unary(&sb, reg);
                    current_reg = reg;
                }
                break;
                case IR_INS_BINOP:
                {
                    IR_BinOp* binop = &instruction->binop;
                    IR_Value* left = &binop->left;
                    IR_Value* right = &binop->right;

                    IR_Register ir_left_reg = left->loc.reg;
                    IR_Register ir_right_reg = right->loc.reg;

                    Scratch_Register s_left_reg = get_or_add_scratch_from_temp(&temp_table, ir_left_reg, &table);
                    Scratch_Register s_right_reg = get_or_add_scratch_from_temp(&temp_table, ir_right_reg, &table);
                    Register left_reg = scratch_to_register(s_left_reg);
                    Register right_reg = scratch_to_register(s_right_reg);

                    switch(binop->operator)
                    {
                    case OP_ADD:
                    {
                        x86_emit_add(&sb, left_reg, right_reg);
                    }
                    break;
                    case OP_SUB:
                    {
                        x86_emit_sub(&sb, left_reg, right_reg);
                        i32 temp = right_reg;
                        right_reg = left_reg;
                        left_reg = temp;

                        IR_Register temp_ir = ir_right_reg;
                        ir_right_reg = ir_left_reg;
                        ir_left_reg = temp_ir;
                    }
                    break;
                    case OP_MUL:
                    {
                        x86_emit_mul(&sb, left_reg, right_reg);
                    }
                    break;
                    case OP_DIV:
                    {
                        x86_emit_div(&sb, left_reg, right_reg);
                    }
                    break;
                    case OP_BIT_OR:
                    {}
                    break;
                    case OP_BIT_AND:
                    {}
                    break;
                    case OP_ASSIGN:
                    {}
                    break;

                    default: compiler_bug("Unsupported operator for binary operation."); break;
                    }

                    current_reg = right_reg;
                    free_temp_scratch(&temp_table, ir_left_reg, &table);
                }
                break;
                case IR_INS_COMPARE:
                {                    
                    IR_Compare* compare = &instruction->compare;

                    switch(compare->operator)
                    {
                    case OP_EQUAL:
                    case OP_OR:
                    case OP_AND:
                    case OP_LESS:
                    case OP_GREATER:
                    case OP_LESS_EQUAL:
                    case OP_GREATER_EQUAL:
                    case OP_NOT_EQUAL:
                    break;
                    default: compiler_bug("Unsupported operator for comparison operation."); break;
                    }

                    IR_Value left = compare->left;
                    IR_Location right = compare->right;

                    if(left.type == VALUE_INT)
                    {
                        x86_emit_cmp_lit_to_loc(&sb, left.integer, right, &table, &temp_table);
                    }
                    else if (left.type == VALUE_LOCATION)
                    {
                        x86_emit_cmp_loc_to_loc(&sb, left.loc, right, &table, &temp_table);
                    }
                }
                break;
                default: compiler_bug("Unhandled IR instruction."); break;
            }
            break;
            }
            default: break;
            }
        }
    }

    /* sb_append(&sb, "\n"); */
    /* x86_emit_comment_line(&sb, "fprintf call to output result temporarily"); */
    /* x86_emit_move_name_to_name(&sb, "stderr", "%rax"); */
    /* x86_emit_move_reg_to_name(&sb, current_reg, "%rdx"); */
    /* x86_emit_move_name_to_name(&sb, "$format", "%rsi"); */
    /* x86_emit_move_name_to_name(&sb, "%rax", "%rdi"); */
    /* x86_emit_move_lit_to_name(&sb, 0, "%rax"); */
    /* x86_emit_call(&sb, "fprintf"); */
    /* x86_emit_move_lit_to_name(&sb, 0, "%rax"); */

    /* x86_emit_pop_name(&sb, "%rbp"); */

    /* x86_emit_ret(&sb); */

    /* x86_emit_asciz(&sb, "format", "%d\\n"); */

    String* assembly = sb_get_result(&sb, allocator);
    return assembly;
}

void x86_codegen_program(AST_Node* program_node, String_Builder* sb, Scratch_Register_Table* table)
{
    sb_append(sb, ".data\n");
    sb_append(sb, ".text\n");
    sb_append(sb, ".global _start\n");
    sb_append(sb, "_start:\n");

    x86_emit_push_reg(sb, REG_RBP);
    x86_emit_move_reg_to_reg(sb, REG_RSP, REG_RBP);

    /* Scratch_Register final_reg = x86_codegen_expression(program_node->program.expression, sb, table); */

    /* x86_emit_move_reg_to_name(sb, final_reg, "%rax"); */
    /* scratch_free(table, final_reg); */

    // @Note: Emit instructions for fprintf call (used for now)
    /* sb_append(sb, "\n"); */
    /* x86_emit_comment_line(sb, "fprintf call to output result temporarily"); */
    /* x86_emit_move_name_to_name(sb, "stderr", "%rax"); */
    /* x86_emit_move_reg_to_name(sb, final_reg, "%rdx"); */
    /* x86_emit_move_name_to_name(sb, "$format", "%rsi"); */
    /* x86_emit_move_name_to_name(sb, "%rax", "%rdi"); */
    /* x86_emit_move_lit_to_name(sb, 0, "%rax"); */
    /* x86_emit_call(sb, "fprintf"); */
    /* x86_emit_move_lit_to_name(sb, 0, "%rax"); */

    /* x86_emit_pop_name(sb, "%rbp"); */

    /* x86_emit_ret(sb); */

    /* x86_emit_asciz(sb, "format", "%d\\n"); */
}

String* x86_codegen_ast(AST_Node* root_node, Allocator* allocator)
{
    String_Builder sb;
    sb_init(&sb, 256);

    Scratch_Register_Table register_table;
    scratch_table_init(&register_table);
    x86_codegen_program(root_node, &sb, &register_table);

    String* assembly = sb_get_result(&sb, allocator);

    return assembly;
}

void x86_codegen_ast_to_file(AST_Node* root_node, String* out_file, Allocator* allocator)
{
    String* assembly = x86_codegen_ast(root_node, allocator);

    FILE* file = NULL;
    if (out_file)
    {
        file = fopen(out_file->str, "w");
    }
    else
    {
        file = fopen("out.s", "w"); 
    }

    if (file)
    {
        string_fprintf(assembly, file);
        fclose(file);
    }
}
