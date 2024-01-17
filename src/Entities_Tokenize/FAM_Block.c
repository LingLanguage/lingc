#include "FAM_Block.h"

void FAM_Block_Init(FAM_Block *dfa_block) {
    memset(dfa_block, 0, sizeof(FAM_Block));
}

void FAM_Block_Free(FAM_Block *dfa_block) {
    FAM_Block *child = dfa_block->dfa_child_block;
    if (child != NULL) {
        FAM_Block_Free(child);
        free(child);
    }
}