#include "B_Tokenize.h"
#include "D_Func.h"
#include "D_Import.h"
#include "D_Struct.h"
#include "D_TopLevel.h"

void B_Tokenize_SeqMove(CTX_Tokenize *ctx, E_Doc *doc, const string filename, const string code, long size) {

    E_Doc_Init(doc, filename);

    FAM_Top *fam = calloc(1, sizeof(FAM_Top));
    FAM_Top_Init(fam);

    M_Cursor cursor = (M_Cursor){0};
    strcpy(cursor.file, filename);
    cursor.index = 0;
    cursor.line = 1;
    cursor.nested = 0;
    cursor.code_size = size;

    while (cursor.index < size) {

        Top_FA top_status = fam->status;
        int line = doc->line;

        int last_index = cursor.index;
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
            D_TopLevel_Process(ctx, fam, code, word, &cursor);
        } else if (top_status == Top_FA_Import) {
            FAM_Import *fam_import = fam->fam_import;
            D_Import_Process(ctx, fam_import, code, word, &cursor);
            if (fam_import->is_done) {
                E_Doc_Import_Add(doc, fam_import->import_id);
                D_TopLevel_Enter(fam, &cursor);
            }
        } else if (top_status == Top_FA_Struct) {
            // FAM_Struct *dfa_struct = fam->dfa_struct;
            // end_index = D_Struct_Process(dfa_struct, filename, line, isSplit, word, end_index, code, size);
            // if (dfa_struct->is_done) {
            //     E_Doc_Struct_Add(doc, dfa_struct->st);
            //     D_TopLevel_Enter(fam);
            // }
        } else if (top_status == Top_FA_Func) {
            FAM_Func *dfa_func = fam->dfa_func;
            D_Func_Process(dfa_func, code, word, &cursor);
            if (dfa_func->is_done) {
                E_Doc_StaticFunc_Add(doc, dfa_func->function);
                D_TopLevel_Enter(fam, &cursor);
                PLogNA("FUNC DONE\r\n");
            }
        }

        if (c == KW_NEWLINE) {
            doc->line++;
        }

        printf("%s", String_SubString(code, last_index, cursor.index - last_index));
    }

    D_TopLevel_Free(fam);
}