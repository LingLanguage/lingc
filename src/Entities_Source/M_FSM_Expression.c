#include "M_FSM_Expression.h"

void M_FSM_Expression_Enter(M_FSM_Expression *fsm, const string access, bool is_static) {
    memset(fsm, 0, sizeof(M_FSM_Expression));
}

int M_FSM_Expression_Process(M_FSM_Expression *fsm, int nested_level, string file, int line, bool is_split, const string word, int index, const string code,
                             long size) {
    ExpressionPhase phase = fsm->phase;
    if (phase == ExpressionPhase_Statement) {
        if (is_split) {
            if (word[0] == OP_EQUAL) {
                // =
                char op_sets[3] = {0};
                int op_count = String_OP_Assign(file, line, index, code, op_sets);
                bool is_ok = E_Guess_Statement(&fsm->guess, file, line, nested_level, &fsm->statement);
                if (is_ok) {
                    fsm->statement.operator= M_Operator_Create(op_sets, OperatorType_Assign);
                    // E_Function_AddStatement(&fsm->function, statement);
                    fsm->phase = ExpressionPhase_Expression;
                }
            } else if (word[0] == KW_SEMICOLON) {
                // ;
            }
        } else {
            E_Guess_PushWord(&fsm->guess, file, line, word);
        }
    }
    return index;
}