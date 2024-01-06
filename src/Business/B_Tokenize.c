#include "B_Tokenize.h"
#include "D_Import.h"
#include "D_Unknown.h"

void B_Tokenize_SeqMove(Context *ctx, string code, long size) {

    E_Cursor *cursor = ctx->cursor;
    E_Cursor_Reset(cursor);

    const string imported[1000];
    int imported_count = 0;

    while (cursor->endIndex < size) {

        BehaviourType behaviourType = cursor->behaviourType;

        int startIndex = cursor->startIndex;
        int endIndex = cursor->endIndex;
        char c = code[cursor->startIndex];
        bool isSplit = true;
        char validVar = Context_IsLetterOrUnderline(ctx, c);
        if (validVar != 0) {
            isSplit = false;
            // 非分隔符, 读取到分隔符为止, 作为一个单词
            for (int i = cursor->startIndex + 1; i < size; i++) {
                char tmp = code[i];
                char validVar = Context_IsLetterOrNumberOrUnderline(ctx, tmp);
                if (validVar == 0) {
                    endIndex = i;
                    break;
                }
            }
        } else {
            // 分隔符, 不读取, 直接跳过
        }

        const string word;
        cursor->startIndex = startIndex;
        cursor->endIndex = endIndex;
        if (!isSplit) {
            word = TextSubtext(code, startIndex, endIndex - startIndex);
            PLog("word:%s\r\n", word);
        } else {
            endIndex = startIndex + 1;
            word = TextSubtext(code, startIndex, endIndex - startIndex);
        }
        // PLog("startIndex:%d endIndex:%d\r\n", startIndex, endIndex);
        // PLog("word:%s\r\n", word);
        // PLog("split:%c\r\n", split);
        if (behaviourType == BehaviourType_Unknown) {
            D_Unknown_Process(ctx, isSplit, word, code, size);
        } else if (behaviourType == BehaviourType_Import) {
            D_Import_Process(ctx, isSplit, word, code, size);
        }
        cursor->startIndex = endIndex;
        cursor->endIndex = endIndex;
    }
}