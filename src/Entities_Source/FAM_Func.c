#include "FAM_Func.h"

void FAM_Func_Init(FAM_Func *fsm, E_Guess *guess) {
    memset(fsm, 0, sizeof(FAM_Func));
    String_CopyAccess(fsm->guess.access, guess->access);
    fsm->guess.is_const = guess->is_const;
    fsm->guess.is_static = guess->is_static;
}

void FAM_Func_Free(FAM_Func *fsm) {
    E_Function_Free(&fsm->function);
    free(fsm);
}