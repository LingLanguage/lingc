#include "D_Top_Func.h"

void D_Top_Func_Enter(Context *ctx, const string access, bool is_static) {
    E_Doc *doc = ctx->doc;
    E_Doc_FSM_Func_Enter(doc, access, is_static);
    PLog("func enter: %s\r\n", access);
}

void D_Top_Func_Process(Context *ctx, bool is_split, const string word, const string code, long size) {
    E_Doc *doc = ctx->doc;
    M_FSM_Func *fsm = &ctx->doc->fsm_func;
    M_FSM_Func_Process(fsm, doc->curFile, doc->curLine, is_split, word, code, size);
    if (fsm->is_done) {
        PLogNA("Top Func End\r\n");
    }
}