#ifndef FACTORY_H__
#define FACTORY_H__

#include "Context.h"

E_Field Factory_CreateField(const string access, const string type, const string name);
E_Import Factory_CreateImport(const string name, ImportType type);

#endif