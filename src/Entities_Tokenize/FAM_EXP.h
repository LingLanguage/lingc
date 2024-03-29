#ifndef FAM_EXP_H__
#define FAM_EXP_H__

#include "E_Expression.h"
#include "import.h"

typedef struct FAM_EXP FAM_EXP;

typedef struct FAM_EXP {
    EXP_FA status;
    int exp_id;
    FAM_EXP *child_fam;
    E_Guess guess;
    OP_Type done_op_type;
    bool is_done;
} FAM_EXP;

#endif