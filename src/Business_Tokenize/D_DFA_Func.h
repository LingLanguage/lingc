#ifndef D_DFA_Func_H__
#define D_DFA_Func_H__

#include "import.h"

void D_DFA_Func_Free(FAM_Func *dfa_func);
void D_DFA_Func_Enter(FAM_Func *dfa_func, E_Guess *guess);
void D_DFA_Func_Process(FAM_Func *dfa_func, const string code, const string word, M_Cursor *cursor);

#endif