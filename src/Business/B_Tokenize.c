#include "B_Tokenize.h"
#include "D_DFA_Func.h"
#include "D_NFA_Top.h"
#include "D_Top_Import.h"
#include "D_Top_Struct.h"

void B_Tokenize_SeqMove(E_Doc *doc, const string filename, const string code, long size) {

    E_Doc_Init(doc, filename);

    const string imported[1000];
    int imported_count = 0;

    while (doc->endIndex < size) {

        TopFSMStatus top_status = doc->top_status;
        int line = doc->curLine;

        int startIndex = doc->startIndex;
        int endIndex = doc->startIndex;
        char c = code[doc->startIndex];
        bool isSplit = true;
        char validVar = Char_IsLetterOrNumberOrUnderline(c);

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
            M_FSM_Struct *fsm_struct = &doc->fsm_struct;
            endIndex = D_Top_Struct_Process(fsm_struct, filename, line, isSplit, word, endIndex, code, size);
            if (doc->fsm_struct.is_done) {
                E_Doc_Struct_Add(doc, fsm_struct->st);
                D_NFA_Top_Enter(doc);
            }
        } else if (top_status == TopFSMStatus_Import) {
            M_FSM_Import *fsm_import = &doc->fsm_import;
            endIndex = D_Top_Import_Process(fsm_import, filename, line, isSplit, word, endIndex, code, size);
            if (fsm_import->is_done) {
                E_Doc_Import_Add(doc, fsm_import->import);
                D_NFA_Top_Enter(doc);
            }
        } else if (top_status == TopFSMStatus_Func) {
            M_FSM_Func *fsm_func = &doc->fsm_func;
            endIndex = D_DFA_Func_Process(fsm_func, filename, line, isSplit, word, endIndex, code, size);
            if (fsm_func->is_done) {
                E_Doc_StaticFunc_Add(doc, fsm_func->function);
                D_NFA_Top_Enter(doc);
            }
        } else if (top_status == TopFSMStatus_Guess) {
            D_NFA_Top_Process(doc, isSplit, word, code, size);
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