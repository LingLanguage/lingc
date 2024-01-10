#ifndef M_NFA_EXPRESSION_H__
#define M_NFA_EXPRESSION_H__

#include "M_NFA_Expression.h"
#include "import.h"

typedef struct M_NFA_Expression {
    NFA_Expressiont_Status status;
    E_Expression expression;
    bool is_done;
} M_NFA_Expression;

#endif