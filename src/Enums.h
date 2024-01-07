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
    TopBT_AfterAccess,
    TopBT_Struct,
} TopBT;

typedef enum StructBT {
    StructBT_Unknown = 0,
    StructBT_Something,
    StructBT_AfterAccess,
    StructBT_Field,
    StructBT_Function,
} StructBT;

#endif