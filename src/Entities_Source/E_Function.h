#ifndef E_FUNCTION_H__
#define E_FUNCTION_H__
#include "import.h"
#include "M_Var.h"

typedef struct E_Function {
    int id;
    int index;
    char access[RULE_ACCESS_NAME_LEN];
    char name[RULE_FUNCTION_NAME_LEN];
    char returnTypes[RULE_STRUCT_TYPE_NAME_MAX][RULE_FUNCTION_RETURN_COUNT];
    int returnTypes_count;
    M_Var params[RULE_FUNCTION_PARAM_COUNT];
    // TODO: Statements
} E_Function;

void E_Function_Free(E_Function *self);
void E_Function_Init(E_Function *self, const string access, const string name);
void E_Function_AddReturnType(E_Function *self, const string type);
void E_Function_AddParam(E_Function *self, const string type, const string name);

#endif