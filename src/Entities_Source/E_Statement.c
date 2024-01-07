#include "E_Statement.h"

E_Statement E_Statement_Create(const string type, const string name, StatementType statementType, byte belong_nested_level) {
    E_Statement self;
    strcpy(self.type, type);
    strcpy(self.name, name);
    self.statementType = statementType;
    self.belong_nested_level = belong_nested_level;
    return self;
}