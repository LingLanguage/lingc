#ifndef E_IMPORT_H__
#define E_IMPORT_H__

#include "import.h"

typedef struct E_Import {
    char name[RULE_IMPORT_FILE_NAME_LEN];
    ImportType importType;
} E_Import;

#endif