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
    bool is_done;
    char words[RULE_STRUCT_TYPE_NAME_MAX][RULE_FUNCTION_RETURN_COUNT + 1];
    int words_count;
} M_FSM_Func;

void M_FSM_Func_Enter(M_FSM_Func *fsm, const string access, bool is_static);
void M_FSM_Func_Process(M_FSM_Func *fsm, string file, int line, bool is_split, const string word, const string code, long size);

#endif