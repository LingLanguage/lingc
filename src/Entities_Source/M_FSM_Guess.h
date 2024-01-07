#ifndef M_FSM_GUESS_H__
#define M_FSM_GUESS_H__

#include "import.h"

typedef struct M_FSM_Guess {
    char access[RULE_ACCESS_NAME_LEN];
    bool is_static;
} M_FSM_Guess;

#endif