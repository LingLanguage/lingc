#ifndef E_STATICVAR_H__
#define E_STATICVAR_H__
#include "import.h"

typedef struct E_StaticVar {
    int id;
    int index;
    char name[RULE_VAR_NAME_MAX];
} E_StaticVar;

void E_StaticVar_Free(E_StaticVar *self);

#endif