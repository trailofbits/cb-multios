/*

Author: Bryce Kerley <bk@cromulence.co>

Copyright (c) 2014-2015 Cromulence LLC

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

#include "libcgc.h"
#include "cgc_churn.h"

churn_item gyre[CHURN_GYRE_SIZE];
cgc_size_t cgc_gyre_pos = 0;

uint64  cgc_init_one(uint64,  uint64);
float64 cgc_init_two(float64, float64);
uint64  cgc_init_thr(uint64,  uint64);
float64 cgc_init_fou(float64, float64);

void cgc_churn_initialize(churn_item* start) {
  // "zedo cat"
  churn_item cursor = {0x7a65646f20636174};
  uint64 shifter = 5;

  for (uint32 i = 0; i < (CHURN_GYRE_SIZE / CHURN_INITIALIZER_COUNT); i++) {
    uint32 s = i * 4;
    churn_item ct;

    gyre[s + 0].i = cursor.i = cgc_init_one(cursor.i ^ s, start[0].i);
    ct = cursor;
    ct.i ^= s;
    gyre[s + 1].f = cursor.f = cgc_init_two(ct.f, start[1].f);
    gyre[s + 2].i = cursor.i = cgc_init_thr(cursor.i ^ s, start[2].i);
    ct = cursor;
    ct.i ^= s;
    gyre[s + 3].f = cursor.f = cgc_init_fou(ct.f, start[3].f);
  }

  cgc_gyre_pos = 0;
}



uint64 cgc_init_one(uint64 i, uint64 j) {
  i = i ^ (j >> 21);
  i = i ^ ((j << 37) & 0x6469652068617264); // die hard
  i = i ^ ((j >> 9) & 0x6372616e6b74776f); // cranktwo
  i = i ^ (j << 50);
  return i;
}

float64 cgc_init_two(float64 i, float64 j) {
  i = cgc_fabs(cgc_sin(i)) + cgc_fabs(cgc_cos(j));
  i *= 3 + cgc_cos(i);
  i += cgc_cos(j) + cgc_cos(i);
  i *= cgc_tan(j);
  return i;
}

uint64 cgc_init_thr(uint64 i, uint64 j) {
  i = i ^ (j << 16);
  i = i ^ ((j >> 44) & 0x6578706e64626c73); // expndbls
  i = i ^ ((j << 36) & 0x636f6d6d616e646f); // commando
  i = i ^ (j >> 10);
  return i;
}

float64 cgc_init_fou(float64 i, float64 j) {
  float64 k = cgc_fabs(cgc_cos(j) / cgc_sin(i));
  j -= cgc_sin(k);
  i += cgc_log2(cgc_fabs(k));
  k += i + j;
  i -= cgc_sin(cgc_fabs(k));
  return i;
}

uint8 cgc_churn_rand_uint8() {
  uint64 candidate = cgc_churn_rand_uint64();
  uint64 selector = 8 * (candidate & 7);
  return (uint8) ((candidate >> selector) & 0xff);
}

uint32 cgc_churn_rand_uint32() {
  uint64 candidate = cgc_churn_rand_uint64();
  if ((candidate & 1) == 1) {
    return (uint32) ((candidate >> 31) & 0x00000000ffffffff);
  } else {
    return (uint32) candidate & 0x00000000ffffffff;
  }
};

uint64 cgc_churn_rand_uint64() {
  return cgc_churn_rand_item().i;
}

float64 cgc_churn_rand_float64() {
  return cgc_churn_rand_item().f;
}

churn_item cgc_churn_rand_item() {
  churn_item candidate = gyre[cgc_gyre_pos];
  churn_item replacement;
  replacement.i = cgc_init_one(candidate.i, cgc_gyre_pos);
  replacement.f = cgc_init_fou(candidate.f, replacement.f);
  gyre[cgc_gyre_pos] = replacement;
  cgc_gyre_pos = (cgc_gyre_pos + 1) % CHURN_GYRE_SIZE;

  return candidate;
}
