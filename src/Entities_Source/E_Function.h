#ifndef E_FUNCTION_H__
#define E_FUNCTION_H__
#include "E_Block.h"
#include "E_Statement.h"
#include "M_Parameter.h"
#include "import.h"

// 函数
typedef struct E_Function {

    char access[RULE_ACCESS_NAME_LEN];
    bool is_static;
    char name[RULE_FUNCTION_NAME_LEN];

    char **returnTypes;
    byte returnTypes_capacity;
    byte returnTypes_count;

    M_Parameter *params;
    byte params_capacity;
    byte params_count;

    E_Block block;

} E_Function;

void E_Function_Free(E_Function *self);
void E_Function_SetName(E_Function *self, const string access, const string name);
void E_Function_AddReturnType(E_Function *self, const string type);
void E_Function_AddParam(E_Function *self, const string type, const string name);
void E_Function_Log(const E_Function *self, bool is_static);

#endif