#ifndef RP_EXP_H__
#define RP_EXP_H__

#include "../Entities_Tokenize/export.h"
#include "Dictionary.h"

typedef struct RP_EXP {
    Dictionary *all;
} RP_EXP;

void RP_EXP_Init(RP_EXP *rp_exp);
void RP_EXP_Free(RP_EXP *rp);
void RP_EXP_Add(RP_EXP *rp, E_Expression *exp);
bool RP_EXP_TryGet(RP_EXP *rp, int id, E_Expression **exp);

#endif