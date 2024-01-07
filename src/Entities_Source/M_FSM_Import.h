#ifndef M_FSM_IMPORT_H__
#define M_FSM_IMPORT_H__

typedef struct M_FSM_Import {
    bool isEntering;
    int leftIndex;
    int rightIndex;
    ImportType importType;
} M_FSM_Import;

void M_FSM_Import_Enter(M_FSM_Import *fsm);

#endif