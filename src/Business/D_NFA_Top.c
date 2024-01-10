#include "D_NFA_Top.h"
#include "D_DFA_Func.h"
#include "D_DFA_Import.h"
#include "D_DFA_Struct.h"

void D_NFA_Top_Enter(E_Doc *doc) {
    E_Doc_FSM_Guess_Enter(doc);
    PLogNA("enter top guess\r\n");
}

void D_NFA_Top_Process(E_Doc *doc, bool isSplit, const string word, const string code, long size) {

    if (isSplit) {
        return;
    }

    M_FSM_Guess *fsm = &doc->fsm_guess;
    E_Guess *guess = &fsm->guess;
    if (!isSplit) {
        if (strcmp(word, KW_IMPORT) == 0) {
            // import
            doc->top_status = TopFSMStatus_Import;
            M_FSM_Import *fsm_import = &doc->fsm_import;
            D_DFA_Import_Enter(fsm_import);
        } else if (strcmp(word, KW_FUNC) == 0) {
            // fn
            doc->top_status = TopFSMStatus_Func;
            M_FSM_Func *fsm_func = &doc->fsm_func;
            D_DFA_Func_Enter(fsm_func, guess);
        } else if (strcmp(word, KW_STRUCT) == 0) {
            // struct
            doc->top_status = TopFSMStatus_Struct;
            D_DFA_Struct_Enter(doc, guess);
        } else if (strcmp(word, KW_STATIC) == 0) {
            // static
            guess->is_static = true;
        } else if (strcmp(word, KW_CONST) == 0) {
            // const
            guess->is_const = true;
        } else if (String_IsAccess(word)) {
            // access: public, private...
            E_Guess_SetAccess(guess, doc->curFile, doc->curLine, word);
        } else {
            // push word
            E_Guess_PushWord(guess, doc->curFile, doc->curLine, word);
        }
    } else {
        if (word[0] == KW_SEMICOLON) {
            // ; field end
            E_Field field;
            bool is_ok = E_Guess_GuessField(&fsm->guess, doc->curFile, doc->curLine, &field);
            if (is_ok) {
                E_Doc_StaticVar_Add(doc, field);
            } else {
                PLogNA("TODO: guess field failed\r\n");
            }
        } else if (word[0] == KW_RIGHT_BRACE) {
            // }
            PFailed(doc->curFile, doc->curLine, ERR_FUNCTION_OR_FIELD_NOT_END);
        }
    }
}