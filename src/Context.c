#include "Context.h"

void Context_Init(Context *ctx) {
    ctx->docs_count = 0;
    ctx->docs_capacity = 10000;
    ctx->docs = (E_Doc **)calloc(ctx->docs_capacity, sizeof(E_Doc *));
}

void Context_AddDoc(Context *ctx, E_Doc *doc) {
    if (ctx->docs_count == ctx->docs_capacity) {
        ctx->docs_capacity *= 2;
        ctx->docs = (E_Doc **)realloc(ctx->docs, ctx->docs_capacity * sizeof(E_Doc *));
    }
    ctx->docs[ctx->docs_count++] = doc;
}

void Context_Free(Context *ctx) {
    for (int i = 0; i < ctx->docs_count; i++) {
        if (ctx->docs[i] != NULL) {
            E_Doc_Free(ctx->docs[i]);
        }
    }
    free(ctx->docs);
}