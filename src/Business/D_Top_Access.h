#ifndef D_TOP_ACCESS_H__
#define D_TOP_ACCESS_H__

#include "import.h"

void D_Top_Access_Enter(E_Doc *doc, const string access);
void D_Top_Access_Process(E_Doc *doc, bool is_split, const string word, const string code, long size);

#endif