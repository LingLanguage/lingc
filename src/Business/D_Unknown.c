#include "D_Unknown.h"
#include "D_Import.h"

void D_Unknown_Enter(Context *ctx) {
    E_Doc *doc = ctx->doc;
    doc->topBT = TopBT_Unknown;
    // PLogNA("D_Unknown_Enter\r\n");
}

void D_Unknown_Process(Context *ctx, bool isSplit, const string word, const string code, long size) {
    E_Doc *doc = ctx->doc;
    if (strcmp(word, KW_IMPORT) == 0) {
        D_Import_Enter(ctx);
    } else if (Context_IsAccess(ctx, word)) {
        D_Access_Enter(ctx);
    }
}