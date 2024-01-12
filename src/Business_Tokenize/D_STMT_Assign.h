#ifndef D_STMT_ASSIGN_H__
#define D_STMT_ASSIGN_H__

#include "import.h"

void D_STMT_Assign_Enter(FAM_STMT *fam, char *op, char **left_words, int left_words_count);
void D_STMT_Assign_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor);

#endif