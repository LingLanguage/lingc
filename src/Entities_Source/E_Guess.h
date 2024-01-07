#ifndef E_GUESS_H__
#define E_GUESS_H__

#include "import.h"
#include "E_Field.h"

typedef struct E_Guess {
    char access[RULE_ACCESS_NAME_LEN];
    bool is_static;
    char words[RULE_VAR_NAME_LEN][10];
    byte words_count;
} E_Guess;

void E_Guess_Reset(E_Guess *self);
void E_Guess_SetAccess(E_Guess *self, string file, int line, const string access);
void E_Guess_PushWord(E_Guess *self, string file, int line, const string word);
bool E_Guess_Field(E_Guess *self, string file, int line, E_Field *field);

#endif