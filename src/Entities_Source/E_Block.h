#ifndef E_BLOCK_H__
#define E_BLOCK_H__

#include "E_Statement.h"

typedef struct E_Block {

    E_Statement *statements;
    int statements_count;

    void *child_blocks;
    int child_blocks_count;

} E_Block;

void E_Block_Free(E_Block *self);

#endif