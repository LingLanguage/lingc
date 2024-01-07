#include "StringCommon.h"

static char kw_split_symbols[256];
static char kw_letters[256];
static char kw_numbers[256];

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

static string KW_CONSTVALUES[] = {
    "true",
    "false",
    "null",
};

static string KW_OPERATORS[] = {
    "+", "-",  "*",  "/",  "%",  "++", "--",  "==",  "!=", ">",  "<",  ">=", "<=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>",
    "=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "|=", "^=", "(",  ")",  "[",  "]",  "{", "}", ".", ",", ";", ":",
};

void StringCommon_Init() {

    memset(kw_split_symbols, 0, 256);
    kw_split_symbols[(int)KW_SPACE] = KW_SPACE;                               // 32 ' '
    kw_split_symbols[(int)KW_NEWLINE] = KW_NEWLINE;                           // 10 '\n'
    kw_split_symbols[(int)KW_NEWLINE_R] = KW_NEWLINE_R;                       // 13 '\r'
    kw_split_symbols[(int)KW_TABLE] = KW_TABLE;                               // 9 '\t'
    kw_split_symbols[(int)KW_SEMICOLON] = KW_SEMICOLON;                       // 59 ';'
    kw_split_symbols[(int)KW_LEFT_BRACKET] = KW_LEFT_BRACKET;                 // 40 '('
    kw_split_symbols[(int)KW_RIGHT_BRACKET] = KW_RIGHT_BRACKET;               // 41 ')'
    kw_split_symbols[(int)KW_LEFT_BRACE] = KW_LEFT_BRACE;                     // 123 '{'
    kw_split_symbols[(int)KW_RIGHT_BRACE] = KW_RIGHT_BRACE;                   // 125 '}'
    kw_split_symbols[(int)KW_LEFT_SQUARE_BRACKET] = KW_LEFT_SQUARE_BRACKET;   // 91 '['
    kw_split_symbols[(int)KW_RIGHT_SQUARE_BRACKET] = KW_RIGHT_SQUARE_BRACKET; // 93 ']'
    kw_split_symbols[(int)KW_LEFT_ANGLE_BRACKET] = KW_LEFT_ANGLE_BRACKET;     // 60 '<'
    kw_split_symbols[(int)KW_RIGHT_ANGLE_BRACKET] = KW_RIGHT_ANGLE_BRACKET;   // 62 '>'
    kw_split_symbols[(int)KW_COMMA] = KW_COMMA;                               // 44 ','
    kw_split_symbols[(int)KW_COLON] = KW_COLON;                               // 58 ':'
    kw_split_symbols[(int)KW_DOT] = KW_DOT;                                   // 46 '.'
    kw_split_symbols[(int)KW_QUOTE] = KW_QUOTE;                               // 34 '\"'
    kw_split_symbols[(int)KW_SINGLE_QUOTE] = KW_SINGLE_QUOTE;                 // 39 '\''

    memset(kw_letters, 0, 256);
    kw_letters[(int)LT_A] = LT_A; // 65 'A'
    kw_letters[(int)LT_a] = LT_a; // 97 'a'
    kw_letters[(int)LT_B] = LT_B; // 66 'B'
    kw_letters[(int)LT_b] = LT_b; // 98 'b'
    kw_letters[(int)LT_C] = LT_C; // 67 'C'
    kw_letters[(int)LT_c] = LT_c; // 99 'c'
    kw_letters[(int)LT_D] = LT_D; // 68 'D'
    kw_letters[(int)LT_d] = LT_d; // 100 'd'
    kw_letters[(int)LT_E] = LT_E; // 69 'E'
    kw_letters[(int)LT_e] = LT_e; // 101 'e'
    kw_letters[(int)LT_F] = LT_F; // 70 'F'
    kw_letters[(int)LT_f] = LT_f; // 102 'f'
    kw_letters[(int)LT_G] = LT_G; // 71 'G'
    kw_letters[(int)LT_g] = LT_g; // 103 'g'
    kw_letters[(int)LT_H] = LT_H; // 72 'H'
    kw_letters[(int)LT_h] = LT_h; // 104 'h'
    kw_letters[(int)LT_I] = LT_I; // 73 'I'
    kw_letters[(int)LT_i] = LT_i; // 105 'i'
    kw_letters[(int)LT_J] = LT_J; // 74 'J'
    kw_letters[(int)LT_j] = LT_j; // 106 'j'
    kw_letters[(int)LT_K] = LT_K; // 75 'K'
    kw_letters[(int)LT_k] = LT_k; // 107 'k'
    kw_letters[(int)LT_L] = LT_L; // 76 'L'
    kw_letters[(int)LT_l] = LT_l; // 108 'l'
    kw_letters[(int)LT_M] = LT_M; // 77 'M'
    kw_letters[(int)LT_m] = LT_m; // 109 'm'
    kw_letters[(int)LT_N] = LT_N; // 78 'N'
    kw_letters[(int)LT_n] = LT_n; // 110 'n'
    kw_letters[(int)LT_O] = LT_O; // 79 'O'
    kw_letters[(int)LT_o] = LT_o; // 111 'o'
    kw_letters[(int)LT_P] = LT_P; // 80 'P'
    kw_letters[(int)LT_p] = LT_p; // 112 'p'
    kw_letters[(int)LT_Q] = LT_Q; // 81 'Q'
    kw_letters[(int)LT_q] = LT_q; // 113 'q'
    kw_letters[(int)LT_R] = LT_R; // 82 'R'
    kw_letters[(int)LT_r] = LT_r; // 114 'r'
    kw_letters[(int)LT_S] = LT_S; // 83 'S'
    kw_letters[(int)LT_s] = LT_s; // 115 's'
    kw_letters[(int)LT_T] = LT_T; // 84 'T'
    kw_letters[(int)LT_t] = LT_t; // 116 't'
    kw_letters[(int)LT_U] = LT_U; // 85 'U'
    kw_letters[(int)LT_u] = LT_u; // 117 'u'
    kw_letters[(int)LT_V] = LT_V; // 86 'V'
    kw_letters[(int)LT_v] = LT_v; // 118 'v'
    kw_letters[(int)LT_W] = LT_W; // 87 'W'
    kw_letters[(int)LT_w] = LT_w; // 119 'w'
    kw_letters[(int)LT_X] = LT_X; // 88 'X'
    kw_letters[(int)LT_x] = LT_x; // 120 'x'
    kw_letters[(int)LT_Y] = LT_Y; // 89 'Y'
    kw_letters[(int)LT_y] = LT_y; // 121 'y'
    kw_letters[(int)LT_Z] = LT_Z; // 90 'Z'
    kw_letters[(int)LT_z] = LT_z; // 122 'z'

    memset(kw_numbers, 0, 256);
    kw_numbers[(int)LT_0] = LT_0; // 48 '0'
    kw_numbers[(int)LT_1] = LT_1; // 49 '1'
    kw_numbers[(int)LT_2] = LT_2; // 50 '2'
    kw_numbers[(int)LT_3] = LT_3; // 51 '3'
    kw_numbers[(int)LT_4] = LT_4; // 52 '4'
    kw_numbers[(int)LT_5] = LT_5; // 53 '5'
    kw_numbers[(int)LT_6] = LT_6; // 54 '6'
    kw_numbers[(int)LT_7] = LT_7; // 55 '7'
    kw_numbers[(int)LT_8] = LT_8; // 56 '8'
    kw_numbers[(int)LT_9] = LT_9; // 57 '9'
}

