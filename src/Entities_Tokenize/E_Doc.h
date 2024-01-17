#ifndef E_DOC_H__
#define E_DOC_H__

#include "E_Import.h"
#include "E_Struct.h"
#include "FAM_Func.h"
#include "FAM_Top.h"
#include "FAM_Import.h"
#include "FAM_Struct.h"
#include "import.h"

// 单份代码文件解析
typedef struct E_Doc {

    char file[FILENAME_MAX * 2];
    int line;

    int *imports;
    byte imports_count;

    E_Struct *structs;
    byte structs_count;

    E_Function *static_funcs;
    byte static_funcs_count;

    E_Field *static_vars;
    byte static_vars_count;

} E_Doc;

void E_Doc_Init(E_Doc *doc, const string file);
void E_Doc_Free(E_Doc *doc);
void E_Doc_Import_Add(E_Doc *doc, int import_id);
void E_Doc_Struct_Add(E_Doc *doc, E_Struct st);
void E_Doc_StaticVar_Add(E_Doc *doc, E_Field var);
void E_Doc_StaticFunc_Add(E_Doc *doc, E_Function func);

#endif