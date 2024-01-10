#include "M_DFA_Func.h"

void M_DFA_Func_Free(M_DFA_Func *fsm) {
    E_Function_Free(&fsm->function);
    free(fsm);
}

void ParamsPhase_Enter(M_DFA_Func *fsm);

void ReturnTypePhase_Process(M_DFA_Func *fsm, const string file, int line, bool is_split, const string word, const string code, long size) {
    if (is_split && word[0] == KW_LEFT_BRACKET) {
        // (
        // set return type
        for (int i = 0; i < fsm->words_count - 1; i++) {
            E_Function_AddReturnType(&fsm->function, fsm->words[i]);
        }
        E_Function_SetName(&fsm->function, fsm->function.access, fsm->words[fsm->words_count - 1]);
        // next phase: params
        ParamsPhase_Enter(fsm);
    } else {
        // types
        if (fsm->words_count >= RULE_FUNCTION_RETURN_COUNT) {
            PFailed(file, line, ERR_FUNCTION_TOO_MANY_RETURN_TYPES);
        } else {
            strcpy(fsm->words[fsm->words_count], word);
            fsm->words_count++;
        }
    }
}

void ParamsPhase_Enter(M_DFA_Func *fsm) {
    fsm->phase = FuncPhase_Params;
    memset(fsm->tmp_param_type, 0, sizeof(fsm->tmp_param_type));
    memset(fsm->tmp_param_name, 0, sizeof(fsm->tmp_param_name));
    fsm->tmp_is_in_param_name = false;
}

void ParamPhase_Process(M_DFA_Func *fsm, const string file, int line, bool is_split, const string word, const string code, long size) {
    if (is_split && word[0] == KW_RIGHT_BRACKET) {
        // )
        fsm->phase = FuncPhase_Body;
    } else if (!is_split) {
        // params
        if (!fsm->tmp_is_in_param_name) {
            strcpy(fsm->tmp_param_type, word);
            fsm->tmp_is_in_param_name = true;
        } else {
            strcpy(fsm->tmp_param_name, word);
            fsm->tmp_is_in_param_name = false;
            E_Function_AddParam(&fsm->function, fsm->tmp_param_type, fsm->tmp_param_name);
            // next param
            ParamsPhase_Enter(fsm);
        }
    }
}

int BodyPhase_Process(M_DFA_Func *fsm, const string file, int line, bool is_split, const string word, int index, const string code, long size) {
    if (is_split) {
        if (word[0] == KW_LEFT_BRACE) {
            // {
            fsm->nested_level++;
        } else if (word[0] == KW_RIGHT_BRACE) {
            // } and nested level is 0, then end
            fsm->nested_level--;
            if (fsm->nested_level == 0) {
                fsm->is_done = true;
            }
        } else {
        }
    } else {
    }
    return index;
}

// public
void M_DFA_Func_Enter(M_DFA_Func *fsm, E_Guess *guess) {
    memset(fsm, 0, sizeof(M_DFA_Func));
    String_CopyAccess(fsm->guess.access, guess->access);
    fsm->guess.is_const = guess->is_const;
    fsm->guess.is_static = guess->is_static;
}

int M_DFA_Func_Process(M_DFA_Func *fsm, const string file, int line, bool is_split, const string word, int index, const string code, long size) {
    FuncPhase phase = fsm->phase;
    if (phase == FuncPhase_ReturnType) {
        ReturnTypePhase_Process(fsm, file, line, is_split, word, code, size);
    } else if (phase == FuncPhase_Params) {
        ParamPhase_Process(fsm, file, line, is_split, word, code, size);
    } else if (phase == FuncPhase_Body) {
        index = BodyPhase_Process(fsm, file, line, is_split, word, index, code, size);
    }
    return index;
}
