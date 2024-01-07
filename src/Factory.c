#include "Factory.h"

E_Field Factory_CreateField(const string access, const string type, const string name) {
    E_Field field = {0};
    strcpy(field.name, name);
    strcpy(field.type, type);
    strcpy(field.access, String_ValidAccess(access));
    return field;
}

E_Import Factory_CreateImport(const string name, ImportType type) {
    E_Import import = {0};
    import.importType = type;
    strcpy(import.name, name);
    return import;
}