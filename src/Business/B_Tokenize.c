#include "B_Tokenize.h"
#include "D_Top_Access.h"
#include "D_Top_Func.h"
#include "D_Top_Import.h"
#include "D_Top_Struct.h"
#include "D_Top_Guess.h"

void B_Tokenize_SeqMove(E_Doc *doc, const string filename, const string code, long size) {

    E_Doc_Init(doc, filename);

    const string imported[1000];
    int imported_count = 0;

    while (doc->endIndex < size) {

        TopFSMStatus top_status = doc->top_status;

        int startIndex = doc->startIndex;
        int endIndex = doc->startIndex;
        char c = code[doc->startIndex];
        bool isSplit = true;
        char validVar = Char_IsLetterOrUnderline(c);

        const string word;
        if (validVar != 0) {
            isSplit = false;
            // 非分隔符, 读取到下个分隔符为止, 作为一个单词
            for (int i = doc->startIndex + 1; i < size; i++) {
                char tmp = code[i];
                char validVar = Char_IsLetterOrNumberOrUnderline(tmp);
                if (validVar == 0) {
                    endIndex = i;
                    break;
                }
            }
            word = TextSubtext(code, startIndex, endIndex - startIndex);
        } else {
            // 分隔符, 不读取, 直接跳过
            word = TextSubtext(code, startIndex, 1);
        }

        doc->endIndex = endIndex;

        if (top_status == TopFSMStatus_Struct) {
            D_Top_Struct_Process(doc, isSplit, word, code, size);
        } else if (top_status == TopFSMStatus_Access) {
            D_Top_Access_Process(doc, isSplit, word, code, size);
        } else if (top_status == TopFSMStatus_Import) {
            D_Top_Import_Process(doc, isSplit, word, code, size);
        } else if (top_status == TopFSMStatus_Func) {
            D_Top_Func_Process(doc, isSplit, word, code, size);
        } else if (top_status == TopFSMStatus_Guess) {
            D_Top_Guess_Process(doc, isSplit, word, code, size);
        }

        if (!isSplit) {
            doc->startIndex = endIndex;
        } else {
            doc->startIndex = endIndex + 1;
        }

        if (c == KW_NEWLINE) {
            doc->curLine++;
        }
    }
}