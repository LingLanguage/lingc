#include "M_DFA_Import.h"

void M_DFA_Import_Init(M_DFA_Import *fsm) {
    memset(fsm, 0, sizeof(M_DFA_Import));
}

void M_DFA_Import_Free(M_DFA_Import *fsm) {
    free(fsm);
}

void M_DFA_Import_Enter(M_DFA_Import *fsm) {
    memset(fsm, 0, sizeof(M_DFA_Import));
    PLogNA("enter import\r\n");
}