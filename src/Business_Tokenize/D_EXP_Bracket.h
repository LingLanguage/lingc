#ifndef D_NFA_EXPRESSION_H__
#define D_NFA_EXPRESSION_H__

#include "CTX_Tokenize.h"
#include "import.h"

void D_EXP_Bracket_Enter(CTX_Tokenize *ctx, FAM_EXP *fam_exp);
void D_EXP_Bracket_Process(CTX_Tokenize *ctx, FAM_EXP *fam_exp, const string code, const string word, M_Cursor *cursor);

#endif