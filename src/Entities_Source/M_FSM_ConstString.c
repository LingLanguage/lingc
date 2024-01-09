#include "M_FSM_ConstString.h"

int M_FSM_ConstString_Process(M_FSM_ConstString *fsm, int nested_level, const string file, int line, bool is_split, const string word, int index, const string code,
                              long size) {

    memset(fsm, 0, sizeof(M_FSM_ConstString));
    // from "
    fsm->start_index = index;
    fsm->end_index = index;

    // to "
    for (int i = index + 1; i < size; i++) {
        char c = code[i];
        if (c == '\"') {
            char last = code[i - 1];
            if (last == '\\') {
                // eg: "hello \"world\""
                continue;
            }
            fsm->end_index = i;
            fsm->is_done = true;
            break;
        }
    }
    return fsm->end_index + 1;
}