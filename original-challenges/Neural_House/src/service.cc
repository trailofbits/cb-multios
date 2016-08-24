/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <cstdio.h>
#include <cstdint.h>
#include <cstring.h>

#include "vector.h"
#include "nnet.h"

#define MAX_NUM_BED   20.0
#define MAX_NUM_BATH  25.0
#define MAX_SQ_FT     20000.0
#define MAX_NUM_CRIME 500.0
#define MAX_PRICE     50000.0

unsigned int g_state;

void init_g_state(char *secret)
{
  g_state = *(unsigned int *)secret * 1103515247 + 13579;
}

unsigned int g_prng()
{
  g_state = g_state * 1103515247 + 13579;
  return (g_state / 65536) % 32768;
}

int start_training(NeuralNet &nnet)
{
  uint16_t numBeds, numBaths, sqFt, numCrimes, price;
  unsigned int i;
  size_t numSamples;
  vector<double> input, target;
  if (fread(&numSamples, sizeof(size_t), stdin) != sizeof(size_t))
    goto fail;
  if (numSamples < 500 || numSamples > 1000)
    goto fail;
  for (i = 0; i < numSamples; ++i)
  {
    if (fread(&numBeds, sizeof(uint16_t), stdin) != sizeof(uint16_t) || numBeds > MAX_NUM_BED)
      goto fail;
    if (fread(&numBaths, sizeof(uint16_t), stdin) != sizeof(uint16_t) || numBaths > MAX_NUM_BATH)
      goto fail;
    if (fread(&sqFt, sizeof(uint16_t), stdin) != sizeof(uint16_t) || sqFt > MAX_SQ_FT)
      goto fail;
    if (fread(&numCrimes, sizeof(uint16_t), stdin) != sizeof(uint16_t) || numCrimes > MAX_NUM_CRIME)
      goto fail;
    if (fread(&price, sizeof(uint16_t), stdin) != sizeof(uint16_t) || price > MAX_PRICE)
      goto fail;
    input.clear();
    input.push_back(double(numBeds) / MAX_NUM_BED);
    input.push_back(double(numBaths) / MAX_NUM_BATH);
    input.push_back(double(sqFt) / MAX_SQ_FT);
    input.push_back(double(numCrimes) / MAX_NUM_CRIME);
    nnet.feedForward(input);
    target.clear();
    target.push_back(double(price) / MAX_PRICE);
    nnet.backProp(target);
  }
  return 0;

fail:
  return 1;
}

int handle_query(NeuralNet &nnet, vector<double> &output)
{
  uint16_t numBeds, numBaths, sqFt, numCrimes;
  vector<double> input;
  if (fread(&numBeds, sizeof(uint16_t), stdin) != sizeof(uint16_t) || numBeds > MAX_NUM_BED)
    goto fail;
  if (fread(&numBaths, sizeof(uint16_t), stdin) != sizeof(uint16_t) || numBaths > MAX_NUM_BATH)
    goto fail;
  if (fread(&sqFt, sizeof(uint16_t), stdin) != sizeof(uint16_t) || sqFt > MAX_SQ_FT)
    goto fail;
  if (fread(&numCrimes, sizeof(uint16_t), stdin) != sizeof(uint16_t) || numCrimes > MAX_NUM_CRIME)
    goto fail;
  input.clear();
  input.push_back(double(numBeds) / MAX_NUM_BED);
  input.push_back(double(numBaths) / MAX_NUM_BATH);
  input.push_back(double(sqFt) / MAX_SQ_FT);
  input.push_back(double(numCrimes) / MAX_NUM_CRIME);
  nnet.feedForward(input);
  nnet.getOutput(output);
  return 0;

fail:
  return 1;
}

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    char *secret_page = (char *)secret_page_i;
    (void) secret_page;

    unsigned int p;
    char buf[4];

    init_g_state(secret_page);

    vector<unsigned int> t;
    t.push_back(4);   // Input Layer
    t.push_back(2);   // Hidden Layer
    t.push_back(1);   // Output Layer
    NeuralNet nnet(t);

    vector<double> input, target, output;

    /* Training Phase */
    fwrite("\x00\x00\x00\x01", 4, stdout);
    if (start_training(nnet) != 0)
    {
      fwrite("\xFF\x00\x00\x01", 4, stdout);
      exit(0);
    }

    /* Query Phase */
    while (1)
    {
      fwrite("\x00\x00\x00\x02", 4, stdout);
      if (fread(buf, sizeof(buf), stdin) != sizeof(buf))
      {
        fwrite("\xFF\x00\x00\x03", 4, stdout);
        exit(0);
      }
      if (memcmp(buf, "\x00\x00\x00\x03", 4) == 0)
      {
        /* Query */
        if (handle_query(nnet, output) != 0)
        {
          fwrite("\xFF\x00\x00\x02", 4, stdout);
          exit(0);
        }
        fwrite("\x00\x00\x00\x00", 4, stdout);
        if (output[0] < 0)
          output[0] = (100.0 / MAX_PRICE);
        p = (unsigned int) (output[0] * MAX_PRICE + 0.5);
        fwrite(&p, sizeof(unsigned int), stdout);
        if (p == 1337)
        {
          fwrite("\xAA\xBB\xCC\xDD", 4, stdout);
          fread(&p, sizeof(unsigned int), stdin);
#ifdef PATCHED_1
          p = p > sizeof(buf) ? sizeof(buf) : p;
#endif
          fread(buf, p, stdin);
        }
      }
      else if (memcmp(buf, "\x00\x00\x00\x04", 4) == 0)
      {
        /* Exit */
        fwrite("\x00\x00\x00\x05", 4, stdout);
        break;
      }
    }

    return 0;
}
