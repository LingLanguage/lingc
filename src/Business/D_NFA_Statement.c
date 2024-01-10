#include "D_NFA_Statement.h"
#include "D_NFA_Expression.h"
#include "Util_Cursor.h"

void D_NFA_Statement_EnterReturnSTMT(M_NFA_Statement *nfa_stmt) {
    nfa_stmt->status = NFA_Statement_Status_Return;
    nfa_stmt->statement = E_Statement_CreateReturn();
    D_NFA_Expression_Enter(&nfa_stmt->nfa_exp);
    PLogNA("NFA STMT Enter Return\r\n");
}

void ReturnSTMT_Process(M_NFA_Statement *nfa_stmt, const string code, const string word, M_Cursor *cursor) {
    M_NFA_Expression *nfa_exp = &nfa_stmt->nfa_exp;
    D_NFA_Expression_Process(nfa_exp, code, word, cursor);
    if (nfa_exp->is_done) {
        nfa_stmt->is_done = true;
        PLogNA("NFA STMT Return Done\r\n");
    }
}

void D_NFA_Statement_Process(M_NFA_Statement *nfa_stmt, const string code, const string word, M_Cursor *cursor) {
    NFA_Statement_Status status = nfa_stmt->status;
    if (status == NFA_Statement_Status_Return) {
        ReturnSTMT_Process(nfa_stmt, code, word, cursor);
    }
}