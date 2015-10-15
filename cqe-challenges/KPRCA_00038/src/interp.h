#ifndef INTERP_H_
#define INTERP_H_

#include "dict.h"
#include "io.h"
#include "lex.h"

enum {
    VAR_NULL,
    VAR_NUMBER,
    VAR_STRING,
    VAR_ARRAY
};

typedef struct {
    struct _record_t _record;

    unsigned int type;
    union {
        struct {
            char *value;
        } v_string;
        struct {
            int value;
            char *strvalue;
        } v_number;
        struct {
            dict_t *value;
        } v_array;
    };
} var_t;

int program_run(program_t *prog, io_t *io);

#endif
