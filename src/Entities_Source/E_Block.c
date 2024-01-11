#include "E_Block.h"

void E_Block_Free(E_Block *self) {
    if (self->statements_count > 0) {
        for (int i = 0; i < self->statements_count; i++) {
            E_Statement_Free(&self->statements[i]);
        }
        free(self->statements);
    }
    if (self->child_blocks_count > 0) {
        for (int i = 0; i < self->child_blocks_count; i++) {
            void *child_block = self->child_blocks + i * sizeof(E_Block);
            E_Block_Free((E_Block *)child_block);
        }
        free(self->child_blocks);
    }
}

void E_Block_AddBlock(E_Block *self, E_Block block) {
    if (self->child_blocks_count == 0) {
        self->child_blocks_capacity = 1;
        self->child_blocks = malloc(sizeof(E_Block));
    } else if (self->child_blocks_count == self->child_blocks_capacity) {
        self->child_blocks_capacity *= 2;
        self->child_blocks = realloc(self->child_blocks, sizeof(E_Block) * self->child_blocks_capacity);
    }
    void *child_block = self->child_blocks + self->child_blocks_count * sizeof(E_Block);
    memcpy(child_block, &block, sizeof(E_Block));
    self->child_blocks_count++;
}

void E_Block_AddStatement(E_Block *self, E_Statement statement) {
    if (self->statements_count == 0) {
        self->statements_capacity = 1;
        self->statements = malloc(sizeof(E_Statement));
    } else if (self->statements_count == self->statements_capacity) {
        self->statements_capacity *= 2;
        self->statements = realloc(self->statements, sizeof(E_Statement) * self->statements_capacity);
    }
    self->statements[self->statements_count] = statement;
    self->statements_count++;
}