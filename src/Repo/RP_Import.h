#ifndef RP_IMPORT_H__
#define RP_IMPORT_H__

#include "Dictionary.h"
#include "import.h"

typedef struct RP_Import RP_Import;

typedef struct RP_Import {
    Dictionary *all;
} RP_Import;

void RP_Import_Init(RP_Import *self);
void RP_Import_Free(RP_Import *self);
void RP_Import_Add(RP_Import *self, int id, E_Import *import);
bool RP_Import_TryGet(RP_Import *self, int id, E_Import **import);

#endif