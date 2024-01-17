#include "D_Doc.h"

void D_Doc_Import_Add(CTX_Tokenize *ctx, E_Doc *doc, int import_id) {

}

void D_Doc_Log(const CTX_Tokenize *ctx, const E_Doc *doc) {
    printf("==== Doc ====\r\n");
    printf("file: %s, total line: %d\r\n", doc->file, doc->line);
    // printf("imports_count: %d\r\n", doc->imports_count);
    // printf("structs_count: %d\r\n", doc->structs_count);
    // printf("static_funcs_count: %d\r\n", doc->static_funcs_count);
    // printf("static_vars_count: %d\r\n", doc->static_vars_count);
    for (int i = 0; i < doc->imports_count; i++) {
        int id = doc->imports[i];
        E_Import *import;
        bool has= RP_Import_TryGet(ctx->rp_import, id, &import);
        if (!has) {
            PFailed(__FILE__, __LINE__, ERR_UNDIFINDED_ERR);
        } else {
            E_Import_Log(import);
        }
    }
    for (int i = 0; i < doc->structs_count; i++) {
        E_Struct *st = &doc->structs[i];
        E_Struct_Log(st);
    }
    for (int i = 0; i < doc->static_funcs_count; i++) {
        E_Function *func = &doc->static_funcs[i];
        E_Function_Log(func, true);
    }
    for (int i = 0; i < doc->static_vars_count; i++) {
        E_Field *var = &doc->static_vars[i];
        printf("static ");
        E_Field_Log(var);
    }
    printf("==== End ====\r\n\r\n");
}