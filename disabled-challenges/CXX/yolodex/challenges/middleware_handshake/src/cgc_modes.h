#ifndef MODES_H_
#define MODES_H_

#include "cgc_codes.h"

typedef struct {
    code_t *code;
    unsigned int mode;
    union {
        unsigned char xm[MAX_BSIZE / 8];
        uint64_t cm;
    } state;
} mode_t;

enum {
    MODE_NULL,
    MODE_BCM,
    MODE_XIM,
    MODE_XOM,
    MODE_END
};

int cgc_modes_init(mode_t *mode, unsigned int mode_id, code_t *code);
int cgc_modes_encode(mode_t *mode, const unsigned char *inb, unsigned int inlen, 
    unsigned char **outb, unsigned int *outlen);
int cgc_modes_decode(mode_t *mode, const unsigned char *inb, unsigned int inlen, 
    unsigned char **outb, unsigned int *outlen);

int cgc_modes_self_test();

#endif
