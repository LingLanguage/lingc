#ifndef E_IMPORT_H__
#define E_IMPORT_H__

#include "import.h"

typedef struct E_Import {
    int id;
    char name[RULE_IMPORT_FILE_NAME_LEN];
    ImportType import_type;
} E_Import;

void E_Import_Log(const E_Import *self);

#endif