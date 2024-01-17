#include "RP_Import.h"

void RP_Import_Init(RP_Import *self) {
    self->all = Dictionary_New(1000);
}

void RP_Import_Free(RP_Import *self) {
    Dictionary_Free(self->all);
    free(self->all);
}

void RP_Import_Add(RP_Import *self, int id, E_Import *import) {
    Dictionary_Add(self->all, id, import);
}

bool RP_Import_TryGet(RP_Import *self, int id, E_Import **import) {
    return Dictionary_TryGet(self->all, id, (void **)import);
}