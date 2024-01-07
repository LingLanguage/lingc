#include "M_Operator.h"

M_Operator M_Operator_Create(const string name, OperatorType type) {
    M_Operator operator;
    strcpy(operator.name, name);
    operator.type = type;
    return operator;
}