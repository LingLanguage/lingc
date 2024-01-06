#include "E_Cursor.h"

void E_Cursor_Reset(E_Cursor *cursor) {
    cursor->behaviourType = BehaviourType_Unknown;
    cursor->topType = TOPTYPE_NONE;
    cursor->topID = -1;

    cursor->struct_isBegin = false;
    cursor->struct_nestedLevel = 0;

    cursor->lastWordsCount = 0;
}

void E_Cursor_FSM_Import_Enter(E_Cursor *cursor) {
    cursor->behaviourType = BehaviourType_Import;
    memset(&cursor->fsm_import, 0, sizeof(M_FSM_Import));
}

void E_Cursor_SlideWord(E_Cursor *cursor, const string word) {

    int capacity = sizeof(cursor->lastWords) / sizeof(cursor->lastWords[0]);
    if (cursor->lastWordsCount < capacity) {
        strcpy(cursor->lastWords[cursor->lastWordsCount], word);
        cursor->lastWordsCount++;
        return;
    }

    int i = 0;
    while (i < cursor->lastWordsCount - 1) {
        strcpy(cursor->lastWords[i], cursor->lastWords[i + 1]);
        i++;
    }
    strcpy(cursor->lastWords[cursor->lastWordsCount - 1], word);

}

void E_Cursor_Struct_Unknow_Enter(E_Cursor *cursor) {
    cursor->struct_behaviourType = StructBehaviourType_Unknown;
}

void E_Cursor_Struct_Something_Enter(E_Cursor *cursor) {
    cursor->struct_behaviourType = StructBehaviourType_Something;
}

void E_Cursor_Struct_AfterAccess_Enter(E_Cursor *cursor) {
    cursor->struct_behaviourType = StructBehaviourType_AfterAccess;
}

void E_Cursor_Struct_Field_Enter(E_Cursor *cursor) {
    cursor->struct_behaviourType = StructBehaviourType_Field;
}

void E_Cursor_Struct_Function_Enter(E_Cursor *cursor) {
    cursor->struct_behaviourType = StructBehaviourType_Function;
}