#include "D_NFA_Expression.h"
#include "Util_Cursor.h"

void D_NFA_Expression_Enter(M_NFA_Expression *nfa_exp) {
    memset(nfa_exp, 0, sizeof(M_NFA_Expression));
}

void D_NFA_Expression_Process(M_NFA_Expression *nfa_exp, const string code, const string word, M_Cursor *cursor) {
    E_Expression *expression = &nfa_exp->expression;
}