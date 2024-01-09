#include "M_FSM_Import.h"

void M_FSM_Import_Enter(M_FSM_Import *fsm) {
    memset(fsm, 0, sizeof(M_FSM_Import));
    PLogNA("enter import\r\n");
}