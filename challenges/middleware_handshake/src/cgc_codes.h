#ifndef CODES_H_
#define CODES_H_

#include "cgc_stdlib.h"
#include "cgc_common.h"

#define MAX_BSIZE 128
#define MAX_KSIZE 256

typedef struct {
    const struct code_def_t *def;
    void *priv;
} code_t;

typedef struct code_def_t {
    const char *name;
    int type;
    unsigned int bsize; // in bits
    unsigned int ksize; // in bits

    int (*init) (code_t *code, const unsigned char *k);
    void (*destroy) (code_t *code);
    int (*encode) (code_t *code, unsigned char *b);
    int (*decode) (code_t *code, unsigned char *b);
} code_def_t;

// type ids
enum {
    C_NULL,
    C_FAITH,
    C_COFFEE,
    C_BEST,
    C_DOLPHIN,
    C_END
};

// type declarations
extern const code_def_t cgc_null_code;
extern const code_def_t cgc_faith_code;
extern const code_def_t cgc_coffee_code;
extern const code_def_t cgc_best_code;
extern const code_def_t cgc_dolphin_code;

extern const code_def_t *codes[];

// function declarations
unsigned int cgc_codes_ksize(unsigned int id);
int cgc_codes_init(code_t *code, unsigned int id, unsigned char *k);
static inline int codes_encode(code_t *code, unsigned char *b)
{
    return code->def->encode(code, b);
}
static inline int codes_decode(code_t *code, unsigned char *b)
{
    return code->def->decode(code, b);
}

int cgc_codes_self_test();

#endif
