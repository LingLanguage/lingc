#ifndef FAM_IMPORT_H__
#define FAM_IMPORT_H__

typedef struct FAM_Import {
    int import_id;
    bool is_recorded;
    bool is_done;
} FAM_Import;

void FAM_Import_Init(FAM_Import *fsm);
void FAM_Import_Free(FAM_Import *fsm);
void FAM_Import_Enter(FAM_Import *fsm);

#endif