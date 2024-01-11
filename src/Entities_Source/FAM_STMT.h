#ifndef FAM_STMT_H__
#define FAM_STMT_H__

#include "E_Statement.h"
#include "M_EXP.h"
#include "import.h"

typedef struct FAM_STMT {
    STMT_FA status;
    M_EXP nfa_exp;
    E_Statement statement;
    bool is_done;

    bool is_return_bracket_done;
} FAM_STMT;

#endif