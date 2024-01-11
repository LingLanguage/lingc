#include "D_NFA_STMT_Return.h"
#include "D_NFA_Expression.h"
#include "Util_Cursor.h"

// block -> stmt -> exp

void D_NFA_STMT_Return_Enter(M_NFA_STMT_Return *nfa_stmt) {
    nfa_stmt->statement = E_Statement_CreateReturn();
    D_NFA_Expression_EnterBracket(&nfa_stmt->nfa_exp);
    PLogNA("NFA STMT Enter Return\r\n");
}

void D_NFA_STMT_Return_Process(M_NFA_STMT_Return *nfa_stmt, const string code, const string word, M_Cursor *cursor) {
    // real: return xx;
    // fake: reutrn (xx);
    M_NFA_Expression *nfa_exp = &nfa_stmt->nfa_exp;
    if (!nfa_stmt->is_return_bracket_done) {
        D_NFA_Expression_Process(nfa_exp, code, word, cursor);
        if (nfa_exp->is_done) {
            // add exp to stmt
            E_Statement_AddBracketExpression(&nfa_stmt->statement, nfa_exp->expression);
            nfa_stmt->is_return_bracket_done = true;
        }
    } else {
        bool is_split = cursor->is_split;
        if (is_split) {
            char split = word[0];
            if (split == KW_SEMICOLON) {
                // ;
                nfa_stmt->is_done = true;
                ++cursor->index;
            } else if (split == KW_LEFT_BRACKET) {
                // (
                D_NFA_Expression_EnterBracket(&nfa_stmt->nfa_exp);
                nfa_stmt->is_return_bracket_done = false;
            } else {
                Util_Cursor_DealEmptySplit(cursor, code, word);
            }
        }
    }
}
