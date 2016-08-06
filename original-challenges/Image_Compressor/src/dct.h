#include <stdint.h>

void dct(const int8_t input[], int16_t output[], const uint8_t scaler[]);
void idct(const int16_t input[], int8_t output[], const uint8_t scaler[]);
