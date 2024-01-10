#ifndef D_DFA_Func_H__
#define D_DFA_Func_H__

#include "import.h"

void D_DFA_Func_Enter(M_FSM_Func *doc, E_Guess *guess);
int D_DFA_Func_Process(M_FSM_Func *doc, const string file, int line, bool is_split, const string word, int index, const string code, long size);

#endif