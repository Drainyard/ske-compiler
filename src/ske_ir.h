#ifndef ARC_IR_H
#define ARC_IR_H

typedef enum
{
    IR_PROGRAM,
    IR_SEQUENCE,
    
} IR_Node_Type;


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
