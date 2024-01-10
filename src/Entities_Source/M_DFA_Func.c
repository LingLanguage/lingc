#include "M_DFA_Func.h"

void M_DFA_Func_Init(M_DFA_Func *fsm, E_Guess *guess) {
    memset(fsm, 0, sizeof(M_DFA_Func));
    String_CopyAccess(fsm->guess.access, guess->access);
    fsm->guess.is_const = guess->is_const;
    fsm->guess.is_static = guess->is_static;
}

void M_DFA_Func_Free(M_DFA_Func *fsm) {
    E_Function_Free(&fsm->function);
    free(fsm);
}