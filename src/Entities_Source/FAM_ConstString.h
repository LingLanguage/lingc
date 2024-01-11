#ifndef FAM_CONSTSTRING_H__
#define FAM_CONSTSTRING_H__

#include "import.h"

typedef struct FAM_ConstString {
    int start_index;
    int end_index;
    bool is_done;
} FAM_ConstString;

int FAM_ConstString_Process(FAM_ConstString *fsm, int nested_level, const string file, int line, bool is_split, const string word, int index, const string code,
                               long size);
#endif