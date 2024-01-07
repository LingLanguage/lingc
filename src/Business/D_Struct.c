#include "D_Struct.h"

void D_Struct_Enter(Context *ctx, const string access, bool is_static) {
    E_Doc *doc = ctx->doc;
    E_Doc_FSM_Struct_Enter(doc, access, is_static);
}

void D_Struct_Process(Context *ctx, bool isSplit, const string word, const string code, long size) {
    E_Doc *doc = ctx->doc;
    M_FSM_Struct *fsm = &doc->fsm_struct;
    StructPhase phase = fsm->phase;
    E_Struct *st = &fsm->st;
    if (phase == StructPhase_Name) {
        // {
        if (isSplit && word[0] == KW_LEFT_BRACE) {
            fsm->phase = StructPhase_Guess;
            PLog("%s struct %s\r\n", st->access, st->name);
        } else if (!isSplit) {
            strcpy(st->name, word);
        }
    } else if (phase == StructPhase_Guess) {
        
    }
}