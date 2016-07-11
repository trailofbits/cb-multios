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
#include "int2str.h"


// takes an int32 and converts it to a string saved in str_buf
// str_buf must be large enough to fit the sign, number(s), and '\0'
// returns 0 on success, -1 if error due to buf_size
int int2str(char* str_buf, int buf_size, int i) {

    int idx = 0;
    int tmp;
    int digit;

    // at least fits 1 digit and '\0'
    if (buf_size < 2) {
        return -1;
    }

    if (i < 0) {
        if (buf_size < 3)
            return -1;
        str_buf[idx++] = '-';
    } else {
        i *= -1; // make i negative
    }

    // i is always 0 or negative at this point.
    tmp = i;

    // increment index in str_buf to where rightmost digit goes
    do {
        idx++;
        tmp = tmp/10;
    } while(tmp < 0);

    // see if this number will fit in the buffer
    if (idx >= buf_size)
        return -1;

    //testing
    // str_buf[0] = '0' - i;
    // str_buf[1] = '\0';

    // insert '\0'
    str_buf[idx--] = '\0';

    // move left through string, writing digits along the way
    do {
        digit = -1 * (i % 10);
        str_buf[idx--] = '0' + digit;
        i /= 10;

    } while (i < 0);

    return 0;
}
