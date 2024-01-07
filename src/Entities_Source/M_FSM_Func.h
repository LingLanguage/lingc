#ifndef M_FSM_FUNC_H__
#define M_FSM_FUNC_H__

#include "import.h"
#include "M_Var.h"
#include "E_Function.h"

typedef struct M_FSM_Func {
    FuncPhase phase;
    char paramType[RULE_STRUCT_TYPE_NAME_MAX];
    char paramName[RULE_VAR_NAME_MAX];
    bool isParamType;
    E_Function function;
} M_FSM_Func;

#endif