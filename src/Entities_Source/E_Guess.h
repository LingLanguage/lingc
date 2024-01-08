#ifndef E_GUESS_H__
#define E_GUESS_H__

#include "E_Field.h"
#include "E_Statement.h"
#include "import.h"

typedef struct E_Guess {
    char access[RULE_ACCESS_NAME_LEN];
    bool is_static;
    bool is_const;
    char words[RULE_VAR_NAME_LEN][RULE_EXPRESSION_WORDS_COUNT];
    byte words_count;
} E_Guess;

void E_Guess_Reset(E_Guess *self);
void E_Guess_SetAccess(E_Guess *self, const string file, int line, const string access);
void E_Guess_PushWord(E_Guess *self, const string file, int line, const string word);
bool E_Guess_Field(E_Guess *self, const string file, int line, E_Field *field);
bool E_Guess_Statement(E_Guess *self, const string file, int line, byte nested_level, char *op, byte op_count, E_Statement *statement);

#endif