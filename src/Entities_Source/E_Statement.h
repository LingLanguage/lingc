#ifndef E_STATEMENT_H__
#define E_STATEMENT_H__

#include "E_Expression.h"
#include "import.h"

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
    int bracket_expressions_count;

    // if / do / while / for
    // {}
    E_Expression *block_expressions;
    int block_expressions_count;

} E_Statement;

E_Statement E_Statement_CreateReturn();
void E_Statement_Free(E_Statement *self);
void E_Statement_Log(const E_Statement *self);

#endif