#ifndef D_BLOCK_H__
#define D_BLOCK_H__

#include "import.h"

void D_Block_Enter(FAM_Block *dfa_block);
void D_Block_Process(FAM_Block *dfa_block, const string code, const string word, M_Cursor *cursor);

#endif