#include "D_STMT_Assign.h"
#include "D_EXP_Bracket.h"

void D_STMT_Assign_Enter(FAM_STMT *fam, char **left_words, int left_words_count) {

    fam->status = STMT_FA_Assign;

    E_Statement *stmt = &fam->stmt;
    stmt->type = StatementType_Assign;
    for (int i = 0; i < left_words_count; i++) {
        E_Statement_AddAssignLeftWord(stmt, left_words[i]);
    }

    D_EXP_Bracket_Enter(&fam->fam_exp);
    PLogNA("STMT Enter Assign\r\n");
}

void D_STMT_Assign_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor) {
    PLogNA("STMT Process Assign\r\n");
}