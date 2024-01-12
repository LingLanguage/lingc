#include "D_Func.h"
#include "Util_Cursor.h"

// ==== Private ====
void D_Func_Enter(FAM_Func *fam, string access, bool is_static);
void D_Func_NamePhase_Process(FAM_Func *fam, const string code, const string word, M_Cursor *cursor);
void D_Func_ParamPhase_Enter(FAM_Func *fam);
void D_Func_ParamPhase_Process(FAM_Func *fam, const string code, const string word, M_Cursor *cursor);
void D_Func_BlockPhase_Enter(FAM_Func *fam);
void D_Func_BlockPhase_Process(FAM_Func *fam, const string code, const string word, M_Cursor *cursor);

bool D_Func_GuessFuctionName(M_Cursor *self, E_Function *func) {
    bool is_ok = true;
    if (self->is_const) {
        PFailed(self->file, self->line, ERR_FUNCTION_CANT_BE_CONST);
        is_ok = false;
    }
    if (self->words_count >= 2) {
        if (self->words_count <= RULE_FUNCTION_RETURN_COUNT) {
            // ok
            // last word is name
            strcpy(func->name, self->words[self->words_count - 1]);
            // other words are return type
            for (int i = 0; i < self->words_count - 1; i++) {
                E_Function_AddReturnType(func, self->words[i]);
            }
        } else {
            PFailed(self->file, self->line, ERR_FUNCTION_TOO_MANY_RETURN_TYPES);
        }
    } else if (self->words_count == 1) {
        PFailed(self->file, self->line, ERR_FUNCTION_TOO_FEW_RETURN_TYPES);
        is_ok = false;
    } else if (self->words_count == 0) {
        PFailed(self->file, self->line, ERR_FUNCTION_NAME_NOT_FOUND);
        is_ok = false;
    }

    if (is_ok) {
        M_Cursor_InitAccess(self);
    }
    return is_ok;
}

void D_Func_NamePhase_Process(FAM_Func *fam, const string code, const string word, M_Cursor *cursor) {
    if (cursor->is_split) {
        char split = word[0];
        if (split == KW_LEFT_BRACKET) {
            // (
            E_Function *func = &fam->function;
            D_Func_GuessFuctionName(cursor, func);
            D_Func_ParamPhase_Enter(fam);
            ++cursor->index;
        } else if (split == KW_COMMA) {
            // ,
            // do nothing
            ++cursor->index;
        } else {
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    } else {
        M_Cursor_PushWord(cursor, word);
    }
}

void D_Func_ParamPhase_Enter(FAM_Func *fam) {
    fam->phase = Func_FA_Params;
    fam->tmp_is_in_param_name = false;
}

void D_Func_ParamPhase_Process(FAM_Func *fam, const string code, const string word, M_Cursor *cursor) {
    if (cursor->is_split) {
        char split = word[0];
        if (split == KW_RIGHT_BRACKET) {
            // )
            D_Func_BlockPhase_Enter(fam);
            ++cursor->index;
        } else if (split == KW_COMMA) {
            // ,
            // do nothing
            ++cursor->index;
        } else {
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    } else {
        // params
        if (!fam->tmp_is_in_param_name) {
            strcpy(fam->tmp_param_type, word);
            fam->tmp_is_in_param_name = true;
        } else {
            strcpy(fam->tmp_param_name, word);
            fam->tmp_is_in_param_name = false;
            E_Function_AddParam(&fam->function, fam->tmp_param_type, fam->tmp_param_name);
            // next param
            D_Func_ParamPhase_Enter(fam);
        }
    }
}

void D_Func_BlockPhase_Enter(FAM_Func *fam) {
    fam->phase = Func_FA_Block;
    D_Block_Enter(&fam->dfa_block);
}

void D_Func_BlockPhase_Process(FAM_Func *fam, const string code, const string word, M_Cursor *cursor) {
    D_Block_Process(&fam->dfa_block, code, word, cursor);
    if (fam->dfa_block.is_done) {
        fam->is_done = true;
    }
}

void D_Func_Free(FAM_Func *fam) {
}

void D_Func_Enter(FAM_Func *fam, string access, bool is_static) {
    // already:
    // public static fn
    FAM_Func_Init(fam, access, is_static);
    PLogNA("Enter DFA Func\r\n");
}

void D_Func_Process(FAM_Func *fam, const string code, const string word, M_Cursor *cursor) {
    Func_FA phase = fam->phase;
    if (phase == Func_FA_Name) {
        D_Func_NamePhase_Process(fam, code, word, cursor);
    } else if (phase == Func_FA_Params) {
        D_Func_ParamPhase_Process(fam, code, word, cursor);
    } else if (phase == Func_FA_Block) {
        D_Func_BlockPhase_Process(fam, code, word, cursor);
    }
}