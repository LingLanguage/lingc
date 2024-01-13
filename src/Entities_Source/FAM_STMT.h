#ifndef FAM_STMT_H__
#define FAM_STMT_H__

#include "E_Statement.h"
#include "FAM_EXP.h"
#include "import.h"

typedef struct FAM_STMT {
    STMT_FA status;
    FAM_EXP fam_exp;
    E_Statement stmt;
    E_Guess guess;
    bool is_done;

    bool is_return_bracket_done;
    bool is_assign_right_done;
} FAM_STMT;

#endif