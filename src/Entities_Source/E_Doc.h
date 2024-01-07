#ifndef E_CURSOR_H__
#define E_CURSOR_H__

#include "E_Import.h"
#include "E_Struct.h"
#include "M_FSM_Access.h"
#include "M_FSM_Func.h"
#include "M_FSM_Import.h"
#include "M_FSM_Struct.h"
#include "import.h"

typedef struct E_Doc {

    string curFile;
    int curLine;

    int startIndex;
    int endIndex;

    E_Import *imports;
    int imports_count;

    TopFSMStatus top_status;
    M_FSM_Import fsm_import;
    M_FSM_Access fsm_access;
    M_FSM_Func fsm_func;
    M_FSM_Struct fsm_struct;

    char access[RULE_ACCESS_NAME_LEN];
    char typeName[RULE_STRUCT_TYPE_NAME_MAX];
    char name[RULE_VAR_NAME_MAX];
    char lastWords[RULE_VAR_NAME_MAX][12];
    int lastWordsCount;
    int topID;

} E_Doc;

void E_Doc_Reset(E_Doc *doc);
void E_Doc_Import_Add(E_Doc *doc, E_Import import);
void E_Doc_FSM_Import_Enter(E_Doc *doc);
void E_Doc_FSM_Access_Enter(E_Doc *doc, const string access);
void E_Doc_FSM_Struct_Enter(E_Doc *doc, const string access, bool is_static);
void E_Doc_FSM_Func_Enter(E_Doc *doc, const string access, bool is_static);
void E_Doc_SlideWord(E_Doc *doc, const string word);

#endif