#ifndef D_TOP_STRUCT_H__
#define D_TOP_STRUCT_H__

#include "import.h"

void D_DFA_Struct_Free(FAM_Struct *dfa_struct);
void D_DFA_Struct_Enter(FAM_Struct *dfa_struct, const string file, int line, E_Guess *guess);
int D_DFA_Struct_Process(FAM_Struct *dfa_struct, const string file, int line, bool isSplit, const string word, int index, const string code, long size);

#endif