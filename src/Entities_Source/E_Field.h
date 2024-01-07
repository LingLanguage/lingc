#ifndef E_FIELD_H__
#define E_FIELD_H__

#include "import.h"

typedef struct E_Field {
    int id;
    int index;
    char name[RULE_FUNCTION_NAME_LEN];
    char type[RULE_STRUCT_TYPE_NAME_MAX];
    char access[RULE_ACCESS_NAME_LEN];
} E_Field;

#endif