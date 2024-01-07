#include "D_Func.h"

void D_Func_Enter(Context *ctx, const string access, bool is_static) {
    E_Doc *doc = ctx->doc;
    E_Doc_FSM_Func_Enter(doc, access, is_static);
    PLog("func enter: %s\r\n", access);
}

void D_Func_Process(Context *ctx, bool is_split, const string word, const string code, long size) {
    M_FSM_Func *fsm = &ctx->doc->fsm_func;
    FuncPhase phase = fsm->phase;
    if (phase == FuncPhase_ReturnType) {
        // (
        if (is_split && word[0] == KW_LEFT_BRACKET) {
            fsm->phase = FuncPhase_Params;
            PLogNA("params enter\r\n");
        } else {
            E_Function_AddReturnType(&fsm->function, word);
            PLog("return type: %s\r\n", word);
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