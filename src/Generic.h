#ifndef GENERIC_H__
#define GENERIC_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <utf8.h>

#include "Enums.h"
#include "Errors.h"

#define PLogNA(x) printf("%s:%d %s", __FILE__, __LINE__, x)
#define PLog(x, ...)                                                                                                                                           \
    printf("%s:%d ", __FILE__, __LINE__);                                                                                                                      \
    printf(x, __VA_ARGS__)
#define PLogCode(file, line, err)                                                                                                                                   \
    PLogNA("[Err]");                                                                                                                                       \
    printf("%s %s:%d\r\n", err, file, line)
#define string utf8_int8_t *
#define byte unsigned char

#define KW_SPACE ' '
#define KW_NEWLINE '\n'
#define KW_NEWLINE_R '\r'
#define KW_TABLE '\t'
#define KW_SEMICOLON ';'
#define KW_LEFT_BRACKET '('
#define KW_RIGHT_BRACKET ')'
#define KW_LEFT_BRACE '{'
#define KW_RIGHT_BRACE '}'
#define KW_LEFT_SQUARE_BRACKET '['
#define KW_RIGHT_SQUARE_BRACKET ']'
#define KW_LEFT_ANGLE_BRACKET '<'
#define KW_RIGHT_ANGLE_BRACKET '>'
#define KW_COMMA ','
#define KW_COLON ':'
#define KW_DOT '.'
#define KW_QUOTE '\"'
#define KW_SINGLE_QUOTE '\''

#define LT_A 'A'
#define LT_a 'a'
#define LT_B 'B'
#define LT_b 'b'
#define LT_C 'C'
#define LT_c 'c'
#define LT_D 'D'
#define LT_d 'd'
#define LT_E 'E'
#define LT_e 'e'
#define LT_F 'F'
#define LT_f 'f'
#define LT_G 'G'
#define LT_g 'g'
#define LT_H 'H'
#define LT_h 'h'
#define LT_I 'I'
#define LT_i 'i'
#define LT_J 'J'
#define LT_j 'j'
#define LT_K 'K'
#define LT_k 'k'
#define LT_L 'L'
#define LT_l 'l'
#define LT_M 'M'
#define LT_m 'm'
#define LT_N 'N'
#define LT_n 'n'
#define LT_O 'O'
#define LT_o 'o'
#define LT_P 'P'
#define LT_p 'p'
#define LT_Q 'Q'
#define LT_q 'q'
#define LT_R 'R'
#define LT_r 'r'
#define LT_S 'S'
#define LT_s 's'
#define LT_T 'T'
#define LT_t 't'
#define LT_U 'U'
#define LT_u 'u'
#define LT_V 'V'
#define LT_v 'v'
#define LT_W 'W'
#define LT_w 'w'
#define LT_X 'X'
#define LT_x 'x'
#define LT_Y 'Y'
#define LT_y 'y'
#define LT_Z 'Z'
#define LT_z 'z'

#define LT_0 '0'
#define LT_1 '1'
#define LT_2 '2'
#define LT_3 '3'
#define LT_4 '4'
#define LT_5 '5'
#define LT_6 '6'
#define LT_7 '7'
#define LT_8 '8'
#define LT_9 '9'

#define KW_UNDERLINE '_'

#define KW_SPACE_STR " "
#define KW_FUNC "fn"
#define KW_STRUCT "struct"
#define KW_IF "if"
#define KW_ELIF "else if"
#define KW_ELSE "else"
#define KW_WHILE "while"
#define KW_FOR "for"
#define KW_BREAK "break"
#define KW_CONTINUE "continue"
#define KW_RETURN "return"

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
static const int KW_ACCESS_COUNT = 1;
static string KW_ACCESS_PRIVATE = "private";
static string KW_STATIC = "static";

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
#define RULE_IMPORT_FILE_NAME_LEN 128
#define RULE_IMPORT_FILE_COUNT 128
#define RULE_FUNCTION_NAME_LEN 128
#define RULE_FUNCTION_RETURN_COUNT 8
#define RULE_FUNCTION_PARAM_NAME_LEN 64
#define RULE_FUNCTION_PARAM_COUNT 32
#define RULE_STRUCT_TYPE_NAME_LEN 128
#define RULE_STRUCT_FIELD_NAME_MAX 128
#define RULE_ACCESS_NAME_LEN 12
#define RULE_VAR_NAME_LEN 128

#endif