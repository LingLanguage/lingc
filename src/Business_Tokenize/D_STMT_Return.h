#ifndef D_NFA_STATEMENT_H__
#define D_NFA_STATEMENT_H__

#include "import.h"

void D_STMT_Return_Enter(FAM_STMT *nfa_stmt);
void D_STMT_Return_Process(FAM_STMT *nfa_stmt, const string code, const string word, M_Cursor *cursor);

#endif