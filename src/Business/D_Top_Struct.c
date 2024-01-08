#include "D_Top_Struct.h"
#include "D_Top_Guess.h"

void FieldEnd(M_FSM_Struct *fsm, string file, int line, bool isSplit, const string word) {
    E_Field field;
    bool is_ok = E_Guess_Field(&fsm->guess, file, line, &field);
    if (is_ok) {
        E_Struct_RecordField(&fsm->st, field);
        M_FSM_Struct_EnterGuess(fsm);
    }
}

void D_Top_Struct_Enter(E_Doc *doc, const string access, bool is_static) {
    E_Doc_FSM_Struct_Enter(doc, access, is_static);
}

int D_Top_Struct_Process(E_Doc *doc, bool isSplit, const string word, int index, const string code, long size) {
    M_FSM_Struct *fsm = &doc->fsm_struct;
    E_Struct *st = &fsm->st;
    StructPhase phase = fsm->phase;
    if (phase == StructPhase_Name) {
        if (isSplit && word[0] == KW_LEFT_BRACE) {
            // {
            fsm->phase = StructPhase_Guess;
            fsm->nested_level += 1;
        } else if (!isSplit) {
            if (strlen(st->name) <= 0) {
                // name
                strcpy(st->name, word);
            } else {
                // err: name redefined
                PFailed(doc->curFile, doc->curLine, ERR_STRUCT_NAME_REDIFINED);
            }
        }
    } else if (phase == StructPhase_Guess) {
        if (!isSplit) {
            if (String_IsAccess(word)) {
                // access: public, private...
                strcpy(fsm->guess.access, word);
                fsm->phase = StructPhase_Access;
            } else if (strcmp(word, KW_FUNC) == 0) {
                // fn
                fsm->phase = StructPhase_Func;
                M_FSM_Func_Enter(&fsm->fsm_func, KW_ACCESS_PRIVATE, false);
            } else {
                // push word
                E_Guess_PushWord(&fsm->guess, doc->curFile, doc->curLine, word);
            }
        } else {
            if (word[0] == KW_SEMICOLON) {
                // ; field end
                FieldEnd(fsm, doc->curFile, doc->curLine, isSplit, word);
            } else if (word[0] == KW_RIGHT_BRACE) {
                // }
                fsm->nested_level -= 1;
                if (fsm->nested_level == 0) {
                    // struct end
                    E_Doc_Struct_Add(doc, *st);
                    D_Top_Guess_Enter(doc);
                }
            }
        }
    } else if (phase == StructPhase_Access) {
        if (!isSplit) {
            if (strcmp(word, KW_FUNC) == 0) {
                // fn
                fsm->phase = StructPhase_Func;
                M_FSM_Func_Enter(&fsm->fsm_func, fsm->guess.access, false);
            } else if (String_IsAccess(word)) {
                // err: access redefined
                PFailed(doc->curFile, doc->curLine, ERR_ACCESS_REDIFINED);
            } else {
                // push word
                E_Guess_PushWord(&fsm->guess, doc->curFile, doc->curLine, word);
            }
        } else {
            if (word[0] == KW_SEMICOLON) {
                // ; field end
                FieldEnd(fsm, doc->curFile, doc->curLine, isSplit, word);
            } else if (word[0] == KW_RIGHT_BRACE) {
                PFailed(doc->curFile, doc->curLine, ERR_FUNCTION_OR_FIELD_NOT_END);
            }
        }
    } else if (phase == StructPhase_Func) {
        M_FSM_Func *fsm_func = &fsm->fsm_func;
        index = M_FSM_Func_Process(fsm_func, doc->curFile, doc->curLine, isSplit, word, index, code, size);
        if (fsm_func->is_done) {
            E_Struct_RecordFunction(st, fsm_func->function);
            M_FSM_Struct_EnterGuess(fsm);
        }
    }
    return index;
}