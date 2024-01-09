#include "M_FSM_Struct.h"

void M_FSM_Struct_EnterGuess(M_FSM_Struct *fsm) {
    fsm->phase = StructPhase_Guess;
    E_Guess_Reset(&fsm->guess);
    memset(&fsm->fsm_func, 0, sizeof(fsm->fsm_func));
}

void M_FSM_Struct_EnterFunc(M_FSM_Struct *fsm, E_Guess *guess) {
    fsm->phase = StructPhase_Func;
    M_FSM_Func_Enter(&fsm->fsm_func, &fsm->guess);
}