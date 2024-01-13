#ifndef E_GUESS_H__
#define E_GUESS_H__

#include "E_Field.h"
#include "E_Statement.h"
#include "E_Struct.h"
#include "import.h"

typedef struct E_Guess {

    char access[RULE_ACCESS_NAME_LEN];
    bool is_static;
    bool is_const;

    char last_word[RULE_VAR_NAME_LEN];

    char **words;
    byte words_capacity;
    byte words_count;

} E_Guess;

void E_Guess_Init(E_Guess *self);
void E_Guess_Free(E_Guess *self);
void E_Guess_InitAccess(E_Guess *self);
void E_Guess_SetAcceess(E_Guess *self, const string file, int line, const string access);
void E_Guess_PushWord(E_Guess *self, const string word);
void E_Guess_SetLastWord(E_Guess *self, const string word);
void E_Guess_CleanLastWord(E_Guess *self);
bool E_Guess_TryGetCalcOP(E_Guess *self, int *ref_index, const string code, const string word, const string last_word, OP_Type *op_type);

#endif