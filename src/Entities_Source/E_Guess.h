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
    char words[RULE_VAR_NAME_LEN][RULE_EXPRESSION_WORDS_COUNT];
    byte words_count;
} E_Guess;

void E_Guess_Init(E_Guess *self);
void E_Guess_SetAccess(E_Guess *self, const string file, int line, const string access);
void E_Guess_SetConst(E_Guess *self, const string file, int line, bool is_const);
void E_Guess_SetStatic(E_Guess *self, const string file, int line, bool is_static);
void E_Guess_PushWord(E_Guess *self, const string file, int line, const string word);

bool E_Guess_GuessStructName(E_Guess *self, const string file, int line, const string name, E_Struct *st);
bool E_Guess_GuessField(E_Guess *self, const string file, int line, E_Field *field);
bool E_Guess_GuessFuctionName(E_Guess *self, const string file, int line, E_Function *func);
bool E_Guess_GuessStatement(E_Guess *self, const string file, int line, byte nested_level, char *op, byte op_count, E_Statement *statement);
void E_Guess_ExpressionLog(const E_Guess *self);

#endif