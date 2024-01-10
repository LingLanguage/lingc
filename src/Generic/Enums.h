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
    FuncPhase_Name = 0,
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
    // order by priority
    // 20(Bracket) means highest priority
    ExpressionType_None = 0,
    ExpressionType_Bracket = 500,          // ()
    ExpressionType_Member = 600,           // . ->
    ExpressionType_Pre_Increment = 700,    // ++x --x
    ExpressionType_Square_Bracket = 800,   // []
    ExpressionType_Pointer = 900,          // * &
    ExpressionType_Calculation_Mul = 1000, // * / %
    ExpressionType_Calculation_Add = 1100, // + -
    ExpressionType_Binary_Move = 1200,     // << >>
    ExpressionType_Compare = 1300,         // == != > < >= <=
    ExpressionType_Binary_And = 1400,      // & ^ |
    ExpressionType_Logic = 1500,           // && ||
    ExpressionType_Condition = 1600,       // ? :
    ExpressionType_Assign = 1700,          // = += -= *= /= %= &= |= ^= ~= <<= >>=
    ExpressionType_Post_Increment = 1800,  // x++ x--
    ExpressionType_Empty = 1900,           // ; eg: for(;;)
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
    StatementType_OnlyLeft,       // `i32 a;`
    StatementType_OnlyExpression, // `FunctionA();`
    StatementType_LeftRight,      // `i32 a = 1;` or `b.value = 1;`
    StatementType_If,             // `if (a == 1) {}`
    StatementType_ElseIf,         // `else if (a == 1) {}`
    StatementType_Else,           // `else {}`
    StatementType_Do,             // `do {} while (a == 1);`
    StatementType_While,          // `while (a == 1) {}`
    StatementType_For,            // `for (i32 i = 0; i < 10; i++) {}`
    StatementType_Return,         // `return 1;`
} StatementType;

#endif