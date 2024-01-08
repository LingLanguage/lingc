#include "E_Function.h"

void E_Function_Free(E_Function *self) {
    free(self->statements);
}

void E_Function_SetName(E_Function *self, const string access, const string name) {
    strcpy(self->access, String_ValidAccess(access));
    strcpy(self->name, name);
}

void E_Function_AddReturnType(E_Function *self, const string type) {
    strcpy(self->returnTypes[self->returnTypes_count], type);
    self->returnTypes_count++;
}

void E_Function_AddParam(E_Function *self, const string type, const string name) {
    M_Parameter *param = &self->params[self->params_count];
    strcpy(param->name, name);
    strcpy(param->type, type);
    self->params_count++;
}

void E_Function_AddStatement(E_Function *self, E_Statement expression) {
    if (self->statements_count == 0) {
        self->statements = (E_Statement *)malloc(sizeof(E_Statement));
    } else {
        self->statements = (E_Statement *)realloc(self->statements, sizeof(E_Statement) * (self->statements_count + 1));
    }
    self->statements[self->statements_count++] = expression;
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

    for (int i = 0; i < self->statements_count; i++) {
        E_Statement *statement = &self->statements[i];
        if (is_static) {
            printf("\t");
        } else {
            printf("\t\t");
        }
        E_Statement_Log(statement);
    }
}