#ifndef M_OPERATOR_H__
#define M_OPERATOR_H__

// 操作符
typedef struct M_Operator {
    OperatorType type;
    char name[RULE_OPERATOR_NAME_LEN];
} M_Operator;

#endif