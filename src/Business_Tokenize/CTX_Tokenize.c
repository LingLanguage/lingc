#include "CTX_Tokenize.h"

void CTX_Tokenize_Init(CTX_Tokenize *ctx) {

    ctx->rp_exp = malloc(sizeof(RP_EXP));
    ctx->exp_id = 1;
    RP_EXP_Init(ctx->rp_exp);

    ctx->rp_import = malloc(sizeof(RP_Import));
    ctx->import_id = 1;
    RP_Import_Init(ctx->rp_import);

}

void CTX_Tokenize_Free(CTX_Tokenize *ctx) {
    RP_EXP_Free(ctx->rp_exp);
    RP_Import_Free(ctx->rp_import);
    free(ctx->rp_exp);
}