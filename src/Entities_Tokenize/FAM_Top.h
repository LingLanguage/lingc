#ifndef FAM_TOP_H__
#define FAM_TOP_H__

#include "E_Guess.h"
#include "FAM_Import.h"
#include "FAM_Struct.h"
#include "FAM_Func.h"
#include "import.h"

typedef struct FAM_Top {
    Top_FA status;
    E_Guess guess;
    FAM_Struct *fam_struct;
    FAM_Import *fam_import;
    FAM_Func *dfa_func;
} FAM_Top;

void FAM_Top_Init(FAM_Top *nfa_top);
void FAM_Top_Free(FAM_Top *nfa_top);

#endif