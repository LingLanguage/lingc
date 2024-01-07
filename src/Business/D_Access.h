#ifndef D_ACCESS_H__
#define D_ACCESS_H__

#include "import.h"

void D_Access_Enter(Context* ctx);
void D_Access_Process(Context* ctx, bool isSplit, const string word, const string code, long size);

#endif