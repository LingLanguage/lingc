#ifndef CONTEXT_H__
#define CONTEXT_H__

#include "Entities_Source/export.h"

typedef struct Context {

    E_Doc *doc;

    char kw_split_symbols[256];
    char kw_letters[256];
    char kw_numbers[256];

    E_Struct *structs;
    int structs_count;
    int structs_idRecord;

    E_Function *static_functions;
    int static_functions_count;
    int static_functions_idRecord;

    E_StaticVar *static_vars;
    int static_vars_count;
    int static_vars_idRecord;

} Context;

static void Context_Init(Context *ctx) {

    memset(ctx->kw_split_symbols, 0, 256);
    ctx->kw_split_symbols[(int)KW_SPACE] = KW_SPACE;                               // 32 ' '
    ctx->kw_split_symbols[(int)KW_NEWLINE] = KW_NEWLINE;                           // 10 '\n'
    ctx->kw_split_symbols[(int)KW_NEWLINE_R] = KW_NEWLINE_R;                       // 13 '\r'
    ctx->kw_split_symbols[(int)KW_TABLE] = KW_TABLE;                               // 9 '\t'
    ctx->kw_split_symbols[(int)KW_SEMICOLON] = KW_SEMICOLON;                       // 59 ';'
    ctx->kw_split_symbols[(int)KW_LEFT_BRACKET] = KW_LEFT_BRACKET;                 // 40 '('
    ctx->kw_split_symbols[(int)KW_RIGHT_BRACKET] = KW_RIGHT_BRACKET;               // 41 ')'
    ctx->kw_split_symbols[(int)KW_LEFT_BRACE] = KW_LEFT_BRACE;                     // 123 '{'
    ctx->kw_split_symbols[(int)KW_RIGHT_BRACE] = KW_RIGHT_BRACE;                   // 125 '}'
    ctx->kw_split_symbols[(int)KW_LEFT_SQUARE_BRACKET] = KW_LEFT_SQUARE_BRACKET;   // 91 '['
    ctx->kw_split_symbols[(int)KW_RIGHT_SQUARE_BRACKET] = KW_RIGHT_SQUARE_BRACKET; // 93 ']'
    ctx->kw_split_symbols[(int)KW_LEFT_ANGLE_BRACKET] = KW_LEFT_ANGLE_BRACKET;     // 60 '<'
    ctx->kw_split_symbols[(int)KW_RIGHT_ANGLE_BRACKET] = KW_RIGHT_ANGLE_BRACKET;   // 62 '>'
    ctx->kw_split_symbols[(int)KW_COMMA] = KW_COMMA;                               // 44 ','
    ctx->kw_split_symbols[(int)KW_COLON] = KW_COLON;                               // 58 ':'
    ctx->kw_split_symbols[(int)KW_DOT] = KW_DOT;                                   // 46 '.'
    ctx->kw_split_symbols[(int)KW_QUOTE] = KW_QUOTE;                               // 34 '\"'
    ctx->kw_split_symbols[(int)KW_SINGLE_QUOTE] = KW_SINGLE_QUOTE;                 // 39 '\''

    memset(ctx->kw_letters, 0, 256);
    ctx->kw_letters[(int)LT_A] = LT_A; // 65 'A'
    ctx->kw_letters[(int)LT_a] = LT_a; // 97 'a'
    ctx->kw_letters[(int)LT_B] = LT_B; // 66 'B'
    ctx->kw_letters[(int)LT_b] = LT_b; // 98 'b'
    ctx->kw_letters[(int)LT_C] = LT_C; // 67 'C'
    ctx->kw_letters[(int)LT_c] = LT_c; // 99 'c'
    ctx->kw_letters[(int)LT_D] = LT_D; // 68 'D'
    ctx->kw_letters[(int)LT_d] = LT_d; // 100 'd'
    ctx->kw_letters[(int)LT_E] = LT_E; // 69 'E'
    ctx->kw_letters[(int)LT_e] = LT_e; // 101 'e'
    ctx->kw_letters[(int)LT_F] = LT_F; // 70 'F'
    ctx->kw_letters[(int)LT_f] = LT_f; // 102 'f'
    ctx->kw_letters[(int)LT_G] = LT_G; // 71 'G'
    ctx->kw_letters[(int)LT_g] = LT_g; // 103 'g'
    ctx->kw_letters[(int)LT_H] = LT_H; // 72 'H'
    ctx->kw_letters[(int)LT_h] = LT_h; // 104 'h'
    ctx->kw_letters[(int)LT_I] = LT_I; // 73 'I'
    ctx->kw_letters[(int)LT_i] = LT_i; // 105 'i'
    ctx->kw_letters[(int)LT_J] = LT_J; // 74 'J'
    ctx->kw_letters[(int)LT_j] = LT_j; // 106 'j'
    ctx->kw_letters[(int)LT_K] = LT_K; // 75 'K'
    ctx->kw_letters[(int)LT_k] = LT_k; // 107 'k'
    ctx->kw_letters[(int)LT_L] = LT_L; // 76 'L'
    ctx->kw_letters[(int)LT_l] = LT_l; // 108 'l'
    ctx->kw_letters[(int)LT_M] = LT_M; // 77 'M'
    ctx->kw_letters[(int)LT_m] = LT_m; // 109 'm'
    ctx->kw_letters[(int)LT_N] = LT_N; // 78 'N'
    ctx->kw_letters[(int)LT_n] = LT_n; // 110 'n'
    ctx->kw_letters[(int)LT_O] = LT_O; // 79 'O'
    ctx->kw_letters[(int)LT_o] = LT_o; // 111 'o'
    ctx->kw_letters[(int)LT_P] = LT_P; // 80 'P'
    ctx->kw_letters[(int)LT_p] = LT_p; // 112 'p'
    ctx->kw_letters[(int)LT_Q] = LT_Q; // 81 'Q'
    ctx->kw_letters[(int)LT_q] = LT_q; // 113 'q'
    ctx->kw_letters[(int)LT_R] = LT_R; // 82 'R'
    ctx->kw_letters[(int)LT_r] = LT_r; // 114 'r'
    ctx->kw_letters[(int)LT_S] = LT_S; // 83 'S'
    ctx->kw_letters[(int)LT_s] = LT_s; // 115 's'
    ctx->kw_letters[(int)LT_T] = LT_T; // 84 'T'
    ctx->kw_letters[(int)LT_t] = LT_t; // 116 't'
    ctx->kw_letters[(int)LT_U] = LT_U; // 85 'U'
    ctx->kw_letters[(int)LT_u] = LT_u; // 117 'u'
    ctx->kw_letters[(int)LT_V] = LT_V; // 86 'V'
    ctx->kw_letters[(int)LT_v] = LT_v; // 118 'v'
    ctx->kw_letters[(int)LT_W] = LT_W; // 87 'W'
    ctx->kw_letters[(int)LT_w] = LT_w; // 119 'w'
    ctx->kw_letters[(int)LT_X] = LT_X; // 88 'X'
    ctx->kw_letters[(int)LT_x] = LT_x; // 120 'x'
    ctx->kw_letters[(int)LT_Y] = LT_Y; // 89 'Y'
    ctx->kw_letters[(int)LT_y] = LT_y; // 121 'y'
    ctx->kw_letters[(int)LT_Z] = LT_Z; // 90 'Z'
    ctx->kw_letters[(int)LT_z] = LT_z; // 122 'z'

    memset(ctx->kw_numbers, 0, 256);
    ctx->kw_numbers[(int)LT_0] = LT_0; // 48 '0'
    ctx->kw_numbers[(int)LT_1] = LT_1; // 49 '1'
    ctx->kw_numbers[(int)LT_2] = LT_2; // 50 '2'
    ctx->kw_numbers[(int)LT_3] = LT_3; // 51 '3'
    ctx->kw_numbers[(int)LT_4] = LT_4; // 52 '4'
    ctx->kw_numbers[(int)LT_5] = LT_5; // 53 '5'
    ctx->kw_numbers[(int)LT_6] = LT_6; // 54 '6'
    ctx->kw_numbers[(int)LT_7] = LT_7; // 55 '7'
    ctx->kw_numbers[(int)LT_8] = LT_8; // 56 '8'
    ctx->kw_numbers[(int)LT_9] = LT_9; // 57 '9'

    ctx->doc = (E_Doc *)calloc(1, sizeof(E_Doc));

    ctx->structs = (E_Struct *)calloc(10000, sizeof(E_Struct));
    ctx->structs_count = 0;
    ctx->structs_idRecord = 1;

    ctx->static_functions = (E_Function *)calloc(50000, sizeof(E_Function));
    ctx->static_functions_count = 0;
    ctx->static_functions_idRecord = 1;

    ctx->static_vars = (E_StaticVar *)calloc(50000, sizeof(E_StaticVar));
    ctx->static_vars_count = 0;
    ctx->static_vars_idRecord = 1;
}

