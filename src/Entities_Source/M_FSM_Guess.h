#ifndef M_FSM_GUESS_H__
#define M_FSM_GUESS_H__

#include "import.h"

typedef struct M_FSM_Guess {
    E_Guess guess;
} M_FSM_Guess;

void M_FSM_Guess_Enter(M_FSM_Guess *fsm);

#endif