#ifndef D_FUNC_H__
#define D_FUNC_H__

#include "import.h"

void D_Top_Func_Enter(Context *ctx, const string access, bool is_static);
void D_Top_Func_Process(Context *ctx, bool is_split, const string word, const string code, long size);

#endif