static void Context_Free(Context *ctx) {

    free(ctx->doc);

    for (int i = 0; i < ctx->structs_count; i++) {
        E_Struct_Free(&ctx->structs[i]);
    }
    free(ctx->structs);

    for (int i = 0; i < ctx->static_functions_count; i++) {
        E_Function_Free(&ctx->static_functions[i]);
    }
    free(ctx->static_functions);

    for (int i = 0; i < ctx->static_vars_count; i++) {
        E_StaticVar_Free(&ctx->static_vars[i]);
    }
    free(ctx->static_vars);
}

static char Context_IsSplitSymbol(Context *ctx, char c) {
    if (ctx->kw_split_symbols[(int)c] == c) {
        return c;
    } else {
        return 0;
    }
}

static char Context_IsLetter(Context *ctx, char c) {
    if (ctx->kw_letters[(int)c] == c) {
        return c;
    } else {
        return 0;
    }
}

static char Context_IsLetterOrUnderline(Context *ctx, char c) {
    if (ctx->kw_letters[(int)c] == c || c == KW_UNDERLINE) {
        return c;
    } else {
        return 0;
    }
}

static char Context_IsNumber(Context *ctx, char c) {
    if (ctx->kw_numbers[(int)c] == c) {
        return c;
    } else {
        return 0;
    }
}

static char Context_IsLetterOrNumber(Context *ctx, char c) {
    if (ctx->kw_letters[(int)c] == c || ctx->kw_numbers[(int)c] == c) {
        return c;
    } else {
        return 0;
    }
}

static char Context_IsLetterOrNumberOrUnderline(Context *ctx, char c) {
    if (ctx->kw_letters[(int)c] == c || ctx->kw_numbers[(int)c] == c || c == KW_UNDERLINE) {
        return c;
    } else {
        return 0;
    }
}

#endif