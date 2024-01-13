#include "E_Expression.h"

void E_Expression_Init(E_Expression *self, ExpressionType type) {

    self->type = type; // type means priority

    self->words = NULL;
    self->words_capacity = 4;
    self->words_count = 0;

    self->child_exps = NULL;
    self->child_exps_capacity = 1;
    self->child_exps_count = 0;
}

void E_Expression_DeepClone(E_Expression *self, E_Expression *other) {
    self->type = other->type;
    self->op_type = other->op_type;

    if (other->words_capacity > 0) {
        self->words = (char **)malloc(sizeof(char *) * other->words_capacity);
        for (int i = 0; i < other->words_count; i++) {
            self->words[i] = (char *)malloc(sizeof(char) * (strlen(other->words[i]) + 1));
            strcpy(self->words[i], other->words[i]);
        }
        self->words_capacity = other->words_capacity;
        self->words_count = other->words_count;
    }

    if (other->child_exps_capacity > 0) {
        self->child_exps = (E_Expression *)malloc(sizeof(E_Expression) * other->child_exps_capacity);
        for (int i = 0; i < other->child_exps_count; i++) {
            E_Expression_DeepClone(&self->child_exps[i], &other->child_exps[i]);
        }
        self->child_exps_capacity = other->child_exps_capacity;
        self->child_exps_count = other->child_exps_count;
    }
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

void E_Expression_AddChildExp(E_Expression *self, E_Expression *child_exp) {
    if (self->child_exps == NULL) {
        self->child_exps = (E_Expression *)malloc(sizeof(E_Expression) * self->child_exps_capacity);
    }
    if (self->child_exps_count >= self->child_exps_capacity) {
        self->child_exps = (E_Expression *)realloc(self->child_exps, sizeof(E_Expression) * (self->child_exps_capacity + 1));
        self->child_exps_capacity += 1;
    }
    E_Expression_DeepClone(&self->child_exps[self->child_exps_count], child_exp);
    self->child_exps_count++;
}