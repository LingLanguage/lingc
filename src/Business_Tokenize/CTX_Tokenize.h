#ifndef CTX_TOKENIZE_H__
#define CTX_TOKENIZE_H__

#include "../Repo/export.h"

typedef struct CTX_Tokenize CTX_Tokenize;

typedef struct CTX_Tokenize {

    RP_EXP *rp_exp;
    int exp_id;

    RP_Import *rp_import;
    int import_id;

} CTX_Tokenize;

void CTX_Tokenize_Init(CTX_Tokenize *ctx);

#endif