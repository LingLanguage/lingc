#ifndef M_DFA_CONSTSTRING_H__
#define M_DFA_CONSTSTRING_H__

#include "import.h"

typedef struct M_DFA_ConstString {
    int start_index;
    int end_index;
    bool is_done;
} M_DFA_ConstString;

int M_DFA_ConstString_Process(M_DFA_ConstString *fsm, int nested_level, const string file, int line, bool is_split, const string word, int index, const string code,
                               long size);
#endif