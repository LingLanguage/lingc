#ifndef M_FSM_FUNC_H__
#define M_FSM_FUNC_H__

#include "E_Function.h"
#include "M_Var.h"
#include "import.h"

typedef struct M_FSM_Func {

    FuncPhase phase;

    E_Function function;

    // for return type
    char words[RULE_STRUCT_TYPE_NAME_LEN][RULE_FUNCTION_RETURN_COUNT + 1];
    int words_count;

    char tmp_param_type[RULE_STRUCT_TYPE_NAME_LEN];
    char tmp_param_name[RULE_VAR_NAME_LEN];
    bool tmp_is_in_param_name;

    bool is_done;

} M_FSM_Func;

void M_FSM_Func_Enter(M_FSM_Func *fsm, const string access, bool is_static);
void M_FSM_Func_Process(M_FSM_Func *fsm, string file, int line, bool is_split, const string word, const string code, long size);
void M_FSM_Func_EnterParams(M_FSM_Func *fsm);
#endif