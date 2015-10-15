/*

Author: Joe Rogers <joe@cromulence.co>

Copyright (c) 2014 Cromulence LLC

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
#include <libcgc.h>
#include "stdlib.h"

unsigned int mt_state[624];
int idx = 0;

// seed the PRNG
void init_mt(unsigned int seed) {
	int i;

	mt_state[0] = seed & 0xffffffffUL;
	for (i = 1; i < 624; i++) {
		mt_state[i] = (0x6c078965 * (mt_state[i-1] ^ (mt_state[i-1] >> 30)) + i);
	}
}

// generate the state array (automatically called the first time rand_mt is called)
void gen_mt_state(void) {
	int i;
	unsigned int t;

	for (i = 0; i < 624; i++) {
		t = (mt_state[i] & 0x80000000) + (mt_state[(i+1) % 624] & 0x7fffffff);
		mt_state[i] = mt_state[(i+397) % 624] ^ (t >> 1);
		if (t % 2 != 0) {
			mt_state[i] = mt_state[i] ^ 0x9908b0df;
		}
	}
}

// generate a random unsigned int
unsigned int rand_mt(void) {
	unsigned int ret;

	if (idx == 0) {
		gen_mt_state();
	}

	ret = mt_state[idx];
	ret = ret ^ (ret >> 11);
	ret = ret ^ ((ret << 7) & 0x9d2c5680);
	ret = ret ^ ((ret << 15) & 0xefc60000);
	ret = ret ^ (ret >> 18);

	idx = (idx + 1) % 624;

	return(ret);
}
