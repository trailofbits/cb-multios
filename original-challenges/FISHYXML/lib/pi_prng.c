/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "pi_prng.h"

#define PI_TERMS_LEN 2800

typedef struct prng_data {
    int pi_terms[PI_TERMS_LEN + 1];
    int pi_idx;
    int pi_total;
    int pi_cur_set[4];
    int pi_cur_set_idx;
} prng_data;

prng_data prng;
int prng_setup = 0;


// prep the pi_terms array
void _prng_setup() {
    prng.pi_cur_set_idx = 4; // start at 4 to trigger _prng_load_four()
    prng.pi_idx = PI_TERMS_LEN;
    prng.pi_total = 0;
    for (int i = 0; i < PI_TERMS_LEN; i++) {
        prng.pi_terms[i] = 2000;
    }
}

// get the next 4 digits of pi as an int, split it into digits
int _prng_load_four() {

    int i = 0;
    int b = 0;
    int d = 0;
    int four_digit_num = 0;

    i = prng.pi_idx;
    for (;;) {
        d += prng.pi_terms[i] * 10000;
        b = 2 * i - 1;

        prng.pi_terms[i] = d % b;
        d /= b;
        i--;
        if (i == 0) break;
        d *= i;
    }

    four_digit_num = prng.pi_total + d / 10000;

    // load the next 4 digits of pi into prng.pi_cur_set[]
    prng.pi_cur_set[3] = four_digit_num % 10;
    prng.pi_cur_set[2] = (four_digit_num / 10) % 10;
    prng.pi_cur_set[1] = (four_digit_num / 100) % 10;
    prng.pi_cur_set[0] = (four_digit_num / 1000) % 10;

    // prepare for next call
    prng.pi_idx -= 14;
    prng.pi_total = d % 10000;

    return 0;
}

int prng_get_next() {

    int result = 0;

    // inital setup of values in prng struct
    if (!prng_setup) {
        _prng_setup();
        prng_setup++;
    }

    // run through 800 digits of pi, then repeat.
    if ( (prng.pi_idx <= 0) && (prng.pi_cur_set_idx > 3) ) {
        _prng_setup();
    }

    if (prng.pi_cur_set_idx > 3) {
        // load the next 4 digits
        result = _prng_load_four();
        
        // reset idx to 0 so result gets first digit.
        prng.pi_cur_set_idx = 0;
    }

    if (!result) {
        // get the next digit and increment idx
        result = prng.pi_cur_set[prng.pi_cur_set_idx++];        
    }

    return result;
}
