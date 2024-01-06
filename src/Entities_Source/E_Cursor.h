#ifndef E_CURSOR_H__
#define E_CURSOR_H__

#include "E_Struct.h"
#include "import.h"

typedef struct E_Cursor {

    int curIndex;
    int lastIndex;
    int line;

    BehaviourType behaviourType;

    E_Struct struct_current;
    bool struct_isBegin;
    StructBehaviourType struct_behaviourType;
    int struct_nestedLevel;
    int struct_lastIndex;

    char access[RULE_ACCESS_MAX];
    char typeName[RULE_STRUCT_TYPE_NAME_MAX];
    char name[RULE_VAR_NAME_MAX];
    char lastWords[RULE_VAR_NAME_MAX][12];
    int lastWordsCount;
    TopType topType;
    int topID;

} E_Cursor;

void E_Cursor_Reset(E_Cursor *cursor);
void E_Cursor_SlideWord(E_Cursor *cursor, const string word);
void E_Cursor_Struct_Unknow_Enter(E_Cursor *ctx);
void E_Cursor_Struct_Something_Enter(E_Cursor *cursor);
void E_Cursor_Struct_AfterAccess_Enter(E_Cursor *cursor);
void E_Cursor_Struct_Field_Enter(E_Cursor *cursor);
void E_Cursor_Struct_Function_Enter(E_Cursor *cursor);

#endif