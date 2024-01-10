#include "D_DFA_Struct.h"
#include "D_NFA_Top.h"

int Phase_Name_Process(M_FSM_Struct *fsm, const string file, int line, bool isSplit, const string word, int index, const string code, long size) {
    if (isSplit) {
        char split = word[0];
        if (split == KW_LEFT_BRACE) {
            // {
            fsm->phase = StructPhase_Guess;
            fsm->nested_level += 1;
            fsm->is_done = true;
        } else {
            if (Char_IsEmptySymbol(split)) {
                // ' ' '\t' '\n' '\r'
                return index;
            }
            PFailed(file, line, ERR_UNDIFINDED_ERR);
        }
    } else {
        E_Guess_PushWord(&fsm->guess, file, line, word);
        bool is_ok = E_Guess_GuessStructName(&fsm->guess, file, line, word, &fsm->st);
        if (is_ok) {
            M_FSM_Struct_EnterGuess(fsm);
        }
    }
    return index;
}

void D_DFA_Struct_Enter(E_Doc *doc, E_Guess *guess) {
    E_Doc_FSM_Struct_Enter(doc, guess);
    PLogNA("enter top struct\r\n");
}

int D_DFA_Struct_Process(M_FSM_Struct *fsm, const string file, int line, bool isSplit, const string word, int index, const string code, long size) {
    E_Struct *st = &fsm->st;
    StructPhase phase = fsm->phase;
    if (phase == StructPhase_Name) {
        index = Phase_Name_Process(fsm, file, line, isSplit, word, index, code, size);
    } else if (phase == StructPhase_Guess) {
        // Guess: field or function
        if (!isSplit) {
            if (String_IsAccess(word)) {
                // access: public, private...
                E_Guess_SetAccess(&fsm->guess, file, line, word);
            } else if (strcmp(word, KW_FUNC) == 0) {
                // fn
                M_FSM_Struct_EnterFunc(fsm, &fsm->guess);
            } else if (strcmp(word, KW_CONST) == 0) {
                // const
                E_Guess_SetConst(&fsm->guess, file, line, word);
            } else {
                // push word
                E_Guess_PushWord(&fsm->guess, file, line, word);
            }
        } else {
            if (word[0] == KW_SEMICOLON) {
                // ; field end
                E_Field field;
                bool is_ok = E_Guess_GuessField(&fsm->guess, file, line, &field);
                if (is_ok) {
                    E_Struct_RecordField(&fsm->st, field);
                    M_FSM_Struct_EnterGuess(fsm);
                }
            } else if (word[0] == KW_RIGHT_BRACE) {
                // }
                fsm->nested_level -= 1;
                if (fsm->nested_level == 0) {
                    // struct end
                    fsm->is_done = true;
                }
            }
        }
    } else if (phase == StructPhase_Func) {
        M_FSM_Func *fsm_func = &fsm->fsm_func;
        index = M_FSM_Func_Process(fsm_func, file, line, isSplit, word, index, code, size);
        if (fsm_func->is_done) {
            E_Struct_RecordFunction(st, fsm_func->function);
            M_FSM_Struct_EnterGuess(fsm);
        }
    }
    return index;
}