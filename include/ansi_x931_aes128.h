#ifndef _ANSI_X931_AES128_H_
#define _ANSI_X931_AES128_H_

#define BLOCK_SIZE 16
#include <stdint.h>

/**
 * This is the AES related info for a prng
 * A prng seed contains all of this data
 */
#pragma pack(push, 1)
typedef struct cgc_aes_state {
    uint8_t vec[BLOCK_SIZE];
    uint8_t key[BLOCK_SIZE];
    uint8_t datetime[BLOCK_SIZE];
} cgc_aes_state;
#pragma pack(pop)

typedef struct cgc_prng {
    cgc_aes_state state;
    uint8_t intermediate[BLOCK_SIZE];
    uint8_t random_data[BLOCK_SIZE];
    uint8_t random_idx;
} cgc_prng;

void cgc_init_prng(cgc_prng*, const cgc_aes_state*);
void cgc_aes_get_bytes(cgc_prng*, uint32_t, uint8_t*);
#endif
