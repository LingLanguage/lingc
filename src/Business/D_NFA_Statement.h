#ifndef D_NFA_STATEMENT_H__
#define D_NFA_STATEMENT_H__

#include "import.h"

void D_NFA_Statement_EnterReturnSTMT(M_NFA_Statement *nfa_stmt);
void D_NFA_Statement_Process(M_NFA_Statement *nfa_stmt, const string code, const string word, M_Cursor *cursor);

#endif