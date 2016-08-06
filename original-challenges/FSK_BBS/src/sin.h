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
#ifndef SIN_H_
#define SIN_H_

#include <stdint.h>

static int16_t sin_tab[256] = {
0, 201, 402, 603, 804, 1005, 1206, 1406, 1607, 1808, 2009, 2209, 2410, 2610, 2811, 3011,
3211, 3411, 3611, 3811, 4011, 4210, 4409, 4608, 4807, 5006, 5205, 5403, 5601, 5799, 5997, 6195,
6392, 6589, 6786, 6982, 7179, 7375, 7571, 7766, 7961, 8156, 8351, 8545, 8739, 8932, 9126, 9319,
9511, 9703, 9895, 10087, 10278, 10469, 10659, 10849, 11038, 11227, 11416, 11604, 11792, 11980, 12166, 12353,
12539, 12724, 12909, 13094, 13278, 13462, 13645, 13827, 14009, 14191, 14372, 14552, 14732, 14911, 15090, 15268,
15446, 15623, 15799, 15975, 16150, 16325, 16499, 16672, 16845, 17017, 17189, 17360, 17530, 17699, 17868, 18036,
18204, 18371, 18537, 18702, 18867, 19031, 19194, 19357, 19519, 19680, 19840, 20000, 20159, 20317, 20474, 20631,
20787, 20942, 21096, 21249, 21402, 21554, 21705, 21855, 22004, 22153, 22301, 22448, 22594, 22739, 22883, 23027,
23169, 23311, 23452, 23592, 23731, 23869, 24006, 24143, 24278, 24413, 24546, 24679, 24811, 24942, 25072, 25201,
25329, 25456, 25582, 25707, 25831, 25954, 26077, 26198, 26318, 26437, 26556, 26673, 26789, 26905, 27019, 27132,
27244, 27355, 27466, 27575, 27683, 27790, 27896, 28001, 28105, 28208, 28309, 28410, 28510, 28608, 28706, 28802,
28897, 28992, 29085, 29177, 29268, 29358, 29446, 29534, 29621, 29706, 29790, 29873, 29955, 30036, 30116, 30195,
30272, 30349, 30424, 30498, 30571, 30643, 30713, 30783, 30851, 30918, 30984, 31049, 31113, 31175, 31236, 31297,
31356, 31413, 31470, 31525, 31580, 31633, 31684, 31735, 31785, 31833, 31880, 31926, 31970, 32014, 32056, 32097,
32137, 32176, 32213, 32249, 32284, 32318, 32350, 32382, 32412, 32441, 32468, 32495, 32520, 32544, 32567, 32588,
32609, 32628, 32646, 32662, 32678, 32692, 32705, 32717, 32727, 32736, 32744, 32751, 32757, 32761, 32764, 32766
};

static int16_t fastsin(int16_t t)
{
    if (t >= 0x4000)
    {
        return sin_tab[(0x3fff - (t & 0x3FFF)) >> 6];
    }
    else if (t >= 0)
    {
        return sin_tab[(t & 0x3FFF) >> 6];
    }
    else if (t < -0x4000)
    {
        return -sin_tab[(t & 0x3FFF) >> 6];
    }
    else /* t >= -0x4000 and t < 0 */
    {
        return -sin_tab[(0x3fff - (t & 0x3FFF)) >> 6];
    }
}

#endif /* !SIN_H_ */
