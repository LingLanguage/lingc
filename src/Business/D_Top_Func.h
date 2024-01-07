#ifndef D_TOP_FUNC_H__
#define D_TOP_FUNC_H__

#include "import.h"

void D_Top_Func_Enter(E_Doc *doc, const string access, bool is_static);
void D_Top_Func_Process(E_Doc *doc, bool is_split, const string word, const string code, long size);

#endif