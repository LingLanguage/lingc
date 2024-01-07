#include "D_Unknown.h"
#include "D_Func.h"
#include "D_Import.h"
#include "D_Struct.h"

void D_Guess_Enter(Context *ctx) {
    E_Doc *doc = ctx->doc;
    E_Doc_FSM_Guess_Enter(doc);
}

void D_Guess_Process(Context *ctx, bool isSplit, const string word, const string code, long size) {
    if (isSplit) {
        return;
    }

    E_Doc *doc = ctx->doc;
    M_FSM_Guess *fsm = &doc->fsm_guess;
    if (strcmp(word, KW_IMPORT) == 0) {
        D_Import_Enter(ctx);
    } else if (Context_IsAccess(ctx, word)) {
        D_Access_Enter(ctx, word);
    } else if (strcmp(word, KW_FUNC) == 0) {
        D_Func_Enter(ctx, KW_ACCESS_PRIVATE, fsm->is_static);
    } else if (strcmp(word, KW_STRUCT) == 0) {
        D_Struct_Enter(ctx, KW_ACCESS_PRIVATE, fsm->is_static);
    } else if (strcmp(word, KW_STATIC) == 0) {
        fsm->is_static = true;
    }
}