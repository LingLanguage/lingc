#include "D_STMT.h"
#include "D_EXP_Bracket.h"

void D_STMT_Enter(FAM_STMT *fam);
void D_STMT_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor);
void D_STMT_Guess_Enter(FAM_STMT *fam);
void D_STMT_Guess_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor);
void D_STMT_Return_Enter(FAM_STMT *fam);
void D_STMT_Return_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor);
void D_STMT_Assign_Enter(FAM_STMT *fam, OP_Type op_type);
void D_STMT_Assign_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor);

void D_STMT_Enter(FAM_STMT *fam) {
    E_Guess_Init(&fam->guess);
    fam->status = STMT_FA_Guess;
    fam->is_done = false;
}

// int a;
// int b = 3;
// b = 5;
// const int c = 4;
// (a.GetOne(b > 5))->GetTwo().value += 1;
void D_STMT_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor) {
    bool is_split = cursor->is_split;
    STMT_FA stmt_fa = fam->status;
    if (stmt_fa == STMT_FA_Guess) {
        D_STMT_Guess_Process(fam, code, word, cursor);
    } else if (stmt_fa == STMT_FA_Return) {
        D_STMT_Return_Process(fam, code, word, cursor);
    } else if (stmt_fa == STMT_FA_Assign) {
        D_STMT_Assign_Process(fam, code, word, cursor);
    }
}

// Guess
void D_STMT_Guess_Enter(FAM_STMT *fam) {
    fam->status = STMT_FA_Guess;
    E_Guess_Init(&fam->guess);
    PLogNA("NFA STMT Enter Guess\r\n");
}

void D_STMT_Guess_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor) {
    D_EXP_Bracket_Process(&fam->fam_exp, code, word, cursor);
    if (fam->fam_exp.is_done) {
        if (OP_Type_IsAssign(fam->fam_exp.done_op_type)) {
            E_Statement_SetLeftExpression(&fam->stmt, fam->fam_exp.expression);
            D_STMT_Assign_Enter(fam, fam->fam_exp.done_op_type);
        } else {
            E_Statement_AddBracketExpression(&fam->stmt, fam->fam_exp.expression);
            fam->is_done = true;
            return;
        }
    }
    bool is_split = cursor->is_split;
    E_Guess *guess = &fam->guess;
    if (is_split) {
        char split = word[0];
        OP_Type op_type;
        if (split == KW_SEMICOLON) {
            // ;
            E_Statement_AddBracketExpression(&fam->stmt, fam->fam_exp.expression);
            fam->is_done = true;
            ++cursor->index;
        } else if (E_Guess_TryGetCalcOP(guess, &cursor->index, code, word, &op_type)) {
            if (OP_Type_IsAssign(op_type)) {
                // if assign, then enter assign statement
                // += -= *= /= %= ~= &= |= ^= <<= >>=
            } else {
                // add exp
                ++cursor->index;
            }
        } else {
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    } else {
        if (strcmp(word, KW_RETURN) == 0) {
            // return
            D_STMT_Return_Enter(fam);
        } else if (strcmp(word, KW_IF) == 0) {
            // if
        } else if (strcmp(word, KW_WHILE) == 0) {
            // while
        } else if (strcmp(word, KW_FOR) == 0) {
            // for
        } else {
            E_Guess_PushWord(&fam->guess, word);
        }
    }
}

// Return
void D_STMT_Return_Enter(FAM_STMT *fam) {
    fam->status = STMT_FA_Return;
    fam->stmt = E_Statement_CreateReturn();
    D_EXP_Bracket_Enter(&fam->fam_exp);
    PLogNA("NFA STMT Enter Return\r\n");
}

void D_STMT_Return_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor) {
    // real: return xx;
    // fake: reutrn (xx);
    FAM_EXP *fam_exp = &fam->fam_exp;
    if (!fam->is_return_bracket_done) {
        D_EXP_Bracket_Process(fam_exp, code, word, cursor);
        if (fam_exp->is_done) {
            // add exp to stmt
            E_Statement_AddBracketExpression(&fam->stmt, fam_exp->expression);
            D_EXP_Bracket_Enter(&fam->fam_exp);
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
                D_EXP_Bracket_Enter(&fam->fam_exp);
                fam->is_return_bracket_done = false;
            } else {
                Util_Cursor_DealEmptySplit(cursor, code, word);
            }
        }
    }
}

// Assign
void D_STMT_Assign_Enter(FAM_STMT *fam, OP_Type op_type) {
    fam->status = STMT_FA_Assign;
    fam->stmt = E_Statement_CreateAssign(op_type);
}

void D_STMT_Assign_Process(FAM_STMT *fam, const string code, const string word, M_Cursor *cursor) {
    if (!fam->is_assign_right_done) {
        D_EXP_Bracket_Process(&fam->fam_exp, code, word, cursor);
        if (fam->fam_exp.is_done) {
            if (fam->fam_exp.done_op_type == OP_Type_End) {

            }
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
