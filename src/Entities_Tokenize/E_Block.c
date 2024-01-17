#include "E_Block.h"
#include "E_Statement.h"

void E_Block_Free(E_Block *self) {
    if (self->statements_count > 0) {
        for (int i = 0; i < self->statements_count; i++) {
            E_Statement_Free(&self->statements[i]);
        }
        free(self->statements);
    }
    if (self->child_blocks_count > 0) {
        for (int i = 0; i < self->child_blocks_count; i++) {
            E_Block *child_block = &self->child_blocks[i];
            E_Block_Free(child_block);
        }
        free(self->child_blocks);
    }
}

void E_Block_DeepClone(E_Block *self, const E_Block *other) {
    if (other->statements_count > 0) {
        self->statements_capacity = other->statements_capacity;
        self->statements_count = other->statements_count;
        self->statements = malloc(sizeof(E_Statement) * self->statements_capacity);
        for (int i = 0; i < self->statements_count; i++) {
            E_Statement_DeepClone(&self->statements[i], &other->statements[i]);
        }
    }

    if (other->child_blocks_count > 0) {
        self->child_blocks_capacity = other->child_blocks_capacity;
        self->child_blocks_count = other->child_blocks_count;
        self->child_blocks = malloc(sizeof(E_Block) * self->child_blocks_capacity);
        for (int i = 0; i < self->child_blocks_count; i++) {
            E_Block_DeepClone(&self->child_blocks[i], &other->child_blocks[i]);
        }
    }
}

void E_Block_AddChildBlock(E_Block *self, const E_Block* child) {
    if (self->child_blocks_count == 0) {
        self->child_blocks_capacity = 1;
        self->child_blocks = malloc(sizeof(E_Block));
    } else if (self->child_blocks_count == self->child_blocks_capacity) {
        self->child_blocks_capacity *= 2;
        self->child_blocks = realloc(self->child_blocks, sizeof(E_Block) * self->child_blocks_capacity);
    }
    E_Block_DeepClone(&self->child_blocks[self->child_blocks_count], child);
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