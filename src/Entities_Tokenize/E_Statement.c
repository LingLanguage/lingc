#include "E_Statement.h"
#include "E_Block.h"

E_Statement E_Statement_CreateReturn() {
    E_Statement self = {0};
    self.type = StatementType_Return;
    return self;
}

E_Statement E_Statement_CreateAssign(OP_Type assign_op_type) {
    E_Statement self = {0};
    self.type = StatementType_Assign;
    self.assign_op_type = assign_op_type;
    return self;
}

void E_Statement_Free(E_Statement *self) {

}

void E_Statement_SetLeftExpression(E_Statement *self, int exp_id) {
    self->left_exp_id = exp_id;
}

void E_Statement_AddBracketExpression(E_Statement *self, int exp_id) {
    self->bracket_expressions_ids[self->bracket_expressions_count++] = exp_id;
}

void E_Statement_AddBlock(E_Statement *self, int block_id) {
    self->blocks[self->blocks_count++] = block_id;
}

void E_Statement_Log(const E_Statement *self) {
}