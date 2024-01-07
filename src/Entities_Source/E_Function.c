#include "E_Function.h"

void E_Function_Free(E_Function *self) {
}

void E_Function_Init(E_Function *self, const string access, const string name) {
    strcpy(self->access, access);
    strcpy(self->name, name);
}

void E_Function_AddReturnType(E_Function *self, const string type) {
    strcpy(self->returnTypes[self->returnTypes_count], type);
    self->returnTypes_count++;
}

void E_Function_AddParam(E_Function *self, const string type, const string name) {
    M_Var *param = &self->params[self->index];
    strcpy(param->name, name);
    strcpy(param->type, type);
    self->index++;
}