#ifndef E_FUNCTION_H__
#define E_FUNCTION_H__
#include "E_Statement.h"
#include "M_Var.h"
#include "import.h"

typedef struct E_Function {

    int id;
    int index;

    char access[RULE_ACCESS_NAME_LEN];
    bool is_static;
    char name[RULE_FUNCTION_NAME_LEN];

    char returnTypes[RULE_STRUCT_TYPE_NAME_LEN][RULE_FUNCTION_RETURN_COUNT];
    byte returnTypes_count;

    M_Var params[RULE_FUNCTION_PARAM_COUNT];
    byte params_count;

} E_Function;

void E_Function_Free(E_Function *self);
void E_Function_SetName(E_Function *self, const string access, const string name);
void E_Function_AddReturnType(E_Function *self, const string type);
void E_Function_AddParam(E_Function *self, const string type, const string name);
void E_Function_Log(E_Function *self);

#endif