#include "M_Cursor.h"

void M_Cursor_InitAccess(M_Cursor *self) {

    memset(self->access, 0, sizeof(self->access));
    self->is_const = false;
    self->is_static = false;

    for (int i = 0; i < self->words_capacity; i++) {
        free(self->words[i]);
    }
    if (self->words_capacity > 0) {
        free(self->words);
    }
    self->words_capacity = 0;
    self->words_count = 0;
}

void M_Cursor_SetAcceess(M_Cursor *self, const string access) {
    if (strlen(self->access) > 1) {
        PFailed(self->file, self->line, ERR_ACCESS_REDIFINED);
        return;
    }
    strcpy(self->access, String_ValidAccess(access));
}

void M_Cursor_PushWord(M_Cursor *self, const string input_word) {
    if (self->words_capacity == 0) {
        self->words_capacity = 2;
        self->words = malloc(sizeof(char *) * self->words_capacity);
    } else if (self->words_count == self->words_capacity) {
        self->words_capacity *= 2;
        self->words = realloc(self->words, sizeof(char *) * self->words_capacity);
    }
    char *w = malloc(sizeof(char) * (strlen(input_word) + 1));
    strcpy(w, input_word);
    self->words[self->words_count] = w;
    self->words_count++;
}

bool M_Cursor_TryGetAssignOP(M_Cursor *self, const string code, const string word, char *op) {
    // word is '='
    char next = code[self->index + 1];
    char prev1 = code[self->index - 1];
    char prev2 = code[self->index - 2];

    // false: ==
    if (next == OP_EQUAL) {
        return false;
    }

    // true: <<= >>=
    if (prev1 == prev2 && (prev1 == OP_CMP_LESS || prev1 == OP_CMP_GREATER)) {
        op[0] = prev2;
        op[1] = prev1;
        op[2] = '=';
        op[3] = '\0';
        return true;
    }

    // true: += -= *= /= %= ~= &= |= ^=
    switch (prev1) {
    case OP_SET_PLUS:     // +=
    case OP_SET_MINUS:    // -=
    case OP_SET_MULTIPLY: // *=
    case OP_SET_DIVIDE:   // /=
    case OP_SET_MOD:      // %=
    case OP_SET_BIN_NOT:  // ~=
    case OP_SET_BIN_AND:  // &=
    case OP_SET_BIN_OR:   // |=
    case OP_SET_BIN_XOR:  // ^=
        op[0] = prev1;
        op[1] = '=';
        op[2] = '\0';
        return true;
    }

    // true: =
    op[0] = OP_EQUAL;
    op[1] = '\0';
    return true;

}