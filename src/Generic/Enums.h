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
    EXP_FA_Bracket,
    EXP_FA_ChildBracket,
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

typedef enum OP_Type {

    OP_Type_None = 0,
    OP_Type_Comment,        // //
    OP_Type_Bracket,        // ()
    OP_Type_Square_Bracket, // []

    OP_Type_Increment, // ++
    OP_Type_Decrement, // --

    OP_Type_Add,                // +
    OP_Type_Sub,                // -
    OP_Type_MulOrPointerAccess, // *
    OP_Type_Div,                // /
    OP_Type_Mod,                // %

    OP_Type_Bin_Not,                // ~
    OP_Type_Bin_AndOrAddressAccess, // &
    OP_Type_Bin_Or,                 // |
    OP_Type_Bin_Xor,                // ^
    OP_Type_Bin_Move_Left,          // <<
    OP_Type_Bin_Move_Right,         // >>

    OP_Type_Logic_Not,     // !
    OP_Type_Logic_And,     // &&
    OP_Type_Logic_Or,      // ||
    OP_Type_Equal,         // ==
    OP_Type_Not_Equal,     // !=
    OP_Type_Greater,       // >
    OP_Type_Less,          // <
    OP_Type_Greater_Equal, // >=
    OP_Type_Less_Equal,    // <=

    OP_Type_Assign = 1000,                // =
    OP_Type_Add_Assign = 1001,            // +=
    OP_Type_Sub_Assign = 1002,            // -=
    OP_Type_Mul_Assign = 1003,            // *=
    OP_Type_Div_Assign = 1004,            // /=
    OP_Type_Mod_Assign = 1005,            // %=
    OP_Type_Bin_And_Assign = 1006,        // &=
    OP_Type_Bin_Or_Assign = 1007,         // |=
    OP_Type_Bin_Xor_Assign = 1008,        // ^=
    OP_Type_Bin_Not_Assign = 1009,        // ~=
    OP_Type_Bin_Move_Left_Assign = 1010,  // <<=
    OP_Type_Bin_Move_Right_Assign = 1011, // >>=

    OP_Type_Member,        // .
    OP_Type_MemberPointer, // ->

    OP_Type_End, // ;
} OP_Type;

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