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

    char **words;
    byte words_capacity;
    byte words_count;

} M_Cursor;

void M_Cursor_InitAccess(M_Cursor *self);
void M_Cursor_SetAcceess(M_Cursor *self, const string access);
void M_Cursor_PushWord(M_Cursor *self, const string word);
bool M_Cursor_TryGetAssignOP(M_Cursor *self, const string code, const string word, char *op);

#endif