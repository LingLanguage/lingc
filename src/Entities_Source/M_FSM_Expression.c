#include "M_FSM_Expression.h"

void M_FSM_Expression_Enter(M_FSM_Expression *fsm) {
    memset(fsm, 0, sizeof(M_FSM_Expression));
}

void StatementAssign_Enter(M_FSM_Expression *fsm, int nested_level, const string file, int line, int index, const string code);
int StatementAssign_Process(M_FSM_Expression *fsm, int nested_level, const string file, int line, bool is_split, const string word, int index,
                            const string code, long size);

int Guess_Process(M_FSM_Expression *fsm, int nested_level, const string file, int line, bool is_split, const string word, int index, const string code,
                  long size) {
    if (is_split) {
        char split = word[0];
        if (split == OP_EQUAL) {
            // =
            // eg: a =
            // eg: i32 a =
            // eg: i32 a +=
            // eg: i32 a >>=
            StatementAssign_Enter(fsm, nested_level, file, line, index, code);
        } else if (split == KW_SEMICOLON) {
            // ;
            // eg: i32 a;
            // statement end, no expression;
            bool is_ok = E_Guess_GuessStatement(&fsm->guess, file, line, nested_level, NULL, 0, &fsm->statement);
            if (is_ok) {
                fsm->is_done = true;
            }
        } else if (split == KW_DOT) {
            // .
            E_Guess_PushWord(&fsm->guess, file, line, word);
        } else if ((split == KW_LEFT_BRACKET) || (split == KW_RIGHT_BRACKET)) {
            // (
            PLog("push word:%s line:%d\r\n ", word, line);
            E_Guess_PushWord(&fsm->guess, file, line, word);
        } else {
            if (Char_IsEmptySymbol(split)) {
                // ' ' '\n' '\r' '\t'
                return index;
            }
            PLogNA("TODO: string constant\r\n");
            // err: unexpected
            PLog("err word:%s\r\n", word);
            PFailed(file, line, ERR_UNDIFINDED_ERR);
        }
    } else {
        if (strcmp(word, KW_RETURN) == 0) {
            // return
            if (fsm->guess.words_count > 0) {
                PFailed(file, line, ERR_FUNCTION_RETURN_MUST_FIRST);
            }
        }
        E_Guess_PushWord(&fsm->guess, file, line, word);
    }
}

void StatementAssign_Enter(M_FSM_Expression *fsm, int nested_level, const string file, int line, int index, const string code) {
    char op_assigns[3] = {0};
    int op_count = String_OP_Assign(file, line, index, code, op_assigns);
    bool is_ok = E_Guess_GuessStatement(&fsm->guess, file, line, nested_level, op_assigns, op_count, &fsm->statement);
    if (is_ok) {
        fsm->statement.statementType = StatementType_LeftRight;
        fsm->statement.operator= M_Operator_Create(op_assigns, OperatorType_Assign);
        fsm->phase = ExpressionPhase_Statement_Assign;
    }
}

int StatementAssign_Process(M_FSM_Expression *fsm, int nested_level, const string file, int line, bool is_split, const string word, int index,
                            const string code, long size) {
    // after =
    if (is_split) {
        char split = word[0];
        char op[2] = {0};
        int op_count = String_OP_Calc(split, file, line, index, code, op);
        if (op_count > 0) {
            index += op_count - 1;
            // operator: + - * / % & | ^ << >> && || == != >= <= > <
            E_Guess_PushWord(&fsm->guess, file, line, op);
        } else if (split == KW_DOT || split == KW_COMMA) {
            // . ,
            E_Guess_PushWord(&fsm->guess, file, line, word);
        } else if (split == KW_SEMICOLON) {
            // ;
            // eg: i32 a = 1;
            // expression end
            for (int i = 0; i < fsm->guess.words_count; i++) {
                E_Statement_AddExpressionOrigin(&fsm->statement, fsm->guess.words[i]);
            }
            fsm->statement.statementType = StatementType_OnlyLeft;
            fsm->is_done = true;
        } else if (split == KW_QUOTE) {
            // "
            index = M_FSM_ConstString_Process(&fsm->fsm_string, nested_level, file, line, is_split, word, index, code, size);
            if (fsm->fsm_string.is_done) {
                const string str = String_SubString(code, fsm->fsm_string.start_index, fsm->fsm_string.end_index - fsm->fsm_string.start_index + 1);
                E_Guess_PushWord(&fsm->guess, file, line, str);
            }
        } else {
            if (Char_IsEmptySymbol(split)) {
                // ' ' '\n' '\r' '\t'
                return index;
            }
            // err: unexpected
            PLog("err word:%s\r\n", word);
            PFailed(file, line, ERR_UNDIFINDED_ERR);
        }
    } else {
        // PLog("push word:%s\r\n", word);
        E_Guess_PushWord(&fsm->guess, file, line, word);
    }
}

int M_FSM_Expression_Process(M_FSM_Expression *fsm, int nested_level, const string file, int line, bool is_split, const string word, int index,
                             const string code, long size) {
    ExpressionPhase phase = fsm->phase;

    if (phase == ExpressionPhase_Guess) {
        index = Guess_Process(fsm, nested_level, file, line, is_split, word, index, code, size);
    } else if (phase == ExpressionPhase_Statement_Assign) {
        index = StatementAssign_Process(fsm, nested_level, file, line, is_split, word, index, code, size);
    } else {
        PLogNA("Unknown Phase\r\n");
    }
    return index;
}