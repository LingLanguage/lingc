#ifndef D_ACCESS_H__
#define D_ACCESS_H__

#include "import.h"

void D_Access_Enter(Context* ctx, const string access);
void D_Access_Process(Context* ctx, bool is_split, const string word, const string code, long size);

#endif