#ifndef E_STATEMENT_H__
#define E_STATEMENT_H__

#include "E_Expression.h"
#include "import.h"

typedef struct E_Block E_Block;

// 语句
typedef struct E_Statement {

    StatementType statementType;

    // assignment
    bool assign_is_const;
    char **assign_words;
    int assign_words_capacity;
    int assign_words_count;

    // = / if / while / for / return
    E_Expression *bracket_expressions;
    int bracket_expressions_capacity;
    int bracket_expressions_count;

    // if / do / while / for
    // {}
    void *blocks;
    int blocks_capacity;
    int blocks_count;

} E_Statement;

E_Statement E_Statement_CreateReturn();
void E_Statement_Free(E_Statement *self);
void E_Statement_AddBracketExpression(E_Statement *self, E_Expression expression);
void E_Statement_AddBlock(E_Statement *self, E_Block block);
void E_Statement_Log(const E_Statement *self);

#endif