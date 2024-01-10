#ifndef M_DFA_BLOCK_H__
#define M_DFA_BLOCK_H__

#include "E_Block.h"
#include "M_NFA_Statement.h"
#include "import.h"

typedef struct M_DFA_Block {
    DFA_Block_Status status;
    M_NFA_Statement nfa_stmt;
    E_Block block;
    bool is_done;
} M_DFA_Block;

void M_DFA_Block_Init(M_DFA_Block *dfa_block);

#endif