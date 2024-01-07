#ifndef ENUMS_H__
#define ENUMS_H__

typedef enum ImportType {
    ImportType_None = 0,
    ImportType_Quote,
    ImportType_ANGLE_BRACKET,
} ImportType;

typedef enum TopFSMStatus {
    TopBT_Unknown = 0,
    TopBT_Something,
    TopBT_Import,
    TopBT_Access,
    TopBT_Func,
    TopBT_Struct,
} TopFSMStatus;

typedef enum StructPhase {
    StructPhase_Name = 0,
    StructPhase_Guess,
    StructPhase_Field,
    StructPhase_Function,
} StructPhase;

typedef enum FuncPhase {
    FuncPhase_ReturnType = 0,
    FuncPhase_Name,
    FuncPhase_Params,
    FuncPhase_Body,
} FuncPhase;

#endif