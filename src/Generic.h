#ifndef GENERIC_H__
#define GENERIC_H__

#include <stdio.h>
#include <string.h>
#include <utf8.h>
#include <stdbool.h>

#define PLogNA(x) printf("%s:%d %s", __FILE__, __LINE__, x)
#define PLog(x, ...)                                                                                                                                           \
    printf("%s:%d ", __FILE__, __LINE__);                                                                                                                      \
    printf(x, __VA_ARGS__)

#define string utf8_int8_t *
#define byte unsigned char

typedef enum TopType
{
    TOPTYPE_NONE,
    TOPTYPE_STRUCT,
    TOPTYPE_STATIC_VARIABLE,
    TOPTYPE_STATIC_FUNCTION,
} TopType;

typedef enum BehaviourType
{
    BehaviourType_Unknown = 0,
    BehaviourType_Something,
    BehaviourType_Import,
    BehaviourType_Struct,
} BehaviourType;

typedef enum StructBehaviourType {
    StructBehaviourType_Unknown = 0,
    StructBehaviourType_Something,
    StructBehaviourType_AfterAccess,
    StructBehaviourType_Field,
    StructBehaviourType_Function,
} StructBehaviourType;

static const char KW_SPACE = ' ';
static const char *KW_SPACE_STR = " ";
static const char KW_NEWLINE = '\n';
static const char KW_NEWLINE_R = '\r';
static const char KW_TABLE = '\t';
static const char KW_END = ';';
static const char KW_LEFT_BRACKET = '(';
static const char KW_RIGHT_BRACKET = ')';
static const char KW_LEFT_BRACE = '{';
static const char KW_RIGHT_BRACE = '}';
static const char KW_LEFT_SQUARE_BRACKET = '[';
static const char KW_RIGHT_SQUARE_BRACKET = ']';
static const char KW_LEFT_ANGLE_BRACKET = '<';
static const char KW_RIGHT_ANGLE_BRACKET = '>';
static const char KW_COMMA = ',';
static const char KW_COLON = ':';
static const char KW_DOT = '.';
static const char KW_QUOTE = '"';
static const char KW_SINGLE_QUOTE = '\'';
static const string KW_FUNC = "fn";
static const string KW_STRUCT = "struct";
static const string KW_IF = "if";
static const string KW_ELIF = "else if";
static const string KW_ELSE = "else";
static const string KW_WHILE = "while";
static const string KW_FOR = "for";
static const string KW_BREAK = "break";
static const string KW_CONTINUE = "continue";
static const string KW_RETURN = "return";

static string KW_SYS_TYPES[] = {
    "i8", "i16", "i32", "i64", "i128", "i256", "u8", "u16", "u32", "u64", "u128", "u256", "f32", "f64", "f128", "bool", "string", "byte", "void",
};

static string KW_MODIFIERS[] = {
    "const",
    "static",
    "inline",
};

static string KW_ACCESS[] = {
    "public",
};
static string KW_ACCESS_PRIVATE = "private";

static string KW_IMPORT = "import";

static string KW_CONSTVALUES[] = {
    "true",
    "false",
    "null",
};

static string KW_OPERATORS[] = {
    "+", "-",  "*",  "/",  "%",  "++", "--",  "==",  "!=", ">",  "<",  ">=", "<=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>",
    "=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "|=", "^=", "(",  ")",  "[",  "]",  "{", "}", ".", ",", ";", ":",
};

// ==== Rule ====
#define RULE_FUNCTION_RETURN_MAX 8
#define RULE_FUNCTION_PARAM_NAME_MAX 64
#define RULE_FUNCTION_PARAM_MAX 32
#define RULE_STRUCT_TYPE_NAME_MAX 128
#define RULE_STRUCT_FIELD_NAME_MAX 128
#define RULE_FUNCTION_NAME_MAX 128
#define RULE_ACCESS_MAX 12
#define RULE_VAR_NAME_MAX 128

#endif