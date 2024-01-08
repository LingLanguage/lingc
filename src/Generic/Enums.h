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

typedef enum ExpressionPhase {
    ExpressionPhase_Statement,
    ExpressionPhase_Operator,
    ExpressionPhase_Expression,
} ExpressionPhase;

typedef enum ExpressionType {
    ExpressionType_None = 0,
    ExpressionType_CallFunc,
    ExpressionType_ConstValue,
    ExpressionType_Variable,
} ExpressionType;

typedef enum OperatorType {
    OperatorType_None = 0,
    OperatorType_Assign,        // = += -= *= /= %= &= |= ^= <<= >>=
    OperatorType_Calculation,   // + - * / %
    OperatorType_Compare,       // == != > < >= <=
    OperatorType_Binary,        // & | ^ << >> ~
    OperatorType_Logic,         // && ||
    OperatorType_Increment,     // ++ --
    OperatorType_Pointer,       // * &
    OperatorType_Condition,     // ? :
    OperatorType_Sizeof,        // sizeof
    OperatorType_Member,        // .
    OperatorType_MemberPointer, // ->
    OperatorType_End,           // ;
} OperatorType;

typedef enum ArgumentType {
    ArgumentType_None = 0,
    ArgumentType_ConstValue,
    ArgumentType_Variable,
    ArgumentType_Expression,
} ArgumentType;

typedef enum StatementType {
    StatementType_None = 0,
    StatementType_OnlyLeft = 1,
    StatementType_OnlyRight = 2,
    StatementType_Both = 1 | 2,
    StatementType_Return = 4,
} StatementType;

#endif