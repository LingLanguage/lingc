#ifndef FAM_FUNC_H__
#define FAM_FUNC_H__

#include "E_Function.h"
#include "E_Guess.h"
#include "M_Parameter.h"
#include "FAM_Block.h"
#include "import.h"

typedef struct FAM_Func {

    Func_FA phase;
    E_Guess guess;
    FAM_Block dfa_block;

    int function_id;

    byte nested_level;

    // params
    char tmp_param_type[RULE_STRUCT_TYPE_NAME_LEN];
    char tmp_param_name[RULE_VAR_NAME_LEN];
    bool tmp_is_in_param_name;

    bool is_done;

} FAM_Func;

void FAM_Func_Init(FAM_Func *fsm, char *access, bool is_static);
void FAM_Func_Free(FAM_Func *fsm);
#endif