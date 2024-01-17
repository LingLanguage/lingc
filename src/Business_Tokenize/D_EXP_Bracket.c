#include "D_EXP_Bracket.h"
#include "Util_Cursor.h"

E_Expression *D_EXP_Spawn(CTX_Tokenize *ctx) {
    E_Expression *exp = calloc(1, sizeof(E_Expression));
    exp->id = ctx->exp_id++;
    RP_EXP_Add(ctx->rp_exp, exp);
    return exp;
}

void D_EXP_Bracket_AddWord(CTX_Tokenize *ctx, FAM_EXP *fam_exp, E_Expression *exp, const string word, M_Cursor *cursor) {
    E_Expression_AddWord(exp, word);
    E_Guess_CleanLastWord(&fam_exp->guess);
}

void D_EXP_Bracket_AddChildExp(CTX_Tokenize *ctx, E_Expression *exp, OP_Type op_type, char *word) {
    E_Expression *child = D_EXP_Spawn(ctx);
    child->op_type = op_type;
    E_Expression_AddWord(child, word);
    E_Expression_AddChildExp(exp, child->id);
}

void D_EXP_Bracket_Enter(CTX_Tokenize *ctx, FAM_EXP *fam_exp);
void D_EXP_Bracket_Process(CTX_Tokenize *ctx, FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor);
void D_EXP_Bracket_EnterSelf(CTX_Tokenize *ctx, FAM_EXP *fam_exp);
void D_EXP_Bracket_ProcessSelf(CTX_Tokenize *ctx, FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor);
void D_EXP_Bracket_EnterChildBracket(CTX_Tokenize *ctx, FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor);
void D_EXP_Bracket_ProcessChilcBracket(CTX_Tokenize *ctx, FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor);

void D_EXP_Bracket_Enter(CTX_Tokenize *ctx, FAM_EXP *fam_exp) {
    // already know: `(` or fake `(`
    D_EXP_Bracket_EnterSelf(ctx, fam_exp);
    PLogNA("EXP Bracket Enter\r\n");
}

void D_EXP_Bracket_Process(CTX_Tokenize *ctx, FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor) {
    EXP_FA status = fam_exp->status;
    if (status == EXP_FA_Bracket) {
        D_EXP_Bracket_ProcessSelf(ctx, fam_exp, code, word, cursor);
    } else if (status == EXP_FA_ChildBracket) {
        D_EXP_Bracket_ProcessChilcBracket(ctx, fam_exp, code, word, cursor);
    }
}

// ==== Self Bracket ====
void D_EXP_Bracket_EnterSelf(CTX_Tokenize *ctx, FAM_EXP *fam_exp) {
    if (fam_exp->child_fam != NULL) {
        free(fam_exp->child_fam);
        fam_exp->child_fam = NULL;
    }
    memset(fam_exp, 0, sizeof(FAM_EXP));
    E_Expression *exp = D_EXP_Spawn(ctx);
    exp->type = ExpressionType_Bracket; // ()
    exp->op_type = OP_Type_Bracket;
    fam_exp->exp_id = exp->id;
    fam_exp->status = EXP_FA_Bracket;
}

void D_EXP_Bracket_ProcessSelf(CTX_Tokenize *ctx, FAM_EXP *fam, const string code, const string word, M_Cursor *cursor) {
    bool is_split = cursor->is_split;
    E_Guess *guess = &fam->guess;
    if (is_split) {
        E_Expression *exp;
        bool has = RP_EXP_TryGet(ctx->rp_exp, fam->exp_id, &exp);
        if (!has) {
            PFailed(__FILE__, __LINE__, ERR_UNDIFINDED_ERR);
        }
        char split = word[0];
        OP_Type opType = OP_Type_None;
        if (split == KW_RIGHT_BRACKET) {
            // ) exp
            // end bracket
            D_EXP_Bracket_AddWord(ctx, fam, exp, word, cursor);
            fam->is_done = true;
            ++cursor->index;
        } else if (split == KW_COMMA) {
            // , exp
            D_EXP_Bracket_AddWord(ctx, fam, exp, word, cursor);
            ++cursor->index;
        } else if (split == KW_LEFT_BRACKET) {
            // ( exp
            // child bracket
            D_EXP_Bracket_EnterChildBracket(ctx, fam, code, word, cursor);
            ++cursor->index;
        } else if (E_Guess_TryGetCalcOP(guess, &cursor->index, code, word, &opType)) {
            D_EXP_Bracket_AddWord(ctx, fam, exp, word, cursor);
            if (opType == OP_Type_End) {
                // ;
                fam->is_done = true;
            } else if (OP_Type_IsAssign(opType)) {
                // = += ...
                // if assign, then end bracket
                fam->is_done = true;
            } else {
                D_EXP_Bracket_AddChildExp(ctx, fam, opType, guess->last_word);
            }
        } else {
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    } else {
        E_Guess_SetLastWord(guess, word);
    }
}

// ==== Child Bracket ====
void D_EXP_Bracket_EnterChildBracket(CTX_Tokenize *ctx, FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor) {
    FAM_EXP *child_fam = calloc(1, sizeof(FAM_EXP));
    fam_exp->child_fam = child_fam;
    D_EXP_Bracket_Enter(ctx, child_fam);

    fam_exp->status = EXP_FA_ChildBracket;
}

void D_EXP_Bracket_ProcessChilcBracket(CTX_Tokenize *ctx, FAM_EXP *fam, const string code, const string word, M_Cursor *cursor) {
    FAM_EXP *child_fam = fam->child_fam;
    D_EXP_Bracket_Process(ctx, child_fam, code, word, cursor);
    if (child_fam->is_done) {
        E_Expression *exp;
        bool has = RP_EXP_TryGet(ctx->rp_exp, fam->exp_id, &exp);
        if (!has) {
            PFailed(__FILE__, __LINE__, ERR_UNDIFINDED_ERR);
        }
        E_Expression_AddChildExp(exp, &child_fam->exp_id);
        OP_Type done_op_type = child_fam->done_op_type;
        if (child_fam->done_op_type == OP_Type_End) {
            // ;
            fam->done_op_type = done_op_type;
            fam->is_done = true;
        } else if (OP_Type_IsAssign(child_fam->done_op_type)) {
            // = += ...
            // if assign, then end bracket
            fam->done_op_type = done_op_type;
            fam->is_done = true;
        } else {
            D_EXP_Bracket_EnterSelf(ctx, fam);
        }
    }
}