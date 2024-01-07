#ifndef ENUMS_H__
#define ENUMS_H__

typedef enum ImportType {
    ImportType_None = 0,
    ImportType_Quote,
    ImportType_ANGLE_BRACKET,
} ImportType;

typedef enum TopBT {
    TopBT_Unknown = 0,
    TopBT_Something,
    TopBT_Import,
    TopBT_Access,
    TopBT_Func,
    TopBT_Struct,
} TopBT;

typedef enum StructBT {
    StructBT_Unknown = 0,
    StructBT_Something,
    StructBT_AfterAccess,
    StructBT_Field,
    StructBT_Function,
} StructBT;

typedef enum FuncPhase {
    FuncPhase_ReturnType = 0,
    FuncPhase_Name,
    FuncPhase_Params,
    FuncPhase_Body,
} FuncPhase;

#endif