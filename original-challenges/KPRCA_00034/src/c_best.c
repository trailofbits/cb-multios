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
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "codes.h"

#define N 8

typedef struct {
    uint8_t K1[(N + 1) * 8];
    uint8_t K2[(N + 1) * 8];
} best_priv_t;

static const uint8_t Kconst[(N + 1) * 8 * 2] = {
    183, 110, 37, 220, 147, 74, 1, 184, 111, 38, 221, 148, 75, 2, 185, 112, 39, 222, 149, 76, 3, 186, 113, 40, 223, 150, 77, 4, 187, 114, 41, 224, 151, 78, 5, 188, 115, 42, 225, 152, 79, 6, 189, 116, 43, 226, 153, 80, 7, 190, 117, 44, 227, 154, 81, 8, 191, 118, 45, 228, 155, 82, 9, 192, 119, 46, 229, 156, 83, 10, 193, 120, 47, 230, 157, 84, 11, 194, 121, 48, 231, 158, 85, 12, 195, 122, 49, 232, 159, 86, 13, 196, 123, 50, 233, 160, 87, 14, 197, 124, 51, 234, 161, 88, 15, 198, 125, 52, 235, 162, 89, 16, 199, 126, 53, 236, 163, 90, 17, 200, 127, 54, 237, 164, 91, 18, 201, 128, 55, 238, 165, 92, 19, 202, 129, 56, 239, 166, 93, 20, 203, 130, 57, 240
};

static const uint8_t S[256] = {
    1, 91, 57, 47, 165, 109, 153, 45, 240, 252, 59, 229, 22, 203, 226, 6, 32, 85, 25, 219, 140, 147, 13, 155, 227, 97, 89, 132, 190, 71, 36, 192, 253, 150, 29, 69, 111, 78, 159, 77, 68, 20, 21, 112, 169, 216, 124, 233, 129, 174, 157, 152, 211, 183, 205, 151, 120, 126, 158, 243, 11, 230, 113, 3, 16, 171, 141, 238, 70, 202, 135, 206, 242, 177, 173, 66, 95, 164, 18, 96, 255, 75, 143, 163, 184, 39, 208, 167, 34, 10, 139, 56, 213, 108, 62, 245, 193, 87, 207, 76, 234, 220, 231, 204, 60, 63, 79, 250, 134, 115, 185, 130, 8, 214, 199, 119, 35, 101, 196, 103, 121, 217, 215, 33, 176, 82, 9, 48, 0, 166, 200, 210, 92, 148, 104, 212, 17, 5, 198, 28, 235, 54, 31, 251, 225, 172, 232, 38, 117, 110, 244, 102, 30, 160, 168, 125, 67, 186, 221, 65, 4, 107, 228, 188, 146, 179, 98, 180, 189, 237, 236, 145, 88, 41, 133, 24, 128, 83, 100, 105, 46, 74, 52, 106, 137, 131, 99, 14, 246, 27, 144, 254, 241, 86, 116, 19, 187, 55, 122, 51, 15, 80, 84, 191, 162, 93, 239, 161, 2, 182, 114, 94, 73, 218, 49, 90, 223, 247, 118, 201, 44, 149, 195, 12, 64, 170, 50, 181, 23, 37, 26, 53, 197, 194, 178, 7, 123, 142, 72, 127, 249, 43, 58, 138, 222, 156, 61, 154, 136, 40, 42, 224, 81, 175, 248, 209
};

