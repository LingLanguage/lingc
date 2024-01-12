#include "D_STMT_Assign.h"
#include "D_EXP_Bracket.h"

void D_STMT_Assign_Enter(FAM_STMT *fam, char *op, char **left_words, int left_words_count) {

    fam->status = STMT_FA_Assign;

    E_Statement *stmt = &fam->stmt;
    stmt->type = StatementType_Assign;
    for (int i = 0; i < left_words_count; i++) {
        E_Statement_AddAssignLeftWord(stmt, left_words[i]);
    }

    strcpy(stmt->assign_op, op);
    D_EXP_Bracket_Enter(&fam->fam_exp);
    PLogNA("STMT Enter Assign\r\n");
}

void D_STMT_Assign_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor) {
    if (!fam->is_assign_right_done) {
        D_EXP_Bracket_Process(&fam->fam_exp, code, word, cursor);
        if (fam->fam_exp.is_done) {
            // add exp to stmt
            E_Statement_AddBracketExpression(&fam->stmt, fam->fam_exp.expression);
            D_EXP_Bracket_Process(&fam->fam_exp, code, word, cursor);
            fam->is_assign_right_done = true;
        }
    } else {
        bool is_split = cursor->is_split;
        if (is_split) {
            char split = word[0];
            if (split == KW_SEMICOLON) {
                // ;
                fam->is_done = true;
                ++cursor->index;
            } else {
                Util_Cursor_DealEmptySplit(cursor, code, word);
            }
        }
    }
}