#include "ansi_x931_aes128.h"
#include "tiny-AES128-C/aes.h"

#include <string.h>
#include <stdlib.h>

// Some helpers for the prng
void cgc_gen_block(cgc_prng*);
void cgc_xor(const uint8_t*, const uint8_t*, uint8_t*);

/**
 * Initializes a PRNG from a given seed
 * @param prng PRNG to initialize
 * @param seed Initial state of the PRNG
 */
void cgc_init_prng(cgc_prng *prng, const cgc_aes_state *seed) {
    memset(prng, 0, sizeof(cgc_prng));
    memcpy(&prng->state, seed, sizeof(cgc_aes_state));

    // Force a new block to be generated immediately
    prng->random_idx = BLOCK_SIZE;
}

/**
 * Generates a chosen amount of random data and saves it to a buffer
 * @param prng Initial PRNG state
 * @param len  Amount of data to generate
 * @param buf  Buffer to store the data in
 */
void cgc_aes_get_bytes(cgc_prng *prng, uint32_t len, uint8_t *buf) {
    uint32_t buf_idx = 0;
    while (buf_idx < len) {
        // Generate another block of random data if needed
        if (prng->random_idx >= BLOCK_SIZE) {
            cgc_gen_block(prng);
        }

        // Copy over data until we run out of data or the end of the buffer is reached
        while (prng->random_idx < BLOCK_SIZE && buf_idx < len) {
            buf[buf_idx++] = prng->random_data[prng->random_idx++];
        }
    }
}


/**
 * XORs the first BLOCK_SIZE bytes of two buffers and saves the result in an output buffer
 * @param a   First input buffer
 * @param b   Second input buffer
 * @param buf Output buffer
 */
void cgc_xor(const uint8_t *a, const uint8_t *b, uint8_t *buf) {
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        buf[i] = a[i] ^ b[i];
    }
}

/**
 * Generates a new block of random data and stores it in the prng
 * @param prng PRNG to generate the new data for
 */
void cgc_gen_block(cgc_prng *prng) {
    // Encrypt counter value, giving the intermediate
    AES128_ECB_encrypt(prng->state.datetime, prng->state.key, prng->intermediate);

    // XOR intermediate and aes vector, encrypt the result to get the random data
    uint8_t tmp[BLOCK_SIZE];
    cgc_xor(prng->intermediate, prng->state.vec, tmp);
    AES128_ECB_encrypt(tmp, prng->state.key, prng->random_data);

    // Reset random data index
    prng->random_idx = 0;

    // XOR random data with intermediate, encrypt the result to get the new vector
    cgc_xor(prng->intermediate, prng->random_data, tmp);
    AES128_ECB_encrypt(tmp, prng->state.key, prng->state.vec);

    // Update the datetime counter
    uint8_t i = BLOCK_SIZE - 1;
    while (i >= 0) {
        ++prng->state.datetime[i];
        if (prng->state.datetime[i] != 0) break;
        i -= 1;
    }
}
