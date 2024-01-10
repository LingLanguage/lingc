#ifndef M_DFA_STRUCT_H__
#define M_DFA_STRUCT_H__

#include "import.h"
#include "E_Struct.h"
#include "E_Guess.h"

typedef struct M_DFA_Struct {
    E_Struct st;
    StructPhase phase;
    byte nested_level;
    E_Guess guess;

    M_DFA_Func dfa_func;
    bool is_done;
} M_DFA_Struct;

#endif