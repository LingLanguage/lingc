#include "E_Guess.h"

void E_Guess_Init(E_Guess *self) {
    self->words_count = 0;
}

void E_Guess_Free(E_Guess *self) {
    if (self->words_capacity > 0) {
        for (int i = 0; i < self->words_capacity; i++) {
            free(self->words[i]);
        }
        free(self->words);
    }
}

void E_Guess_InitAccess(E_Guess *self) {

    memset(self->access, 0, sizeof(self->access));
    self->is_const = false;
    self->is_static = false;

    for (int i = 0; i < self->words_capacity; i++) {
        free(self->words[i]);
    }
    if (self->words_capacity > 0) {
        free(self->words);
    }
    self->words_capacity = 0;
    self->words_count = 0;
}

void E_Guess_SetAcceess(E_Guess *self, const string file, int line, const string access) {
    if (strlen(self->access) > 1) {
        PFailed(file, line, ERR_ACCESS_REDIFINED);
        return;
    }
    strcpy(self->access, String_ValidAccess(access));
}

void E_Guess_PushWord(E_Guess *self, const string input_word) {
    if (self->words_capacity == 0) {
        self->words_capacity = 2;
        self->words = malloc(sizeof(char *) * self->words_capacity);
    } else if (self->words_count == self->words_capacity) {
        self->words_capacity *= 2;
        self->words = realloc(self->words, sizeof(char *) * self->words_capacity);
    }
    char *w = malloc(sizeof(char) * (strlen(input_word) + 1));
    strcpy(w, input_word);
    self->words[self->words_count] = w;
    self->words_count++;
}

void E_Guess_SetLastWord(E_Guess *self, const string word) {
    strcpy(self->last_word, word);
}

void E_Guess_CleanLastWord(E_Guess *self) {
    memset(self->last_word, 0, sizeof(self->last_word));
}

