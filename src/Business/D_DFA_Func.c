#include "D_DFA_Func.h"

void D_DFA_Func_Free(M_DFA_Func *dfa_func) {
}

void D_DFA_Func_Enter(M_DFA_Func *dfa_func, E_Guess *guess) {
    // already:
    // public static fn
    M_DFA_Func_Init(dfa_func, guess);
    PLogNA("Enter DFA Func\r\n");
}

void NamePhase_Process(M_DFA_Func *dfa_func, const string code, const string word, M_Cursor *cursor) {
    // (
}

void D_DFA_Func_Process(M_DFA_Func *dfa_func, const string code, const string word, M_Cursor *cursor) {
}