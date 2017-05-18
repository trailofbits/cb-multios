#ifndef BN_H_
#define BN_H_

#include "cgc_stdint.h"
#include "cgc_rng.h"

typedef struct {
    uint32_t *data;
    unsigned int length;
} bn_t;

void cgc_bn_init(bn_t *bn);
int cgc_bn_init_bits(bn_t *bn, unsigned int bits);
void cgc_bn_destroy(bn_t *bn);
unsigned int cgc_bn_length(const bn_t *bn);

int cgc_bn_const(bn_t *bn, uint32_t c);
int cgc_bn_copy(bn_t *bn, const bn_t *src);
int cgc_bn_from_bytes(bn_t *bn, const unsigned char *bytes, unsigned int n);
void cgc_bn_to_bytes(const bn_t *bn, unsigned char *bytes, unsigned int n);
int cgc_bn_cgc_random(bn_t *bn, const bn_t *max, rng_t *rng);

void cgc_bn_slr(bn_t *dst, unsigned int cnt);
int cgc_bn_mul(bn_t *dst, const bn_t *a, const bn_t *b);
int cgc_bn_div(bn_t *Q, bn_t *R, const bn_t *N, const bn_t *D);
int cgc_bn_modexp(bn_t *dst, const bn_t *b, const bn_t *e, const bn_t *m);

int cgc_bn_cmp(const bn_t *a, const bn_t *b);

int cgc_bn_self_test();

#endif
