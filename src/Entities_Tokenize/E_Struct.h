#ifndef E_STRUCT_H__
#define E_STRUCT_H__

#include "E_Field.h"
#include "E_Function.h"
#include "import.h"

// 结构体
typedef struct E_Struct {

    int id;
    int index;

    char access[RULE_ACCESS_NAME_LEN];
    char name[RULE_STRUCT_TYPE_NAME_LEN];

    int *field_ids;
    byte fields_count;

    int *function_ids;
    int functions_count;

} E_Struct;

void E_Struct_Free(E_Struct *self);
void E_Struct_RecordField(E_Struct *self, int field_id);
void E_Struct_RecordFunction(E_Struct *self, int function_id);

#endif