#include "D_EXP_Bracket.h"
#include "Util_Cursor.h"

void D_EXP_Bracket_Enter(M_EXP *fam_exp);
void D_EXP_Bracket_Process(M_EXP *fam_exp, const string code, const string word, M_Cursor *cursor);

void D_EXP_Bracket_Enter(M_EXP *fam_exp) {
    // already know: (
    memset(fam_exp, 0, sizeof(M_EXP));
    fam_exp->expression.type = ExpressionType_Bracket; // ()
    fam_exp->status = NFA_EXPression_Status_Bracket;
    PLogNA("EXP Bracket Enter\r\n");
}

void D_EXP_Bracket_Process(M_EXP *fam_exp, const string code, const string word, M_Cursor *cursor) {
    bool is_split = cursor->is_split;
    if (is_split) {
        char split = word[0];
        if (split == KW_RIGHT_BRACKET) {
            // )
            // end bracket
            fam_exp->is_done = true;
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
            fam_exp->is_done = true;
        } else {
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    } else {
        E_Expression *expression = &fam_exp->expression;
        E_Expression_AddWord(expression, word);
    }
}