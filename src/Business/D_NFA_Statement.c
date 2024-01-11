#include "D_NFA_Statement.h"
#include "D_NFA_Expression.h"
#include "Util_Cursor.h"

void D_NFA_Statement_Process(M_NFA_Statement *nfa_stmt, const string code, const string word, M_Cursor *cursor);
void D_NFA_Statement_EnterReturnSTMT(M_NFA_Statement *nfa_stmt);
void D_NFA_Statement_Return_Process(M_NFA_Statement *nfa_stmt, const string code, const string word, M_Cursor *cursor);

void D_NFA_Statement_EnterReturnSTMT(M_NFA_Statement *nfa_stmt) {
    nfa_stmt->status = NFA_Statement_Status_Return;
    nfa_stmt->statement = E_Statement_CreateReturn();
    D_NFA_Expression_EnterBracket(&nfa_stmt->nfa_exp);
    PLogNA("NFA STMT Enter Return\r\n");
}

void D_NFA_Statement_Process(M_NFA_Statement *nfa_stmt, const string code, const string word, M_Cursor *cursor) {
    NFA_Statement_Status status = nfa_stmt->status;
    if (status == NFA_Statement_Status_Return) {
        D_NFA_Statement_Return_Process(nfa_stmt, code, word, cursor);
    }
}

void D_NFA_Statement_Return_Process(M_NFA_Statement *nfa_stmt, const string code, const string word, M_Cursor *cursor) {
    // real: return xx;
    // fake: reutrn (xx);
    M_NFA_Expression *nfa_exp = &nfa_stmt->nfa_exp;
    D_NFA_Expression_Process(nfa_exp, code, word, cursor);
    if (nfa_exp->is_done) {
        E_Statement_AddBracketExpression(&nfa_stmt->statement, nfa_exp->expression);
        nfa_stmt->is_done = true;
    }
}

