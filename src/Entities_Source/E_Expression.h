#ifndef E_EXPRESSION_H__
#define E_EXPRESSION_H__

#include "M_Operator.h"
#include "M_Parameter.h"
#include "import.h"

// 表达式
typedef struct E_Expression {

    ExpressionType type;
    int priority;

    char **words;
    int words_capacity;
    int words_count;

} E_Expression;

void E_Expression_Init(E_Expression *self, ExpressionType type, int priority);
void E_Expression_Free(E_Expression *self);
void E_Expression_AddWord(E_Expression *self, const string word);

#endif