#ifndef M_CURSOR_H__
#define M_CURSOR_H__

#include "import.h"

typedef struct M_Cursor {
    char file[FILENAME_MAX];
    char word[RULE_VAR_NAME_LEN];
    bool is_split;
    int line;
    int index;
    int code_size; // readonly
} M_Cursor;

#endif