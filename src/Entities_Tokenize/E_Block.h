#ifndef E_BLOCK_H__
#define E_BLOCK_H__

#include "import.h"

typedef struct E_Statement E_Statement;
typedef struct E_Block E_Block;
typedef struct E_Statement E_Statement;

// 代码块
typedef struct E_Block {

    E_Statement *statements;
    int statements_capacity;
    int statements_count;

    E_Block *child_blocks;
    int child_blocks_capacity;
    int child_blocks_count;

} E_Block;

void E_Block_Free(E_Block *self);
void E_Block_DeepClone(E_Block *self, const E_Block *block);
void E_Block_AddChildBlock(E_Block *self, const E_Block *child);
void E_Block_AddStatement(E_Block *self, E_Statement statement);

#endif