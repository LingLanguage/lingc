#include "M_FSM_Struct.h"

void M_FSM_Struct_EnterGuess(M_FSM_Struct *fsm) {
    fsm->phase = StructPhase_Guess;
    memset(fsm->guess_access, 0, sizeof(fsm->guess_access));
    memset(fsm->guess_words, 0, sizeof(fsm->guess_words));
    fsm->guess_words_count = 0;
    memset(&fsm->fsm_func, 0, sizeof(fsm->fsm_func));
}