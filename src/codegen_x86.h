#ifndef SKE_X86_CODEGEN_H
#define SKE_X86_CODEGEN_H

/* #define SKE_CODEGEN_INTEL 1 */
#define SKE_CODEGEN_AT_T 1
#define ASM_OUT_INDENT 4

/* TODO for specifying argument size (al, ax, eax, rax):
   - I want to be able to push instructions
   - These instructions have to take arguments
   - Depending on the arguments, the instruction will look different
   - So we need something like:
*/
typedef enum
{
    REG_AL, REG_AH, REG_AX, REG_EAX, REG_RAX,
    REG_BL, REG_BH, REG_BX, REG_EBX, REG_RBX,
    REG_CL, REG_CH, REG_CX, REG_ECX, REG_RCX,
    REG_DL, REG_DH, REG_DX, REG_EDX, REG_RDX,

    REG_SIL, REG_SI, REG_ESI, REG_RSI,
    REG_DIL, REG_DI, REG_EDI, REG_RDI,

    REG_SPL, REG_SP, REG_ESP, REG_RSP,

    REG_BPL, REG_BP, REG_EBP, REG_RBP,

    REG_R8B, REG_R8W, REG_R8D, REG_R8,
    REG_R9B, REG_R9W, REG_R9D, REG_R9,
    REG_R10B, REG_R10W, REG_R10D, REG_R10,
    REG_R11B, REG_R11W, REG_R11D, REG_R11,
    REG_R12B, REG_R12W, REG_R12D, REG_R12,
    REG_R13B, REG_R13W, REG_R13D, REG_R13,
    REG_R14B, REG_R14W, REG_R14D, REG_R14,
    REG_R15B, REG_R15W, REG_R15D, REG_R15,

    REG_COUNT
}  Register;

typedef enum
{
    REG_SIZE_BYTE,
    REG_SIZE_WORD,
    REG_SIZE_LONG,
    REG_SIZE_QUAD,
    REG_SIZE_COUNT
} Reg_Size;

