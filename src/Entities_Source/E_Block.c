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