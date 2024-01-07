#include "D_Access.h"
#include "D_Func.h"
#include "D_Struct.h"

void D_Access_Enter(Context *ctx, const string access) {
    E_Doc *doc = ctx->doc;
    E_Doc_FSM_Access_Enter(doc, access);
}

void D_Access_Process(Context *ctx, bool is_split, const string word, const string code, long size) {
    E_Doc *doc = ctx->doc;
    M_FSM_Access *fsm = &doc->fsm_access;
    if (strcmp(word, KW_FUNC) == 0) {
        D_Func_Enter(ctx, fsm->access, fsm->isStatic);
    } else if (strcmp(word, KW_STRUCT) == 0) {
        D_Struct_Enter(ctx, fsm->access, fsm->isStatic);
    } else if (strcmp(word, KW_STATIC) == 0) {
        fsm->isStatic = true;
    }
}