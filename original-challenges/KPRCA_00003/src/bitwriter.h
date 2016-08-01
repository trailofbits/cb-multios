#include <stdint.h>

typedef void (*func_output)(uint8_t byte);
typedef struct {
    func_output output;
    int8_t bits;
    uint8_t partial;
} bitwriter_t;

static void bitwriter_init(bitwriter_t *bw, func_output f)
{
    bw->output = f;
    bw->bits = 0;
    bw->partial = 0;
}
void bitwriter_output(bitwriter_t *bw, uint32_t value, int8_t bits);
void bitwriter_flush(bitwriter_t *bw, uint8_t bit);
