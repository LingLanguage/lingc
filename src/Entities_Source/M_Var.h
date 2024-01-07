#ifndef M_VAR_H__
#define M_VAR_H__

#include "import.h"

typedef struct M_Var {
    char type[RULE_STRUCT_TYPE_NAME_MAX];
    char name[RULE_VAR_NAME_MAX];
} M_Var;

#endif