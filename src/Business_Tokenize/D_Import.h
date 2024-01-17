#ifndef D_TOP_IMPORT_H__
#define D_TOP_IMPORT_H__

#include "import.h"

void D_Import_Enter(CTX_Tokenize *ctx, FAM_Import *fsm);
void D_Import_Process(CTX_Tokenize *ctx, FAM_Import *fsm, const string code, const string word, M_Cursor *cursor);

#endif