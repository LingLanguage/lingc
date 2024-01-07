#include "M_FSM_Func.h"

void M_FSM_Func_Enter(M_FSM_Func *fsm, const string access, bool is_static) {
    memset(fsm, 0, sizeof(M_FSM_Func));
    strcpy(fsm->function.access, ValidAccess(access));
    fsm->function.is_static = is_static;
}

void M_FSM_Func_Process(M_FSM_Func *fsm, string file, int line, bool is_split, const string word, const string code, long size) {
    FuncPhase phase = fsm->phase;
    if (phase == FuncPhase_ReturnType) {
        if (is_split && word[0] == KW_LEFT_BRACKET) {
            // (
            // set return type
            for (int i = 0; i < fsm->words_count - 1; i++) {
                E_Function_AddReturnType(&fsm->function, fsm->words[i]);
            }
            E_Function_SetName(&fsm->function, fsm->function.access, fsm->words[fsm->words_count - 1]);
            // next phase: params
            M_FSM_Func_EnterParams(fsm);
        } else {
            // types
            if (fsm->words_count >= RULE_FUNCTION_RETURN_COUNT) {
                PLogCode(file, line, ERR_FUNCTION_TOO_MANY_RETURN_TYPES);
            } else {
                strcpy(fsm->words[fsm->words_count], word);
                fsm->words_count++;
            }
        }
    } else if (phase == FuncPhase_Params) {
        if (is_split && word[0] == KW_RIGHT_BRACKET) {
            // )
            fsm->phase = FuncPhase_Body;
            E_Function_Log(&fsm->function);
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
                M_FSM_Func_EnterParams(fsm);
            }
        }
    } else if (phase == FuncPhase_Body) {
        // {
        if (is_split && word[0] == KW_LEFT_BRACE) {
            fsm->phase = FuncPhase_Body;
        } else {
            // fsm->phase = FuncPhase_End;
        }
    }
}

void M_FSM_Func_EnterParams(M_FSM_Func *fsm) {
    fsm->phase = FuncPhase_Params;
    memset(fsm->tmp_param_type, 0, sizeof(fsm->tmp_param_type));
    memset(fsm->tmp_param_name, 0, sizeof(fsm->tmp_param_name));
    fsm->tmp_is_in_param_name = false;
}