#include "E_Function.h"

void E_Function_Free(E_Function *self) {
}

void E_Function_SetName(E_Function *self, const string access, const string name) {
    strcpy(self->access, ValidAccess(access));
    strcpy(self->name, name);
}

void E_Function_AddReturnType(E_Function *self, const string type) {
    strcpy(self->returnTypes[self->returnTypes_count], type);
    self->returnTypes_count++;
}

void E_Function_AddParam(E_Function *self, const string type, const string name) {
    M_Var *param = &self->params[self->params_count];
    strcpy(param->name, name);
    strcpy(param->type, type);
    self->params_count++;
}

void E_Function_Log(E_Function *self) {
    char returnTypes[RULE_STRUCT_TYPE_NAME_MAX * RULE_FUNCTION_RETURN_COUNT];
    memset(returnTypes, 0, sizeof(returnTypes));
    for (int i = 0; i < self->returnTypes_count; i++) {
        strcat(returnTypes, self->returnTypes[i]);
    }
    PLog("Function: %s fn%s%s \r\n", self->access, returnTypes, self->name);
}