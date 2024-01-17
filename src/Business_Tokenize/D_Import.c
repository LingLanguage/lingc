#include "D_Import.h"
#include "D_TopLevel.h"
#include "Util_Cursor.h"
#include "import.h"

E_Import *D_Import_Spawn(CTX_Tokenize *ctx) {
    E_Import *e = calloc(1, sizeof(E_Import));
    e->id = ctx->import_id++;
    RP_Import_Add(ctx->rp_import, e->id, e);
    return e;
}

void D_Import_Set(CTX_Tokenize *ctx, int id, const string import_name, ImportType import_type) {
    E_Import *e;
    if (RP_Import_TryGet(ctx->rp_import, id, &e)) {
        strcpy(e->name, import_name);
        e->import_type = import_type;
    } else {
        PLog("err import id:%d\r\n", id);
        PFailed(__FILE__, __LINE__, ERR_UNDIFINDED_ERR);
    }
}

void D_Import_Enter(CTX_Tokenize *ctx, FAM_Import *fsm) {
    memset(fsm, 0, sizeof(FAM_Import));
    E_Import *e = D_Import_Spawn(ctx);
    fsm->import_id = e->id;
}

void D_Import_Process(CTX_Tokenize *ctx, FAM_Import *fsm, const string code, const string word, M_Cursor *cursor) {

    if (cursor->is_split) {
        char split = word[0];
        if (split == KW_QUOTE) {
            // "
            int right_index = String_CutBetweenSameChars(cursor->index, code, cursor->code_size, KW_QUOTE);
            if (right_index != -1) {
                const string value = String_SubString(code, cursor->index + 1, right_index - cursor->index - 1); // 去掉两边的引号
                D_Import_Set(ctx, fsm->import_id, value, ImportType_Quote);
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
                D_Import_Set(ctx, fsm->import_id, value, ImportType_ANGLE_BRACKET);
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
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    } else {
        PFailed(cursor->file, cursor->line, ERR_UNDIFINDED_ERR);
    }
}