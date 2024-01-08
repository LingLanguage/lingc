#include "M_FSM_Expression.h"

void M_FSM_Expression_Enter(M_FSM_Expression *fsm) {
    memset(fsm, 0, sizeof(M_FSM_Expression));
}

int M_FSM_Expression_Process(M_FSM_Expression *fsm, int nested_level, string file, int line, bool is_split, const string word, int index, const string code,
                             long size) {
    ExpressionPhase phase = fsm->phase;

    if (is_split && Char_IsEmptySymbol(word[0])) {
        // ' ' '\n' '\r' '\t'
        return index;
    }

    if (phase == ExpressionPhase_Statement) {
        if (is_split) {
            if (word[0] == OP_EQUAL) {
                // =
                // eg: a =
                // eg: i32 a =
                // eg: i32 a +=
                // eg: i32 a >>=
                char op_assigns[3] = {0};
                int op_count = String_OP_Assign(file, line, index, code, op_assigns);
                bool is_ok = E_Guess_Statement(&fsm->guess, file, line, nested_level, op_assigns, op_count, &fsm->statement);
                if (is_ok) {
                    fsm->statement.operator= M_Operator_Create(op_assigns, OperatorType_Assign);
                    fsm->phase = ExpressionPhase_Expression;
                }
            } else if (word[0] == KW_SEMICOLON) {
                // ;
                // eg: i32 a;
                // statement end, no expression;
                bool is_ok = E_Guess_Statement(&fsm->guess, file, line, nested_level, NULL, 0, &fsm->statement);
                if (is_ok) {
                    fsm->is_done = true;
                }
            }
        } else {
            if (strcmp(word, KW_RETURN) == 0) {
                // return
                PLogNA("TODO: return\r\n");
            } else {
                E_Guess_PushWord(&fsm->guess, file, line, word);
            }
        }
    } else if (phase == ExpressionPhase_Expression) {
        if (is_split) {
            char op[2] = {0};
            int op_count = String_OP_Calc(word[0], file, line, index, code, op);
            if (op_count > 0) {
                index += op_count - 1;
                // operator: + - * / % & | ^ << >> && || == != >= <= > <
                E_Guess_PushWord(&fsm->guess, file, line, op);
            } else if (word[0] == KW_SEMICOLON) {
                // ;
                // eg: i32 a = 1;
                // expression end
                PLogNA("TODO: EXpression\r\n");
                // E_Guess_Log(&fsm->guess);
                fsm->is_done = true;
            } else {
                // err: unexpected
                PLog("err word:%s\r\n", word);
                PFailed(file, line, ERR_UNDIFINDED_ERR);
            }
        } else {
            // PLog("push word:%s\r\n", word);
            E_Guess_PushWord(&fsm->guess, file, line, word);
        }
    }
    return index;
}