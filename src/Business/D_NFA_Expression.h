#ifndef D_NFA_EXPRESSION_H__
#define D_NFA_EXPRESSION_H__

#include "import.h"

void D_NFA_Expression_Enter(M_NFA_Expression *nfa_exp);
void D_NFA_Expression_Process(M_NFA_Expression *nfa_exp, const string code, const string word, M_Cursor *cursor);

#endif