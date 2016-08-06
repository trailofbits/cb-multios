#ifndef RNG_H_
#define RNG_H_

typedef struct {
    const struct rng_def_t *def;
    void *priv;
} rng_t;

typedef struct rng_def_t {
    const char *name;
    unsigned int id;
    int (*init) (rng_t *rng);
    int (*get_bytes) (rng_t *rng, unsigned char *out, unsigned int cnt);
} rng_def_t;

enum {
    RNG_SYSTEM,
    RNG_LCG,
    RNG_END
};

int rng_init(rng_t *, unsigned int id);

static inline int rng_get_bytes(rng_t *rng, unsigned char *out, unsigned int cnt)
{
    return rng->def->get_bytes(rng, out, cnt);
}

#endif
