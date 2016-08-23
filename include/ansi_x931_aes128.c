#include "ansi_x931_aes128.h"
#include "tiny-AES128-C/aes.h"

#include <string.h>
#include <stdlib.h>

// TODO: CROSS PLATFORM?

// Some helpers for the prng
void __cgc_gen_block(cgc_prng*);
void __cgc_xor(const uint8_t*, const uint8_t*, uint8_t*);

/**
 * Initializes a PRNG from a given seed
 * @param  seed Initial state of the PRNG
 * @return      Generated PRNG
 */
cgc_prng cgc_init_prng(const uint8_t *seed) {
    cgc_prng prng;
    memcpy(&prng.state, seed, sizeof(cgc_aes_state));
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        prng.random_data[i] = '\x00';
        prng.intermediate[i] = '\x00';
    }

    // Force a new block to be generated immediately
    prng.random_idx = BLOCK_SIZE;

    return prng;
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
            __cgc_gen_block(prng);
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
void __cgc_xor(const uint8_t *a, const uint8_t *b, uint8_t *buf) {
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        buf[i] = a[i] ^ b[i];
    }
}

/**
 * Generates a new block of random data and stores it in the prng
 * @param prng PRNG to generate the new data for
 */
void __cgc_gen_block(cgc_prng *prng) {
    // Encrypt counter value, giving the intermediate
    AES128_ECB_encrypt(prng->state.datetime, prng->state.key, prng->intermediate);

    // XOR intermediate and aes vector, encrypt the result to get the random data
    uint8_t tmp[16];
    __cgc_xor(prng->intermediate, prng->state.vec, tmp);
    AES128_ECB_encrypt(tmp, prng->state.key, prng->random_data);

    // Reset random data index
    prng->random_idx = 0;

    // XOR random data with intermediate, encrypt the result to get the new vector
    __cgc_xor(prng->intermediate, prng->random_data, tmp);
    AES128_ECB_encrypt(tmp, prng->state.key, prng->state.vec);

    // Update the datetime counter
    uint8_t i = BLOCK_SIZE - 1;
    while (i >= 0) {
        ++prng->state.datetime[i];
        if (prng->state.datetime[i] != 0) break;
        i -= 1;
    }
}
