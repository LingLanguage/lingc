#ifndef D_FUNC_H__
#define D_FUNC_H__

#include "import.h"

void D_Func_Enter(Context *ctx, const string access);
void D_Func_Process(Context *ctx, bool isSplit, const string word, const string code, long size);

#endif