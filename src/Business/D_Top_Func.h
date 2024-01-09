#ifndef D_TOP_FUNC_H__
#define D_TOP_FUNC_H__

#include "import.h"

void D_Top_Func_Enter(M_FSM_Func *doc, E_Guess *guess);
int D_Top_Func_Process(M_FSM_Func *doc, const string file, int line, bool is_split, const string word, int index, const string code, long size);

#endif