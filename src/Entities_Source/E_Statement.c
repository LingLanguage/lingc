#include "E_Statement.h"
#include "E_Block.h"

E_Statement E_Statement_CreateReturn() {
    E_Statement self = {0};
    self.type = StatementType_Return;
    return self;
}

E_Statement E_Statement_CreateAssign() {
    E_Statement self = {0};
    self.type = StatementType_Assign;
    return self;
}

void E_Statement_Free(E_Statement *self) {

    if (self->assign_words_count > 0) {
        for (int i = 0; i < self->assign_words_count; i++) {
            free(self->assign_words[i]);
        }
        free(self->assign_words);
    }

    if (self->bracket_expressions_count > 0) {
        for (int i = 0; i < self->bracket_expressions_count; i++) {
            E_Expression_Free(&self->bracket_expressions[i]);
        }
        free(self->bracket_expressions);
    }

    if (self->blocks_count > 0) {
        for (int i = 0; i < self->blocks_count; i++) {
            void *child_block = self->blocks + i * sizeof(E_Block);
            E_Block_Free((E_Block *)child_block);
        }
        free(self->blocks);
    }

}

void E_Statement_AddAssignLeftWord(E_Statement *self, char *word) {
    if (self->assign_words_count == 0) {
        self->assign_words_capacity = 2;
        self->assign_words = malloc(sizeof(char *));
    } else if (self->assign_words_count == self->assign_words_capacity) {
        self->assign_words_capacity *= 2;
        self->assign_words = realloc(self->assign_words, sizeof(char *) * self->assign_words_capacity);
    }
    strcpy(self->assign_words[self->assign_words_count], word);
    self->assign_words_count++;
}

void E_Statement_AddBracketExpression(E_Statement *self, E_Expression expression) {
    if (self->bracket_expressions_count == 0) {
        self->bracket_expressions_capacity = 2;
        self->bracket_expressions = malloc(sizeof(E_Expression));
    } else if (self->bracket_expressions_count == self->bracket_expressions_capacity) {
        self->bracket_expressions_capacity *= 2;
        self->bracket_expressions = realloc(self->bracket_expressions, sizeof(E_Expression) * self->bracket_expressions_capacity);
    }
    self->bracket_expressions[self->bracket_expressions_count] = expression;
    self->bracket_expressions_count++;
}

void E_Statement_AddBlock(E_Statement *self, E_Block block) {
    if (self->blocks_count == 0) {
        self->blocks_capacity = 2;
        self->blocks = malloc(sizeof(E_Block));
    } else if (self->blocks_count == self->blocks_capacity) {
        self->blocks_capacity *= 2;
        self->blocks = realloc(self->blocks, sizeof(E_Block) * self->blocks_capacity);
    }
    void *child_block = self->blocks + self->blocks_count * sizeof(E_Block);
    memcpy(child_block, &block, sizeof(E_Block));
    self->blocks_count++;
}

void E_Statement_Log(const E_Statement *self) {
}