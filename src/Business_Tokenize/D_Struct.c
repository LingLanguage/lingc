#include "D_Struct.h"
#include "D_TopLevel.h"
#include "Util_Cursor.h"

bool D_Struct_GuessStructName(E_Guess *guess, const string file, int line, const string name, E_Struct *st) {
    bool is_ok = true;
    if (guess->words_count == 0) {
        PFailed(file, line, ERR_STRUCT_NAME_NOT_FOUND);
        is_ok = false;
    } else if (guess->words_count == 1) {
        if (guess->is_const) {
            PFailed(file, line, ERR_STRUCT_CANNOT_BE_CONST);
            is_ok = false;
        } else {
            // name
            if (strlen(st->name) <= 0) {
                strcpy(st->name, guess->words[0]);
            } else {
                PFailed(file, line, ERR_STRUCT_NAME_REDIFINED);
                is_ok = false;
            }
        }
    } else {
        for (int i = 0; i < guess->words_count; i++) {
            printf("%s\r\n", guess->words[i]);
        }
        PFailed(file, line, ERR_STRUCT_NAME_TOO_MANY_WORDS);
        is_ok = false;
    }

    if (is_ok) {
        String_CopyAccess(st->access, guess->access);
        E_Guess_InitAccess(guess);
    }
    return is_ok;
}

void D_Struct_Free(FAM_Struct *fam) {
}

void D_Struct_Guess_Enter(FAM_Struct *fam) {
    fam->phase = Struct_FA_Guess;
    E_Guess_Init(&fam->guess);
    PLogNA("Enter DFA Struct\r\n");
}

void Phase_Name_Process(FAM_Struct *fam, const string code, const string word, M_Cursor *cursor) {
    E_Guess *guess = &fam->guess;
    if (cursor->is_split) {
        char split = word[0];
        if (split == KW_LEFT_BRACE) {
            // {
            fam->phase = Struct_FA_Guess;
            fam->nested_level += 1;
            fam->is_done = true;
            ++cursor->index;
        } else {
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    } else {
        E_Guess_PushWord(guess, word);
        bool is_ok = D_Struct_GuessStructName(guess, cursor->file, cursor->line, word, &fam->st);
        if (is_ok) {
            D_Struct_Guess_Enter(fam);
        }
    }
}

void D_Struct_Enter(FAM_Struct *fam, M_Cursor *cursor) {
    memset(fam, 0, sizeof(FAM_Struct));
    fam->phase = Struct_FA_Name;
}

void D_Struct_Process(FAM_Struct *fam, const string code, const string word, M_Cursor *cursor) {
    E_Struct *st = &fam->st;
    Struct_FA phase = fam->phase;
    if (phase == Struct_FA_Name) {
        Phase_Name_Process(fam, code, word, cursor);
    } else if (phase == Struct_FA_Guess) {
    } else if (phase == Struct_FA_Func) {
    }
}