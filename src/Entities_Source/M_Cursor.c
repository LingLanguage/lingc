#include "M_Cursor.h"

void M_Cursor_InitAccess(M_Cursor *self) {

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

void M_Cursor_SetAcceess(M_Cursor *self, const string access) {
    if (strlen(self->access) > 1) {
        PFailed(self->file, self->line, ERR_ACCESS_REDIFINED);
        return;
    }
    strcpy(self->access, String_ValidAccess(access));
}

void M_Cursor_PushWord(M_Cursor *self, const string input_word) {
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

void M_Cursor_SetLastWord(M_Cursor *self, const string word) {
    strcpy(self->last_word, word);
}

void M_Cursor_CleanLastWord(M_Cursor *self) {
    memset(self->last_word, 0, sizeof(self->last_word));
}

bool M_Cursor_TryGetAssignOP(M_Cursor *self, const string code, const string word, char *op) {
    // word is '='
    char next = code[self->index + 1];
    char prev1 = code[self->index - 1];
    char prev2 = code[self->index - 2];

    // false: ==
    if (next == OP_EQUAL) {
        return false;
    }

    // true: <<= >>=
    if (prev1 == prev2 && (prev1 == OP_CMP_LESS || prev1 == OP_CMP_GREATER)) {
        op[0] = prev2;
        op[1] = prev1;
        op[2] = '=';
        op[3] = '\0';
        return true;
    }

    // true: += -= *= /= %= ~= &= |= ^=
    switch (prev1) {
    case OP_CALC_PLUS:     // +=
    case OP_CALC_MINUS:    // -=
    case OP_CALC_MULTIPLY: // *=
    case OP_CALC_DIVIDE:   // /=
    case OP_CALC_MOD:      // %=
    case OP_CALC_BIN_NOT:  // ~=
    case OP_CALC_BIN_AND:  // &=
    case OP_CALC_BIN_OR:   // |=
    case OP_CALC_BIN_XOR:  // ^=
        op[0] = prev1;
        op[1] = '=';
        op[2] = '\0';
        return true;
    }

    // true: =
    op[0] = OP_EQUAL;
    op[1] = '\0';
    return true;
}

bool M_Cursor_TryGetCalcOP(M_Cursor *self, const string code, const string word, const string last_word, OP_Type *op_type) {
    const char cur = word[0];
    char next = code[self->index + 1];
    char next2 = code[self->index + 2];

    // .
    if (cur == KW_DOT) {
        *op_type = OP_Type_Member;
        return true;
    }

    // =
    if (cur == OP_EQUAL) {
        // ==
        if (next ==cur) {
            *op_type = OP_Type_Equal;
            ++self->index;
            return true;
        }
        // =
        *op_type = OP_Type_Assign;
        return true;
    }

    // op2: - -> -- -=
    if (cur == OP_CALC_MINUS) {
        // ->
        if (next == OP_CMP_MORE) {
            *op_type = OP_Type_MemberPointer;
            ++self->index;
            return true;
        }
        // --
        if (cur == next) {
            // var-- or --var
            *op_type = OP_Type_Decrement;
            ++self->index;
            return true;
        }
        // -=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Sub_Assign;
            ++self->index;
            return true;
        }
        // -
        *op_type = OP_Type_Sub;
        return true;
    }

    // op2: + ++ +=
    if (cur == OP_CALC_PLUS) {
        // ++
        if (cur == next) {
            // var++ or ++var
            *op_type = OP_Type_Increment;
            ++self->index;
            return true;
        }
        // +=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Add_Assign;
            ++self->index;
            return true;
        }
        // +
        *op_type = OP_Type_Add;
        return true;
    }

    // * *=
    // op2: ** means math `*` and pointer `*`
    if (cur == OP_CALC_MULTIPLY) {
        // *=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Mul_Assign;
            ++self->index;
            return true;
        }
        // var * 3 or *var
        *op_type = OP_Type_MulOrPointerAccess;
        return true;
    }

    // /
    if (cur == OP_CALC_DIVIDE) {
        // //
        if (next == cur) {
            *op_type = OP_Type_Comment;
            ++self->index;
            return true;
        }
        // /=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Div_Assign;
            ++self->index;
            return true;
        }
        // /
        *op_type = OP_Type_Div;
        return true;
    }

    // %
    if (cur == OP_CALC_MOD) {
        // %=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Mod_Assign;
            ++self->index;
            return true;
        }
        // %
        *op_type = OP_Type_Mod;
        return true;
    }

    // &
    if (cur == OP_CALC_BIN_AND) {
        // &&
        if (next == cur) {
            *op_type = OP_Type_Logic_And;
            ++self->index;
            return true;
        }
        // &=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Bin_And_Assign;
            ++self->index;
            return true;
        }
        // &
        *op_type = OP_Type_Bin_AndOrAddressAccess;
        return true;
    }

    // |
    if (cur == OP_Type_Bin_Or) {
        // ||
        if (next == cur) {
            *op_type = OP_Type_Logic_Or;
            ++self->index;
            return true;
        }
        // |=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Bin_Or_Assign;
            ++self->index;
            return true;
        }
        // |
        *op_type = OP_Type_Bin_Or;
        return true;
    }

    // ^
    if (cur == OP_CALC_BIN_XOR) {
        // ^=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Bin_Xor_Assign;
            ++self->index;
            return true;
        }
        // ^
        *op_type = OP_Type_Bin_Xor;
        return true;
    }

    // ~
    if (cur == OP_CALC_BIN_NOT) {
        // ~=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Bin_Not_Assign;
            ++self->index;
            return true;
        }
        // ~
        *op_type = OP_Type_Bin_Not;
        return true;
    }

    // <
    if (cur == OP_CMP_LESS) {
        if (next == cur) {
            // <<=
            if (next2 == OP_EQUAL) {
                *op_type = OP_Type_Bin_Move_Left_Assign;
                self->index += 2;
                return true;
            }
            // <<
            *op_type = OP_Type_Bin_Move_Left;
            ++self->index;
            return true;
        }
        // <=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Less_Equal;
            ++self->index;
            return true;
        }
        // <
        *op_type = OP_Type_Less;
        return true;
    }

    // >
    if (cur == OP_CMP_GREATER) {
        if (next == cur) {
            // >>=
            if (next2 == OP_EQUAL) {
                *op_type = OP_Type_Bin_Move_Right_Assign;
                self->index += 2;
                return true;
            }
            // >>
            *op_type = OP_Type_Bin_Move_Right;
            ++self->index;
            return true;
        }
        // >=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Greater_Equal;
            ++self->index;
            return true;
        }
        // >
        *op_type = OP_Type_Greater;
        return true;
    }

    // !
    if (cur == OP_Type_Logic_Not) {
        // !=
        if (next == OP_EQUAL) {
            *op_type = OP_Type_Not_Equal;
            ++self->index;
            return true;
        }
        // !
        *op_type = OP_Type_Logic_Not;
        return true;
    }

    // [
    if (cur == KW_LEFT_SQUARE_BRACKET) {
        *op_type = OP_Type_Bracket;
        return true;
    }

    return false;

}