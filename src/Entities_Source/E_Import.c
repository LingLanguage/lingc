#include "E_Import.h"

void E_Import_Log(const E_Import *self) {
    if (self->importType == ImportType_ANGLE_BRACKET) {
        printf("import: <%s>\r\n", self->name);
    } else if (self->importType == ImportType_Quote) {
        printf("import: \"%s\"\r\n", self->name);
    }
}