#ifndef E_FUNCTION_H__
#define E_FUNCTION_H__
#include "import.h"

typedef struct E_Function {
    int id;
    int index;
    string name;
    int belongStructID;
    char returns[RULE_FUNCTION_NAME_MAX][RULE_FUNCTION_RETURN_MAX];
    byte returns_count;
    char params[RULE_FUNCTION_PARAM_NAME_MAX][RULE_FUNCTION_PARAM_MAX];
    byte params_count;
} E_Function;

#endif