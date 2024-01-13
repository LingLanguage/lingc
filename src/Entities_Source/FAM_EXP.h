#ifndef FAM_EXP_H__
#define FAM_EXP_H__

#include "E_Expression.h"
#include "import.h"

typedef struct FAM_EXP FAM_EXP;

typedef struct FAM_EXP {
    EXP_FA status;
    E_Expression expression;
    FAM_EXP *child_fam;
    E_Guess guess;
    bool is_done;
} FAM_EXP;

#endif