#ifndef E_CURSOR_H__
#define E_CURSOR_H__

#include "E_Import.h"
#include "E_Struct.h"
#include "E_StaticVar.h"
#include "M_FSM_Access.h"
#include "M_FSM_Func.h"
#include "M_FSM_Import.h"
#include "M_FSM_Struct.h"
#include "M_FSM_Guess.h"
#include "import.h"

typedef struct E_Doc {

    string curFile;
    int curLine;

    int startIndex;
    int endIndex;

    E_Import *imports;
    byte imports_count;

    E_Struct *structs;
    byte structs_count;

    E_Function *static_funcs;
    byte static_funcs_count;

    E_StaticVar *static_vars;
    byte static_vars_count;

    // ==== Temp ====
    TopFSMStatus top_status;
    M_FSM_Guess fsm_guess;
    M_FSM_Import fsm_import;
    M_FSM_Access fsm_access;
    M_FSM_Func fsm_func;
    M_FSM_Struct fsm_struct;

} E_Doc;

void E_Doc_Reset(E_Doc *doc);
void E_Doc_Import_Add(E_Doc *doc, E_Import import);
void E_Doc_FSM_Guess_Enter(E_Doc *doc);
void E_Doc_FSM_Import_Enter(E_Doc *doc);
void E_Doc_FSM_Access_Enter(E_Doc *doc, const string access);
void E_Doc_FSM_Struct_Enter(E_Doc *doc, const string access, bool is_static);
void E_Doc_FSM_Func_Enter(E_Doc *doc, const string access, bool is_static);

#endif