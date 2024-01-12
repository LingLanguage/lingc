#include "FAM_Func.h"

void FAM_Func_Init(FAM_Func *fsm, char *access, bool is_static) {

    memset(fsm, 0, sizeof(FAM_Func));

    String_CopyAccess(fsm->function.access, access);
    fsm->function.is_static = is_static;
}

void FAM_Func_Free(FAM_Func *fsm) {
    E_Function_Free(&fsm->function);
    free(fsm);
}