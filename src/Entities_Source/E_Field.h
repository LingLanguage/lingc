#ifndef E_FIELD_H__
#define E_FIELD_H__

#include "import.h"

// 字段/静态变量
typedef struct E_Field {
    char access[RULE_ACCESS_NAME_LEN];
    char type[RULE_STRUCT_TYPE_NAME_LEN];
    char name[RULE_FUNCTION_NAME_LEN];
} E_Field;

E_Field E_Field_Create(const string access, const string type, const string name);
void E_Field_Log(const E_Field *self);

#endif