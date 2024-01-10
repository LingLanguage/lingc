#include "E_Guess.h"

void E_Guess_Init(E_Guess *self) {
    memset(self, 0, sizeof(E_Guess));
}

void E_Guess_SetAccess(E_Guess *self, const string file, int line, const string access) {
    if (strlen(self->access) > 1) {
        PFailed(file, line, ERR_ACCESS_REDIFINED);
        return;
    }
    strcpy(self->access, String_ValidAccess(access));
}

void E_Guess_SetConst(E_Guess *self, const string file, int line, bool is_const) {
    if (self->is_const && is_const) {
        PFailed(file, line, ERR_CONST_REDIFINED);
        return;
    }
    self->is_const = is_const;
}

void E_Guess_SetStatic(E_Guess *self, const string file, int line, bool is_static) {
    if (self->is_static && is_static) {
        PFailed(file, line, ERR_STATIC_REDIFINED);
        return;
    }
    self->is_static = is_static;
}

void E_Guess_PushWord(E_Guess *self, const string file, int line, const string word) {
    if (self->words_count < RULE_EXPRESSION_WORDS_COUNT) {
        strcpy(self->words[self->words_count], word);
        self->words_count++;
    } else {
        PFailed(file, line, ERR_VAR_TOO_MANY_WORDS);
    }
}

// ==== Guess ====
bool E_Guess_GuessStructName(E_Guess *self, const string file, int line, const string name, E_Struct *st) {
    bool is_ok = true;
    if (self->words_count == 0) {
        PFailed(file, line, ERR_STRUCT_NAME_NOT_FOUND);
        is_ok = false;
    } else if (self->words_count == 1) {
        if (self->is_const) {
            PFailed(file, line, ERR_STRUCT_CANNOT_BE_CONST);
            is_ok = false;
        } else {
            // name
            if (strlen(st->name) <= 0) {
                strcpy(st->name, self->words[0]);
            } else {
                PFailed(file, line, ERR_STRUCT_NAME_REDIFINED);
                is_ok = false;
            }
        }
    } else {
        for (int i = 0; i < self->words_count; i++) {
            printf("%s\r\n", self->words[i]);
        }
        PFailed(file, line, ERR_STRUCT_NAME_TOO_MANY_WORDS);
        is_ok = false;
    }

    if (is_ok) {
        String_CopyAccess(st->access, self->access);
        E_Guess_Init(self);
    }
    return is_ok;
}

bool E_Guess_GuessField(E_Guess *self, const string file, int line, E_Field *field) {
    bool is_ok = true;
    if (self->words_count == 2) {
        *field = E_Field_Create(self->access, self->words[0], self->words[1]);
    } else {
        PLog("words_count:%d\r\n", self->words_count);
        PFailed(file, line, ERR_FIELD_COUNT);
        is_ok = false;
    }

    if (is_ok) {
        E_Guess_Init(self);
    }
    return is_ok;
}

bool E_Guess_GuessFuctionName(E_Guess *self, const string file, int line, E_Function *func) {
    bool is_ok = true;
    if (self->is_const) {
        PFailed(file, line, ERR_FUNCTION_CANT_BE_CONST);
        is_ok = false;
    }
    if (self->words_count >= 2) {
        if (self->words_count <= RULE_FUNCTION_RETURN_COUNT) {
            // ok
            // last word is name
            strcpy(func->name, self->words[self->words_count - 1]);
            // other words are return type
            for (int i = 0; i < self->words_count - 1; i++) {
                E_Function_AddReturnType(func, self->words[i]);
            }
        } else {
            PFailed(file, line, ERR_FUNCTION_TOO_MANY_RETURN_TYPES);
        }
    } else if (self->words_count == 1) {
        PFailed(file, line, ERR_FUNCTION_TOO_FEW_RETURN_TYPES);
        is_ok = false;
    } else if (self->words_count == 0) {
        PFailed(file, line, ERR_FUNCTION_NAME_NOT_FOUND);
        is_ok = false;
    }

    if (is_ok) {
        String_CopyAccess(func->access, self->access);
        E_Guess_Init(self);
    }
    return is_ok;
}

bool E_Guess_GuessStatement(E_Guess *self, const string file, int line, byte nested_level, char *op, byte op_count, E_Statement *statement) {
    bool is_ok = true;
    if (self->words_count == 0) {
        if (self->is_const) {
            PFailed(file, line, ERR_CONST_NOT_VAR);
            is_ok = false;
        } else {
            PFailed(file, line, ERR_STATEMENT_NOT_VAR);
            is_ok = false;
        }
    }

    statement->is_const = self->is_const;
    statement->belong_nested_level = nested_level;
    if (self->words_count == 1) {
        if (op_count == 0) {
            // name;
            // err
            PFailed(file, line, ERR_VAR_NO_TYPE);
            is_ok = false;
        } else {
            // name = value;
            E_Statement_AddName(statement, self->words[0]);
        }
    } else if (self->words_count >= 2) {
        // type name = value;
        // type name1, name2 = value;
        E_Statement_SetType(statement, self->words[0]);
        for (int i = 1; i < self->words_count; i++) {
            E_Statement_AddName(statement, self->words[i]);
        }
    } else if (self->words_count > RULE_FUNCTION_RETURN_COUNT) {
        PFailed(file, line, ERR_VAR_TOO_MANY_WORDS);
        is_ok = false;
    } else {
        PFailed(file, line, ERR_UNDIFINDED_ERR);
        is_ok = false;
    }

    if (is_ok) {
        E_Guess_Init(self);
    }
    return is_ok;
}

void E_Guess_ExpressionLog(const E_Guess *self) {
    // printf("%s %s:\r\n", self->access, self->is_static);
    printf("expression:");
    for (int i = 0; i < self->words_count; i++) {
        printf("%s ", self->words[i]);
    }
    printf("\r\n");
}