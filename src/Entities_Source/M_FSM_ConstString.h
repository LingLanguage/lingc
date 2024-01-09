#ifndef M_FSM_CONSTSTRING_H__
#define M_FSM_CONSTSTRING_H__

#include "import.h"

typedef struct M_FSM_ConstString {
    int start_index;
    int end_index;
    bool is_done;
} M_FSM_ConstString;

int M_FSM_ConstString_Process(M_FSM_ConstString *fsm, int nested_level, const string file, int line, bool is_split, const string word, int index, const string code,
                               long size);
#endif