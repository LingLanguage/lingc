#ifndef D_NFA_EXPRESSION_H__
#define D_NFA_EXPRESSION_H__

#include "import.h"

void D_EXP_Bracket_EnterBracket(M_EXP *fam_exp);
void D_EXP_Bracket_Process(M_EXP *fam_exp, const string code, const string word, M_Cursor *cursor);

#endif