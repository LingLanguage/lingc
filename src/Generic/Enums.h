#ifndef ENUMS_H__
#define ENUMS_H__

typedef enum ImportType {
    ImportType_None = 0,
    ImportType_Quote,
    ImportType_ANGLE_BRACKET,
} ImportType;

typedef enum NFA_Top_Status {
    NFA_Top_Status_Guess = 0,
    NFA_Top_Status_Something,
    NFA_Top_Status_Import,
    NFA_Top_Status_Access,
    NFA_Top_Status_Func,
    NFA_Top_Status_Struct,
} NFA_Top_Status;

typedef enum StructPhase {
    StructPhase_Name = 0,
    StructPhase_Guess,
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
    ExpressionPhase_Guess,
    ExpressionPhase_Statement_Assign,
    ExpressionPhase_Statement_If,
    ExpressionPhase_Statement_Return,
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
    StatementType_OnlyLeft,
    StatementType_OnlyRight,
    StatementType_LeftRight,
    StatementType_If,
    StatementType_While,
    StatementType_For,
    StatementType_Return,
} StatementType;

#endif