static const uint8_t Si[256] = {
    128, 0, 208, 63, 160, 137, 15, 235, 112, 126, 89, 60, 223, 22, 187, 200, 64, 136, 78, 195, 41, 42, 12, 228, 175, 18, 230, 189, 139, 34, 152, 142, 16, 123, 88, 116, 30, 229, 147, 85, 249, 173, 250, 241, 220, 7, 180, 3, 127, 214, 226, 199, 182, 231, 141, 197, 91, 2, 242, 10, 104, 246, 94, 105, 224, 159, 75, 156, 40, 35, 68, 29, 238, 212, 181, 81, 99, 39, 37, 106, 201, 252, 125, 177, 202, 17, 193, 97, 172, 26, 215, 1, 132, 205, 211, 76, 79, 25, 166, 186, 178, 117, 151, 119, 134, 179, 183, 161, 93, 5, 149, 36, 43, 62, 210, 109, 194, 148, 218, 115, 56, 120, 198, 236, 46, 155, 57, 239, 176, 48, 111, 185, 27, 174, 108, 70, 248, 184, 243, 90, 20, 66, 237, 82, 190, 171, 164, 21, 133, 221, 33, 55, 51, 6, 247, 23, 245, 50, 58, 38, 153, 207, 204, 83, 77, 4, 129, 87, 154, 44, 225, 65, 145, 74, 49, 253, 124, 73, 234, 165, 167, 227, 209, 53, 84, 110, 157, 196, 163, 168, 28, 203, 31, 96, 233, 222, 118, 232, 138, 114, 130, 219, 69, 13, 103, 54, 71, 98, 86, 255, 131, 52, 135, 92, 113, 122, 45, 121, 213, 19, 101, 158, 244, 216, 251, 144, 14, 24, 162, 11, 61, 102, 146, 47, 100, 140, 170, 169, 67, 206, 8, 192, 72, 59, 150, 95, 188, 217, 254, 240, 107, 143, 9, 32, 191, 80
};

static inline uint8_t rot3(uint8_t x)
{
    return (x << 3) | (x >> 5);
}

static void /*inline void __attribute__((always_inline))*/ R(const uint8_t *K1, const uint8_t *K2, uint8_t *b)
{
#define XOR(n) b[n] = S[(uint8_t)(b[n] ^ K1[n])] + K2[n];
#define ADD(n) b[n] = Si[(uint8_t)(b[n] + K1[n])] ^ K2[n];
    XOR(0)
    ADD(1)
    ADD(2)
    XOR(3)
    XOR(4)
    ADD(5)
    ADD(6)
    XOR(7)
#undef XOR
#undef ADD

#define MIX(n, m) { \
    uint8_t t_n = 2 * b[n] + b[m]; \
    b[m] = b[n] + b[m]; \
    b[n] = t_n; \
}
#define EXCHANGE() { \
        uint8_t b1 = b[1], b2 = b[2], b3 = b[3], b4 = b[4], b5 = b[5], b6 = b[6]; \
        b[1] = b2; \
        b[2] = b4; \
        b[3] = b6; \
        b[4] = b1; \
        b[5] = b3; \
        b[6] = b5; \
}
    MIX(0, 1)
    MIX(2, 3)
    MIX(4, 5)
    MIX(6, 7)
    EXCHANGE()
    MIX(0, 1)
    MIX(2, 3)
    MIX(4, 5)
    MIX(6, 7)
    EXCHANGE()
    MIX(0, 1)
    MIX(2, 3)
    MIX(4, 5)
    MIX(6, 7)
#undef MIX
#undef EXCHANGE
}

static inline void Rd(const uint8_t *K1, const uint8_t *K2, uint8_t *b)
{
#define MIX(n, m) { \
    uint8_t t_n = b[n] - b[m]; \
    b[m] = b[m] - t_n; \
    b[n] = t_n; \
}
#define EXCHANGE() { \
        uint8_t b1 = b[1], b2 = b[2], b3 = b[3], b4 = b[4], b5 = b[5], b6 = b[6]; \
        b[1] = b4; \
        b[2] = b1; \
        b[3] = b5; \
        b[4] = b2; \
        b[5] = b6; \
        b[6] = b3; \
}
    MIX(0, 1)
    MIX(2, 3)
    MIX(4, 5)
    MIX(6, 7)
    EXCHANGE()
    MIX(0, 1)
    MIX(2, 3)
    MIX(4, 5)
    MIX(6, 7)
    EXCHANGE()
    MIX(0, 1)
    MIX(2, 3)
    MIX(4, 5)
    MIX(6, 7)
#undef MIX
#undef EXCHANGE

#define XOR(n) b[n] = Si[(uint8_t)(b[n] - K2[n])] ^ K1[n];
#define ADD(n) b[n] = S[(uint8_t)(b[n] ^ K2[n])] - K1[n];
    XOR(0)
    ADD(1)
    ADD(2)
    XOR(3)
    XOR(4)
    ADD(5)
    ADD(6)
    XOR(7)
