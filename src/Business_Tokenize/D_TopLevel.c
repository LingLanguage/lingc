#include "D_TopLevel.h"
#include "D_Import.h"
#include "D_Struct.h"
#include "D_Func.h"
#include "Util_Cursor.h"

void D_TopLevel_Free(FAM_Top *fam) {
    FAM_Top_Free(fam);
}

void D_TopLevel_Enter(FAM_Top *fam, M_Cursor *cursor) {
    fam->status = Top_FA_Guess;
    E_Guess_InitAccess(&fam->guess);
    // PLogNA("Enter Top\r\n");
}

void D_TopLevel_Process(FAM_Top *fam, const string code, const string word, M_Cursor *cursor) {

    // import <stdio.h>;
    // import "raylib.h";
    E_Guess *guess = &fam->guess;

    if (!cursor->is_split) {
        if (strcmp(word, KW_IMPORT) == 0) {
            // import
            fam->status = Top_FA_Import;
            FAM_Import *dfa_import = fam->dfa_import;
            D_Import_Enter(dfa_import);
        } else if (strcmp(word, KW_FUNC) == 0) {
            // fn
            fam->status = Top_FA_Func;
            FAM_Func *dfa_func = fam->dfa_func;
            D_Func_Enter(dfa_func, guess->access, guess->is_static);
        } else if (strcmp(word, KW_STRUCT) == 0) {
            // struct
            // fam->status = Top_FA_Struct;
            // FAM_Struct *dfa_struct = fam->dfa_struct;
            // D_Struct_Enter(dfa_struct, file, line, guess);
        } else if (strcmp(word, KW_STATIC) == 0) {
            // static
            guess->is_static = true;
        } else if (strcmp(word, KW_CONST) == 0) {
            // const
            guess->is_const = true;
        } else if (String_IsAccess(word)) {
            // access: public, private...
            E_Guess_SetAcceess(guess, cursor->file, cursor->line, word);
        } else {
            // push word
            E_Guess_PushWord(guess, word);
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
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    }
}