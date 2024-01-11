#include "D_STMT_Assign.h"

void D_STMT_Assign_Enter(FAM_STMT *fam) {
    fam->status = STMT_FA_Return;
}