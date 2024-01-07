#include "E_Guess.h"

void E_Guess_Reset(E_Guess *self) {
    memset(self, 0, sizeof(E_Guess));
}

void E_Guess_SetAccess(E_Guess *self, const string file, int line, const string access) {
    if (strlen(self->access) > 1) {
        PLogCode(file, line, ERR_REDIFINED_ACCESS);
        return;
    }
    strcpy(self->access, String_ValidAccess(access));
}

void E_Guess_PushWord(E_Guess *self, const string file, int line, const string word) {
    if (self->words_count < RULE_FUNCTION_RETURN_COUNT) {
        strcpy(self->words[self->words_count], word);
        self->words_count++;
    } else {
        PLogCode(file, line, ERR_TOO_MANY_WORDS);
    }
}

bool E_Guess_Field(E_Guess *self, const string file, int line, E_Field *field) {
    if (self->words_count == 2) {
        *field = E_Field_Create(self->access, self->words[0], self->words[1]);
        return true;
    } else {
        PLogCode(file, line, ERR_VAR_CANNOT_START_WITH_NUMBER);
        return false;
    }
}

bool E_Guess_Statement(E_Guess *self, const string file, int line, byte nested_level, E_Statement *statement) {
    if (self->words_count == 1) {
        *statement = E_Statement_Create(self->words[0], '\0', '\0', nested_level);
        return true;
    } else {
        PLogCode(file, line, ERR_VAR_CANNOT_START_WITH_NUMBER);
        return false;
    }
}