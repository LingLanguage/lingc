#ifndef M_FSM_ACCESS_H__
#define M_FSM_ACCESS_H__

#include "import.h"

// Access -> static var / static fn / struct / fn / field
typedef struct M_FSM_Access {
    char access[RULE_ACCESS_NAME_LEN];
    bool isStatic;
    char words[RULE_VAR_NAME_MAX][10];
    int words_count;
} M_FSM_Access;

#endif