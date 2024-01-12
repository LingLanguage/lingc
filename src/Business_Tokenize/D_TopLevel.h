#ifndef D_TopLevel_H__
#define D_TopLevel_H__

#include "import.h"

void D_TopLevel_Free(FAM_Top *fam);
void D_TopLevel_Enter(FAM_Top *fam, M_Cursor *cursor);
void D_TopLevel_Process(FAM_Top *fam, const string code, const string word, M_Cursor *cursor);

#endif