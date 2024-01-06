#ifndef CONTEXT_H__
#define CONTEXT_H__

#include "Entities_Source/export.h"

typedef struct Context {

    E_Cursor *cursor;

    E_Struct *structs;
    int structs_count;
    int structs_idRecord;

    E_Function *static_functions;
    int static_functions_count;
    int static_functions_idRecord;

    E_StaticVar *static_vars;
    int static_vars_count;
    int static_vars_idRecord;

} Context;

static void Context_Init(Context *ctx) {

    ctx->cursor = (E_Cursor *)calloc(1, sizeof(E_Cursor));

    ctx->structs = (E_Struct *)calloc(10000, sizeof(E_Struct));
    ctx->structs_count = 0;
    ctx->structs_idRecord = 1;

    ctx->static_functions = (E_Function *)calloc(50000, sizeof(E_Function));
    ctx->static_functions_count = 0;
    ctx->static_functions_idRecord = 1;

    ctx->static_vars = (E_StaticVar *)calloc(50000, sizeof(E_StaticVar));
    ctx->static_vars_count = 0;
    ctx->static_vars_idRecord = 1;
}

#endif