#include "B_Tokenize.h"
#include "D_DFA_Func.h"
#include "D_DFA_Import.h"
#include "D_DFA_Struct.h"
#include "D_NFA_Top.h"

void B_Tokenize_SeqMove(E_Doc *doc, const string filename, const string code, long size) {

    E_Doc_Init(doc, filename);

    FAM_Top *nfa_top = calloc(1, sizeof(FAM_Top));
    FAM_Top_Init(nfa_top);

    M_Cursor cursor = (M_Cursor){0};
    strcpy(cursor.file, filename);
    cursor.index = 0;
    cursor.line = 1;
    cursor.code_size = size;

    while (cursor.index < size) {

        Top_FA top_status = nfa_top->status;
        int line = doc->line;

        int start_index = cursor.index;
        int end_index = cursor.index;
        char c = code[cursor.index];
        cursor.is_split = true;
        char validVar = Char_IsLetterOrNumberOrUnderline(c);

        // ==== Word ====
        const string word;
        if (validVar != 0) {
            cursor.is_split = false;
            // 非分隔符, 读取到下个分隔符为止, 作为一个单词
            for (int i = start_index + 1; i < size; i++) {
                char tmp = code[i];
                char validVar = Char_IsLetterOrNumberOrUnderline(tmp);
                if (validVar == 0) {
                    end_index = i;
                    break;
                }
            }
            word = String_SubString(code, start_index, end_index - start_index);
        } else {
            // 分隔符, 不读取, 直接跳过
            word = String_SubString(code, start_index, 1);
        }

        cursor.index = end_index;

        if (top_status == Top_FA_Guess) {
            D_NFA_Top_Process(nfa_top, code, word, &cursor);
        } else if (top_status == Top_FA_Import) {
            FAM_Import *dfa_import = nfa_top->dfa_import;
            D_DFA_Import_Process(dfa_import, code, word, &cursor);
            if (dfa_import->is_done) {
                E_Doc_Import_Add(doc, dfa_import->import);
                D_NFA_Top_Enter(nfa_top);
            }
        } else if (top_status == Top_FA_Struct) {
            // FAM_Struct *dfa_struct = nfa_top->dfa_struct;
            // end_index = D_DFA_Struct_Process(dfa_struct, filename, line, isSplit, word, end_index, code, size);
            // if (dfa_struct->is_done) {
            //     E_Doc_Struct_Add(doc, dfa_struct->st);
            //     D_NFA_Top_Enter(nfa_top);
            // }
        } else if (top_status == Top_FA_Func) {
            FAM_Func *dfa_func = nfa_top->dfa_func;
            D_DFA_Func_Process(dfa_func, code, word, &cursor);
            if (dfa_func->is_done) {
                E_Doc_StaticFunc_Add(doc, dfa_func->function);
                D_NFA_Top_Enter(nfa_top);
            }
        }

        if (c == KW_NEWLINE) {
            doc->line++;
        }
    }

    D_NFA_Top_Free(nfa_top);
}