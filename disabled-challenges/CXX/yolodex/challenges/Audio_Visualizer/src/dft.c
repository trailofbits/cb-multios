/*
 * Author: Sagar Momin <sagar.momin@kapricasecurity.com>
 *
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

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_dft.h"

static complex_t *cgc_cfft(complex_t *coeff, unsigned int samples) {
    const double PI = cgc_atan2(1, 1) * 4;
    double theta, cos_val, sin_val;
    if (samples == 1) {
        complex_t *xk = cgc_malloc(sizeof(complex_t));
        xk->real = coeff[0].real;
        xk->imag = coeff[0].imag;
        return xk;
    }

    complex_t *e = cgc_malloc(sizeof(complex_t) * samples/2);
    complex_t *o = cgc_malloc(sizeof(complex_t) * samples/2);

    int k =0;
    for (k = 0; k < samples/2; k++) {
        e[k] = coeff[(2*k)];
        o[k] = coeff[(2*k) + 1];
    }
    complex_t *ek = cgc_cfft(e, samples/2);
    complex_t *ok = cgc_cfft(o, samples/2);

    complex_t *Xk = cgc_malloc(sizeof(complex_t) * samples);
    for (k = 0; k < samples/2; k++) {
        theta = (2 * PI * k ) / (double)(samples);
        cos_val = cgc_cos(theta);
        sin_val = cgc_sin(theta);

        Xk[k].real = ek[k].real + ok[k].real * cos_val + ok[k].imag * sin_val;
        Xk[k].imag = ek[k].imag + -ok[k].real * sin_val + ok[k].imag * cos_val;

        Xk[k + samples/2].real = ek[k].real - (ok[k].real * cos_val + ok[k].imag * sin_val);
        Xk[k + samples/2].imag = ek[k].imag - (-ok[k].real * sin_val + ok[k].imag * cos_val);
    }

    cgc_free(e);
    cgc_free(o);
    cgc_free(ek);
    cgc_free(ok);

    return Xk;
}

static complex_t *cgc_fft(double *real_coeff, unsigned int samples) {
    complex_t *coeff = cgc_malloc(sizeof(complex_t) * samples);
    complex_t *Xk = NULL;

    int i;
    for (i = 0; i < samples; i++) {
        coeff[i].real = real_coeff[i];
        coeff[i].imag = 0;
    }

    Xk = cgc_cfft(coeff, samples);
    cgc_free(coeff);

    return Xk;
}

complex_t *cgc_dft(double *real_coeff, unsigned int samples, int *len) {
    int p_of_2 = cgc_log2(samples);
    complex_t *Xk = NULL;

    if ((1 << p_of_2) != samples) {
        unsigned int orig_samples = samples;
        double *real_coeff_padded = NULL;
        samples = 1 << (p_of_2 + 1);

        real_coeff_padded = cgc_malloc(sizeof(double) * samples);
        if(real_coeff_padded == NULL) {
            *len = 0;
            return NULL;
        }

        cgc_memset(real_coeff_padded, 0, sizeof(double) * samples);
        cgc_memcpy(real_coeff_padded, real_coeff, sizeof(double) * orig_samples);

        Xk = cgc_fft(real_coeff_padded, samples);
        cgc_free(real_coeff_padded);
    } else {
        Xk = cgc_fft(real_coeff, samples);
    }

    *len = samples;
    return Xk;
}

double *cgc_idft(complex_t *coeff, unsigned int samples, int *len) {
    int p_of_2 = cgc_log2(samples);
    complex_t *xt = NULL;
    double *Xt = NULL;
    int i;

    // conjugate complex number
    for (i = 0; i < samples; i++)
        coeff[i].imag = -coeff[i].imag;

    if ((1 << p_of_2) != samples) {
        unsigned int orig_samples = samples;
        complex_t *coeff_padded = NULL;
        samples = 1 << (p_of_2 + 1);

        coeff_padded = cgc_malloc(sizeof(complex_t) * samples);
        if(coeff_padded == NULL) {
            for (i = 0; i < samples; i++)
                coeff[i].imag = -coeff[i].imag;

            *len = 0;
            return NULL;
        }

        cgc_memset(coeff_padded, 0, sizeof(complex_t) * samples);
        cgc_memcpy(coeff_padded, coeff, sizeof(complex_t) * orig_samples);

        xt = cgc_cfft(coeff_padded, samples);
        cgc_free(coeff_padded);
    } else {
        xt = cgc_cfft(coeff, samples);
    }

    // conjugate complex number back
    for (i = 0; i < samples; i++)
        coeff[i].imag = -coeff[i].imag;

    if (xt == NULL)
        return NULL;

    Xt = cgc_malloc(sizeof(double) * samples);
    if (Xt == NULL) {
        cgc_free(xt);
        *len = 0;
        return NULL;
    }

    for (i = 0; i < samples; i++)
        Xt[i] = xt[i].real / samples; //scaling

    cgc_free(xt);
    *len = samples;
    return Xt;
}
