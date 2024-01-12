#ifndef M_CURSOR_H__
#define M_CURSOR_H__

#include "import.h"

typedef struct M_Cursor {

    char file[FILENAME_MAX];
    bool is_split;
    int line;
    int index;
    int code_size; // readonly

    char access[RULE_ACCESS_NAME_LEN];
    bool is_const;
    bool is_static;

    char last_word[RULE_VAR_NAME_LEN];

    char **words;
    byte words_capacity;
    byte words_count;

} M_Cursor;

void M_Cursor_InitAccess(M_Cursor *self);
void M_Cursor_SetAcceess(M_Cursor *self, const string access);
void M_Cursor_PushWord(M_Cursor *self, const string word);
void M_Cursor_SetLastWord(M_Cursor *self, const string word);
void M_Cursor_CleanLastWord(M_Cursor *self);
bool M_Cursor_TryGetAssignOP(M_Cursor *self, const string code, const string word, char *op);
bool M_Cursor_TryGetCalcOP(M_Cursor *self, const string code, const string word, const string last_word, OperatorType *op_type);

#endif