#ifndef D_STRUCT_H__
#define D_STRUCT_H__

#include "import.h"

void D_Struct_Enter(Context *ctx, const string access, bool is_static);
void D_Struct_Process(Context *ctx, bool isSplit, const string word, const string code, long size);

#endif