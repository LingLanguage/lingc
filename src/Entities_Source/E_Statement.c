#include "E_Statement.h"

E_Statement E_Statement_CreateReturn() {
    E_Statement self = {0};
    self.statementType = StatementType_Return;
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

    if (self->block_expressions_count > 0) {
        for (int i = 0; i < self->block_expressions_count; i++) {
            E_Expression_Free(&self->block_expressions[i]);
        }
        free(self->block_expressions);
    }
}

void E_Statement_Log(const E_Statement *self) {
}