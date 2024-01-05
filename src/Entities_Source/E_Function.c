#include "import.h"
#include "E_Function.h"

typedef struct {
    int id;
    int index;
    string name;
    string returns[RULE_FUNCTION_RETURN_MAX];
    byte returns_count;
    string params[RULE_FUNCTION_PARAM_MAX];
    byte params_count;
} E_Function;