#include "D_DFA_Func.h"

void D_DFA_Func_Free(M_DFA_Func *dfa_func) {
    PLogNA("free top func\r\n");
}

void D_DFA_Func_Enter(M_DFA_Func *dfa_func, E_Guess *guess) {
    M_DFA_Func_Enter(dfa_func, guess);
    PLogNA("enter top func\r\n");
}

int D_DFA_Func_Process(M_DFA_Func *dfa_func, const string file, int line, bool is_split, const string word, int index, const string code, long size) {
    return index;
}