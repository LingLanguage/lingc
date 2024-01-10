#include "D_DFA_Func.h"
#include "Util_Cursor.h"

// ==== Private ====
void D_DFA_Func_Enter(M_DFA_Func *dfa_func, E_Guess *guess);
void NamePhase_Process(M_DFA_Func *dfa_func, const string code, const string word, M_Cursor *cursor);
void ParamPhase_Enter(M_DFA_Func *dfa_func);
void ParamPhase_Process(M_DFA_Func *dfa_func, const string code, const string word, M_Cursor *cursor);
void BodyPhase_Enter(M_DFA_Func *dfa_func);
void BodyPhase_Process(M_DFA_Func *dfa_func, const string code, const string word, M_Cursor *cursor);

void NamePhase_Process(M_DFA_Func *dfa_func, const string code, const string word, M_Cursor *cursor) {
    if (cursor->is_split) {
        char split = word[0];
        if (split == KW_LEFT_BRACKET) {
            // (
            E_Function *func = &dfa_func->function;
            E_Guess_GuessFuctionName(&dfa_func->guess, cursor->file, cursor->line, func);
            ++cursor->index;
            ParamPhase_Enter(dfa_func);
        } else if (split == KW_COMMA) {
            // ,
            // do nothing
            ++cursor->index;
        } else {
            Util_Cursor_DealEmpty(cursor, code, word);
        }
    } else {
        E_Guess_PushWord(&dfa_func->guess, cursor->file, cursor->line, word);
    }
}

void ParamPhase_Enter(M_DFA_Func *dfa_func) {
    dfa_func->phase = FuncPhase_Params;
    dfa_func->tmp_is_in_param_name = false;
}

void ParamPhase_Process(M_DFA_Func *dfa_func, const string code, const string word, M_Cursor *cursor) {
    if (cursor->is_split) {
        char split = word[0];
        if (split == KW_RIGHT_BRACKET) {
            // )
            BodyPhase_Enter(dfa_func);
            ++cursor->index;
        } else if (split == KW_COMMA) {
            // ,
            // do nothing
            ++cursor->index;
        } else {
            Util_Cursor_DealEmpty(cursor, code, word);
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
            ParamPhase_Enter(dfa_func);
        }
    }
}

void BodyPhase_Enter(M_DFA_Func *dfa_func) {
    dfa_func->phase = FuncPhase_Body;
}

void BodyPhase_Process(M_DFA_Func *dfa_func, const string code, const string word, M_Cursor *cursor) {
    if (cursor->is_split) {
        char split = word[0];
        if (split == KW_LEFT_BRACE) {
            // {
            ++dfa_func->nested_level;
            ++cursor->index;
        } else if (split == KW_RIGHT_BRACE) {
            // } and nested level is 0, then end
            --dfa_func->nested_level;
            ++cursor->index;
            if (dfa_func->nested_level == 0) {
                dfa_func->is_done = true;
            }
        } else if (split == KW_EQUAL) {
            // =
            ++cursor->index;
            printf("TODO assign stm\r\n");
        } else if (split == KW_SEMICOLON) {
            // ;
            ++cursor->index;
            printf("TODO field end\r\n");
        } else {
            Util_Cursor_DealEmpty(cursor, code, word);
        }
    } else {
        if (strcmp(word, KW_RETURN) == 0) {
            // return
            printf("TODO return stm\r\n");
        } else {
            E_Guess_PushWord(&dfa_func->guess, cursor->file, cursor->line, word);
        }
    }
}

void D_DFA_Func_Free(M_DFA_Func *dfa_func) {
}

void D_DFA_Func_Enter(M_DFA_Func *dfa_func, E_Guess *guess) {
    // already:
    // public static fn
    M_DFA_Func_Init(dfa_func, guess);
    PLogNA("Enter DFA Func\r\n");
}

void D_DFA_Func_Process(M_DFA_Func *dfa_func, const string code, const string word, M_Cursor *cursor) {
    FuncPhase phase = dfa_func->phase;
    if (phase == FuncPhase_Name) {
        NamePhase_Process(dfa_func, code, word, cursor);
    } else if (phase == FuncPhase_Params) {
        ParamPhase_Process(dfa_func, code, word, cursor);
    } else if (phase == FuncPhase_Body) {
        BodyPhase_Process(dfa_func, code, word, cursor);
    }
}