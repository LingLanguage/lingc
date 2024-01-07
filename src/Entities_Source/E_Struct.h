#ifndef E_STRUCT_H__
#define E_STRUCT_H__

#include "E_Field.h"
#include "E_Function.h"
#include "E_Guess.h"
#include "import.h"

// 结构体
typedef struct E_Struct {

    int id;
    int index;

    char access[RULE_ACCESS_NAME_LEN];
    bool is_static;
    char name[RULE_STRUCT_TYPE_NAME_LEN];

    E_Field *fields;
    byte fields_count;

    E_Function *functions;
    byte functions_count;

} E_Struct;

void E_Struct_Free(E_Struct *self);
void E_Struct_RecordField(E_Struct *self, E_Field field);
void E_Struct_RecordFunction(E_Struct *self, E_Function function);
void E_Struct_Log(const E_Struct *self);

#endif