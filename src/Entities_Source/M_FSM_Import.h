#ifndef M_FSM_IMPORT_H__
#define M_FSM_IMPORT_H__

typedef enum ImportType {
    ImportType_None = 0,
    ImportType_Quote,
    ImportType_ANGLE_BRACKET,
} ImportType;

typedef struct M_FSM_Import {
    bool isEntering;
    int leftIndex;
    int rightIndex;
    ImportType importType;
} M_FSM_Import;

#endif