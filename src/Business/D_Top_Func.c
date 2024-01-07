#include "D_Top_Func.h"

void D_Top_Func_Enter(E_Doc *doc, const string access, bool is_static) {
    E_Doc_FSM_Func_Enter(doc, access, is_static);
}

void D_Top_Func_Process(E_Doc *doc, bool is_split, const string word, const string code, long size) {
    M_FSM_Func *fsm = &doc->fsm_func;
    M_FSM_Func_Process(fsm, doc->curFile, doc->curLine, is_split, word, code, size);
    if (fsm->is_done) {
        E_Doc_StaticFunc_Add(doc, fsm->function);
        D_Top_Guess_Enter(doc);
    }
}