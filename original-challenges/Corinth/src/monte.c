/*

Author: Bryce Kerley <bk@cromulence.co>

Copyright (c) 2016 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <libcgc.h>
#include <stdlib.h>
#include <stdio.h>

#include "monte.h"
#include "block.h"

#define PI 3.14126535
#define CHECKS 0x1000
#define COUNTER_MAX 0x100

uint8* random_page = (uint8*)RANDOM_PAGE_ADDRESS;

float64 kajigger;
uint64 counter;

float64 splatter = 128.0;
float64 scaler = 1.0;

float64 monte_gen();
float64 kajigger_from_random_int(uint64 random_int);

void monte_initialize() {
  uint64* random_uint_page = (uint64*) random_page;
  kajigger = kajigger_from_random_int(random_uint_page[0]);
  counter = 0;
}

float64 kajigger_from_random_int(uint64 random_int) {
  float64 cast = (float64) random_int;
  float64 sine = sin(cast);
  uint64  sine_bytes = *((uint64*)&sine);
  uint64 new_sine_bytes = sine_bytes & 0xffffffffffff0000;
  return *((float64*)&new_sine_bytes);
}

void monte_adjust(float64 new_splatter, float64 new_scaler) {
  splatter = new_splatter;
  scaler = new_scaler;
}

float64 monte_gen_step(float64 kj, uint64 ctr, float64 spl, float64 scl) {
  float64 line = tan(sin(kj + (spl * ctr))) * (2.0 / PI);
  return (line + 1) * scl;
}

float64 monte_gen() {
  float64 result = monte_gen_step(kajigger, counter, splatter, scaler);
  counter++;
  if (counter >= COUNTER_MAX) counter = 0;

  return result;
}

uint8 monte_happy() {
  uint64 in_circle = 0;

  for (int i = 0; i < CHECKS; i++) {
    float64 x = monte_gen();
    float64 y = monte_gen();

    float64 dist = sqrt((x * x) + (y * y));

    if (dist <= 1) in_circle++;
  }

  float64 ratio = ((float64) in_circle) / ((float64)CHECKS);

  float64 diff = fabs((4 * ratio) - PI);

  float64 doubler_size = 50 * log10(1.0 / diff);
  /* printf("scl %f rat %f dif %f dbl %f\n", scaler, ratio, diff, doubler_size); */
  if (doubler_size > 254.0) return 0xff;
  if (doubler_size < 1.0) return 0;

  return (uint8) doubler_size;
}

uint8 check_random_params(float64 check_kj,
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
  uint8 size = monte_happy();

  counter = existing_counter;
  kajigger = existing_kajigger;
  splatter = existing_splatter;
  scaler = existing_scaler;

  return size;
}
