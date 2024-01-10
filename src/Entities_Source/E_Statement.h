#ifndef E_STATEMENT_H__
#define E_STATEMENT_H__

#include "E_Expression.h"
#include "import.h"

// 语句
typedef struct E_Statement {

    StatementType statementType;

    // assignment
    bool assign_is_const;
    char assign_words[RULE_VAR_NAME_LEN][RULE_FUNCTION_RETURN_COUNT];
    byte assign_words_count;

    // if / while / for
    E_Expression expression;

} E_Statement;

void E_Statement_SetType(E_Statement *self, const string type);
void E_Statement_AddName(E_Statement *self, const string name);
void E_Statement_SetExpression(E_Statement *self, E_Expression expression);
void E_Statement_SetOperator(E_Statement *self, M_Operator operator);
void E_Statement_AddExpressionOrigin(E_Statement *self, const string word);
void E_Statement_Log(const E_Statement *self);

#endif