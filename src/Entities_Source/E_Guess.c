#include "E_Guess.h"

void E_Guess_Reset(E_Guess *self) {
    memset(self, 0, sizeof(E_Guess));
}

void E_Guess_SetAccess(E_Guess *self, const string file, int line, const string access) {
    if (strlen(self->access) > 1) {
        PFailed(file, line, ERR_ACCESS_REDIFINED);
        return;
    }
    strcpy(self->access, String_ValidAccess(access));
}

void E_Guess_SetReturn(E_Guess *self, const string file, int line, bool is_return) {
    if (self->is_return && is_return) {
        PFailed(file, line, ERR_FUNCTION_RETURN_REDIFINED);
        return;
    }
    self->is_return = is_return;
}

void E_Guess_PushWord(E_Guess *self, const string file, int line, const string word) {
    if (self->words_count < RULE_EXPRESSION_WORDS_COUNT) {
        strcpy(self->words[self->words_count], word);
        self->words_count++;
    } else {
        PFailed(file, line, ERR_VAR_TOO_MANY_WORDS);
    }
}

bool E_Guess_Field(E_Guess *self, const string file, int line, E_Field *field) {
    bool is_ok = true;
    if (self->words_count == 2) {
        *field = E_Field_Create(self->access, self->words[0], self->words[1]);
    } else {
        PLog("words_count:%d\r\n", self->words_count);
        PFailed(file, line, ERR_FIELD_COUNT);
        is_ok = false;
    }

    if (is_ok) {
        E_Guess_Reset(self);
    }
}

bool E_Guess_Statement(E_Guess *self, const string file, int line, byte nested_level, char *op, byte op_count, E_Statement *statement) {
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
        E_Guess_Reset(self);
    }
}

void E_Guess_ExpressionLog(const E_Guess *self) {
    // printf("%s %s:\r\n", self->access, self->is_static);
    printf("expression:");
    for (int i = 0; i < self->words_count; i++) {
        printf("%s", self->words[i]);
    }
    printf("\r\n");
}