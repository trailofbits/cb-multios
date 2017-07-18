#ifndef INTERP_H_
#define INTERP_H_

#include "cgc_dict.h"
#include "cgc_io.h"
#include "cgc_lex.h"

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

int cgc_program_run(program_t *prog, io_t *io);

#endif
