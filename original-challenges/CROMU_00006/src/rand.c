#include "libc.h"
#include "rand.h"
#include "charter.h"
#include "data.h"

uint32 index = 0;
uint32 mt[624];
uint32 seeded = 0;

void seed() {
  uint32 seed_value;
  read(&seed_value, sizeof(seed_value));

  index = 0;
  mt[index] = seed_value;
  for (uint32 i = 1; i < 624; i++) {
    mt[i] = 0xffffffff & (1812433253 * 
                          (mt[i - 1] ^ (mt[i - 1] >> 30)) + 1);
  }

  seeded = 1;

  uint32 example = rand();
  transmit_all(STDOUT, (char*)(&example), 4);
}

void noise() {
  uint32 noise_qty;
  read(&noise_qty, sizeof(noise_qty));

  uint32 noise_words = noise_qty / 4;

  for (uint32 i = 0; i < noise_words; i++) {
    uint32 example = rand();
    transmit_all(STDOUT, (char*)(&example), 4);
  }
}

void replacer(data_package pack) {
  __block uint32 max = 0;
  uint32* pd = (uint32*) pack.contents;
  each(pack, ^(uint32 cur, uint32 datum){
      if (datum > max) max = datum;
    });

  each(pack, ^(uint32 cur, uint32 datum){
      if (max > 0) {
        pd[cur] = rand() % max;
      } else {
        pd[cur] = 0;
      }
    });
}

void generate_numbers();

uint32 rand() {
  if (seeded == 0) return 0;

  if (index == 0) generate_numbers();

  uint32 y = mt[index];
  y = y ^ (y >> 11);
  y = y ^ ((y << 7) & 0x9d2c5680);
  y = y ^ ((y << 15) & 0xefc60000);
  y = y ^ (y >> 18);

  index = (index + 1) % 624;

  return y;
}

void generate_numbers() {
  for (uint32 i = 0; i < 624; i++) {
    uint32 y = (mt[i] & 0x80000000 +
         (mt[(i + 1) % 624] & (0x7fffffff)));
    mt[i] = mt[(i + 397) % 624] ^ (y >> 1);
    if (y % 2 == 1) mt[i] = mt[i] ^ 0x9908b0df;
  }
}
