#ifndef M_NFA_TOP_H__
#define M_NFA_TOP_H__

#include "E_Guess.h"
#include "M_DFA_Import.h"
#include "M_DFA_Struct.h"
#include "M_DFA_Func.h"
#include "import.h"

typedef struct M_NFA_Top {
    NFA_Top_Status status;
    M_DFA_Struct *dfa_struct;
    M_DFA_Import *dfa_import;
    M_DFA_Func *dfa_func;
    E_Guess guess;
} M_NFA_Top;

void M_NFA_Top_Init(M_NFA_Top *nfa_top);
void M_NFA_Top_Free(M_NFA_Top *nfa_top);

#endif