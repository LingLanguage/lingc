#ifndef E_STATEMENT_H__
#define E_STATEMENT_H__

#include "import.h"
#include "E_Expression.h"

// 声明
typedef struct E_Statement {
    char type[RULE_STRUCT_TYPE_NAME_LEN];
    char names[RULE_VAR_NAME_LEN][RULE_FUNCTION_RETURN_COUNT];
    byte names_count;
    bool is_const;
    byte belong_nested_level;
    StatementType statementType;
    M_Operator operator;
    E_Expression expression;
    char expression_origin[RULE_VAR_NAME_LEN][RULE_EXPRESSION_WORDS_COUNT];
    int expression_origin_count;
} E_Statement;

void E_Statement_SetType(E_Statement *self, const string type);
void E_Statement_AddName(E_Statement *self, const string name);
void E_Statement_SetExpression(E_Statement *self, E_Expression expression);
void E_Statement_SetOperator(E_Statement *self, M_Operator operator);
void E_Statement_AddExpressionOrigin(E_Statement *self, const string word);
void E_Statement_Log(const E_Statement *self);

#endif