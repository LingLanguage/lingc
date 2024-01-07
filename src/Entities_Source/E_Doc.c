#include "E_Doc.h"

void E_Doc_Reset(E_Doc *doc) {
    memset(doc, 0, sizeof(E_Doc));
}

void E_Doc_Import_Add(E_Doc *doc, E_Import import) {
    if (doc->imports_count == 0) {
        doc->imports = (E_Import *)malloc(sizeof(E_Import) * 4);
    } else {
        doc->imports = (E_Import *)realloc(doc->imports, sizeof(E_Import) * (doc->imports_count * 2));
    }
    doc->imports[doc->imports_count++] = import;
}

// ==== FSM ====
void E_Doc_FSM_Guess_Enter(E_Doc *doc) {
    doc->top_status = TopFSMStatus_Guess;
    M_FSM_Guess *fsm = &doc->fsm_guess;
    memset(fsm, 0, sizeof(M_FSM_Guess));
}

void E_Doc_FSM_Import_Enter(E_Doc *doc) {
    doc->top_status = TopFSMStatus_Import;
    M_FSM_Import *fsm = &doc->fsm_import;
    memset(fsm, 0, sizeof(M_FSM_Import));
}

void E_Doc_FSM_Access_Enter(E_Doc *doc, const string access) {
    doc->top_status = TopFSMStatus_Access;
    M_FSM_Access *fsm = &doc->fsm_access;
    memset(fsm, 0, sizeof(M_FSM_Access));
    strcpy(fsm->access, access);
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
