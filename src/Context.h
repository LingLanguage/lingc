#ifndef CONTEXT_H__
#define CONTEXT_H__

#include "Entities_Source/export.h"

typedef struct Context {
    E_Doc **docs;
    int docs_count;
    int docs_capacity;
} Context;

void Context_Init(Context *ctx);
void Context_AddDoc(Context *ctx, E_Doc *doc);
void Context_Free(Context *ctx);

#endif