#ifdef SKE_CODEGEN_INTEL
const char* register_names[REG_COUNT] =
{
  [REG_AL]   = "al",
  [REG_AH]   = "ah",
  [REG_AX]   = "ax",
  [REG_EAX]  = "eax",
  [REG_RAX]  = "rax",
               
  [REG_BL]   = "bl",
  [REG_BH]   = "bh",
  [REG_BX]   = "bx",
  [REG_EBX]  = "ebx",
  [REG_RBX]  = "rax",
               
  [REG_CL]   = "cl",
  [REG_CH]   = "ch",
  [REG_CX]   = "cx",
  [REG_ECX]  = "ecx",
  [REG_RCX]  = "rcx",
               
  [REG_DL]   = "dl",
  [REG_DH]   = "dh",
  [REG_DX]   = "dx",
  [REG_EDX]  = "edx",
  [REG_RDX]  = "rdx",
               
  [REG_SIL]  = "sil",
  [REG_SI]   = "si",
  [REG_ESI]  = "esi",
  [REG_RSI]  = "rsi",
               
  [REG_DIL]  = "dil",
  [REG_DI]   = "di",
  [REG_EDI]  = "edi",
  [REG_RDI]  = "rdi",
               
  [REG_SPL]  = "spl",
  [REG_SP]   = "sp",
  [REG_ESP]  = "esp",
  [REG_RSP]  = "rsp",
               
  [REG_BPL]  = "bpl",
  [REG_BP]   = "bp",
  [REG_EBP]  = "ebp",
  [REG_RBP]  = "rbp",
               
  [REG_R8B]  = "r8b",
  [REG_R8W]  = "r8w",
  [REG_R8D]  = "r8d",
  [REG_R8]   = "r8",
               
  [REG_R9B]  = "r9b",
  [REG_R9W]  = "r9w",
  [REG_R9D]  = "r9d",
  [REG_R9]   = "r9", 

  [REG_R10B] = "r10b",
  [REG_R10W] = "r10w",
  [REG_R10D] = "r10d",
  [REG_R10]  = "r10", 
              
  [REG_R11B] = "r11b",
  [REG_R11W] = "r11w",
  [REG_R11D] = "r11d",
  [REG_R11]  = "r11", 
              
  [REG_R12B] = "r12b",
  [REG_R12W] = "r12w",
  [REG_R12D] = "r12d",
  [REG_R12]  = "r12", 
              
  [REG_R13B] = "r13b",
  [REG_R13W] = "r13w",
  [REG_R13D] = "r13d",
  [REG_R13]  = "r13", 
              
  [REG_R14B] = "r14b",
  [REG_R14W] = "r14w",
  [REG_R14D] = "r14d",
  [REG_R14]  = "r14", 
              
  [REG_R15B] = "r15b",
  [REG_R15W] = "r15w",
  [REG_R15D] = "r15d",
  [REG_R15]  = "r15", 
};
#elif SKE_CODEGEN_AT_T
const char* register_names[REG_COUNT] =
{
  [REG_AL]   = "%al",
  [REG_AH]   = "%ah",
  [REG_AX]   = "%ax",
  [REG_EAX]  = "%eax",
  [REG_RAX]  = "%rax",
               
  [REG_BL]   = "%bl",
  [REG_BH]   = "%bh",
  [REG_BX]   = "%bx",
  [REG_EBX]  = "%ebx",
  [REG_RBX]  = "%rax",
               
  [REG_CL]   = "%cl",
  [REG_CH]   = "%ch",
  [REG_CX]   = "%cx",
  [REG_ECX]  = "%ecx",
  [REG_RCX]  = "%rcx",
               
  [REG_DL]   = "%dl",
  [REG_DH]   = "%dh",
  [REG_DX]   = "%dx",
  [REG_EDX]  = "%edx",
  [REG_RDX]  = "%rdx",
               
  [REG_SIL]  = "%sil",
  [REG_SI]   = "%si",
  [REG_ESI]  = "%esi",
  [REG_RSI]  = "%rsi",
               
  [REG_DIL]  = "%dil",
  [REG_DI]   = "%di",
  [REG_EDI]  = "%edi",
  [REG_RDI]  = "%rdi",
               
  [REG_SPL]  = "%spl",
  [REG_SP]   = "%sp",
  [REG_ESP]  = "%esp",
  [REG_RSP]  = "%rsp",
               
  [REG_BPL]  = "%bpl",
  [REG_BP]   = "%bp",
  [REG_EBP]  = "%ebp",
  [REG_RBP]  = "%rbp",
               
  [REG_R8B]  = "%r8b",
  [REG_R8W]  = "%r8w",
  [REG_R8D]  = "%r8d",
  [REG_R8]   = "%r8",
               
  [REG_R9B]  = "%r9b",
  [REG_R9W]  = "%r9w",
  [REG_R9D]  = "%r9d",
  [REG_R9]   = "%r9", 

  [REG_R10B] = "%r10b",
  [REG_R10W] = "%r10w",
  [REG_R10D] = "%r10d",
  [REG_R10]  = "%r10", 
              
  [REG_R11B] = "%r11b",
  [REG_R11W] = "%r11w",
  [REG_R11D] = "%r11d",
  [REG_R11]  = "%r11", 
              
  [REG_R12B] = "%r12b",
  [REG_R12W] = "%r12w",
  [REG_R12D] = "%r12d",
  [REG_R12]  = "%r12", 
              
  [REG_R13B] = "%r13b",
  [REG_R13W] = "%r13w",
  [REG_R13D] = "%r13d",
  [REG_R13]  = "%r13", 
              
  [REG_R14B] = "%r14b",
  [REG_R14W] = "%r14w",
  [REG_R14D] = "%r14d",
  [REG_R14]  = "%r14", 
              
  [REG_R15B] = "%r15b",
  [REG_R15W] = "%r15w",
  [REG_R15D] = "%r15d",
  [REG_R15]  = "%r15", 
};
#endif

