#ifndef REGEXP_H_
#define REGEXP_H_

#include <stdlib.h>
#include <stdint.h>

enum {
    RFLAG_ONE = 0,
    RFLAG_ONE_OR_MORE,
    RFLAG_ZERO_OR_MORE,
    RFLAG_ZERO_OR_ONE,
    RFLAG_FREED
};

enum {
    ROP_FRONT,
    ROP_BACK,
    ROP_WILDCARD,
    ROP_SEQ,
    ROP_CLASS,
    ROP_GROUP,
    ROP_OR
};

typedef struct rop_t {
    unsigned char op, flag;
    struct rop_t *next, *parent;

    union {
        struct {
            struct rop_t *e[0];
        } r_or;
        struct {
            uint8_t data[0];
        } r_class;
        struct {
            struct rop_t *e;
        } r_group;
        struct {
            char seq;
        } r_seq;
    };
} rop_t;

typedef struct {
    char *input;
    rop_t *tree;

    rop_t **states;
    unsigned int num_states;
    unsigned int max_states;

    // loop detection (only an issue for begin and end)
    rop_t **prev_states;
    unsigned int num_prev_states;
} regexp_t;

int regexp_init(regexp_t *r, const char *str);
int regexp_free(regexp_t *r);
int regexp_match(regexp_t *r, const char *input);

#endif
