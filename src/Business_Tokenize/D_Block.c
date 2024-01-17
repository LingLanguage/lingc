#include "D_Block.h"
#include "D_STMT.h"
#include "Util_Cursor.h"

// block -> stmt -> exp

void D_Block_Enter(FAM_Block *fam);
void D_Block_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor);
void D_Block_Statement_Enter(FAM_Block *fam);
void D_Block_Statement_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor);
void D_Block_ChildBlock_Enter(FAM_Block *fam, const string code, const string word, M_Cursor *cursor);
void D_Block_ChildBlock_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor);

// ==== Entry ====
void D_Block_Enter(FAM_Block *fam) {
    FAM_Block_Init(fam);
    D_Block_Statement_Enter(fam);
}

void D_Block_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor) {

    if (cursor->is_split) {
        char split = word[0];
        if (split == KW_LEFT_BRACE) {
            ++cursor->nested;
        } else if (split == KW_RIGHT_BRACE) {
            --cursor->nested;
            if (cursor->nested == 0) {
                fam->is_done = true;
                return;
            }
        }
    }

    Block_FA status = fam->status;
    if (status == Block_FA_Statement) {
        D_Block_Statement_Process(fam, code, word, cursor);
    } else if (status == Block_FA_ChildBlock) {
        D_Block_ChildBlock_Process(fam, code, word, cursor);
    }
}

// Phase: Statement
void D_Block_Statement_Enter(FAM_Block *fam) {
    fam->status = Block_FA_Statement;
}

void D_Block_Statement_Process(FAM_Block *fam, const string code, const string word, M_Cursor *cursor) {
    FAM_STMT *fam_stmt = &fam->fam_stmt;
    D_STMT_Process(fam_stmt, code, word, cursor);
    if (fam_stmt->is_done) {
        E_Block_AddStatement(&fam->block, fam_stmt->stmt);
        D_Block_Statement_Enter(fam);
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
        E_Block_AddChildBlock(&fam->block, &dfa_child_block->block);
        FAM_Block_Free(dfa_child_block);
        if (fam->last_status == Block_FA_Statement) {
            D_Block_Statement_Enter(fam);
        } else if (fam->last_status == Block_FA_ChildBlock) {
            D_Block_ChildBlock_Enter(fam, code, word, cursor);
        }
    }
}