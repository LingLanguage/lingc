#ifndef D_TOP_IMPORT_H__
#define D_TOP_IMPORT_H__

#include "import.h"

void D_DFA_Import_Free(M_DFA_Import *fsm);
void D_DFA_Import_Enter(M_DFA_Import *fsm);
void D_DFA_Import_Process(M_DFA_Import *fsm, const string code, const string word, M_Cursor *cursor);

#endif