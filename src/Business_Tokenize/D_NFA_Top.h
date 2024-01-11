#ifndef D_NFA_Top_H__
#define D_NFA_Top_H__

#include "import.h"

void D_NFA_Top_Free(FAM_Top *nfa_top);
void D_NFA_Top_Enter(FAM_Top *nfa_top);
void D_NFA_Top_Process(FAM_Top *nfa_top, const string code, const string word, M_Cursor *cursor);

#endif