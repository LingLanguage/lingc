#ifndef D_UNKNOWN_H__
#define D_UNKNOWN_H__

#include "import.h"

void D_Unknown_Enter(Context *ctx);
void D_Unknown_Process(Context *ctx, bool isSplit, const string word, const string code, long size);

#endif