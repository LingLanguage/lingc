#ifndef ENUMS_H__
#define ENUMS_H__

typedef enum ImportType {
    ImportType_None = 0,
    ImportType_Quote,
    ImportType_ANGLE_BRACKET,
} ImportType;

typedef enum TopFSMStatus {
    TopFSMStatus_Guess = 0,
    TopFSMStatus_Something,
    TopFSMStatus_Import,
    TopFSMStatus_Access,
    TopFSMStatus_Func,
    TopFSMStatus_Struct,
} TopFSMStatus;

typedef enum StructPhase {
    StructPhase_Name = 0,
    StructPhase_Guess,
    StructPhase_Access,
    StructPhase_Field,
    StructPhase_Func,
} StructPhase;

typedef enum FuncPhase {
    FuncPhase_ReturnType = 0,
    FuncPhase_Name,
    FuncPhase_Params,
    FuncPhase_Body,
} FuncPhase;

typedef enum StatementType {
    StatementType_None = 0,
    StatementType_OnlyLeft = 1,
    StatementType_OnlyRight = 2,
    StatementType_Both = 1 | 2,
} StatementType;

#endif