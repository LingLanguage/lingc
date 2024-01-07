#include "D_Import.h"
#include "D_Unknown.h"
#include "import.h"

void D_Import_Enter(Context *ctx) {
    E_Doc *doc = ctx->doc;
    E_Doc_FSM_Import_Enter(doc);
    // PLogNA("D_Import_Enter\r\n");
}

void D_Import_Process(Context *ctx, bool isSplit, const string word, const string code, long size) {
    E_Doc *doc = ctx->doc;
    M_FSM_Import *fsm = &doc->fsm_import;
    int len = strlen(word);
    // PLog("word:%s %d\r\n", word, len);
    char split = word[len - 1];
    if (split == KW_QUOTE && fsm->leftIndex == 0 && fsm->importType == ImportType_None) {
        fsm->leftIndex = doc->endIndex;
        fsm->importType = ImportType_Quote;
    } else if (split == KW_QUOTE && fsm->rightIndex == 0 && fsm->importType == ImportType_Quote) {
        fsm->rightIndex = doc->endIndex;
    }

    if (split == KW_LEFT_ANGLE_BRACKET && fsm->leftIndex == 0 && fsm->importType == ImportType_None) {
        fsm->leftIndex = doc->endIndex;
        fsm->importType = ImportType_ANGLE_BRACKET;
    } else if (split == KW_RIGHT_ANGLE_BRACKET && fsm->rightIndex == 0 && fsm->importType == ImportType_ANGLE_BRACKET) {
        fsm->rightIndex = doc->endIndex;
    }

    if (split == KW_SEMICOLON && fsm->leftIndex != 0 && fsm->rightIndex != 0) {
        const string importName = TextSubtext(code, fsm->leftIndex + 1, fsm->rightIndex - fsm->leftIndex - 1);

        E_Import import = Factory_CreateImport(ctx, importName, fsm->importType);
        E_Doc_Import_Add(doc, import);
        PLog("importName:%s\r\n", importName);

        D_Unknown_Enter(ctx);
    }
}