#undef XOR
#undef ADD
}

static int best_init(code_t *code, const unsigned char *k)
{
    int i, r;
    uint8_t tmp[9];
    best_priv_t *priv;

    code->priv = priv = malloc(sizeof(best_priv_t));
    if (priv == NULL)
        return FAILURE;

    memcpy(tmp, &k[8], 8);
    tmp[8] = 0;
    for (i = 0; i < 8; i++)
        tmp[8] ^= tmp[i];

    for (r = 0; r < N+1; r++)
    {
#define BYTE(x) { \
        tmp[(r + x) % 9] = rot3(tmp[(r + x) % 9]); \
        priv->K1[r * 8 + x] = tmp[(r + x) % 9] ^ Kconst[r * 8 + x]; \
}
        BYTE(0)
        BYTE(1)
        BYTE(2)
        BYTE(3)
        BYTE(4)
        BYTE(5)
        BYTE(6)
        BYTE(7)
#undef BYTE
    }

    memcpy(tmp, &k[0], 8);
    tmp[8] = 0;
    for (i = 0; i < 8; i++)
        tmp[8] ^= tmp[i];

    for (r = 0; r < N+1; r++)
    {
#define BYTE(x) { \
        tmp[(r + x) % 9] = rot3(tmp[(r + x) % 9]); \
        priv->K2[r * 8 + x] = tmp[(r + x) % 9] ^ Kconst[(N + 1 + r) * 8 + x]; \
}
        BYTE(0)
        BYTE(1)
        BYTE(2)
        BYTE(3)
        BYTE(4)
        BYTE(5)
        BYTE(6)
        BYTE(7)
#undef BYTE
    }

    return SUCCESS;
}

static void best_destroy(code_t *code)
{
    free(code->priv);
}

static int best_encode(code_t *code, unsigned char *b)
{
    int i;
    uint8_t block[8];
    best_priv_t *priv = code->priv;
    
    for (i = 0; i < sizeof(block); i++)
        block[i] = b[i];

#define ROUND(x) R(&priv->K1[x * 8], &priv->K2[x * 8], block);
    ROUND(0)
    ROUND(1)
    ROUND(2)
    ROUND(3)
    ROUND(4)
    ROUND(5)
    ROUND(6)
    ROUND(7)
#undef ROUND

    block[0] ^= priv->K1[N * 8 + 0];
    block[1] += priv->K1[N * 8 + 1];
    block[2] += priv->K1[N * 8 + 2];
    block[3] ^= priv->K1[N * 8 + 3];
    block[4] ^= priv->K1[N * 8 + 4];
    block[5] += priv->K1[N * 8 + 5];
    block[6] += priv->K1[N * 8 + 6];
    block[7] ^= priv->K1[N * 8 + 7];
    
    for (i = 0; i < sizeof(block); i++)
        b[i] = block[i];
    return SUCCESS;
}

static int best_decode(code_t *code, unsigned char *b)
{
    int i;
    uint8_t block[8];
    best_priv_t *priv = code->priv;
    
    for (i = 0; i < sizeof(block); i++)
        block[i] = b[i];

    block[0] ^= priv->K1[N * 8 + 0];
    block[1] -= priv->K1[N * 8 + 1];
    block[2] -= priv->K1[N * 8 + 2];
    block[3] ^= priv->K1[N * 8 + 3];
    block[4] ^= priv->K1[N * 8 + 4];
    block[5] -= priv->K1[N * 8 + 5];
    block[6] -= priv->K1[N * 8 + 6];
    block[7] ^= priv->K1[N * 8 + 7];

#define ROUND(x) Rd(&priv->K1[x * 8], &priv->K2[x * 8], block);
    ROUND(7)
    ROUND(6)
    ROUND(5)
    ROUND(4)
    ROUND(3)
    ROUND(2)
    ROUND(1)
    ROUND(0)
#undef ROUND
    
    for (i = 0; i < sizeof(block); i++)
        b[i] = block[i];
    return SUCCESS;
}

const code_def_t best_code = {
    .name = "BEST+",
    .type = C_BEST,
    .bsize = 64,
    .ksize = 128,
    .init = best_init,
    .destroy = best_destroy,
    .encode = best_encode,
    .decode = best_decode
};
