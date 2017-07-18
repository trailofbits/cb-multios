#ifndef KX_H_
#define KX_H_

#include "cgc_bn.h"
#include "cgc_rng.h"

typedef struct {
    bn_t P;
    bn_t Q;
    bn_t G;
    bn_t a;
    bn_t b;
    bn_t S;
} kx_t;

enum {
    KX_GROUP_1024_160,
    KX_GROUP_2048_224,
    KX_GROUP_2048_256,
    KX_GROUP_3072_3072,
    KX_GROUP_END
};

int cgc_kx_init_std(kx_t *kx, unsigned int group);
int cgc_kx_init(kx_t *kx, bn_t *P, bn_t *Q, bn_t *G);
void cgc_kx_destroy(kx_t *kx);
int cgc_kx_gen_a(kx_t *kx, rng_t *rng);
int cgc_kx_get_A(kx_t *kx, bn_t *A);
int cgc_kx_set_b(kx_t *kx, bn_t *b);
int cgc_kx_get_sk(kx_t *kx, unsigned char *out, unsigned int n);

int cgc_kx_self_test();

#endif
