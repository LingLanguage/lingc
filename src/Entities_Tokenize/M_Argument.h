#ifndef M_ARGUMENT_H__
#define M_ARGUMENT_H__

#include "import.h"

// 实参
typedef struct M_Argument {
    ArgumentType type;
    char name[RULE_VAR_NAME_LEN];
} M_Argument;

#endif