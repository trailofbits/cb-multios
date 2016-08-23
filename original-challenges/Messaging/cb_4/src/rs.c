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
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_DEGREE 512

typedef struct {
    uint16_t degree;
    uint8_t terms[MAX_DEGREE];
} poly_t;

static uint8_t gf_exp[] = {1, 2, 4, 8, 16, 32, 64, 128, 29, 58, 116, 232, 205, 135, 19, 38, 76, 152, 45, 90, 180, 117, 234, 201, 143, 3, 6, 12, 24, 48, 96, 192, 157, 39, 78, 156, 37, 74, 148, 53, 106, 212, 181, 119, 238, 193, 159, 35, 70, 140, 5, 10, 20, 40, 80, 160, 93, 186, 105, 210, 185, 111, 222, 161, 95, 190, 97, 194, 153, 47, 94, 188, 101, 202, 137, 15, 30, 60, 120, 240, 253, 231, 211, 187, 107, 214, 177, 127, 254, 225, 223, 163, 91, 182, 113, 226, 217, 175, 67, 134, 17, 34, 68, 136, 13, 26, 52, 104, 208, 189, 103, 206, 129, 31, 62, 124, 248, 237, 199, 147, 59, 118, 236, 197, 151, 51, 102, 204, 133, 23, 46, 92, 184, 109, 218, 169, 79, 158, 33, 66, 132, 21, 42, 84, 168, 77, 154, 41, 82, 164, 85, 170, 73, 146, 57, 114, 228, 213, 183, 115, 230, 209, 191, 99, 198, 145, 63, 126, 252, 229, 215, 179, 123, 246, 241, 255, 227, 219, 171, 75, 150, 49, 98, 196, 149, 55, 110, 220, 165, 87, 174, 65, 130, 25, 50, 100, 200, 141, 7, 14, 28, 56, 112, 224, 221, 167, 83, 166, 81, 162, 89, 178, 121, 242, 249, 239, 195, 155, 43, 86, 172, 69, 138, 9, 18, 36, 72, 144, 61, 122, 244, 245, 247, 243, 251, 235, 203, 139, 11, 22, 44, 88, 176, 125, 250, 233, 207, 131, 27, 54, 108, 216, 173, 71, 142};
static uint8_t gf_log[] = {0, 0, 1, 25, 2, 50, 26, 198, 3, 223, 51, 238, 27, 104, 199, 75, 4, 100, 224, 14, 52, 141, 239, 129, 28, 193, 105, 248, 200, 8, 76, 113, 5, 138, 101, 47, 225, 36, 15, 33, 53, 147, 142, 218, 240, 18, 130, 69, 29, 181, 194, 125, 106, 39, 249, 185, 201, 154, 9, 120, 77, 228, 114, 166, 6, 191, 139, 98, 102, 221, 48, 253, 226, 152, 37, 179, 16, 145, 34, 136, 54, 208, 148, 206, 143, 150, 219, 189, 241, 210, 19, 92, 131, 56, 70, 64, 30, 66, 182, 163, 195, 72, 126, 110, 107, 58, 40, 84, 250, 133, 186, 61, 202, 94, 155, 159, 10, 21, 121, 43, 78, 212, 229, 172, 115, 243, 167, 87, 7, 112, 192, 247, 140, 128, 99, 13, 103, 74, 222, 237, 49, 197, 254, 24, 227, 165, 153, 119, 38, 184, 180, 124, 17, 68, 146, 217, 35, 32, 137, 46, 55, 63, 209, 91, 149, 188, 207, 205, 144, 135, 151, 178, 220, 252, 190, 97, 242, 86, 211, 171, 20, 42, 93, 158, 132, 60, 57, 83, 71, 109, 65, 162, 31, 45, 67, 216, 183, 123, 164, 118, 196, 23, 73, 236, 127, 12, 111, 246, 108, 161, 59, 82, 41, 157, 85, 170, 251, 96, 134, 177, 187, 204, 62, 90, 203, 89, 95, 176, 156, 169, 160, 81, 11, 245, 22, 235, 122, 117, 44, 215, 79, 174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168, 80, 88, 175};
uint8_t encoded[] = {
    191, 34, 87, 97, 205, 93, 58, 86, 72, 68, 82, 5, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static uint8_t gf_mul(uint8_t x, uint8_t y)
{
    if (x == 0 || y == 0)
        return 0;
    return gf_exp[(gf_log[x] + gf_log[y]) % 255];
}

static uint8_t gf_div(uint8_t x, uint8_t y)
{
    if (x == 0)
        return 0;
    return gf_exp[(gf_log[x] + 255 - gf_log[y]) % 255];
}

static uint8_t gf_inverse(uint8_t x)
{
    return gf_exp[(255 - gf_log[x]) % 255];
}

static uint8_t gf_poly_eval(const poly_t *poly, uint8_t x)
{
    uint8_t result = poly->terms[poly->degree - 1];
    for (int i = poly->degree - 2; i >= 0; i--)
        result = gf_mul(result, x) ^ poly->terms[i];
    return result;
}

static void gf_poly_copy(poly_t *dst, const poly_t *a)
{
    dst->degree = a->degree;
    memcpy(dst->terms, a->terms, dst->degree);
}

static void gf_poly_reduce(poly_t *dst)
{
    while (dst->degree > 0 && dst->terms[dst->degree - 1] == 0)
        dst->degree--;
}

static void gf_poly_add(poly_t *dst, poly_t *a, const poly_t *b)
{
    if (dst != a)
        gf_poly_copy(dst, a);
    for (int i = 0; i < b->degree && i < dst->degree; i++)
        dst->terms[i] ^= b->terms[i];
    for (; dst->degree < b->degree; dst->degree++)
        dst->terms[dst->degree] = b->terms[dst->degree];
}

static void gf_poly_mul(poly_t *dst, const poly_t *a, const poly_t *b)
{
    dst->degree = a->degree + b->degree - 1;
    memset(dst->terms, 0, dst->degree);

    for (int i = 0; i < a->degree; i++)
    for (int j = 0; j < b->degree; j++)
        dst->terms[i + j] ^= gf_mul(a->terms[i], b->terms[j]);
}

static void gf_poly_mul_const(poly_t *dst, poly_t *a, uint8_t c)
{
    dst->degree = a->degree;
    for (int i = 0; i < a->degree; i++)
        dst->terms[i] = gf_mul(a->terms[i], c);
}

static void rs_calc_synd(poly_t *dst, const poly_t *msg, int k)
{
    dst->degree = k;
    for (int i = 0; i < k; i++)
        dst->terms[k - 1 - i] = gf_poly_eval(msg, gf_exp[i]);
}

static void rs_calc_sigma(poly_t *dst, const poly_t *synd)
{
    int L = 0;
    poly_t T = { .degree = 1, .terms[0] = 1 };
    poly_t tmp;
    dst->degree = 1;
    dst->terms[0] = 1;

    for (int k = 0; k < synd->degree; k++)
    {
        uint8_t delta;

        // T(x) = T(x) * x
        memmove(&T.terms[1], &T.terms[0], T.degree++);
        T.terms[0] = 0;

        delta = synd->terms[synd->degree - 1 - k];
        for (int i = 1; i < dst->degree; i++)
            delta ^= gf_mul(dst->terms[i], synd->terms[synd->degree - 1 - (k - i)]);

        if (delta != 0)
        {
            gf_poly_mul_const(&tmp, &T, delta);
            if (L <= k)
            {
                L = k;
                gf_poly_mul_const(&T, dst, gf_inverse(delta));
            }
            gf_poly_add(dst, dst, &tmp);
        }
    }

    gf_poly_reduce(dst);
}

static void rs_calc_pos(poly_t *dst, const poly_t *sigma)
{
    poly_t tmp;
    dst->degree = 0;
    tmp.degree = sigma->degree;
    // terms[0] is constant
    for (int k = 1; k < sigma->degree; k++)
        tmp.terms[k] = gf_mul(sigma->terms[k], gf_exp[k]);

    for (int i = 0; i < 255; i++)
    {
        // terms[0] is constant
        uint8_t sum = 1;
        for (int k = 1; k < tmp.degree; k++)
        {
            sum ^= tmp.terms[k];
            tmp.terms[k] = gf_mul(tmp.terms[k], gf_exp[k]);
        }
        if (sum == 0)
            dst->terms[dst->degree++] = i;
    }
}

static void rs_calc_omega(poly_t *dst, const poly_t *synd, const poly_t *sigma)
{
    poly_t tmp;
    tmp.degree = synd->degree;
    for (int i = 0; i < synd->degree; i++)
        tmp.terms[i] = synd->terms[synd->degree - 1 - i];
    // S * sigma
    gf_poly_mul(dst, &tmp, sigma);
    // mod x^2t
    if (dst->degree > synd->degree)
        dst->degree = synd->degree;
    gf_poly_reduce(dst);
}

static void rs_calc_sigma_deriv(poly_t *sigma)
{
    for (int i = 0; i < sigma->degree - 1; i += 2)
    {
        sigma->terms[i] = sigma->terms[i + 1];
        sigma->terms[i + 1] = 0;
    }
    sigma->degree--;
}

#if 0
static void print_poly(poly_t *p)
{
    fprintf(stderr, "%d ", p->degree);
    for (int i = 0; i < p->degree; i++)
        fprintf(stderr, "%02x ", p->terms[i]);
    fprintf(stderr, "\n");
}
#endif

int rs_decode(uint8_t *encoded, int n_parity)
{
    poly_t tmp, synd, sigma, pos;
    memcpy(tmp.terms, encoded, 255);
    tmp.degree = 255;
    rs_calc_synd(&synd, &tmp, n_parity);

    // synd.degree must equal n_parity, e.g. don't eliminate zero terms
    rs_calc_sigma(&sigma, &synd);
    rs_calc_pos(&pos, &sigma);
    rs_calc_omega(&tmp, &synd, &sigma);
    rs_calc_sigma_deriv(&sigma);
    for (int i = 0; i < pos.degree; i++)
    {
        uint8_t x_inv = gf_inverse(gf_exp[(255 - 1 - pos.terms[i]) % 255]);
        uint8_t mag = gf_div(gf_poly_eval(&tmp, x_inv), gf_mul(x_inv, gf_poly_eval(&sigma, x_inv)));
        encoded[255 - 1 - pos.terms[i]] ^= mag;
    }

    // test result for errors
    memcpy(tmp.terms, encoded, 255);
    tmp.degree = 255;
    rs_calc_synd(&synd, &tmp, n_parity);
    gf_poly_reduce(&synd);
    // if no errors, then we succesfully decoded
    return synd.degree == 0;
}
