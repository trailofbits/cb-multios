#include <stdint.h>

typedef struct {
    uint8_t sizes[256];
    uint16_t codes[256];
} ht_t;

void huffman_decode_table(ht_t *output, const uint8_t input[]);
