#include "D_Access.h"
#include "D_Func.h"

void D_Access_Enter(Context *ctx) {
    E_Doc *doc = ctx->doc;
    E_Doc_FSM_Access_Enter(doc);
}

void D_Access_Process(Context *ctx, bool isSplit, const string word, const string code, long size) {
    if (strcmp(word, KW_FUNC) == 0) {
        D_Func_Enter(ctx, word);
    } else if (strcmp(word, KW_STRUCT) == 0) {
        PLogNA("struct enter\r\n");
    }
}