Reg_Size register_sizes[REG_COUNT] =
{
  [REG_AL]  = REG_SIZE_BYTE,
  [REG_AH]  = REG_SIZE_BYTE,
  [REG_AX]  = REG_SIZE_WORD,
  [REG_EAX] = REG_SIZE_LONG,
  [REG_RAX] = REG_SIZE_QUAD,

  [REG_BL]  = REG_SIZE_BYTE,
  [REG_BH]  = REG_SIZE_BYTE,
  [REG_BX]  = REG_SIZE_WORD,
  [REG_EBX] = REG_SIZE_LONG,
  [REG_RBX] = REG_SIZE_QUAD,

  [REG_CL]  = REG_SIZE_BYTE,
  [REG_CH]  = REG_SIZE_BYTE,
  [REG_CX]  = REG_SIZE_WORD,
  [REG_ECX] = REG_SIZE_LONG,
  [REG_RCX] = REG_SIZE_QUAD,

  [REG_DL]  = REG_SIZE_BYTE,
  [REG_DH]  = REG_SIZE_BYTE,
  [REG_DX]  = REG_SIZE_WORD,
  [REG_EDX] = REG_SIZE_LONG,
  [REG_RDX] = REG_SIZE_QUAD,

  [REG_SIL] = REG_SIZE_BYTE,
  [REG_SI]  = REG_SIZE_WORD,
  [REG_ESI] = REG_SIZE_LONG,
  [REG_RSI] = REG_SIZE_QUAD,

  [REG_DIL] = REG_SIZE_BYTE,
  [REG_DI]  = REG_SIZE_WORD,
  [REG_EDI] = REG_SIZE_LONG,
  [REG_RDI] = REG_SIZE_QUAD,

  [REG_SPL] = REG_SIZE_BYTE,
  [REG_SP]  = REG_SIZE_WORD,
  [REG_ESP] = REG_SIZE_LONG,
  [REG_RSP] = REG_SIZE_QUAD,

  [REG_BPL] = REG_SIZE_BYTE,
  [REG_BP]  = REG_SIZE_WORD,
  [REG_EBP] = REG_SIZE_LONG,
  [REG_RBP] = REG_SIZE_QUAD,

  [REG_R8B] = REG_SIZE_BYTE,
  [REG_R8W] = REG_SIZE_WORD,
  [REG_R8D] = REG_SIZE_LONG,
  [REG_R8]  = REG_SIZE_QUAD,

  [REG_R9B] = REG_SIZE_BYTE,
  [REG_R9W] = REG_SIZE_WORD,
  [REG_R9D] = REG_SIZE_LONG,
  [REG_R9]  = REG_SIZE_QUAD,

  [REG_R10B] = REG_SIZE_BYTE,
  [REG_R10W] = REG_SIZE_WORD,
  [REG_R10D] = REG_SIZE_LONG,
  [REG_R10]  = REG_SIZE_QUAD,

  [REG_R11B] = REG_SIZE_BYTE,
  [REG_R11W] = REG_SIZE_WORD,
  [REG_R11D] = REG_SIZE_LONG,
  [REG_R11]  = REG_SIZE_QUAD,

  [REG_R12B] = REG_SIZE_BYTE,
  [REG_R12W] = REG_SIZE_WORD,
  [REG_R12D] = REG_SIZE_LONG,
  [REG_R12]  = REG_SIZE_QUAD,

  [REG_R13B] = REG_SIZE_BYTE,
  [REG_R13W] = REG_SIZE_WORD,
  [REG_R13D] = REG_SIZE_LONG,
  [REG_R13]  = REG_SIZE_QUAD,

  [REG_R14B] = REG_SIZE_BYTE,
  [REG_R14W] = REG_SIZE_WORD,
  [REG_R14D] = REG_SIZE_LONG,
  [REG_R14]  = REG_SIZE_QUAD,

  [REG_R15B] = REG_SIZE_BYTE,
  [REG_R15W] = REG_SIZE_WORD,
  [REG_R15D] = REG_SIZE_LONG,
  [REG_R15]  = REG_SIZE_QUAD,
};

typedef enum
{
    SCRATCH_RBX,
    SCRATCH_R10,
    SCRATCH_R11,
    SCRATCH_R12,
    SCRATCH_R13,
    SCRATCH_R14,
    SCRATCH_R15,
    SCRATCH_COUNT
} Scratch_Register;

typedef enum
{
    LINUX_SC_EXIT = 60
} Linux_Syscall;

typedef struct X86_Memory X86_Memory;
struct X86_Memory
{
    enum X86_Memory_Type
    {
        MEM_TYPE_IMMEDIATE,
        MEM_TYPE_REGISTER,
        MEM_TYPE_OFFSET,
        MEM_TYPE_SCALED_INDEXED_BASE,
        MEM_TYPE_SCALED_INDEXED,
    } type;

    union
    {
        i32 immediate;
        Register  reg;
        struct
        {
            Register reg;
            i32      offset;
        } offset;
        struct
        {
            Register base;
            Register offset_register;
            i32      scaled;
        } scaled_indexed;
    };
};

typedef struct X86_Location X86_Location;
struct X86_Location
{
    enum X86_Location_Type
    {
        LOC_REGISTER,
        LOC_MEMORY
    } type;

    union
    {
        Register reg;
        X86_Memory memory;
    };
};

typedef struct
{
    bool inuse_table[SCRATCH_COUNT];
} Scratch_Register_Table;


#ifdef SKE_CODEGEN_INTEL

const char* scratch_register_names[SCRATCH_COUNT] =
{
    [SCRATCH_RBX] = "rbx",
    [SCRATCH_R10] = "r10",
    [SCRATCH_R11] = "r11",
    [SCRATCH_R12] = "r12",
    [SCRATCH_R13] = "r13",
    [SCRATCH_R14] = "r14",
    [SCRATCH_R15] = "r15",
};

#elif SKE_CODEGEN_AT_T

#endif


typedef struct Temp_Table_Entry Temp_Table_Entry;


typedef struct Temp_Table Temp_Table;
struct Temp_Table
{
    i32* keys;
    Scratch_Register* entries;
    i32 count;
    i32 capacity;
};


#define TABLE_MAX_LOAD 0.75f

