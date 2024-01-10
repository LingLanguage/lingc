#ifndef M_FSM_FUNC_H__
#define M_FSM_FUNC_H__

#include "E_Function.h"
#include "E_Guess.h"
#include "M_Parameter.h"
#include "M_DFA_Block.h"
#include "import.h"

typedef struct M_DFA_Func {

    FuncPhase phase;

    M_DFA_Block dfa_block;

    E_Function function;

    byte nested_level;

    // name and return type
    E_Guess guess;

    // params
    char tmp_param_type[RULE_STRUCT_TYPE_NAME_LEN];
    char tmp_param_name[RULE_VAR_NAME_LEN];
    bool tmp_is_in_param_name;

    bool is_done;

} M_DFA_Func;

void M_DFA_Func_Init(M_DFA_Func *fsm, E_Guess *guess);
void M_DFA_Func_Free(M_DFA_Func *fsm);
#endif