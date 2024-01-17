#include "E_Doc.h"

void E_Doc_Init(E_Doc *doc, const string file) {
    strcpy(doc->file, file);
    doc->line = 1;
}

void E_Doc_Free(E_Doc *doc) {

    // - Import
    for (int i = 0; i < doc->imports_count; i++) {
        // E_Import_Free(&doc->imports[i]);
    }
    if (doc->imports_count > 0) {
        free(doc->imports);
    }

    // - Struct
    for (int i = 0; i < doc->structs_count; i++) {
        E_Struct_Free(&doc->structs[i]);
    }
    if (doc->structs_count > 0) {
        free(doc->structs);
    }

    // - StaticFunc
    for (int i = 0; i < doc->static_funcs_count; i++) {
        E_Function_Free(&doc->static_funcs[i]);
    }
    if (doc->static_funcs_count > 0) {
        free(doc->static_funcs);
    }

    // - StaticVar
    for (int i = 0; i < doc->static_vars_count; i++) {
        // E_Field_Free(&doc->static_vars[i]);
    }
    if (doc->static_vars_count > 0) {
        free(doc->static_vars);
    }

    free(doc);
}

void E_Doc_Import_Add(E_Doc *doc, int import_id) {
    if (doc->imports_count == 0) {
        doc->imports = (int *)malloc(sizeof(int) * 4);
    } else {
        doc->imports = (int *)realloc(doc->imports, sizeof(int) * (doc->imports_count * 2));
    }
    doc->imports[doc->imports_count++] = import_id;
}

void E_Doc_Struct_Add(E_Doc *doc, E_Struct st) {
    if (doc->structs_count == 0) {
        doc->structs = (E_Struct *)malloc(sizeof(E_Struct) * 4);
    } else {
        doc->structs = (E_Struct *)realloc(doc->structs, sizeof(E_Struct) * (doc->structs_count * 2));
    }
    doc->structs[doc->structs_count++] = st;
}

void E_Doc_StaticVar_Add(E_Doc *doc, E_Field field) {
    if (doc->static_vars_count == 0) {
        doc->static_vars = (E_Field *)malloc(sizeof(E_Field) * 4);
    } else {
        doc->static_vars = (E_Field *)realloc(doc->static_vars, sizeof(E_Field) * (doc->static_vars_count * 2));
    }
    doc->static_vars[doc->static_vars_count++] = field;
}

void E_Doc_StaticFunc_Add(E_Doc *doc, E_Function func) {
    if (doc->static_funcs_count == 0) {
        doc->static_funcs = (E_Function *)malloc(sizeof(E_Function) * 4);
    } else {
        doc->static_funcs = (E_Function *)realloc(doc->static_funcs, sizeof(E_Function) * (doc->static_funcs_count * 2));
    }
    doc->static_funcs[doc->static_funcs_count++] = func;
}
