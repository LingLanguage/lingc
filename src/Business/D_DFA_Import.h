#ifndef D_TOP_IMPORT_H__
#define D_TOP_IMPORT_H__

#include "import.h"

void D_DFA_Import_Enter(M_FSM_Import *fsm);
int D_DFA_Import_Process(M_FSM_Import *fsm, const string file, int line, bool is_split, const string word, int index, const string code, long size);

#endif