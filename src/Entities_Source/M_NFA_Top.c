#include "M_NFA_Top.h"

void M_NFA_Top_Init(M_NFA_Top *nfa_top) {
    nfa_top->status = NFA_Top_Status_Guess;
    nfa_top->dfa_struct = calloc(1, sizeof(M_DFA_Struct));
    nfa_top->dfa_import = calloc(1, sizeof(M_DFA_Import));
    nfa_top->dfa_func = calloc(1, sizeof(M_DFA_Func));
    E_Guess_Init(&nfa_top->guess);
}

void M_NFA_Top_Free(M_NFA_Top *nfa_top) {
    M_DFA_Func_Free(nfa_top->dfa_func);
    M_DFA_Import_Free(nfa_top->dfa_import);
    M_DFA_Struct_Free(nfa_top->dfa_struct);
    free(nfa_top);
}