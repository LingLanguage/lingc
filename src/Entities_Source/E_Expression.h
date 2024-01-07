#ifndef E_EXPRESSION_H__
#define E_EXPRESSION_H__

#include "M_Operator.h"
#include "M_Parameter.h"
#include "import.h"

// 表达式
// call function
// const value: custom const, string, number, bool, null
// variable
typedef struct E_Expression {

    ExpressionType type;

    M_Operator operator_before;
    M_Operator operator_after;

    // for call function
    char call_func_name[RULE_FUNCTION_NAME_LEN];
    char call_func_args[RULE_FUNCTION_PARAM_COUNT];

    // for const value
    char const_value[RULE_VAR_NAME_LEN];

    // for variable
    char var_name[RULE_VAR_NAME_LEN];

} E_Expression;

#endif