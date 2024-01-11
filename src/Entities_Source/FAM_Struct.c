#include "FAM_Struct.h"

void FAM_Struct_Init(FAM_Struct *dfa_struct) {
    memset(dfa_struct, 0, sizeof(FAM_Struct));
}

void FAM_Struct_Free(FAM_Struct *dfa_struct) {
    free(dfa_struct);
}