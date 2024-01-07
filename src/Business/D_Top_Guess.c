#include "D_Top_Guess.h"
#include "D_Top_Func.h"
#include "D_Top_Import.h"
#include "D_Top_Struct.h"

void D_Top_Guess_Enter(Context *ctx) {
    E_Doc *doc = ctx->doc;
    E_Doc_FSM_Guess_Enter(doc);
}

void D_Top_Guess_Process(Context *ctx, bool isSplit, const string word, const string code, long size) {
    if (isSplit) {
        return;
    }

    E_Doc *doc = ctx->doc;
    M_FSM_Guess *fsm = &doc->fsm_guess;
    if (strcmp(word, KW_IMPORT) == 0) {
        // import
        D_Top_Import_Enter(ctx);
    } else if (Context_IsAccess(ctx, word)) {
        // access: public, private...
        D_Top_Access_Enter(ctx, word);
    } else if (strcmp(word, KW_FUNC) == 0) {
        // fn
        D_Top_Func_Enter(ctx, KW_ACCESS_PRIVATE, fsm->is_static);
    } else if (strcmp(word, KW_STRUCT) == 0) {
        // struct
        D_Top_Struct_Enter(ctx, KW_ACCESS_PRIVATE, fsm->is_static);
    } else if (strcmp(word, KW_STATIC) == 0) {
        // static
        fsm->is_static = true;
    }
}