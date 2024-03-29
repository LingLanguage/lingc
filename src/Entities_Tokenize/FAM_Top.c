#include "FAM_Top.h"

void FAM_Top_Init(FAM_Top *nfa_top) {
    nfa_top->status = Top_FA_Guess;
    nfa_top->fam_struct = calloc(1, sizeof(FAM_Struct));
    nfa_top->fam_import = calloc(1, sizeof(FAM_Import));
    nfa_top->dfa_func = calloc(1, sizeof(FAM_Func));
}

void FAM_Top_Free(FAM_Top *nfa_top) {
    FAM_Func_Free(nfa_top->dfa_func);
    FAM_Import_Free(nfa_top->fam_import);
    FAM_Struct_Free(nfa_top->fam_struct);
    free(nfa_top);
}