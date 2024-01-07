#include "E_Field.h"

E_Field E_Field_Create(const string access, const string type, const string name) {
    E_Field field = {0};
    strcpy(field.name, name);
    strcpy(field.type, type);
    strcpy(field.access, String_ValidAccess(access));
    return field;
}