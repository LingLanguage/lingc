#ifndef E_TYPE_H__
#define E_TYPE_H__

#include "E_Field.h"
#include "E_Function.h"
#include "import.h"

typedef enum StructBehaviourType {
    StructBehaviourType_Unknown = 0,
    StructBehaviourType_Something,
    StructBehaviourType_AfterAccess,
    StructBehaviourType_Field,
    StructBehaviourType_Function,
} StructBehaviourType;

typedef struct E_Struct {
    int id;
    int index;
    char access[RULE_ACCESS_MAX];
    char name[RULE_STRUCT_TYPE_NAME_MAX];

    E_Field *fields;
    int fields_count;

    E_Function *functions;
    int functions_count;

} E_Struct;

void E_Struct_Free(E_Struct *self);
void E_Struct_RecordField(E_Struct *self, int id, int index, string access, string name, string type);

#endif