#include "B_Tokenize.h"
#include "D_DFA_Func.h"
#include "D_DFA_Import.h"
#include "D_DFA_Struct.h"
#include "D_NFA_Top.h"

void B_Tokenize_SeqMove(E_Doc *doc, const string filename, const string code, long size) {

    E_Doc_Init(doc, filename);

    M_NFA_Top *nfa_top = calloc(1, sizeof(M_NFA_Top));
    int index = 0;

    while (index < size) {

        NFA_Top_Status top_status = nfa_top->status;
        int line = doc->line;

        int start_index = index;
        int end_index = index;
        char c = code[index];
        bool isSplit = true;
        char validVar = Char_IsLetterOrNumberOrUnderline(c);

        const string word;
        if (validVar != 0) {
            isSplit = false;
            // 非分隔符, 读取到下个分隔符为止, 作为一个单词
            for (int i = start_index + 1; i < size; i++) {
                char tmp = code[i];
                char validVar = Char_IsLetterOrNumberOrUnderline(tmp);
                if (validVar == 0) {
                    end_index = i;
                    break;
                }
            }
            word = TextSubtext(code, start_index, end_index - start_index);
        } else {
            // 分隔符, 不读取, 直接跳过
            word = TextSubtext(code, start_index, 1);
        }

        if (top_status == NFA_Top_Status_Import) {
            M_DFA_Import *dfa_import = nfa_top->dfa_import;
            end_index = D_DFA_Import_Process(dfa_import, filename, line, isSplit, word, end_index, code, size);
            if (dfa_import->is_done) {
                E_Doc_Import_Add(doc, dfa_import->import);
                D_NFA_Top_Enter(nfa_top);
            }
        } else if (top_status == NFA_Top_Status_Struct) {
            M_DFA_Struct *dfa_struct = nfa_top->dfa_struct;
            end_index = D_DFA_Struct_Process(dfa_struct, filename, line, isSplit, word, end_index, code, size);
            if (dfa_struct->is_done) {
                E_Doc_Struct_Add(doc, dfa_struct->st);
                D_NFA_Top_Enter(nfa_top);
            }
        } else if (top_status == NFA_Top_Status_Func) {
            M_DFA_Func *fsm_func = nfa_top->dfa_func;
            end_index = D_DFA_Func_Process(fsm_func, filename, line, isSplit, word, end_index, code, size);
            if (fsm_func->is_done) {
                E_Doc_StaticFunc_Add(doc, fsm_func->function);
                D_NFA_Top_Enter(nfa_top);
            }
        } else if (top_status == NFA_Top_Status_Guess) {
            D_NFA_Top_Process(nfa_top, filename, line, isSplit, word, code, size);
        }

        if (!isSplit) {
            index = end_index;
        } else {
            index = end_index + 1;
        }

        if (c == KW_NEWLINE) {
            doc->line++;
        }
    }

    D_NFA_Top_Free(nfa_top);
}