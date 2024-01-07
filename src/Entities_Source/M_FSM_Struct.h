#ifndef M_FSM_STRUCT_H__
#define M_FSM_STRUCT_H__

#include "import.h"
#include "E_Struct.h"

typedef struct M_FSM_Struct {
    E_Struct st;
    StructPhase phase;
    byte nested_level;
    char guess_access[RULE_ACCESS_NAME_LEN];
    char guess_words[RULE_VAR_NAME_LEN][RULE_FUNCTION_RETURN_COUNT];
    byte guess_words_count;
    M_FSM_Func fsm_func;
} M_FSM_Struct;

void M_FSM_Struct_EnterGuess(M_FSM_Struct *fsm);

#endif