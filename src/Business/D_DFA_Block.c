#include "D_DFA_Block.h"
#include "D_NFA_Statement.h"
#include "Util_Cursor.h"

void D_DFA_Block_Enter(M_DFA_Block *dfa_block);
void D_DFA_Block_Process(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor);
void D_DFA_Block_Guess_Enter(M_DFA_Block *dfa_block);
void D_DFA_Block_Guess_Process(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor);
void D_DFA_Block_Statement_Enter(M_DFA_Block *dfa_block);
void D_DFA_Block_Statement_Process(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor);
void D_DFA_Block_ChildBlock_Enter(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor);
void D_DFA_Block_ChildBlock_Process(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor);

// ==== Entry ====
void D_DFA_Block_Enter(M_DFA_Block *dfa_block) {
    M_DFA_Block_Init(dfa_block);
    D_DFA_Block_Guess_Enter(dfa_block);
}

void D_DFA_Block_Process(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor) {
    DFA_Block_Status status = dfa_block->status;
    if (status == DFA_Block_Status_Guess) {
        D_DFA_Block_Guess_Process(dfa_block, code, word, cursor);
    } else if (status == DFA_Block_Status_Statement) {
        D_DFA_Block_Statement_Process(dfa_block, code, word, cursor);
    } else if (status == DFA_Block_Status_ChildBlock) {
        D_DFA_Block_ChildBlock_Process(dfa_block, code, word, cursor);
    }
}

// Phase: Guess
void D_DFA_Block_Guess_Enter(M_DFA_Block *dfa_block) {
    dfa_block->status = DFA_Block_Status_Guess;
}

void D_DFA_Block_Guess_Process(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor) {
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
            dfa_block->is_done = true;
            ++cursor->index;
        } else if (split == KW_LEFT_BRACE) {
            // {
            D_DFA_Block_Enter(dfa_block);
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
            D_DFA_Block_Statement_Enter(dfa_block);
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

// Phase: Statement
void D_DFA_Block_Statement_Enter(M_DFA_Block *dfa_block) {
    dfa_block->status = DFA_Block_Status_Statement;
}

void D_DFA_Block_Statement_Process(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor) {
    D_NFA_Statement_Process(&dfa_block->nfa_stmt, code, word, cursor);
    if (dfa_block->nfa_stmt.is_done) {
        E_Block_AddStatement(&dfa_block->block, dfa_block->nfa_stmt.statement);
        D_DFA_Block_Guess_Enter(dfa_block);
    }
}

// Phase: ChildBlock
void D_DFA_Block_ChildBlock_Enter(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor) {
    dfa_block->last_status = dfa_block->status;
    dfa_block->status = DFA_Block_Status_ChildBlock;
    M_DFA_Block *dfa_child_block = malloc(sizeof(M_DFA_Block));
    dfa_block->dfa_child_block = dfa_child_block;
    D_DFA_Block_Enter(dfa_child_block);
}

void D_DFA_Block_ChildBlock_Process(M_DFA_Block *dfa_block, const string code, const string word, M_Cursor *cursor) {
    M_DFA_Block *dfa_child_block = dfa_block->dfa_child_block;
    D_DFA_Block_Process(dfa_child_block, code, word, cursor);
    if (dfa_child_block->is_done) {
        E_Block_AddBlock(&dfa_block->block, dfa_child_block->block);
        M_DFA_Block_Free(dfa_child_block);
        if (dfa_block->last_status == DFA_Block_Status_Guess) {
            D_DFA_Block_Guess_Enter(dfa_block);
        } else if (dfa_block->last_status == DFA_Block_Status_Statement) {
            D_DFA_Block_Statement_Enter(dfa_block);
        }
    }
}