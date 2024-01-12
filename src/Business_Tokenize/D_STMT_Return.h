#ifndef D_NFA_STATEMENT_H__
#define D_NFA_STATEMENT_H__

#include "import.h"

void D_STMT_Return_Enter(FAM_STMT *fam);
void D_STMT_Return_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor);

#endif