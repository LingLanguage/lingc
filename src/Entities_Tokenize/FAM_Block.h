#ifndef FAM_BLOCK_H__
#define FAM_BLOCK_H__

#include "E_Block.h"
#include "FAM_STMT.h"
#include "import.h"

typedef struct FAM_Block FAM_Block;

typedef struct FAM_Block {
    Block_FA status;
    Block_FA last_status;
    FAM_STMT fam_stmt;
    E_Expression tmp_exp;
    FAM_Block *dfa_child_block;
    int block_id;
    E_Guess guess;
    bool is_done;
} FAM_Block;

void FAM_Block_Init(FAM_Block *dfa_block);
void FAM_Block_Free(FAM_Block *dfa_block);

#endif