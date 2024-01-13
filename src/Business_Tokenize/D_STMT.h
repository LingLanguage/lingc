#ifndef D_STMT_GUESS_H__
#define D_STMT_GUESS_H__

#include "import.h"

void D_STMT_Enter(FAM_STMT *fam);
void D_STMT_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor);

#endif