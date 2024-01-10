#include "D_DFA_Import.h"
#include "D_NFA_Top.h"
#include "import.h"

void D_DFA_Import_Free(M_DFA_Import *fsm) {
}

void D_DFA_Import_Enter(M_DFA_Import *fsm) {
    memset(fsm, 0, sizeof(M_DFA_Import));
    PLogNA("enter top import\r\n");
}

int D_DFA_Import_Process(M_DFA_Import *fsm, const string file, int line, bool is_split, const string word, int index, const string code, long size) {

    if (!is_split) {
        return index;
    }
    
    if (Char_IsEmptySymbol(word[0])) {
        return index;
    }

    char split = word[0];
    if (split == KW_QUOTE) {
        // "
        int right_index = String_CutBetweenSameChars(index, code, size, KW_QUOTE);
        if (right_index != -1) {
            const string value = String_SubString(code, index + 1, right_index - index - 1); // 去掉两边的引号
            fsm->import = Factory_CreateImport(value, ImportType_Quote);
            index = right_index;
        } else {
            PLog("err word:%s\r\n", word);
            PFailed(file, line, ERR_UNDIFINDED_ERR);
        }
    } else if (split == KW_LEFT_ANGLE_BRACKET) {
        // <
        int right_index = String_CutBetweenDifferentChars(index, code, size, KW_LEFT_ANGLE_BRACKET, KW_RIGHT_ANGLE_BRACKET);
        if (right_index != -1) {
            const string value = String_SubString(code, index + 1, right_index - index - 1); // 去掉两边的尖括号
            fsm->import = Factory_CreateImport(value, ImportType_ANGLE_BRACKET);
            index = right_index;
        } else {
            PLog("err word:%s\r\n", word);
            PFailed(file, line, ERR_UNDIFINDED_ERR);
        }
    }

    if (split == KW_SEMICOLON) {
        // ;
        fsm->is_done = true;
    }

    return index;
}