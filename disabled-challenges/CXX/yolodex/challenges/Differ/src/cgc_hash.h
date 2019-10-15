#ifndef HASH_H_
#define HASH_H_

typedef struct {
    unsigned int hash1;
    unsigned int hash2;
} lhash_t;

lhash_t cgc_get_lhash(char *str);

#endif
