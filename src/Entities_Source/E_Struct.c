#include "E_Struct.h"

void Field_Add(E_Struct *self, E_Field field) {
    if (self->fields_count == 0) {
        self->fields = (E_Field *)malloc(sizeof(E_Field) * 4);
    } else {
        self->fields = (E_Field *)realloc(self->fields, sizeof(E_Field) * (self->fields_count * 2));
    }
    self->fields[self->fields_count++] = field;
}

void E_Struct_Free(E_Struct *self) {
    if (self->fields_count > 0) {
        free(self->fields);
    }
    if (self->functions_count > 0) {
        free(self->functions);
    }
}

void E_Struct_RecordField(E_Struct *self, E_Field field) {
    Field_Add(self, field);
}

void E_Struct_RecordFunction(E_Struct *self, E_Function function) {
    if (self->functions_count == 0) {
        self->functions = (E_Function *)malloc(sizeof(E_Function) * 4);
    } else {
        self->functions = (E_Function *)realloc(self->functions, sizeof(E_Function) * (self->functions_count * 2));
    }
    self->functions[self->functions_count++] = function;
}

void E_Struct_Log(const E_Struct *self) {
    printf("Struct: %s %s\r\n", self->access, self->name);
    for (int i = 0; i < self->fields_count; i++) {
        printf("\t");
        E_Field_Log(&self->fields[i]);
    }
    for (int i = 0; i < self->functions_count; i++) {
        printf("\t");
        E_Function_Log(&self->functions[i]);
    }
}