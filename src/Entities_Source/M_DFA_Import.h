#ifndef M_DFA_IMPORT_H__
#define M_DFA_IMPORT_H__

typedef struct M_DFA_Import {
    bool isEntering;
    int leftIndex;
    int rightIndex;
    ImportType importType;
    bool is_done;
    E_Import import;
} M_DFA_Import;

void M_DFA_Import_Init(M_DFA_Import *fsm);
void M_DFA_Import_Free(M_DFA_Import *fsm);
void M_DFA_Import_Enter(M_DFA_Import *fsm);

#endif