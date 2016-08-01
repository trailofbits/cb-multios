#ifndef TREP_H_
#define TREP_H_
#include "state.h"

typedef enum {PARTIAL, ALL} match_type_e;

void debug_state(state_t *state);
void match(state_t *state, unsigned char *str, match_type_e match_type);
state_t *evalrpn(unsigned char *rpn);

#endif