bool E_Guess_TryGetCalcOP(E_Guess *self, int *ref_index, const string code, const string word, OP_Type *op_type) {

    int index = *ref_index;
    bool is_ok = false;

    const char cur = word[0];
    char next = code[index + 1];
    char next2 = code[index + 2];

    ++index;

    if (cur == KW_DOT) {
        // .
        *op_type = OP_Type_Member;
        is_ok = true;
    } else if (cur == OP_EQUAL) {
        // =
        if (next == cur) {
            // ==
            *op_type = OP_Type_Equal;
            ++index;
            is_ok = true;
        } else {
            // =
            *op_type = OP_Type_Assign;
            is_ok = true;
        }
    } else if (cur == OP_CALC_MINUS) {
        // -
        if (next == OP_CMP_MORE) {
            // ->
            *op_type = OP_Type_MemberPointer;
            ++index;
            is_ok = true;
        } else if (cur == next) {
            // --
            // var-- or --var
            *op_type = OP_Type_Decrement;
            ++index;
            is_ok = true;
        } else if (next == OP_EQUAL) {
            // -=
            *op_type = OP_Type_Sub_Assign;
            ++index;
            is_ok = true;
        } else {
            // -
            *op_type = OP_Type_Sub;
            is_ok = true;
        }
    } else if (cur == OP_CALC_PLUS) {
        // +
        if (cur == next) {
            // ++
            // var++ or ++var
            *op_type = OP_Type_Increment;
            ++index;
            is_ok = true;
        } else if (next == OP_EQUAL) {
            // +=
            *op_type = OP_Type_Add_Assign;
            ++index;
            is_ok = true;
        } else {
            // +
            *op_type = OP_Type_Add;
            is_ok = true;
        }
    } else if (cur == OP_CALC_MULTIPLY) {
        // * *=
        // op2: ** means math `*` and pointer `*`
        if (next == OP_EQUAL) {
            // *=
            *op_type = OP_Type_Mul_Assign;
            ++index;
            is_ok = true;
        } else {
            // var * 3 or *var
            *op_type = OP_Type_MulOrPointerAccess;
            is_ok = true;
        }
    } else if (cur == OP_CALC_DIVIDE) {
        // /
        if (next == cur) {
            // //
            *op_type = OP_Type_Comment;
            ++index;
            is_ok = true;
        }
        if (next == OP_EQUAL) {
            // /=
            *op_type = OP_Type_Div_Assign;
            ++index;
            is_ok = true;
        } else {
            // /
            *op_type = OP_Type_Div;
            is_ok = true;
        }
    } else if (cur == OP_CALC_MOD) {
        if (next == OP_EQUAL) {
            // %=
            *op_type = OP_Type_Mod_Assign;
            ++index;
            is_ok = true;
        } else {
            // %
            *op_type = OP_Type_Mod;
            is_ok = true;
        }
    } else if (cur == OP_CALC_BIN_AND) {
        if (next == cur) {
            // &&
            *op_type = OP_Type_Logic_And;
            ++index;
            is_ok = true;
        } else if (next == OP_EQUAL) {
            // &=
            *op_type = OP_Type_Bin_And_Assign;
            ++index;
            is_ok = true;
        } else {
            // &
            *op_type = OP_Type_Bin_AndOrAddressAccess;
            is_ok = true;
        }
    } else if (cur == OP_Type_Bin_Or) {
        if (next == cur) {
            // ||
            *op_type = OP_Type_Logic_Or;
            ++index;
            is_ok = true;
        } else if (next == OP_EQUAL) {
            // |=
            *op_type = OP_Type_Bin_Or_Assign;
            ++index;
            is_ok = true;
        } else {
            // |
            *op_type = OP_Type_Bin_Or;
            is_ok = true;
        }
    } else if (cur == OP_CALC_BIN_XOR) {
        if (next == OP_EQUAL) {
            // ^=
            *op_type = OP_Type_Bin_Xor_Assign;
            ++index;
            is_ok = true;
        } else {
            // ^
            *op_type = OP_Type_Bin_Xor;
            is_ok = true;
        }
    } else if (cur == OP_CALC_BIN_NOT) {
        if (next == OP_EQUAL) {
            // ~=
            *op_type = OP_Type_Bin_Not_Assign;
            ++index;
            is_ok = true;
        } else {
            // ~
            *op_type = OP_Type_Bin_Not;
            is_ok = true;
        }
    } else if (cur == OP_CMP_LESS) {
        if (next == cur) {
            if (next2 == OP_EQUAL) {
                // <<=
                *op_type = OP_Type_Bin_Move_Left_Assign;
                index += 2;
                is_ok = true;
            } else {
                // <<
                *op_type = OP_Type_Bin_Move_Left;
                ++index;
                is_ok = true;
            }
        } else if (next == OP_EQUAL) {
            // <=
            *op_type = OP_Type_Less_Equal;
            ++index;
            is_ok = true;
        } else {
            // <
            *op_type = OP_Type_Less;
            is_ok = true;
        }
    } else if (cur == OP_CMP_GREATER) {
        if (next == cur) {
            if (next2 == OP_EQUAL) {
                // >>=
                *op_type = OP_Type_Bin_Move_Right_Assign;
                index += 2;
                is_ok = true;
            } else {
                // >>
                *op_type = OP_Type_Bin_Move_Right;
                ++index;
                is_ok = true;
            }
        } else if (next == OP_EQUAL) {
            *op_type = OP_Type_Greater_Equal;
            ++index;
            is_ok = true;
        } else {
            // >
            *op_type = OP_Type_Greater;
            is_ok = true;
        }
    } else if (cur == OP_Type_Logic_Not) {
        if (next == OP_EQUAL) {
            // !=
            *op_type = OP_Type_Not_Equal;
            ++index;
            is_ok = true;
        } else {
            // !
            *op_type = OP_Type_Logic_Not;
            is_ok = true;
        }
    } else if (cur == KW_LEFT_SQUARE_BRACKET) {
        // [
        *op_type = OP_Type_Bracket;
        is_ok = true;
    } else if (cur == KW_SEMICOLON) {
        // ;
        *op_type = OP_Type_End;
        is_ok = true;
    }

    *ref_index = index;
    return is_ok;
}