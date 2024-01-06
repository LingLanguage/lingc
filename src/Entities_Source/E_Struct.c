#include "E_Struct.h"

void Field_Add(E_Struct *self, E_Field field) {
    if (self->fields_count == 0) {
        self->fields = (E_Field *)malloc(sizeof(E_Field) * 4);
    } else {
        self->fields = (E_Field *)realloc(self->fields, sizeof(E_Field) * (self->fields_count * 2));
    }
    self->fields[self->fields_count++] = field;
}

void E_Struct_RecordField(E_Struct *self, int id, int index, string access, string name, string type) {
    E_Field field;
    field.id = id;
    field.index = index;
    strcpy(field.access, access);
    strcpy(field.name, name);
    strcpy(field.type, type);
    Field_Add(self, field);
}
