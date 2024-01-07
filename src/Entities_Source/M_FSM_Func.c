#include "M_FSM_Func.h"

void M_FSM_Func_Enter(M_FSM_Func *fsm, const string access, bool is_static) {
    memset(fsm, 0, sizeof(M_FSM_Func));
    strcpy(fsm->function.access, ValidAccess(access));
    fsm->function.is_static = is_static;
}

void M_FSM_Func_Process(M_FSM_Func *fsm, string file, int line, bool is_split, const string word, const string code, long size) {
    FuncPhase phase = fsm->phase;
    if (phase == FuncPhase_ReturnType) {
        // (
        if (is_split && word[0] == KW_LEFT_BRACKET) {
            fsm->phase = FuncPhase_Params;
            for (int i = 0; i < fsm->words_count - 1; i++) {
                E_Function_AddReturnType(&fsm->function, fsm->words[i]);
            }
            E_Function_SetName(&fsm->function, fsm->function.access, fsm->words[fsm->words_count - 1]);
            E_Function_Log(&fsm->function);
        } else {
            if (fsm->words_count >= RULE_FUNCTION_RETURN_COUNT) {
                PLogCode(file, line, ERR_FUNCTION_TOO_MANY_RETURN_TYPES);
            } else {
                strcpy(fsm->words[fsm->words_count], word);
                fsm->words_count++;
            }
        }
    } else if (phase == FuncPhase_Params) {
        // )
        if (is_split && word[0] == KW_RIGHT_BRACKET) {
            fsm->phase = FuncPhase_Body;
        } else if (!is_split) {
            if (fsm->isParamType) {
                strcpy(fsm->paramType, word);
                fsm->isParamType = false;
            } else {
                strcpy(fsm->paramName, word);
                fsm->isParamType = true;
                E_Function_AddParam(&fsm->function, fsm->paramType, fsm->paramName);
            }
            PLog("param: %s\r\n", word);
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