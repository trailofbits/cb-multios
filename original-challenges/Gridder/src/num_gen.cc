/*
 * Copyright (c) 2016 Kaprica Security, Inc.
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
#include "num_gen.h"
#include <cstdio.h>

NumGen::NumGen(unsigned char *pool)
{
    rand_pool_ = pool;
    rand_idx_ = 0;
    cache_len_ = 0;
    nums_available_ = NUM_CELLS;
    for (int i = 0; i < NUM_CELLS; i++)
        numbers_[i] = UNUSED;
}

int NumGen::GetRandomNumber()
{
    if (!nums_available_)
        return 0;

    unsigned char rand = rand_pool_[rand_idx_++] % NUM_CELLS;
    rand_idx_ %= POOL_SIZE;

    for (int i = 0; i < NUM_CELLS; i++)
    {
        int idx = (rand + i) % NUM_CELLS;
        if (numbers_[idx] == UNUSED)
        {
            numbers_[idx] = USED;
            --nums_available_;
            return idx+1;
        }
    }

    return 0;
}

bool NumGen::ReinstateNumber(int number)
{
    --number;
    if (numbers_[number] == USED)
    {
        numbers_[number] = UNUSED;
        ++nums_available_;
        return true;
    }
    return false;
}

void NumGen::CacheNumber(int number)
{
    cached_numbers_[cache_len_++] = number;
}

void NumGen::FlushCache(int flush_count)
{
    flush_count = flush_count > cache_len_ ? cache_len_ : flush_count;

    for (int i = 1; i <= flush_count; i++)
        ReinstateNumber(cached_numbers_[cache_len_ - i]);

    cache_len_ -= flush_count;
}

void NumGen::Reset()
{
    cache_len_ = 0;
    nums_available_ = NUM_CELLS;
    for (int i = 0; i < NUM_CELLS; i++)
        numbers_[i] = UNUSED;
}

int NumGen::AvailableNumbers()
{
    return nums_available_;
}
