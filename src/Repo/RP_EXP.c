#include "RP_EXP.h"

void RP_EXP_Init(RP_EXP *rp) {
    rp->all = Dictionary_New(1000);
}

void RP_EXP_Free(RP_EXP *rp) {
    Dictionary_Free(rp->all);
    free(rp->all);
}

void RP_EXP_Add(RP_EXP *rp, E_Expression *exp) {
    Dictionary_Add(rp->all, exp->id, exp);
}

bool RP_EXP_TryGet(RP_EXP *rp, int id, E_Expression **exp) {
    return Dictionary_TryGet(rp->all, id, (void **)exp);
}