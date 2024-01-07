#include "D_Top_Struct.h"
#include "D_Top_Guess.h"

void Field_End(string file, int line, M_FSM_Struct *fsm) {
    // field
    E_Struct *st = &fsm->st;
    if (fsm->guess_words_count == 2) {
        E_Field field = Factory_CreateField(fsm->guess_access, fsm->guess_words[0], fsm->guess_words[1]);
        PLog("field: %s %s %s\r\n", field.access, field.type, field.name);
        E_Struct_RecordField(st, field);
        M_FSM_Struct_EnterGuess(fsm);
    } else {
        PLogCode(file, line, ERR_VAR_CANNOT_START_WITH_NUMBER);
    }
}

void D_Top_Struct_Enter(Context *ctx, const string access, bool is_static) {
    E_Doc *doc = ctx->doc;
    E_Doc_FSM_Struct_Enter(doc, access, is_static);
}

void D_Top_Struct_Process(Context *ctx, bool isSplit, const string word, const string code, long size) {
    E_Doc *doc = ctx->doc;
    M_FSM_Struct *fsm = &doc->fsm_struct;
    E_Struct *st = &fsm->st;
    StructPhase phase = fsm->phase;
    if (phase == StructPhase_Name) {
        // {
        if (isSplit && word[0] == KW_LEFT_BRACE) {
            fsm->phase = StructPhase_Guess;
            fsm->nested_level += 1;
            PLog("struct: %s struct %s\r\n", st->access, st->name);
        } else if (!isSplit) {
            if (strlen(st->name) > 0) {
                PLogCode(doc->curFile, doc->curLine, ERR_REDIFINED_STRUCT_NAME);
            } else {
                strcpy(st->name, word);
            }
        }
    } else if (phase == StructPhase_Guess) {
        if (!isSplit) {
            if (Context_IsAccess(ctx, word)) {
                // set access
                strcpy(fsm->guess_access, word);
                fsm->phase = StructPhase_Access;
            } else if (strcmp(word, KW_FUNC) == 0) {
                fsm->phase = StructPhase_Func;
                M_FSM_Func_Enter(&fsm->fsm_func, KW_ACCESS_PRIVATE, false);
            } else {
                // push word
                strcpy(fsm->guess_words[fsm->guess_words_count], word);
                fsm->guess_words_count += 1;
            }
        } else {
            if (word[0] == KW_SEMICOLON) {
                Field_End(doc->curFile, doc->curLine, fsm);
            } else if (word[0] == KW_RIGHT_BRACE) {
                fsm->nested_level -= 1;
                if (fsm->nested_level == 0) {
                    D_Top_Guess_Enter(ctx);
                }
            }
        }
    } else if (phase == StructPhase_Access) {
        if (!isSplit) {
            if (Context_IsAccess(ctx, word)) {
                PLogCode(doc->curFile, doc->curLine, ERR_REDIFINED_ACCESS);
            } else if (strcmp(word, KW_FUNC) == 0) {
                // fn
                fsm->phase = StructPhase_Func;
                M_FSM_Func_Enter(&fsm->fsm_func, fsm->guess_access, false);
            } else {
                // push word
                if (fsm->guess_words_count > RULE_FUNCTION_RETURN_COUNT) {
                    PLogCode(doc->curFile, doc->curLine, ERR_TOO_MANY_WORDS);
                } else {
                    strcpy(fsm->guess_words[fsm->guess_words_count], word);
                    fsm->guess_words_count += 1;
                }
            }
        } else {
            if (word[0] == KW_SEMICOLON) {
                // ; field end
                Field_End(doc->curFile, doc->curLine, fsm);
            } else if (word[0] == KW_RIGHT_BRACE) {
                PLogCode(doc->curFile, doc->curLine, ERR_FUNC_OR_FIELD_NOT_END);
            }
        }
    } else if (phase == StructPhase_Func) {
        M_FSM_Func *fsm_func = &fsm->fsm_func;
        M_FSM_Func_Process(fsm_func, doc->curFile, doc->curLine, isSplit, word, code, size);
        if (fsm_func->is_done) {
            PLogNA("STRUCT FUNC DONE\r\n");
        }
    }
}