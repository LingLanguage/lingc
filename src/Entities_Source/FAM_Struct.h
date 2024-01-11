#ifndef FAM_STRUCT_H__
#define FAM_STRUCT_H__

#include "import.h"
#include "E_Struct.h"
#include "E_Guess.h"

typedef struct FAM_Struct {
    E_Struct st;
    StructPhase phase;
    byte nested_level;
    E_Guess guess;

    FAM_Func dfa_func;
    bool is_done;
} FAM_Struct;

void FAM_Struct_Init(FAM_Struct *dfa_struct);
void FAM_Struct_Free(FAM_Struct *dfa_struct);

#endif