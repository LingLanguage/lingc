#ifndef D_Func_H__
#define D_Func_H__

#include "import.h"

void D_Func_Free(FAM_Func *fam);
void D_Func_Enter(FAM_Func *fam, string access, bool is_static);
void D_Func_Process(FAM_Func *fam, const string code, const string word, M_Cursor *cursor);

#endif