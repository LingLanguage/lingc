#include "D_DFA_Func.h"
#include "Util_Cursor.h"

// ==== Private ====
void D_DFA_Func_Enter(FAM_Func *dfa_func, E_Guess *guess);
void D_DFA_Func_NamePhase_Process(FAM_Func *dfa_func, const string code, const string word, M_Cursor *cursor);
void D_DFA_Func_ParamPhase_Enter(FAM_Func *dfa_func);
void D_DFA_Func_ParamPhase_Process(FAM_Func *dfa_func, const string code, const string word, M_Cursor *cursor);
void D_DFA_Func_BlockPhase_Enter(FAM_Func *dfa_func);
void D_DFA_Func_BlockPhase_Process(FAM_Func *dfa_func, const string code, const string word, M_Cursor *cursor);

void D_DFA_Func_NamePhase_Process(FAM_Func *dfa_func, const string code, const string word, M_Cursor *cursor) {
    if (cursor->is_split) {
        char split = word[0];
        if (split == KW_LEFT_BRACKET) {
            // (
            E_Function *func = &dfa_func->function;
            E_Guess_GuessFuctionName(&dfa_func->guess, cursor->file, cursor->line, func);
            ++cursor->index;
            D_DFA_Func_ParamPhase_Enter(dfa_func);
        } else if (split == KW_COMMA) {
            // ,
            // do nothing
            ++cursor->index;
        } else {
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    } else {
        E_Guess_PushWord(&dfa_func->guess, cursor->file, cursor->line, word);
    }
}

void D_DFA_Func_ParamPhase_Enter(FAM_Func *dfa_func) {
    dfa_func->phase = Func_FA_Params;
    dfa_func->tmp_is_in_param_name = false;
}

void D_DFA_Func_ParamPhase_Process(FAM_Func *dfa_func, const string code, const string word, M_Cursor *cursor) {
    if (cursor->is_split) {
        char split = word[0];
        if (split == KW_RIGHT_BRACKET) {
            // )
            D_DFA_Func_BlockPhase_Enter(dfa_func);
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
        if (!dfa_func->tmp_is_in_param_name) {
            strcpy(dfa_func->tmp_param_type, word);
            dfa_func->tmp_is_in_param_name = true;
        } else {
            strcpy(dfa_func->tmp_param_name, word);
            dfa_func->tmp_is_in_param_name = false;
            E_Function_AddParam(&dfa_func->function, dfa_func->tmp_param_type, dfa_func->tmp_param_name);
            // next param
            D_DFA_Func_ParamPhase_Enter(dfa_func);
        }
    }
}

void D_DFA_Func_BlockPhase_Enter(FAM_Func *dfa_func) {
    dfa_func->phase = Func_FA_Block;
    D_DFA_Block_Enter(&dfa_func->dfa_block);
}

void D_DFA_Func_BlockPhase_Process(FAM_Func *dfa_func, const string code, const string word, M_Cursor *cursor) {
    D_DFA_Block_Process(&dfa_func->dfa_block, code, word, cursor);
    if (dfa_func->dfa_block.is_done) {
        dfa_func->is_done = true;
    }
}

void D_DFA_Func_Free(FAM_Func *dfa_func) {
}

void D_DFA_Func_Enter(FAM_Func *dfa_func, E_Guess *guess) {
    // already:
    // public static fn
    FAM_Func_Init(dfa_func, guess);
    PLogNA("Enter DFA Func\r\n");
}

void D_DFA_Func_Process(FAM_Func *dfa_func, const string code, const string word, M_Cursor *cursor) {
    Func_FA phase = dfa_func->phase;
    if (phase == Func_FA_Name) {
        D_DFA_Func_NamePhase_Process(dfa_func, code, word, cursor);
    } else if (phase == Func_FA_Params) {
        D_DFA_Func_ParamPhase_Process(dfa_func, code, word, cursor);
    } else if (phase == Func_FA_Block) {
        D_DFA_Func_BlockPhase_Process(dfa_func, code, word, cursor);
    }
}