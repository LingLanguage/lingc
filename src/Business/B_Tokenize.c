#include "B_Tokenize.h"

void Unknown_Enter(Context *ctx, string code, long size);
void Unknown_Process(Context *ctx, char c, string code, long size);
void Something_Enter(Context *ctx, string code, long size);
void Something_Process(Context *ctx, char c, string code, long size);
void Import_Enter(Context *ctx, string code, long size);
void Import_Process(Context *ctx, char c, string code, long size);
void Struct_Enter(Context *ctx, string code, long size);
void Struct_Process(Context *ctx, char c, string code, long size);

void B_Tokenize_SeqMove(Context *ctx, string code, long size) {
    // 1. Free Move, until not `KW_SPACE`
    E_Cursor *cursor = ctx->cursor;
    E_Cursor_Reset(cursor);
    const string imported[1000];
    int imported_count = 0;
    while (cursor->curIndex < size) {
        char c = code[cursor->curIndex];
        if (cursor->behaviourType == BehaviourType_Unknown) {
            Unknown_Process(ctx, c, code, size);
        } else if (cursor->behaviourType == BehaviourType_Something) {
            Something_Process(ctx, c, code, size);
        } else if (cursor->behaviourType == BehaviourType_Import) {
            Import_Process(ctx, c, code, size);
        } else if (cursor->behaviourType == BehaviourType_Struct) {
            Struct_Process(ctx, c, code, size);
        }
        if (c == KW_NEWLINE) {
            cursor->line++;
        }
        cursor->curIndex++;
    }
}

void Unknown_Enter(Context *ctx, string code, long size) {
    E_Cursor *cursor = ctx->cursor;
    cursor->behaviourType = BehaviourType_Unknown;
    cursor->lastIndex = cursor->curIndex;
    // PLogNA("enter unknown\r\n");
}

void Unknown_Process(Context *ctx, char c, string code, long size) {
    E_Cursor *cursor = ctx->cursor;
    if (c != KW_SPACE) {
        Something_Enter(ctx, code, size);
    }
}

void Something_Enter(Context *ctx, string code, long size) {
    E_Cursor *cursor = ctx->cursor;
    cursor->behaviourType = BehaviourType_Something;
    cursor->lastIndex = cursor->curIndex;
    // PLogNA("enter something\r\n");
}

void Something_Process(Context *ctx, char c, string code, long size) {
    E_Cursor *cursor = ctx->cursor;
    if (c == KW_SPACE) {
        if (cursor->lastIndex >= cursor->curIndex) {
            PLogNA("something error \r\n");
            return;
        }
        const string word = TextSubtext(code, cursor->lastIndex, cursor->curIndex - cursor->lastIndex);
        if (String_SameWhenTrimEnd(word, KW_IMPORT)) {
            Import_Enter(ctx, code, size);
        } else if (String_SameWhenTrimEnd(word, KW_STRUCT)) {
            Struct_Enter(ctx, code, size);
        } else if (String_IsAccess(word)) {
            PLog("access word: %s\r\n", word);
            TextCopy(cursor->access, word);
            // Unknown_Enter(ctx, code, size);
        } else {
            Unknown_Enter(ctx, code, size);
        }
    }
}

void Import_Enter(Context *ctx, string code, long size) {
    E_Cursor *cursor = ctx->cursor;
    cursor->behaviourType = BehaviourType_Import;
    cursor->lastIndex = cursor->curIndex;
    // PLogNA("enter import\r\n");
}

void Import_Process(Context *ctx, char c, string code, long size) {
    E_Cursor *cursor = ctx->cursor;
    if (c == KW_END) {
        const string word = TextSubtext(code, cursor->lastIndex + 1, cursor->curIndex - cursor->lastIndex);
        PLog("import:%s\r\n", word);
        Unknown_Enter(ctx, code, size);
    }
}

void Struct_Enter(Context *ctx, string code, long size) {
    E_Cursor *cursor = ctx->cursor;
    cursor->behaviourType = BehaviourType_Struct;
    cursor->lastIndex = cursor->curIndex;
    // PLogNA("enter struct\r\n");

    cursor->struct_isBegin = false;
    cursor->struct_nestedLevel = 0;
    E_Cursor_Struct_Unknow_Enter(cursor);

    E_Struct *st = &cursor->struct_current;
    memset(st, 0, sizeof(E_Struct));
    st->id = ctx->structs_idRecord++;
    strcpy(st->access, cursor->access);
}

void Struct_Process(Context *ctx, char c, string code, long size) {
    E_Cursor *cursor = ctx->cursor;
    E_Struct *st = &cursor->struct_current;
    if (!cursor->struct_isBegin) {
        if (c == KW_LEFT_BRACE) {
            const string word = TextSubtext(code, cursor->lastIndex, cursor->curIndex - cursor->lastIndex);
            strcpy(st->name, word);
            cursor->struct_isBegin = true;
            cursor->struct_nestedLevel = 1;
        }
    } else {
        StructBehaviourType status = cursor->struct_behaviourType;
        if (status == StructBehaviourType_Unknown) {
            if (c != KW_SPACE && c != KW_RIGHT_BRACE) {
                E_Cursor_Struct_Something_Enter(cursor);
            } else if (c == KW_RIGHT_BRACE) {
                cursor->struct_nestedLevel--;
                if (cursor->struct_nestedLevel == 0) {
                    PLog("struct end: %s\r\n", st->name);
                    Unknown_Enter(ctx, code, size);
                }
            }
        } else if (status == StructBehaviourType_Something) {
            if (c == KW_SPACE) {
                const string word = TextSubtext(code, cursor->struct_lastIndex, cursor->curIndex - cursor->struct_lastIndex);
                int word_len = strlen(word);
                if (word_len <= 1 || String_SameWhenTrimEnd(word, KW_SPACE_STR)) {
                    E_Cursor_Struct_Unknow_Enter(cursor);
                } else if (String_SameWhenTrimEnd(word, KW_FUNC)) {
                    E_Cursor_Struct_Function_Enter(cursor);
                    PLogNA("struct function");
                } else if (String_IsAccess(word)) {
                    TextCopy(cursor->access, word);
                    E_Cursor_Struct_AfterAccess_Enter(cursor);
                } else {
                    // PLog("field:%s\r\n", word);
                    if (word[word_len - 2] == KW_END) {
                        PLogNA("field end\r\n");
                    }
                    E_Cursor_SlideWord(cursor, word);
                    E_Cursor_Struct_Unknow_Enter(cursor);
                }
            }

        } else if (status == StructBehaviourType_AfterAccess) {
            // function: access fn varType,varType varName(varType varName,varType varName) {}
            // field: access varType varName;
            int tmpIndex = cursor->curIndex;
            int tmpLastIndex = cursor->curIndex;
            bool tmpIsVarType = false;
            while (tmpIndex < size) {
                char tmpC = code[tmpIndex];
                if (tmpC != KW_SPACE && !tmpIsVarType) {
                    tmpLastIndex = tmpIndex;
                    tmpIsVarType = true;
                } else if (tmpC == KW_SPACE && tmpIsVarType) {
                    const string word = TextSubtext(code, tmpLastIndex, tmpIndex - tmpLastIndex);
                }
                tmpIndex++;
            }
        } else if (status == StructBehaviourType_Field) {

        } else if (status == StructBehaviourType_Function) {
        }
        // Fields
        // Functions
    }
}