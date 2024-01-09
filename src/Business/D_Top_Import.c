#include "D_Top_Import.h"
#include "D_Top_Guess.h"
#include "import.h"

void D_Top_Import_Enter(M_FSM_Import *fsm) {
    memset(fsm, 0, sizeof(M_FSM_Import));
    PLogNA("enter top import\r\n");
}

int D_Top_Import_Process(M_FSM_Import *fsm, const string file, int line, bool is_split, const string word, int index, const string code, long size) {

    if (is_split && Char_IsEmptySymbol(word[0])) {
        return index;
    }

    char split = word[0];
    const string value;
    ImportType type;
    if (split == KW_QUOTE) {
        // "
        value = String_CutBetweenSameChars(index, code, size, KW_QUOTE);
        if (value == NULL) {
            printf("err word:%s\r\n", word);
            PFailed(file, line, ERR_UNDIFINDED_ERR);
        } else {
            type = ImportType_Quote;
        }
    } else if (split == KW_LEFT_ANGLE_BRACKET) {
        // <
        value = String_CutBetweenDifferentChars(index, code, size, KW_LEFT_ANGLE_BRACKET, KW_RIGHT_ANGLE_BRACKET);
        if (value == NULL) {
            PFailed(file, line, ERR_UNDIFINDED_ERR);
        } else {
            type = ImportType_ANGLE_BRACKET;
        }
    } else if (split == KW_SEMICOLON) {
        // ;
        fsm->is_done = true;
    }

    if (value != NULL) {
        fsm->import = Factory_CreateImport(value, type);
        fsm->is_done = true;
    }
    return index;
}