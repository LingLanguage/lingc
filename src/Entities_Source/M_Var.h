#ifndef M_VAR_H__
#define M_VAR_H__

#include "import.h"

typedef struct M_Var {
    char type[RULE_STRUCT_TYPE_NAME_LEN];
    char name[RULE_VAR_NAME_LEN];
} M_Var;

#endif