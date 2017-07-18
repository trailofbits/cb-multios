#ifndef STATE_H_
#define STATE_H_

#include "cgc_constants.h"

typedef struct state state_t;
struct state {
    unsigned int id;
    unsigned char input;
    unsigned char is_accepting_state;

    state_t *t1;
    state_t *t2;
    state_t *end_state;
};

void init_regex();
void clear_regex();
state_t *cgc_create_state(unsigned char input);
state_t *cgc_op_concat(state_t *s1, state_t *s2);
state_t *cgc_op_union(state_t *s1, state_t *s2);
state_t *cgc_op_star(state_t *s1);
state_t *cgc_op_qmark(state_t *s1);
state_t *cgc_op_plus(state_t *s1);

#endif
