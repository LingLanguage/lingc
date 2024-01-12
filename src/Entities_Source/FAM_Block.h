#ifndef FAM_BLOCK_H__
#define FAM_BLOCK_H__

#include "E_Block.h"
#include "FAM_STMT.h"
#include "import.h"

typedef struct FAM_Block {
    Block_FA status;
    Block_FA last_status;
    FAM_STMT fam_stmt;
    void *dfa_child_block;
    E_Block block;
    E_Guess guess;
    bool is_done;
} FAM_Block;

void FAM_Block_Init(FAM_Block *dfa_block);
void FAM_Block_Free(FAM_Block *dfa_block);

#endif