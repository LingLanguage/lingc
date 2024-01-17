#ifndef M_CURSOR_H__
#define M_CURSOR_H__

#include "import.h"

typedef struct M_Cursor {
    char file[FILENAME_MAX];
    bool is_split;
    int line;
    int nested;
    int index;
    int code_size; // readonly
} M_Cursor;

#endif