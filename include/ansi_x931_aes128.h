#ifndef _ANSI_X931_AES128_H_
#define _ANSI_X931_AES128_H_

#define BLOCK_SIZE 16
#include <stdint.h>

/**
 * This is the AES related info for a prng
 * A prng seed contains all of this data
 */
typedef struct cgc_aes_state {
    uint8_t vec[BLOCK_SIZE];
    uint8_t key[BLOCK_SIZE];
    uint8_t datetime[BLOCK_SIZE];
} cgc_aes_state;

typedef struct cgc_prng {
    cgc_aes_state state;
    uint8_t intermediate[BLOCK_SIZE];
    uint8_t random_data[BLOCK_SIZE];
    uint8_t random_idx;
} cgc_prng;

cgc_prng cgc_init_prng(const uint8_t*);
void cgc_aes_get_bytes(cgc_prng*, uint32_t, uint8_t*);
#endif
