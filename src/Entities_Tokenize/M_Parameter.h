#ifndef M_PARAMETER_H__
#define M_PARAMETER_H__

#include "import.h"

// 形参
typedef struct M_Parameter {
    char type[RULE_STRUCT_TYPE_NAME_LEN];
    char name[RULE_VAR_NAME_LEN];
} M_Parameter;

#endif