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
    self->operator = operator;
}