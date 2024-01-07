#ifndef E_DOC_H__
#define E_DOC_H__

#include "E_Import.h"
#include "E_Struct.h"
#include "M_FSM_Access.h"
#include "M_FSM_Func.h"
#include "M_FSM_Import.h"
#include "M_FSM_Struct.h"
#include "M_FSM_Guess.h"
#include "import.h"

// 单份代码文件解析
typedef struct E_Doc {

    char curFile[FILENAME_MAX * 2];
    int curLine;

    int startIndex;
    int endIndex;

    E_Import *imports;
    byte imports_count;

    E_Struct *structs;
    byte structs_count;

    E_Function *static_funcs;
    byte static_funcs_count;

    E_Field *static_vars;
    byte static_vars_count;

    // ==== Temp ====
    TopFSMStatus top_status;
    M_FSM_Guess fsm_guess;
    M_FSM_Import fsm_import;
    M_FSM_Access fsm_access;
    M_FSM_Func fsm_func;
    M_FSM_Struct fsm_struct;

} E_Doc;

void E_Doc_Free(E_Doc *doc);
void E_Doc_Init(E_Doc *doc, const string file);
void E_Doc_Import_Add(E_Doc *doc, E_Import import);
void E_Doc_Struct_Add(E_Doc *doc, E_Struct st);
void E_Doc_StaticVar_Add(E_Doc *doc, E_Field var);
void E_Doc_StaticFunc_Add(E_Doc *doc, E_Function func);
void E_Doc_FSM_Guess_Enter(E_Doc *doc);
void E_Doc_FSM_Import_Enter(E_Doc *doc);
void E_Doc_FSM_Access_Enter(E_Doc *doc, const string access);
void E_Doc_FSM_Struct_Enter(E_Doc *doc, const string access, bool is_static);
void E_Doc_FSM_Func_Enter(E_Doc *doc, const string access, bool is_static);
void E_Doc_Log(E_Doc *doc);

#endif