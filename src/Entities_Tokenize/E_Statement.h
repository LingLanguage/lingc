#ifndef E_STATEMENT_H__
#define E_STATEMENT_H__

#include "E_Expression.h"
#include "import.h"

typedef struct E_Block E_Block;

// 语句
typedef struct E_Statement {

    StatementType type;

    // left
    int left_exp_id;
    OP_Type assign_op_type;

    // = / if / while / for / return
    int bracket_expressions_ids[64];
    int bracket_expressions_count;

    // if / do / while / for
    // {}
    int blocks[64];
    int blocks_count;

} E_Statement;

E_Statement E_Statement_CreateReturn();
E_Statement E_Statement_CreateAssign(OP_Type assign_op_type);
void E_Statement_Free(E_Statement *self);
void E_Statement_SetLeftExpression(E_Statement *self, int exp_id);
void E_Statement_AddBracketExpression(E_Statement *self, int exp_id);
void E_Statement_AddBlock(E_Statement *self, int block_id);
void E_Statement_Log(const E_Statement *self);

#endif