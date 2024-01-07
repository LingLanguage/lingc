#include "E_Doc.h"

void E_Doc_Reset(E_Doc *doc) {
    doc->topBT = TopBT_Unknown;
    doc->topID = -1;

    doc->struct_isBegin = false;
    doc->struct_nestedLevel = 0;

    doc->lastWordsCount = 0;
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
void E_Doc_FSM_Import_Enter(E_Doc *doc) {
    doc->topBT = TopBT_Import;
    memset(&doc->fsm_import, 0, sizeof(M_FSM_Import));
}

void E_Doc_FSM_Access_Enter(E_Doc *doc) {
    doc->topBT = TopBT_Access;
    memset(&doc->fsm_access, 0, sizeof(M_FSM_Access));
}

void E_Doc_FSM_Func_Enter(E_Doc *doc, const string access) {
    doc->topBT = TopBT_Func;
    memset(&doc->fsm_func, 0, sizeof(M_FSM_Func));
    strcpy(doc->fsm_func.function.access, access);
}

void E_Doc_SlideWord(E_Doc *doc, const string word) {

    int capacity = sizeof(doc->lastWords) / sizeof(doc->lastWords[0]);
    if (doc->lastWordsCount < capacity) {
        strcpy(doc->lastWords[doc->lastWordsCount], word);
        doc->lastWordsCount++;
        return;
    }

    int i = 0;
    while (i < doc->lastWordsCount - 1) {
        strcpy(doc->lastWords[i], doc->lastWords[i + 1]);
        i++;
    }
    strcpy(doc->lastWords[doc->lastWordsCount - 1], word);
}

void E_Doc_Struct_Unknow_Enter(E_Doc *doc) {
    doc->struct_behaviourType = StructBT_Unknown;
}

void E_Doc_Struct_Something_Enter(E_Doc *doc) {
    doc->struct_behaviourType = StructBT_Something;
}

void E_Doc_Struct_AfterAccess_Enter(E_Doc *doc) {
    doc->struct_behaviourType = StructBT_AfterAccess;
}

void E_Doc_Struct_Field_Enter(E_Doc *doc) {
    doc->struct_behaviourType = StructBT_Field;
}

void E_Doc_Struct_Function_Enter(E_Doc *doc) {
    doc->struct_behaviourType = StructBT_Function;
}