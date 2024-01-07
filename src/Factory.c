#include "Factory.h"

E_Import Factory_CreateImport(Context* context, const string name, ImportType type) {
    E_Import import = {0};
    import.importType = type;
    strcpy(import.name, name);
    return import;
}