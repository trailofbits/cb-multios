#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

SALE_HEAD = '''/*
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
#include <libcgc.h>
#include "sale.h"

#define END_MARKER NULL

'''

SALE_FN_TMPL = '''
float __attribute__((regparm(2))) sale_{0}(unsigned int model_num, float cost) {1}
	unsigned int percent_int = {0};
	float adjustment = 1.0 - ((float)percent_int / 100.0);
	return cost * adjustment;
{2}
'''

SALE_ARRAY_HEAD = '''
float __attribute__((regparm(2))) (*onsale_fn[{0}])(unsigned int model_num, float cost) = {1}
'''
	# func0,
	# func1,
	# <funcN>,
	# func99,
SALE_ARRAY_FOOT = '''
	END_MARKER
{0};
'''

def build_c(f_name):
    sale_fn_cnt = 100
    c_file_name = "{0}.c".format(f_name)
    with open(c_file_name,"wb") as f:
        f.write(SALE_HEAD)

        sa = SALE_ARRAY_HEAD.format(sale_fn_cnt + 1, '{')

        for percent in range(sale_fn_cnt):
            f.write(SALE_FN_TMPL.format(percent, '{', '}'))
            sa += "\tsale_{0},\n".format(percent)

        sa += SALE_ARRAY_FOOT.format('}')
        f.write(sa)

def main():
    build_c("sale")
    # print SALE_FN_TMPL.format(1, '{', '}')


if __name__=="__main__":
    main()
