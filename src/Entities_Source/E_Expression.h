#ifndef E_EXPRESSION_H__
#define E_EXPRESSION_H__

#include "M_Operator.h"
#include "M_Parameter.h"
#include "import.h"

// 表达式
// call function
// const value: custom const, string, number, bool, null
// variable
// return
typedef struct E_Expression {

    ExpressionType type;

} E_Expression;

#endif