#ifndef BN_H_
#define BN_H_

#include <stdint.h>
#include "rng.h"

typedef struct {
    uint32_t *data;
    unsigned int length;
} bn_t;

void bn_init(bn_t *bn);
int bn_init_bits(bn_t *bn, unsigned int bits);
void bn_destroy(bn_t *bn);
unsigned int bn_length(const bn_t *bn);

int bn_const(bn_t *bn, uint32_t c);
int bn_copy(bn_t *bn, const bn_t *src);
int bn_from_bytes(bn_t *bn, const unsigned char *bytes, unsigned int n);
void bn_to_bytes(const bn_t *bn, unsigned char *bytes, unsigned int n);
int bn_random(bn_t *bn, const bn_t *max, rng_t *rng);

void bn_slr(bn_t *dst, unsigned int cnt);
int bn_mul(bn_t *dst, const bn_t *a, const bn_t *b);
int bn_div(bn_t *Q, bn_t *R, const bn_t *N, const bn_t *D);
int bn_modexp(bn_t *dst, const bn_t *b, const bn_t *e, const bn_t *m);

int bn_cmp(const bn_t *a, const bn_t *b);

int bn_self_test();

#endif
