#ifndef M_EXP_H__
#define M_EXP_H__

#include "M_EXP.h"
#include "import.h"

typedef struct M_EXP {
    NFA_Expression_Status status;
    E_Expression expression;
    bool is_done;
} M_EXP;

#endif