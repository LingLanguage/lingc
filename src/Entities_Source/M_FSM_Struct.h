#ifndef M_FSM_STRUCT_H__
#define M_FSM_STRUCT_H__

#include "import.h"
#include "E_Struct.h"

typedef struct M_FSM_Struct {
    E_Struct st;
    StructPhase phase;
    byte nested_level;
    E_Guess guess;

    M_FSM_Func fsm_func;
    bool is_done;
} M_FSM_Struct;

void M_FSM_Struct_EnterGuess(M_FSM_Struct *fsm);
void M_FSM_Struct_EnterFunc(M_FSM_Struct *fsm, E_Guess *guess);

#endif