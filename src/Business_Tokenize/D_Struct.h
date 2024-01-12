#ifndef D_TOP_STRUCT_H__
#define D_TOP_STRUCT_H__

#include "import.h"

void D_Struct_Free(FAM_Struct *fam);
void D_Struct_Enter(FAM_Struct *fam, M_Cursor *cursor);
void D_Struct_Process(FAM_Struct *fam, const string code, const string word, M_Cursor *cursor);

#endif