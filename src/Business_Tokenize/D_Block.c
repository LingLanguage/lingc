#include "D_Block.h"
#include "D_STMT_Assign.h"
#include "D_STMT_Return.h"
#include "Util_Cursor.h"

// block -> stmt -> exp

void D_Block_Enter(FAM_Block *fam);
void D_Block_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor);
void D_Block_Guess_Enter(FAM_Block *fam);
void D_Block_Guess_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor);
void D_Block_Statement_Enter(FAM_Block *fam);
void D_Block_Statement_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor);
void D_Block_ChildBlock_Enter(FAM_Block *fam, const string code, const string word, M_Cursor *cursor);
void D_Block_ChildBlock_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor);

// ==== Entry ====
void D_Block_Enter(FAM_Block *fam) {
    FAM_Block_Init(fam);
    D_Block_Guess_Enter(fam);
}

void D_Block_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor) {
    Block_FA status = fam->status;
    if (status == Block_FA_Guess) {
        D_Block_Guess_Process(fam, code, word, cursor);
    } else if (status == Block_FA_Statement) {
        D_Block_Statement_Process(fam, code, word, cursor);
    } else if (status == Block_FA_ChildBlock) {
        D_Block_ChildBlock_Process(fam, code, word, cursor);
    }
}

// Phase: Guess
void D_Block_Guess_Enter(FAM_Block *fam) {
    fam->status = Block_FA_Guess;
    E_Guess_Init(&fam->guess);
}

void D_Block_Guess_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor) {
    bool is_split = cursor->is_split;
    if (is_split) {
        char split = word[0];
        if (split == KW_EQUAL) {
            // =
            D_Block_Statement_Enter(fam);
            D_STMT_Assign_Enter(&fam->fam_stmt, fam->guess.words, fam->guess.words_count);
            ++cursor->index;
        } else if (split == KW_SEMICOLON) {
            // ;
            PLogNA("TODO: DFA Block Process: ;\r\n");
            ++cursor->index;
        } else if (split == KW_RIGHT_BRACE) {
            // }
            fam->is_done = true;
            ++cursor->index;
        } else if (split == KW_LEFT_BRACE) {
            // {
            D_Block_Enter(fam);
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
            Util_Cursor_DealEmptySplit(cursor, code, word);
        }
    } else {
        if (strcmp(word, KW_RETURN) == 0) {
            // return
            D_Block_Statement_Enter(fam);
            D_STMT_Return_Enter(&fam->fam_stmt);
        } else if (strcmp(word, KW_IF) == 0) {
            // if
        } else if (strcmp(word, KW_WHILE) == 0) {
            // while
        } else if (strcmp(word, KW_FOR) == 0) {
            // for
        } else {
            E_Guess_PushWord(&fam->guess, cursor->file, cursor->line, word);
        }
    }
}

// Phase: Statement
void D_Block_Statement_Enter(FAM_Block *fam) {
    fam->status = Block_FA_Statement;
}

void D_Block_Statement_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor) {
    FAM_STMT *fam_stmt = &fam->fam_stmt;
    STMT_FA stmt_fa = fam->fam_stmt.status;
    if (stmt_fa == STMT_FA_Return) {
        D_STMT_Return_Process(&fam->fam_stmt, code, word, cursor);
        if (fam->fam_stmt.is_done) {
            E_Block_AddStatement(&fam->block, fam->fam_stmt.stmt);
            D_Block_Guess_Enter(fam);
            PLogNA("STMT Return DONE\r\n");
        }
    } else if (stmt_fa == STMT_FA_Assign) {
        D_STMT_Assign_Process(&fam->fam_stmt, code, word, cursor);
        if (fam->fam_stmt.is_done) {
            E_Block_AddStatement(&fam->block, fam->fam_stmt.stmt);
            D_Block_Guess_Enter(fam);
            PLogNA("STMT Assign DONE\r\n");
        }
    }
}

// Phase: ChildBlock
void D_Block_ChildBlock_Enter(FAM_Block *fam, const string code, const string word, M_Cursor *cursor) {
    fam->last_status = fam->status;
    fam->status = Block_FA_ChildBlock;
    FAM_Block *dfa_child_block = malloc(sizeof(FAM_Block));
    fam->dfa_child_block = dfa_child_block;
    D_Block_Enter(dfa_child_block);
}

void D_Block_ChildBlock_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor) {
    FAM_Block *dfa_child_block = fam->dfa_child_block;
    D_Block_Process(dfa_child_block, code, word, cursor);
    if (dfa_child_block->is_done) {
        E_Block_AddBlock(&fam->block, dfa_child_block->block);
        FAM_Block_Free(dfa_child_block);
        if (fam->last_status == Block_FA_Guess) {
            D_Block_Guess_Enter(fam);
        } else if (fam->last_status == Block_FA_Statement) {
            D_Block_Statement_Enter(fam);
        }
    }
}