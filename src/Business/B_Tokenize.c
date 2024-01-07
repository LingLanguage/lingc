#include "B_Tokenize.h"
#include "D_Import.h"
#include "D_Unknown.h"

void B_Tokenize_SeqMove(Context *ctx, string filename, string code, long size) {

    E_Doc *doc = ctx->doc;
    E_Doc_Reset(doc);

    doc->curLine = 1;
    doc->curFile = filename;

    const string imported[1000];
    int imported_count = 0;

    while (doc->endIndex < size) {

        TopBT topBT = doc->topBT;

        int startIndex = doc->startIndex;
        int endIndex = doc->endIndex;
        char c = code[doc->startIndex];
        bool isSplit = true;
        char validVar = Context_IsLetterOrUnderline(ctx, c);

        if (validVar != 0) {
            isSplit = false;
            // 非分隔符, 读取到分隔符为止, 作为一个单词
            for (int i = doc->startIndex + 1; i < size; i++) {
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
        doc->startIndex = startIndex;
        doc->endIndex = endIndex;
        if (!isSplit) {
            word = TextSubtext(code, startIndex, endIndex - startIndex);
            // PLog("word:%s\r\n", word);
        } else {
            endIndex = startIndex + 1;
            word = TextSubtext(code, startIndex, endIndex - startIndex);
            // PLog("split:%s\r\n", word);
        }
        if (topBT == TopBT_Unknown) {
            D_Unknown_Process(ctx, isSplit, word, code, size);
        } else if (topBT == TopBT_Import) {
            D_Import_Process(ctx, isSplit, word, code, size);
        }
        doc->startIndex = endIndex;
        doc->endIndex = endIndex;

        if (c == KW_NEWLINE) {
            doc->curLine++;
        }
    }
}