#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"

#include "cgc_monte.h"
#include "cgc_block.h"

#define PI 3.14126535
#define CHECKS 0x1000
#define COUNTER_MAX 0x100

uint8* random_page = (uint8*)RANDOM_PAGE_ADDRESS;

float64 kajigger;
uint64 counter;

float64 splatter = 128.0;
float64 scaler = 1.0;

float64 cgc_monte_gen();
float64 cgc_kajigger_from_random_int(uint64 random_int);

void cgc_monte_initialize() {
  uint64* random_uint_page = (uint64*) random_page;
  kajigger = cgc_kajigger_from_random_int(random_uint_page[0]);
  counter = 0;
}

float64 cgc_kajigger_from_random_int(uint64 random_int) {
  return cgc_sin((float64)random_int);
}

void cgc_monte_adjust(float64 new_splatter, float64 new_scaler) {
  splatter = new_splatter;
  scaler = new_scaler;
}

float64 cgc_monte_gen_step(float64 kj, uint64 ctr, float64 spl, float64 scl) {
  float64 line = cgc_tan(cgc_sin(kj + (spl * ctr))) * (2.0 / PI);
  return (line + 1) * scl;
}

float64 cgc_monte_gen() {
  float64 result = cgc_monte_gen_step(kajigger, counter, splatter, scaler);
  counter++;
  if (counter >= COUNTER_MAX) counter = 0;

  return result;
}

uint8 cgc_monte_happy() {
  uint64 in_circle = 0;

  for (int i = 0; i < CHECKS; i++) {
    float64 x = cgc_monte_gen();
    float64 y = cgc_monte_gen();

    float64 dist = cgc_sqrt((x * x) + (y * y));

    if (dist <= 1) in_circle++;
  }

  float64 ratio = ((float64) in_circle) / ((float64)CHECKS);

  float64 diff = cgc_fabs((4 * ratio) - PI);

  float64 doubler_size = 30 * cgc_log10(1.0 / diff);
  /* cgc_printf("scl %f rat %f dif %f dbl %f\n", scaler, ratio, diff, doubler_size); */
  if (doubler_size > 254.0) return 0xff;
  if (doubler_size < 1.0) return 0;

  return (uint8) doubler_size;
}

uint8 cgc_check_random_params(float64 check_kj,
                          uint64 check_counter,
                          float64 spl,
                          float64 scl) {
  float64 existing_kajigger = kajigger;
  kajigger = check_kj;
  uint64 existing_counter = counter;
  counter = check_counter;

  float64 existing_splatter = splatter;
  float64 existing_scaler = scaler;

  splatter = spl;
  scaler = scl;
  uint8 size = cgc_monte_happy();

  counter = existing_counter;
  kajigger = existing_kajigger;
  splatter = existing_splatter;
  scaler = existing_scaler;

  return size;
}
