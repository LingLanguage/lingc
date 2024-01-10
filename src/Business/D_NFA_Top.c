#include "D_NFA_Top.h"
#include "D_DFA_Func.h"
#include "D_DFA_Import.h"
#include "D_DFA_Struct.h"

void D_NFA_Top_Free(M_NFA_Top *nfa_top) {
    D_DFA_Func_Free(nfa_top->dfa_func);
    D_DFA_Import_Free(nfa_top->dfa_import);
    D_DFA_Struct_Free(nfa_top->dfa_struct);
    free(nfa_top);
}

void D_NFA_Top_Enter(M_NFA_Top *nfa_top) {
    E_Guess_Init(&nfa_top->guess);
}

void D_NFA_Top_Process(M_NFA_Top *nfa_top, const string file, int line, bool is_split, const string word, const string code, long size) {

    if (is_split) {
        return;
    }

    E_Guess *guess = &nfa_top->guess;
    if (!is_split) {
        if (strcmp(word, KW_IMPORT) == 0) {
            // import
            nfa_top->status = NFA_Top_Status_Import;
            M_DFA_Import *dfa_import = nfa_top->dfa_import;
            D_DFA_Import_Enter(dfa_import);
        } else if (strcmp(word, KW_FUNC) == 0) {
            // fn
            nfa_top->status = NFA_Top_Status_Func;
            M_DFA_Func *dfa_func = nfa_top->dfa_func;
            D_DFA_Func_Enter(dfa_func, guess);
        } else if (strcmp(word, KW_STRUCT) == 0) {
            // struct
            nfa_top->status = NFA_Top_Status_Struct;
            M_DFA_Struct *dfa_struct = nfa_top->dfa_struct;
            D_DFA_Struct_Enter(dfa_struct, file, line, guess);
        } else if (strcmp(word, KW_STATIC) == 0) {
            // static
            guess->is_static = true;
        } else if (strcmp(word, KW_CONST) == 0) {
            // const
            guess->is_const = true;
        } else if (String_IsAccess(word)) {
            // access: public, private...
            E_Guess_SetAccess(guess, file, line, word);
        } else {
            // push word
            E_Guess_PushWord(guess, file, line, word);
        }
    } else {
        if (word[0] == KW_SEMICOLON) {
            // ; field end
        } else if (word[0] == KW_RIGHT_BRACE) {
            // }
            PFailed(file, line, ERR_FUNCTION_OR_FIELD_NOT_END);
        }
    }
}