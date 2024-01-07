#ifndef FACTORY_H__
#define FACTORY_H__

#include "Context.h"

E_Import Factory_CreateImport(Context* context, const string name, ImportType type) {
    E_Import import = {0};
    import.importType = type;
    strcpy(import.name, name);
    return import;
}

#endif