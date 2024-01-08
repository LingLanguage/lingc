#include "E_Statement.h"

void E_Statement_SetType(E_Statement *self, const string type) {
    strcpy(self->type, type);
}

void E_Statement_AddName(E_Statement *self, const string name) {
    strcpy(self->names[self->names_count], name);
    self->names_count++;
}

void E_Statement_SetExpression(E_Statement *self, E_Expression expression) {
    self->expression = expression;
}

void E_Statement_SetOperator(E_Statement *self, M_Operator operator) {
    self->operator= operator;
}

void E_Statement_AddExpressionOrigin(E_Statement *self, const string word) {
    strcpy(self->expression_origin[self->expression_origin_count], word);
    self->expression_origin_count++;
}

void E_Statement_Log(const E_Statement *self) {
    char expression_origin[RULE_VAR_NAME_LEN * RULE_EXPRESSION_WORDS_COUNT];
    memset(expression_origin, 0, sizeof(expression_origin));
    for (int i = 0; i < self->expression_origin_count; i++) {
        strcat(expression_origin, self->expression_origin[i]);
        strcat(expression_origin, " ");
    }
    if (self->names_count > 0) {
        char names[RULE_VAR_NAME_LEN * RULE_FUNCTION_RETURN_COUNT];
        memset(names, 0, sizeof(names));
        for (int i = 0; i < self->names_count; i++) {
            strcat(names, self->names[i]);
            if (i < self->names_count - 1) {
                strcat(names, " ");
            }
        }
        printf("%s %s %s %s %s \r\n", self->type, names, self->operator.name, self->expression.const_value, expression_origin);
    } else {
        // return
        printf("%s\r\n", expression_origin);
    }
}