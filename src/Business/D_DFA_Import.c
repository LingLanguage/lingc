#include "D_DFA_Import.h"
#include "D_NFA_Top.h"
#include "Util_Cursor.h"
#include "import.h"

void D_DFA_Import_Free(M_DFA_Import *fsm) {
}

void D_DFA_Import_Enter(M_DFA_Import *fsm) {
    memset(fsm, 0, sizeof(M_DFA_Import));
    PLogNA("Enter DFA Import\r\n");
}

void D_DFA_Import_Process(M_DFA_Import *fsm, const string code, const string word, M_Cursor *cursor) {

    if (cursor->is_split) {
        char split = word[0];
        if (split == KW_QUOTE) {
            // "
            int right_index = String_CutBetweenSameChars(cursor->index, code, cursor->code_size, KW_QUOTE);
            if (right_index != -1) {
                const string value = String_SubString(code, cursor->index + 1, right_index - cursor->index - 1); // 去掉两边的引号
                fsm->import = Factory_CreateImport(value, ImportType_Quote);
                cursor->index = right_index + 1;
            } else {
                PLog("err word:%s\r\n", word);
                PFailed(cursor->file, cursor->line, ERR_UNDIFINDED_ERR);
            }
        } else if (split == KW_LEFT_ANGLE_BRACKET) {
            // <
            int right_index = String_CutBetweenDifferentChars(cursor->index, code, cursor->code_size, KW_LEFT_ANGLE_BRACKET, KW_RIGHT_ANGLE_BRACKET);
            if (right_index != -1) {
                const string value = String_SubString(code, cursor->index + 1, right_index - cursor->index - 1); // 去掉两边的尖括号
                fsm->import = Factory_CreateImport(value, ImportType_ANGLE_BRACKET);
                cursor->index = right_index + 1;
            } else {
                PLog("err word:%s\r\n", word);
                PFailed(cursor->file, cursor->line, ERR_UNDIFINDED_ERR);
            }
        } else if (split == KW_SEMICOLON) {
            // ;
            ++cursor->index;
            fsm->is_done = true;
        } else {
            Util_Cursor_DealEmpty(cursor, code, word);
        }
    } else {
        PFailed(cursor->file, cursor->line, ERR_UNDIFINDED_ERR);
    }
}