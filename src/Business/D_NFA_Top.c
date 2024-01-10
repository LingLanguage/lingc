#include "D_NFA_Top.h"
#include "D_DFA_Func.h"
#include "D_DFA_Import.h"
#include "D_DFA_Struct.h"
#include "Util_Cursor.h"

void D_NFA_Top_Free(M_NFA_Top *nfa_top) {
    M_NFA_Top_Free(nfa_top);
}

void D_NFA_Top_Enter(M_NFA_Top *nfa_top) {
    nfa_top->status = NFA_Top_Status_Guess;
    E_Guess_Init(&nfa_top->guess);
}

void D_NFA_Top_Process(M_NFA_Top *nfa_top, const string code, const string word, M_Cursor *cursor) {

    // import <stdio.h>;
    // import "raylib.h";

    E_Guess *guess = &nfa_top->guess;
    if (!cursor->is_split) {
        if (strcmp(word, KW_IMPORT) == 0) {
            // import
            nfa_top->status = NFA_Top_Status_Import;
            M_DFA_Import *dfa_import = nfa_top->dfa_import;
            D_DFA_Import_Enter(dfa_import);
        } else if (strcmp(word, KW_FUNC) == 0) {
            // fn
            // nfa_top->status = NFA_Top_Status_Func;
            // M_DFA_Func *dfa_func = nfa_top->dfa_func;
            // D_DFA_Func_Enter(dfa_func, guess);
        } else if (strcmp(word, KW_STRUCT) == 0) {
            // struct
            // nfa_top->status = NFA_Top_Status_Struct;
            // M_DFA_Struct *dfa_struct = nfa_top->dfa_struct;
            // D_DFA_Struct_Enter(dfa_struct, file, line, guess);
        } else if (strcmp(word, KW_STATIC) == 0) {
            // static
            guess->is_static = true;
        } else if (strcmp(word, KW_CONST) == 0) {
            // const
            guess->is_const = true;
        } else if (String_IsAccess(word)) {
            // access: public, private...
            E_Guess_SetAccess(guess, cursor->file, cursor->line, word);
        } else {
            // push word
            E_Guess_PushWord(guess, cursor->file, cursor->line, word);
        }
    } else {
        char split = word[0];
        if (split == KW_EQUAL) {
            // = assign stm
            ++cursor->index;
            PLogNA("TODO assign stm\r\n");
        } else if (split == KW_SEMICOLON) {
            // ; field end
            ++cursor->index;
            PLogNA("TODO field end\r\n");
        } else if (split == KW_RIGHT_BRACE) {
            // }
            PFailed(cursor->file, cursor->line, ERR_FUNCTION_OR_FIELD_NOT_END);
        } else {
            Util_Cursor_DealEmpty(cursor, code, word);
        }
    }
}