#include "E_Expression.h"

void E_Expression_Init(E_Expression *self, ExpressionType type) {

    self->type = type; // type means priority

    self->words = NULL;
    self->words_capacity = 4;
    self->words_count = 0;

    self->child_exps_count = 0;
}

void E_Expression_Free(E_Expression *self) {
    if (self->words != NULL) {
        for (int i = 0; i < self->words_count; i++) {
            free(self->words[i]);
        }
        free(self->words);
    }

    if (self->child_exps != NULL) {
        for (int i = 0; i < self->child_exps_count; i++) {
            E_Expression *child_exp = &self->child_exps[i];
            E_Expression_Free(child_exp);
        }
        free(self->child_exps);
    }
}

void E_Expression_AddWord(E_Expression *self, const string word) {
    if (strlen(word) == 0) {
        return;
    }
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

void E_Expression_AddChildExp(E_Expression *self, int child_exp_id) {
    self->child_exps[self->child_exps_count] = child_exp_id;
    self->child_exps_count++;
}