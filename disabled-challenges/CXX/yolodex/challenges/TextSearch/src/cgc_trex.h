#ifndef TREP_H_
#define TREP_H_
#include "cgc_state.h"

typedef enum {PARTIAL, ALL} match_type_e;

void cgc_debug_state(state_t *state);
void cgc_match(state_t *state, unsigned char *str, match_type_e match_type);
state_t *cgc_evalrpn(unsigned char *rpn);

#endif