const char* scratch_name(Scratch_Register reg);

typedef enum
{
    INS_MOV,
    INS_PUSH,
    INS_POP,
    INS_ADD,
    INS_SUB,
    INS_MUL,
    INS_DIV,
    INS_CMP,
    INS_RET,
    INS_NEG,
    INS_CQO,
    INS_XOR,
    INS_CALL,
    INS_COUNT
} Instruction;

const char* instruction_names[INS_COUNT] =
{
    [INS_MOV ] = "mov",
    [INS_PUSH] = "push",
    [INS_POP]  = "pop",
    [INS_ADD]  = "add",
    [INS_SUB]  = "sub",
    [INS_MUL]  = "imul",
    [INS_DIV]  = "idiv",
    [INS_CMP]  = "cmp",
    [INS_RET]  = "ret",
    [INS_NEG]  = "neg",
    [INS_CQO]  = "cqo",
    [INS_XOR]  = "xor",
    [INS_CALL] = "call"
};

#define INS_NAME_MOV  "mov"
#define INS_NAME_PUSH "push"
#define INS_NAME_POP  "pop"
#define INS_NAME_ADD  "add"
#define INS_NAME_SUB  "sub"
#define INS_NAME_MUL  "imul"
#define INS_NAME_DIV  "idiv"
#define INS_NAME_CMP  "cmp"
#define INS_NAME_RET  "ret"
#define INS_NAME_NEG  "neg"
#define INS_NAME_CQO  "cqo"
#define INS_NAME_XOR  "xor"
#define INS_NAME_CALL "call"

#define REG_SUFFIX_BYTE "b"
#define REG_SUFFIX_WORD "w"
#define REG_SUFFIX_LONG "l"
#define REG_SUFFIX_QUAD "q"

void x86_emit_label(String_Builder* sb, const char* label);
void x86_emit_ret(String_Builder* sb);
void x86_emit_call(String_Builder* sb, const char* function);
void x86_emit_comment_line(String_Builder* sb, const char* comment);
void x86_emit_syscall(String_Builder* sb, Linux_Syscall syscall);
void x86_emit_exit_syscall(String_Builder* sb);
void x86_emit_start(String_Builder* sb);

/* ======================
   Values
   ====================== */
void x86_emit_asciz(String_Builder* sb, const char* name, const char* value);

/* ======================
   Stack related instructions
   ====================== */
void x86_emit_pop_reg(String_Builder* sb, Register reg);
void x86_emit_push_reg(String_Builder* sb, Register reg);

/* ======================
   Moves
   ====================== */
void x86_emit_move_reg_to_reg(String_Builder* sb, Register src, Register dst);
void x86_emit_move_lit_to_reg(String_Builder* sb, i32 num, Register dst);
void x86_emit_move_loc_to_loc(String_Builder* sb, IR_Location src, IR_Location dst, 
                              Scratch_Register_Table* table, Temp_Table* temp_table);
void x86_emit_move_reg_to_mem(String_Builder* sb, Register src, IR_Mem dst, 
                              Scratch_Register_Table* table, Temp_Table* temp_table);
void x86_emit_move_mem_to_mem(String_Builder* sb, IR_Mem src, IR_Mem dst, 
                              Scratch_Register_Table* table, Temp_Table* temp_table);
void x86_emit_move_mem_to_reg(String_Builder* sb, IR_Mem src, Register dst, 
                              Scratch_Register_Table* table, Temp_Table* temp_table);

/* ======================
   Comparisons
   ====================== */
void x86_emit_cmp_lit_to_loc(String_Builder* sb, i32 lhs, IR_Location rhs,
                             Scratch_Register_Table* table, Temp_Table* temp_table);

void x86_emit_cmp_loc_to_loc(String_Builder* sb, IR_Location lhs, IR_Location rhs,
                             Scratch_Register_Table* table, Temp_Table* temp_table);

void x86_emit_cmp_reg_to_reg(String_Builder* sb, Register s_lhs, Register s_rhs, IR_Op operator);

void x86_emit_setcc(String_Builder* sb, IR_Op operator, Register result_reg);

/* ======================
   Arithmetic instructions
   ====================== */
void x86_emit_unary(String_Builder* sb, Register reg);
void x86_emit_div(String_Builder* sb, Register src, Register dst);
void x86_emit_mul(String_Builder* sb, Register src, Register dst);
void x86_emit_sub(String_Builder* sb, Register src, Register dst);
void x86_emit_add(String_Builder* sb, Register src, Register dst);

void x86_emit_xor_reg_to_reg(String_Builder* sb, Register lhs, Register rhs);

/* ======================
   Interface
   ====================== */
String* x86_codegen_ir(IR_Program* program_node, Allocator* allocator);

#endif
