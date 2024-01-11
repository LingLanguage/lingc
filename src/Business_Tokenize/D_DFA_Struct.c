#include "D_DFA_Struct.h"
#include "D_NFA_Top.h"

void D_DFA_Struct_Free(FAM_Struct *dfa_struct) {
}

void Guess_Enter(FAM_Struct *dfa_struct) {
    dfa_struct->phase = Struct_FA_Guess;
    E_Guess_Init(&dfa_struct->guess);
    PLogNA("Enter DFA Struct\r\n");
}

int Phase_Name_Process(FAM_Struct *dfa_struct, const string file, int line, bool isSplit, const string word, int index, const string code, long size) {
    if (isSplit) {
        char split = word[0];
        if (split == KW_LEFT_BRACE) {
            // {
            dfa_struct->phase = Struct_FA_Guess;
            dfa_struct->nested_level += 1;
            dfa_struct->is_done = true;
        } else {
            if (Char_IsEmptySymbolButNewLine(split)) {
                // ' ' '\t' '\n' '\r'
                return index;
            }
            PFailed(file, line, ERR_UNDIFINDED_ERR);
        }
    } else {
        E_Guess_PushWord(&dfa_struct->guess, file, line, word);
        bool is_ok = E_Guess_GuessStructName(&dfa_struct->guess, file, line, word, &dfa_struct->st);
        if (is_ok) {
            Guess_Enter(dfa_struct);
        }
    }
    return index;
}

void D_DFA_Struct_Enter(FAM_Struct *dfa_struct, const string file, int line, E_Guess *guess) {
    memset(dfa_struct, 0, sizeof(FAM_Struct));
    E_Guess_SetAccess(&dfa_struct->guess, file, line, guess->access);
    E_Guess_SetConst(&dfa_struct->guess, file, line, guess->is_const);
    E_Guess_SetStatic(&dfa_struct->guess, file, line, guess->is_static);
    dfa_struct->phase = Struct_FA_Name;
}

int D_DFA_Struct_Process(FAM_Struct *dfa_struct, const string file, int line, bool isSplit, const string word, int index, const string code, long size) {
    E_Struct *st = &dfa_struct->st;
    Struct_FA phase = dfa_struct->phase;
    if (phase == Struct_FA_Name) {
        index = Phase_Name_Process(dfa_struct, file, line, isSplit, word, index, code, size);
    } else if (phase == Struct_FA_Guess) {
    } else if (phase == Struct_FA_Func) {
    }
    return index;
}