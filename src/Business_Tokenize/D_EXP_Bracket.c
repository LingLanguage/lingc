#include "D_EXP_Bracket.h"
#include "Util_Cursor.h"

void D_EXP_Bracket_AddWord(FAM_EXP *fam_exp, const string word, M_Cursor *cursor) {
    E_Expression_AddWord(&fam_exp->expression, word);
    M_Cursor_CleanLastWord(cursor);
}

void D_EXP_Bracket_AddChildExp(FAM_EXP *fam_exp, OP_Type op_type, char *word) {
    E_Expression child = {0};
    child.op_type = op_type;
    E_Expression_AddWord(&child, word);

    E_Expression_AddChildExp(&fam_exp->expression, &child);
}

void D_EXP_Bracket_Enter(FAM_EXP *fam_exp);
void D_EXP_Bracket_Process(FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor);
void D_EXP_Bracket_EnterSelf(FAM_EXP *fam_exp);
void D_EXP_Bracket_ProcessSelf(FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor);
void D_EXP_Bracket_EnterChildBracket(FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor);
void D_EXP_Bracket_ProcessChilcBracket(FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor);

void D_EXP_Bracket_Enter(FAM_EXP *fam_exp) {
    // already know: `(` or fake `(`
    D_EXP_Bracket_EnterSelf(fam_exp);
    PLogNA("EXP Bracket Enter\r\n");
}

void D_EXP_Bracket_Process(FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor) {
    EXP_FA status = fam_exp->status;
    if (status == EXP_FA_Bracket) {
        D_EXP_Bracket_ProcessSelf(fam_exp, code, word, cursor);
    } else if (status == EXP_FA_ChildBracket) {
        D_EXP_Bracket_ProcessChilcBracket(fam_exp, code, word, cursor);
    }
}

// ==== Self Bracket ====
void D_EXP_Bracket_EnterSelf(FAM_EXP *fam_exp) {
    if (fam_exp->child_fam != NULL) {
        free(fam_exp->child_fam);
        fam_exp->child_fam = NULL;
    }
    memset(fam_exp, 0, sizeof(FAM_EXP));
    fam_exp->expression.type = ExpressionType_Bracket; // ()
    fam_exp->expression.op_type = OP_Type_Bracket;
    fam_exp->status = EXP_FA_Bracket;
}

void D_EXP_Bracket_ProcessSelf(FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor) {
    bool is_split = cursor->is_split;
    if (is_split) {
        char split = word[0];
        OP_Type opType;
        if (split == KW_RIGHT_BRACKET) {
            // ) exp
            // end bracket
            D_EXP_Bracket_AddWord(fam_exp, word, cursor);
            fam_exp->is_done = true;
            ++cursor->index;
        } else if (split == KW_COMMA) {
            // , exp
            D_EXP_Bracket_AddWord(fam_exp, word, cursor);
            ++cursor->index;
        } else if (split == KW_SEMICOLON) {
            /* ;
               also end bracket
               because: like `return (xx);`, the `)` is not truely exists, so `;` is also bracket end
               DONT ++cursor->index; see: D_STMT end by `;`
               DONT ++cursor->index; see: D_STMT end by `;`
               DONT ++cursor->index; see: D_STMT end by `;`
            */
            D_EXP_Bracket_AddWord(fam_exp, word, cursor);
            fam_exp->is_done = true;
        } else if (split == KW_LEFT_BRACKET) {
            // ( exp
            // child bracket
            D_EXP_Bracket_EnterChildBracket(fam_exp, code, word, cursor);
            ++cursor->index;
        } else if (M_Cursor_TryGetCalcOP(cursor, code, word, cursor->last_word, &opType)) {
            // + - * / % ~ & | ^ << >> && || == != <= >= < >
            D_EXP_Bracket_AddWord(fam_exp, word, cursor);
            D_EXP_Bracket_AddChildExp(fam_exp, opType, cursor->last_word);
        } else {
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    } else {
        M_Cursor_SetLastWord(cursor, word);
    }
}

// ==== Child Bracket ====
void D_EXP_Bracket_EnterChildBracket(FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor) {
    FAM_EXP *child_fam = calloc(1, sizeof(FAM_EXP));
    fam_exp->child_fam = child_fam;
    D_EXP_Bracket_Enter(child_fam);

    fam_exp->status = EXP_FA_ChildBracket;
}

void D_EXP_Bracket_ProcessChilcBracket(FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor) {
    FAM_EXP *child_fam = fam_exp->child_fam;
    D_EXP_Bracket_Process(child_fam, code, word, cursor);
    if (child_fam->is_done) {
        // add child exp to self exp
        E_Expression_AddChildExp(&fam_exp->expression, &child_fam->expression);
        D_EXP_Bracket_EnterSelf(fam_exp);
    }
}