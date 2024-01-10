#include "D_DFA_Func.h"

void D_DFA_Func_Enter(M_FSM_Func *fsm, E_Guess *guess) {
    M_FSM_Func_Enter(fsm, guess);
    PLogNA("enter top func\r\n");
}

int D_DFA_Func_Process(M_FSM_Func *fsm, const string file, int line, bool is_split, const string word, int index, const string code, long size) {
    index = M_FSM_Func_Process(fsm, file, line, is_split, word, index, code, size);
    return index;
}