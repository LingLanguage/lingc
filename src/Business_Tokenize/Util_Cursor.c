#include "Util_Cursor.h"

void Util_Cursor_DealEmptySplit(M_Cursor *cursor, const string code, const string word) {
    if (!cursor->is_split) {
        PFailed(cursor->file, cursor->line, ERR_UNDIFINDED_ERR);
        return;
    }
    char split = word[0];
    if (Char_IsEmptySymbolButNewLine(split)) {
        // ' ' '\t'
        ++cursor->index;
    } else if (split == KW_NEWLINE_R) {
        // '\r'
        if (code[cursor->index + 1] == KW_NEWLINE) {
            // '\r\n'
            ++cursor->index;
            ++cursor->line;
        }
    } else if (split == KW_NEWLINE) {
        // '\n'
        ++cursor->index;
        ++cursor->line;
    } else {
        // printf("err word:%s\r\n", word);
        // PFailed(cursor->file, cursor->line, ERR_UNDIFINDED_ERR);
    }
}