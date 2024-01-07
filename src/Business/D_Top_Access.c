#include "D_Top_Access.h"
#include "D_Top_Func.h"
#include "D_Top_Struct.h"

void D_Top_Access_Enter(E_Doc *doc, const string access) {
    E_Doc_FSM_Access_Enter(doc, access);
}

void D_Top_Access_Process(E_Doc *doc, bool is_split, const string word, const string code, long size) {
    M_FSM_Access *fsm = &doc->fsm_access;
    if (!is_split) {
        if (strcmp(word, KW_FUNC) == 0) {
            // fn
            D_Top_Func_Enter(doc, fsm->guess.access, fsm->guess.is_static);
        } else if (strcmp(word, KW_STRUCT) == 0) {
            // struct
            D_Top_Struct_Enter(doc, fsm->guess.access, fsm->guess.is_static);
        } else if (strcmp(word, KW_STATIC) == 0) {
            // static
            fsm->guess.is_static = true;
        } else if (String_IsAccess(word)) {
            // err: access redefined
            PFailed(doc->curFile, doc->curLine, ERR_REDIFINED_ACCESS);
        } else {
            // push word
            E_Guess_PushWord(&fsm->guess, doc->curFile, doc->curLine, word);
        }
    } else {
        if (word[0] == KW_SEMICOLON) {
            // ; field end
            E_Field field;
            bool is_ok = E_Guess_Field(&fsm->guess, doc->curFile, doc->curLine, &field);
            if (is_ok) {
                E_Doc_StaticVar_Add(doc, field);
            }
        } else if (word[0] == KW_RIGHT_BRACE) {
            PFailed(doc->curFile, doc->curLine, ERR_FUNC_OR_FIELD_NOT_END);
        }
    }
}