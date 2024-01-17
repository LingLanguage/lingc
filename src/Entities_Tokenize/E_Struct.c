#include "E_Struct.h"

void E_Struct_Free(E_Struct *self) {
    if (self->fields_count > 0) {
        free(self->field_ids);
    }
    if (self->functions_count > 0) {
        free(self->function_ids);
    }
}

void E_Struct_RecordField(E_Struct *self, int field_id) {
    if (self->fields_count == 0) {
        self->field_ids = (int *)malloc(sizeof(int) * 4);
    } else {
        self->field_ids = (int *)realloc(self->field_ids, sizeof(int) * (self->fields_count * 2));
    }
    self->field_ids[self->fields_count++] = field_id;
}

void E_Struct_RecordFunction(E_Struct *self, int function_id) {
    if (self->functions_count == 0) {
        self->function_ids = (int *)malloc(sizeof(int) * 4);
    } else {
        self->function_ids = (int *)realloc(self->function_ids, sizeof(int) * (self->functions_count * 2));
    }
    self->function_ids[self->functions_count++] = function_id;
}