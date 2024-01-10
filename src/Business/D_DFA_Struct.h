#ifndef D_TOP_STRUCT_H__
#define D_TOP_STRUCT_H__

#include "import.h"

void D_DFA_Struct_Free(M_DFA_Struct *dfa_struct);
void D_DFA_Struct_Enter(M_DFA_Struct *dfa_struct, const string file, int line, E_Guess *guess);
int D_DFA_Struct_Process(M_DFA_Struct *dfa_struct, const string file, int line, bool isSplit, const string word, int index, const string code, long size);

#endif