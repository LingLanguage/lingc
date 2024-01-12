#include "D_STMT_Return.h"
#include "D_EXP_Bracket.h"
#include "Util_Cursor.h"

// block -> stmt -> exp

void D_STMT_Return_Enter(FAM_STMT *fam) {
    fam->stmt = E_Statement_CreateReturn();
    D_EXP_Bracket_EnterBracket(&fam->fam_exp);
    PLogNA("NFA STMT Enter Return\r\n");
}

void D_STMT_Return_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor) {
    // real: return xx;
    // fake: reutrn (xx);
    M_EXP *fam_exp = &fam->fam_exp;
    if (!fam->is_return_bracket_done) {
        D_EXP_Bracket_Process(fam_exp, code, word, cursor);
        if (fam_exp->is_done) {
            // add exp to stmt
            E_Statement_AddBracketExpression(&fam->stmt, fam_exp->expression);
            fam->is_return_bracket_done = true;
        }
    } else {
        bool is_split = cursor->is_split;
        if (is_split) {
            char split = word[0];
            if (split == KW_SEMICOLON) {
                // ;
                fam->is_done = true;
                ++cursor->index;
            } else if (split == KW_LEFT_BRACKET) {
                // (
                D_EXP_Bracket_EnterBracket(&fam->fam_exp);
                fam->is_return_bracket_done = false;
            } else {
                Util_Cursor_DealEmptySplit(cursor, code, word);
            }
        }
    }
}
