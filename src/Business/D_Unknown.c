#include "D_Unknown.h"
#include "D_Import.h"

void D_Unknown_Enter(Context *ctx) {
    E_Cursor *cursor = ctx->cursor;
    cursor->behaviourType = BehaviourType_Unknown;
    PLogNA("D_Unknown_Enter\r\n");
}

void D_Unknown_Process(Context *ctx, bool isSplit, const string word, const string code, long size) {
    E_Cursor *cursor = ctx->cursor;
    if (strcmp(word, KW_IMPORT) == 0) {
        D_Import_Enter(ctx);
    }
}