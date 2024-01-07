#include "E_Doc.h"

void E_Doc_Free(E_Doc *doc) {

    for (int i = 0; i < doc->imports_count; i++) {
        // E_Import_Free(&doc->imports[i]);
    }
    free(doc->imports);

    for (int i = 0; i < doc->structs_count; i++) {
        E_Struct_Free(&doc->structs[i]);
    }
    free(doc->structs);

    for (int i = 0; i < doc->static_funcs_count; i++) {
        E_Function_Free(&doc->static_funcs[i]);
    }
    free(doc->static_funcs);

    for (int i = 0; i < doc->static_vars_count; i++) {
        // E_Field_Free(&doc->static_vars[i]);
    }
    free(doc->static_vars);

    free(doc);
}

void E_Doc_Init(E_Doc *doc, const string file) {
    memset(doc, 0, sizeof(E_Doc));
    strcpy(doc->curFile, file);
    doc->curLine = 1;
}

void E_Doc_Import_Add(E_Doc *doc, E_Import import) {
    if (doc->imports_count == 0) {
        doc->imports = (E_Import *)malloc(sizeof(E_Import) * 4);
    } else {
        doc->imports = (E_Import *)realloc(doc->imports, sizeof(E_Import) * (doc->imports_count * 2));
    }
    doc->imports[doc->imports_count++] = import;
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

// ==== FSM ====
void E_Doc_FSM_Guess_Enter(E_Doc *doc) {
    doc->top_status = TopFSMStatus_Guess;
    M_FSM_Guess *fsm = &doc->fsm_guess;
    M_FSM_Guess_Enter(fsm);
}

void E_Doc_FSM_Import_Enter(E_Doc *doc) {
    doc->top_status = TopFSMStatus_Import;
    M_FSM_Import *fsm = &doc->fsm_import;
    M_FSM_Import_Enter(fsm);
}

void E_Doc_FSM_Access_Enter(E_Doc *doc, const string access) {
    doc->top_status = TopFSMStatus_Access;
    M_FSM_Access *fsm = &doc->fsm_access;
    memset(fsm, 0, sizeof(M_FSM_Access));
    E_Guess_SetAccess(&fsm->guess, doc->curFile, doc->curLine, access);
}

void E_Doc_FSM_Struct_Enter(E_Doc *doc, const string access, bool is_static) {
    doc->top_status = TopFSMStatus_Struct;
    M_FSM_Struct *fsm = &doc->fsm_struct;
    memset(fsm, 0, sizeof(M_FSM_Struct));
    fsm->st.is_static = is_static;
    strcpy(fsm->st.access, String_ValidAccess(access));
}

void E_Doc_FSM_Func_Enter(E_Doc *doc, const string access, bool is_static) {
    doc->top_status = TopFSMStatus_Func;
    M_FSM_Func *fsm = &doc->fsm_func;
    M_FSM_Func_Enter(fsm, access, is_static);
}
