#include "D_Import.h"
#include "D_Unknown.h"

void D_Import_Enter(Context *ctx) {
    E_Cursor *cursor = ctx->cursor;
    E_Cursor_FSM_Import_Enter(cursor);
    PLogNA("D_Import_Enter\r\n");
}

void D_Import_Process(Context *ctx, bool isSplit, const string word, const string code, long size) {
    E_Cursor *cursor = ctx->cursor;
    M_FSM_Import *fsm = &cursor->fsm_import;
    int len = strlen(word);
    // PLog("word:%s %d\r\n", word, len);
    char split = word[len - 1];
    if (split == KW_QUOTE && fsm->leftIndex == 0 && fsm->importType == ImportType_None) {
        fsm->leftIndex = cursor->endIndex;
        fsm->importType = ImportType_Quote;
    } else if (split == KW_QUOTE && fsm->rightIndex == 0 && fsm->importType == ImportType_Quote) {
        fsm->rightIndex = cursor->endIndex;
        const string importName = TextSubtext(code, fsm->leftIndex + 1, fsm->rightIndex - fsm->leftIndex - 1);
        PLog("importName:\"%s\"\r\n", importName);
    }

    if (split == KW_LEFT_ANGLE_BRACKET && fsm->leftIndex == 0 && fsm->importType == ImportType_None) {
        fsm->leftIndex = cursor->endIndex;
        fsm->importType = ImportType_ANGLE_BRACKET;
    } else if (split == KW_RIGHT_ANGLE_BRACKET && fsm->rightIndex == 0 && fsm->importType == ImportType_ANGLE_BRACKET) {
        fsm->rightIndex = cursor->endIndex;
        const string importName = TextSubtext(code, fsm->leftIndex + 1, fsm->rightIndex - fsm->leftIndex - 1);
        PLog("importName:<%s>\r\n", importName);
    }

    if (split == KW_SEMICOLON && fsm->leftIndex != 0 && fsm->rightIndex != 0) {
        D_Unknown_Enter(ctx);
    }
}