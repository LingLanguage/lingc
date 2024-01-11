#ifndef E_EXPRESSION_H__
#define E_EXPRESSION_H__

#include "M_Operator.h"
#include "M_Parameter.h"
#include "import.h"

typedef struct E_Expression E_Expression;

// 表达式
typedef struct E_Expression {

    ExpressionType type;

    char **words;
    int words_capacity;
    int words_count;

    E_Expression *child_exps;
    int child_exps_capacity;
    int child_exps_count;

} E_Expression;

void E_Expression_Init(E_Expression *self, ExpressionType type);
void E_Expression_Free(E_Expression *self);
void E_Expression_AddWord(E_Expression *self, const string word);
void E_Expression_AddChildExp(E_Expression *self, E_Expression *child_exp);

#endif