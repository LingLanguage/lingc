#ifndef E_STATEMENT_H__
#define E_STATEMENT_H__

#include "import.h"
#include "E_Expression.h"

typedef struct E_Statement {
    char type[RULE_STRUCT_TYPE_NAME_LEN];
    char name[RULE_VAR_NAME_LEN];
    StatementType statementType;
    E_Expression expression;
    byte belong_nested_level;
} E_Statement;

#endif