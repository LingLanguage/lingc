#include "D_NFA_Expression.h"
#include "Util_Cursor.h"

void D_NFA_Expression_EnterBracket(M_NFA_Expression *nfa_exp);
void D_NFA_Expression_ProcessBracket(M_NFA_Expression *nfa_exp, const string code, const string word, M_Cursor *cursor);

void D_NFA_Expression_EnterBracket(M_NFA_Expression *nfa_exp) {
    // already know: (
    memset(nfa_exp, 0, sizeof(M_NFA_Expression));
    nfa_exp->expression.type = ExpressionType_Bracket; // ()
    nfa_exp->status = NFA_EXPression_Status_Bracket;
}

void D_NFA_Expression_ProcessBracket(M_NFA_Expression *nfa_exp, const string code, const string word, M_Cursor *cursor) {
    bool is_split = cursor->is_split;
    if (is_split) {
        char split = word[0];
        if (split == KW_RIGHT_BRACKET) {
            // )
            // end bracket
            nfa_exp->is_done = true;
            ++cursor->index;
        } else if (split == KW_COMMA) {
            // ,
            ++cursor->index;
        } else if (split == KW_SEMICOLON) {
            // ;
            // also end bracket
            // DONT ++cursor->index;
            // DONT ++cursor->index;
            // DONT ++cursor->index;
            nfa_exp->is_done = true;
        } else {
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    } else {
        E_Expression *expression = &nfa_exp->expression;
        E_Expression_AddWord(expression, word);
    }
}

void D_NFA_Expression_Process(M_NFA_Expression *nfa_exp, const string code, const string word, M_Cursor *cursor) {
    NFA_Expression_Status status = nfa_exp->status;
    if (status == NFA_EXPression_Status_Bracket) {
        D_NFA_Expression_ProcessBracket(nfa_exp, code, word, cursor);
    }
}