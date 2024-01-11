#include "FAM_Import.h"

void FAM_Import_Init(FAM_Import *fsm) {
    memset(fsm, 0, sizeof(FAM_Import));
}

void FAM_Import_Free(FAM_Import *fsm) {
    free(fsm);
}

void FAM_Import_Enter(FAM_Import *fsm) {
    memset(fsm, 0, sizeof(FAM_Import));
    PLogNA("enter import\r\n");
}