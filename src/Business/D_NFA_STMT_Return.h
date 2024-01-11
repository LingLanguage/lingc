#ifndef D_NFA_STATEMENT_H__
#define D_NFA_STATEMENT_H__

#include "import.h"

void D_NFA_STMT_Return_Enter(M_NFA_STMT_Return *nfa_stmt);
void D_NFA_STMT_Return_Process(M_NFA_STMT_Return *nfa_stmt, const string code, const string word, M_Cursor *cursor);

#endif