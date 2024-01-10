#ifndef D_NFA_Top_H__
#define D_NFA_Top_H__

#include "import.h"

void D_NFA_Top_Enter(E_Doc *doc);
void D_NFA_Top_Process(E_Doc *doc, bool isSplit, const string word, const string code, long size);

#endif