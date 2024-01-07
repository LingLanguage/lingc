#ifndef D_TOP_GUESS_H__
#define D_TOP_GUESS_H__

#include "import.h"

void D_Top_Guess_Enter(E_Doc *doc);
void D_Top_Guess_Process(E_Doc *doc, bool isSplit, const string word, const string code, long size);

#endif