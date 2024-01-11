#ifndef ENUMS_H__
#define ENUMS_H__

typedef enum ImportType {
    ImportType_None = 0,
    ImportType_Quote,
    ImportType_ANGLE_BRACKET,
} ImportType;

typedef enum Top_FA {
    Top_FA_Guess = 0,
    Top_FA_Something,
    Top_FA_Import,
    Top_FA_Access,
    Top_FA_Func,
    Top_FA_Struct,
} Top_FA;

typedef enum Block_FA {
    Block_FA_Guess = 0,
    Block_FA_Statement,
    Block_FA_ChildBlock,
} Block_FA;

typedef enum STMT_FA {
    STMT_FA_Guess = 0,
    STMT_FA_Return,
    STMT_FA_Assign,
} STMT_FA;

typedef enum EXP_FA {
    EXP_FA_Guess = 0,
    NFA_EXPression_Status_Bracket,
    EXP_FA_Recursion,
} EXP_FA;

typedef enum Struct_FA {
    Struct_FA_Name = 0,
    Struct_FA_Guess,
    Struct_FA_Field,
    Struct_FA_Func,
} Struct_FA;

typedef enum Func_FA {
    Func_FA_Name = 0,
    Func_FA_Params,
    Func_FA_Block,
} Func_FA;

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

typedef enum StatementType {
    StatementType_None = 0,
    StatementType_OnlyLeft,       // `i32 a;`
    StatementType_OnlyExpression, // `FunctionA();`
    StatementType_Assign,         // `i32 a = 1;` or `b.value = 1;`
    StatementType_If,             // `if (a == 1) {}`
    StatementType_ElseIf,         // `else if (a == 1) {}`
    StatementType_Else,           // `else {}`
    StatementType_Do,             // `do {} while (a == 1);`
    StatementType_While,          // `while (a == 1) {}`
    StatementType_For,            // `for (i32 i = 0; i < 10; i++) {}`
    StatementType_Return,         // `return 1;`
} StatementType;

#endif