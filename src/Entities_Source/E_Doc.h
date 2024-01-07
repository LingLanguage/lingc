#ifndef E_CURSOR_H__
#define E_CURSOR_H__

#include "E_Import.h"
#include "E_Struct.h"
#include "M_FSM_Import.h"
#include "import.h"

typedef struct E_Doc {

    string curFile;
    int curLine;

    int startIndex;
    int endIndex;

    TopBT topBT;

    E_Import *imports;
    int imports_count;

    M_FSM_Import fsm_import;

    E_Struct struct_current;
    bool struct_isBegin;
    StructBT struct_behaviourType;
    int struct_nestedLevel;
    int struct_lastIndex;

    char access[RULE_ACCESS_MAX];
    char typeName[RULE_STRUCT_TYPE_NAME_MAX];
    char name[RULE_VAR_NAME_MAX];
    char lastWords[RULE_VAR_NAME_MAX][12];
    int lastWordsCount;
    int topID;

} E_Doc;

void E_Doc_Reset(E_Doc *doc);
void E_Doc_Import_Add(E_Doc *doc, E_Import import);
void E_Doc_FSM_Import_Enter(E_Doc *doc);
void E_Doc_SlideWord(E_Doc *doc, const string word);
void E_Doc_Struct_Unknow_Enter(E_Doc *ctx);
void E_Doc_Struct_Something_Enter(E_Doc *doc);
void E_Doc_Struct_AfterAccess_Enter(E_Doc *doc);
void E_Doc_Struct_Field_Enter(E_Doc *doc);
void E_Doc_Struct_Function_Enter(E_Doc *doc);

#endif