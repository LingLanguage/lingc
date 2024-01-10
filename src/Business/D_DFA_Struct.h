#ifndef D_TOP_STRUCT_H__
#define D_TOP_STRUCT_H__

#include "import.h"

void D_DFA_Struct_Enter(E_Doc *doc, E_Guess *guess);
int D_DFA_Struct_Process(M_FSM_Struct *fsm, const string file, int line, bool isSplit, const string word, int index, const string code, long size);

#endif