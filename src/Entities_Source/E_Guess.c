#include "E_Guess.h"

void E_Guess_Init(E_Guess *self) {
    self->words_count = 0;
}

void E_Guess_Free(E_Guess *self) {
    if (self->words_capacity > 0) {
        for (int i = 0; i < self->words_capacity; i++) {
            free(self->words[i]);
        }
        free(self->words);
    }
}

void E_Guess_SetAccess(E_Guess *self, const string file, int line, const string access) {
    if (strlen(self->access) > 1) {
        PFailed(file, line, ERR_ACCESS_REDIFINED);
        return;
    }
    strcpy(self->access, String_ValidAccess(access));
}

void E_Guess_SetConst(E_Guess *self, const string file, int line, bool is_const) {
    if (self->is_const && is_const) {
        PFailed(file, line, ERR_CONST_REDIFINED);
        return;
    }
    self->is_const = is_const;
}

void E_Guess_SetStatic(E_Guess *self, const string file, int line, bool is_static) {
    if (self->is_static && is_static) {
        PFailed(file, line, ERR_STATIC_REDIFINED);
        return;
    }
    self->is_static = is_static;
}

void E_Guess_PushWord(E_Guess *self, const string file, int line, const string word) {
    if (self->words_count == 0) {
        self->words_capacity = 2;
        self->words = malloc(sizeof(char *));
    } else if (self->words_count == self->words_capacity) {
        self->words_capacity *= 2;
        self->words = realloc(self->words, sizeof(char *) * self->words_capacity);
    }
    self->words[self->words_count] = malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(self->words[self->words_count], word);
    self->words_count++;
}

// ==== Guess ====
bool E_Guess_GuessField(E_Guess *self, const string file, int line, E_Field *field) {
    bool is_ok = true;
    if (self->words_count == 2) {
        *field = E_Field_Create(self->access, self->words[0], self->words[1]);
    } else {
        PLog("words_count:%d\r\n", self->words_count);
        PFailed(file, line, ERR_FIELD_COUNT);
        is_ok = false;
    }

    if (is_ok) {
        E_Guess_Init(self);
    }
    return is_ok;
}

void E_Guess_ExpressionLog(const E_Guess *self) {
    // printf("%s %s:\r\n", self->access, self->is_static);
    printf("expression:");
    for (int i = 0; i < self->words_count; i++) {
        printf("%s ", self->words[i]);
    }
    printf("\r\n");
}