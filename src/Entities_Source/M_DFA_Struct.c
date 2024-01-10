#include "M_DFA_Struct.h"

void M_DFA_Struct_Init(M_DFA_Struct *dfa_struct) {
    memset(dfa_struct, 0, sizeof(M_DFA_Struct));
}

void M_DFA_Struct_Free(M_DFA_Struct *dfa_struct) {
    free(dfa_struct);
}