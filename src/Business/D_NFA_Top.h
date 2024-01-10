#ifndef D_NFA_Top_H__
#define D_NFA_Top_H__

#include "import.h"

void D_NFA_Top_Free(M_NFA_Top *nfa_top);
void D_NFA_Top_Enter(M_NFA_Top *nfa_top);
void D_NFA_Top_Process(M_NFA_Top *nfa_top, const string code, const string word, M_Cursor *cursor);

#endif