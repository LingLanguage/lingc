#ifndef M_DFA_IMPORT_H__
#define M_DFA_IMPORT_H__

typedef struct M_DFA_Import {
    E_Import import;
    bool is_recorded;
    bool is_done;
} M_DFA_Import;

void M_DFA_Import_Init(M_DFA_Import *fsm);
void M_DFA_Import_Free(M_DFA_Import *fsm);
void M_DFA_Import_Enter(M_DFA_Import *fsm);

#endif