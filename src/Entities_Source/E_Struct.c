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
