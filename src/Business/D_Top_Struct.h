#ifndef D_TOP_STRUCT_H__
#define D_TOP_STRUCT_H__

#include "import.h"

void D_Top_Struct_Enter(E_Doc *doc, const string access, bool is_static);
int D_Top_Struct_Process(E_Doc *doc, bool isSplit, const string word, int index, const string code, long size);

#endif