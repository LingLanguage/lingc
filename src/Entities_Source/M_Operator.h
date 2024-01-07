#ifndef M_OPERATOR_H__
#define M_OPERATOR_H__

#include "import.h"

// 操作符
typedef struct M_Operator {
    OperatorType type;
    char name[RULE_OPERATOR_NAME_LEN];
} M_Operator;

M_Operator M_Operator_Create(const string name, OperatorType type);

#endif