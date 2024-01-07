#ifndef FACTORY_H__
#define FACTORY_H__

#include "Context.h"

E_Import Factory_CreateImport(Context *context, const string name, ImportType type);

#endif