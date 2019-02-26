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
import support as sp

from product import Product

C_HEAD = '''/*
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
#include <stdint.h>
#include "libc.h"
#include "memcpy.h"
#include "memset.h"
#include "list.h"
#include "malloc.h"
#include "string.h"

#include "products.h"
#include "inventory.h"
#include "sale.h"

void load_inventory(Inventory *inv) {
    Product *p = NULL;
    const char *b = NULL;
    const char *d = NULL;

'''

C_FOOT='''
}

'''

C_FN_TMPL = '''    //
    p = malloc(sizeof(Product));
    MALLOC_OK(p);
    memset(p, '\\0', sizeof(Product));

    b = "{0}";
    d = "{1}";
    memcpy(p->barcode, b, strlen(b, '\\0'));
    memcpy(p->desc, d, strlen(d, '\\0'));
    p->model_num = {2};
    p->cost = {3};
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    list_insert_at_end(inv, p);
    //
'''

PY_HEAD = '''#!/usr/bin/env python
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
from product import Product

def get_initial_inventory():
  inv = []
'''

PY_FN_TMPL = '''  inv.append(Product(barcode="{0}", description="{1}", model_num={2}, cost={3}))
'''

PY_FOOT = '''
  return inv

'''

def build_c(f_name, count):
    c_file_name = "{0}.c".format(f_name)
    py_file_name = "{0}.py".format(f_name)

    products = []
    for prod in range(count):
        products.append(Product())

    with open(c_file_name,"wb") as f:
        f.write(C_HEAD)
        for p in products:
            f.write(C_FN_TMPL.format(p.barcode,
                                    p.description,
                                    p.model_num,
                                    p.cost))

        f.write(C_FOOT)

    with open(py_file_name,"wb") as f:
        f.write(PY_HEAD)
        for p in products:
            f.write(PY_FN_TMPL.format(p.barcode,
                                    p.description,
                                    p.model_num,
                                    p.cost))

        f.write(PY_FOOT)


def main():
    build_c("inventory", 64)
    # print SALE_FN_TMPL.format(1, '{', '}')


if __name__=="__main__":
    main()
