#ifndef M_FSM_EXPRESSION_H__
#define M_FSM_EXPRESSION_H__

#include "E_Expression.h"
#include "E_Guess.h"
#include "E_Statement.h"
#include "M_Operator.h"
#include "import.h"

// left: statement
// middle: operator
// right: expression
typedef struct M_FSM_Expression {
    ExpressionPhase phase;
    E_Statement statement;
    M_Operator operator;
    E_Expression expression;
    E_Guess guess;
} M_FSM_Expression;

void M_FSM_Expression_Enter(M_FSM_Expression *fsm, const string access, bool is_static);
int M_FSM_Expression_Process(M_FSM_Expression *fsm, int nested_level, string file, int line, bool is_split, const string word, int index, const string code,
                             long size);
#endif