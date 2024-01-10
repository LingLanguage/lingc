#include "D_DFA_Block.h"
#include "D_NFA_Statement.h"
#include "Util_Cursor.h"

void D_DFA_Block_Enter(M_DFA_Block *dfa_block);
void Guess_Process(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor);

void D_DFA_Block_Enter(M_DFA_Block *dfa_block) {
    M_DFA_Block_Init(dfa_block);
}

void Guess_Process(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor) {
    bool is_split = cursor->is_split;
    if (is_split) {
        char split = word[0];
        if (split == KW_EQUAL) {
            // =
            PLogNA("TODO: DFA Block Process: =\r\n");
            ++cursor->index;
        } else if (split == KW_SEMICOLON) {
            // ;
            PLogNA("TODO: DFA Block Process: ;\r\n");
            ++cursor->index;
        } else if (split == KW_RIGHT_BRACE) {
            // }
            PLogNA("TODO: DFA Block Process: }\r\n");
            ++cursor->index;
        } else if (split == KW_LEFT_BRACE) {
            // {
            PLogNA("TODO: DFA Block Process: {\r\n");
            ++cursor->index;
        } else if (split == KW_LEFT_BRACKET) {
            // (
            PLogNA("TODO: DFA Block Process: (\r\n");
            ++cursor->index;
        } else if (split == KW_RIGHT_BRACKET) {
            // )
            PLogNA("TODO: DFA Block Process: )\r\n");
            ++cursor->index;
        } else if (split == KW_COMMA) {
            // ,
            PLogNA("TODO: DFA Block Process: ,\r\n");
            ++cursor->index;
        } else {
            Util_Cursor_DealEmpty(cursor, code, word);
        }
    } else {
        if (strcmp(word, KW_RETURN) == 0) {
            // return
            D_NFA_Statement_EnterReturnSTMT(&dfa_block->nfa_stmt);
        } else if (strcmp(word, KW_IF) == 0) {
            // if
        } else if (strcmp(word, KW_WHILE) == 0) {
            // while
        } else if (strcmp(word, KW_FOR) == 0) {
            // for
        } else {
        }
    }
}

void D_DFA_Block_Process(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor) {
    DFA_Block_Status status = dfa_block->status;
    if (status == DFA_Block_Status_Guess) {
        Guess_Process(dfa_block, code, word, cursor);
    } else if (status == DFA_Block_Status_Statement) {
        D_NFA_Statement_Process(&dfa_block->nfa_stmt, code, word, cursor);
    }
}