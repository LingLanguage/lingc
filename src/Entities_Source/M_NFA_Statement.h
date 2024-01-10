#ifndef M_NFA_STATEMENT_H__
#define M_NFA_STATEMENT_H__

#include "E_Statement.h"
#include "M_NFA_Expression.h"
#include "import.h"

typedef struct M_NFA_Statement {
    NFA_Statement_Status status;
    M_NFA_Expression nfa_exp;
    E_Statement statement;
    bool is_done;
} M_NFA_Statement;

#endif