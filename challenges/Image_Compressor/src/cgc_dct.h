#include "cgc_stdint.h"

void cgc_dct(const int8_t input[], int16_t output[], const uint8_t scaler[]);
void cgc_idct(const int16_t input[], int8_t output[], const uint8_t scaler[]);
