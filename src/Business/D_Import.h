#ifndef D_IMPORT_H__
#define D_IMPORT_H__

#include "import.h"

void D_Import_Enter(Context *ctx);
void D_Import_Process(Context *ctx, bool isSplit, const string word, const string code, long size);

#endif