bool String_IsAccess(const string word) {
    for (int i = 0; i < KW_ACCESS_COUNT; i += 1) {
        if (strcmp(word, KW_ACCESS[i]) == 0) {
            return true;
        }
    }
    return false;
}

const string String_ValidAccess(const string access) {
    if (strlen(access) == 0) {
        return KW_ACCESS_PRIVATE;
    } else {
        return access;
    }
}

char Char_IsSplitSymbol(char c) {
    if (kw_split_symbols[(int)c] == c) {
        return c;
    } else {
        return 0;
    }
}

char Char_IsLetter(char c) {
    if (kw_letters[(int)c] == c) {
        return c;
    } else {
        return 0;
    }
}

char Char_IsLetterOrUnderline(char c) {
    if (kw_letters[(int)c] == c || c == KW_UNDERLINE) {
        return c;
    } else {
        return 0;
    }
}

char Char_IsNumber(char c) {
    if (kw_numbers[(int)c] == c) {
        return c;
    } else {
        return 0;
    }
}

char Char_IsLetterOrNumber(char c) {
    if (kw_letters[(int)c] == c || kw_numbers[(int)c] == c) {
        return c;
    } else {
        return 0;
    }
}

char Char_IsLetterOrNumberOrUnderline(char c) {
    if (kw_letters[(int)c] == c || kw_numbers[(int)c] == c || c == KW_UNDERLINE) {
        return c;
    } else {
        return 0;
    }
}

bool Char_NotEmpty(char c) {
    return c != KW_SPACE && c != KW_NEWLINE && c != KW_NEWLINE_R && c != KW_TABLE;
}

bool Char_IsValidVar(char c) {
    return Char_IsLetter(c) || Char_IsNumber(c) || c == '_';
}