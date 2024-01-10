#include "E_Expression.h"

void E_Expression_Init(E_Expression *self, ExpressionType type, int priority) {
    self->type = type;
    self->priority = priority;
    self->words = NULL;
    self->words_capacity = 4;
    self->words_count = 0;
}

void E_Expression_Free(E_Expression *self) {
    if (self->words != NULL) {
        for (int i = 0; i < self->words_count; i++) {
            free(self->words[i]);
        }
        free(self->words);
    }
}

void E_Expression_AddWord(E_Expression *self, const string word) {
    if (self->words == NULL) {
        self->words = (char **)malloc(sizeof(char *) * self->words_capacity);
    }
    if (self->words_count >= self->words_capacity) {
        self->words = (char **)realloc(self->words, sizeof(char *) * (self->words_capacity + 4));
        self->words_capacity += 4;
    }
    self->words[self->words_count] = (char *)malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(self->words[self->words_count], word);
    self->words_count++;
}
