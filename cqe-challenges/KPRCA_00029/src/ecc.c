/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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
/*
 * --- (127, 99, 4) implementation
 * Messages are stored LSB
 */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "ecc.h"

#define M 7
#define N 127 // number of bits
#define K 99 // number of message bits
#define T 4 // number of correctable bits

const static unsigned int G = 0x1c9c26b9; // generator polynomial
const static unsigned int prim = 0x89; // primitive polynomial
static uint8_t field[N];
static uint8_t gf_index[N+1];

#define FMUL(x, y) (field[(gf_index[x] + gf_index[y]) % N])
#define FINV(x) (field[(N - gf_index[x]) % N])

void ecc_init()
{
    int i;

    for (i = 0; i < M; i++)
        field[i] = 1 << i;
    field[M] = prim ^ (1 << M);
    for (i = M+1; i < N; i++)
    {
        field[i] = field[i-1] << 1;
        if (field[i] & (1 << M))
        {
           // hard case, outside of the field
           field[i] = field[M] ^ (field[i] ^ (1 << M));
        }
    }

    // fill in gf_index table
    for (i = 0; i < N; i++)
        gf_index[field[i]] = i;
}

int ecc_encode(uint8_t *bits)
{
    int i, j;
    // clear the parity bits
    for (i = 0; i < N-K; i++)
        bits[i] = 0;
    // treat the parity bits as an LFSR in order to do polynomial division
    // the input is the message bits, configuration of the LFSR is hard-coded
    // to the generator polynomial: 11100100111000010011010111001
    // "input" into the LFSR is the XOR of the feedback and the input bit
    // afterwards, the parity bits will contain the remainder of the division
    for (i = N-1; i >= N-K; i--)
    {
        uint8_t input = bits[N-K-1] ^ bits[i];

        // shift the register
        for (j = N-K-1; j > 0; j--)
            bits[j] = bits[j-1];

        // apply polynomial
        bits[0] = 0;
        if (input)
            for (j = 0; j < N-K; j++)
                bits[j] ^= (G >> j) & 1;
    }
    return 0;
}

int ecc_decode(uint8_t *bits)
{
    int i, j, L, m, b, corrections;
    uint8_t s[2*T], C[T+1], B[T+1];

    // calculate syndromes
    for (i = 0; i < 2*T; i++)
        s[i] = 0;
    for (i = 0; i < N; i++)
    {
        if (bits[i])
            for (j = 0; j < 2*T; j++)
                s[j] ^= field[(i * (j + 1)) % N];
    }

    // Berlekamp-Massey algorithm
    memset(B, 0, sizeof(B));
    memset(C, 0, sizeof(C));
    B[0] = 1;
    C[0] = 1;
    L = 0;
    m = 1;
    b = 1;
    for (i = 0; i < 2*T; i++, m++)
    {
        uint8_t d = s[i];
        for (j = 1; j <= L; j++)
            d ^= FMUL(C[j], s[i - j]);
        if (d != 0)
        {
            uint8_t tmp[T+1];
            memcpy(tmp, C, sizeof(C));

            for (j = 0; j < T; j++)
                if (B[j])
                    C[m + j] ^= FMUL(d, FMUL(FINV(b), B[j]));

            if (2 * L <= i)
            {
                L = i + 1 - L;
                b = d;
                m = 0;
                memcpy(B, tmp, sizeof(B));
            }
        }
    }

    // Find the roots in C using Chien search
    corrections = 0;
    for (i = 0; i < N; i++)
    {
        uint8_t sum = 0;
        for (j = 0; j <= L; j++)
            sum ^= FMUL(C[j], field[(i * j) % N]);
        if (sum == 0)
        {
            // found a root, error location is inverse of i
            corrections++;
            bits[(N - i) % N] ^= 1;
        }
    }

    if (L > 2)
        fdprintf(STDERR, "\nFOUND ERRORS: %d %d\n", corrections, L);
    return corrections == L;
}
