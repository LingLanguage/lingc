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