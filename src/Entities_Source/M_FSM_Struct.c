#include "M_FSM_Struct.h"

void M_FSM_Struct_Enter(M_FSM_Struct *fsm, const string access, bool is_static) {
    memset(fsm, 0, sizeof(M_FSM_Struct));
    strcpy(fsm->st.access, String_ValidAccess(access));
    fsm->st.is_static = is_static;
}

void M_FSM_Struct_EnterGuess(M_FSM_Struct *fsm) {
    fsm->phase = StructPhase_Guess;
    E_Guess_Reset(&fsm->guess);
    memset(&fsm->fsm_func, 0, sizeof(fsm->fsm_func));
}