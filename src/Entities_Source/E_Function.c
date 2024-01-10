#include "E_Function.h"

void E_Function_Free(E_Function *self) {

    if (self->returnTypes_count > 0) {
        for (int i = 0; i < self->returnTypes_count; i++) {
            free(self->returnTypes[i]);
        }
        free(self->returnTypes);
    }

    if (self->params_count > 0) {
        for (int i = 0; i < self->params_count; i++) {
            free(self->params[i].type);
            free(self->params[i].name);
        }
        free(self->params);
    }

    E_Block_Free(&self->block);
}

void E_Function_SetName(E_Function *self, const string access, const string name) {
    strcpy(self->access, String_ValidAccess(access));
    strcpy(self->name, name);
}

void E_Function_AddReturnType(E_Function *self, const string type) {
    if (self->returnTypes == NULL) {
        self->returnTypes = malloc(sizeof(string) * 2);
        self->returnTypes_capacity = 2;
    }
    if (self->returnTypes_count >= self->returnTypes_capacity) {
        self->returnTypes_capacity += 2;
        self->returnTypes = realloc(self->returnTypes, sizeof(string) * self->returnTypes_capacity);
    }
    self->returnTypes[self->returnTypes_count] = malloc(sizeof(char) * RULE_STRUCT_TYPE_NAME_LEN);
    strcpy(self->returnTypes[self->returnTypes_count], type);
    self->returnTypes_count++;
}

void E_Function_AddParam(E_Function *self, const string type, const string name) {
    if (self->params == NULL) {
        self->params = malloc(sizeof(M_Parameter) * 5);
        self->params_capacity = 5;
    }
    if (self->params_count >= self->params_capacity) {
        self->params_capacity += 5;
        self->params = realloc(self->params, sizeof(M_Parameter) * self->params_capacity);
    }
    M_Parameter *param = &self->params[self->params_count];
    strcpy(param->type, type);
    strcpy(param->name, name);
    self->params_count++;
}

void E_Function_Log(const E_Function *self, bool is_static) {
    char returnTypes[RULE_STRUCT_TYPE_NAME_LEN * RULE_FUNCTION_RETURN_COUNT];
    memset(returnTypes, 0, sizeof(returnTypes));
    for (int i = 0; i < self->returnTypes_count; i++) {
        strcat(returnTypes, self->returnTypes[i]);
    }

    char params[RULE_STRUCT_TYPE_NAME_LEN * RULE_FUNCTION_PARAM_COUNT];
    memset(params, 0, sizeof(params));
    for (int i = 0; i < self->params_count; i++) {
        M_Parameter param = self->params[i];
        strcat(params, param.type);
        strcat(params, " ");
        strcat(params, param.name);
    }
    if (is_static) {
        printf("Static ");
    }
    printf("Function: %s fn%s%s(%s) \r\n", self->access, returnTypes, self->name, params);
}