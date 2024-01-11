#ifndef M_NFA_STMT_RETURN_H__
#define M_NFA_STMT_RETURN_H__

#include "E_Statement.h"
#include "M_NFA_Expression.h"
#include "import.h"

typedef struct M_NFA_STMT_Return {
    NFA_Statement_Status status;
    M_NFA_Expression nfa_exp;
    E_Statement statement;
    bool is_done;

    bool is_return_bracket_done;
} M_NFA_STMT_Return;

#endif