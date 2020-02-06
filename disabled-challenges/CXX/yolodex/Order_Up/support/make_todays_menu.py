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

from menu import Appetizer, Meal, Dessert, Menu

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
#include "malloc.h"
#include "string.h"

#include "menu.h"
#include "todays_menu.h"

/**
 * Add an appetizer to the menu.
 *
 * @param m     Menu
 * @param a     Appetizer to add to menu
 */
static void add_appetizer(Menu *m, Appetizer *a) {
    Appetizer *cur = m->appetizer_list;
    if (NULL == cur) {
        m->appetizer_list = a;
    } else {
        for (; NULL != cur->next; cur=(Appetizer *)cur->next);

        cur->next = a;
    }
}

/**
 * Add a meal to the menu.
 *
 * @param m     Menu
 * @param meal  Meal to add to menu
 */
static void add_meal(Menu *m, Meal *meal) {
    Meal *cur = m->meal_list;
    if (NULL == cur) {
        m->meal_list = meal;
    } else {
        for (; NULL != cur->next; cur=(Meal *)cur->next);

        cur->next = meal;
    }
}

/**
 * Add a dessert to the menu
 *
 * @param m     Menu
 * @param d     Dessert to add to menu
 */
static void add_dessert(Menu *m, Dessert *d) {
    Dessert *cur = m->dessert_list;
    if (NULL == cur) {
        m->dessert_list = d;
    } else {
        for (; NULL != cur->next; cur=(Dessert *)cur->next);

        cur->next = d;
    }
}

void load_menu(Menu *menu) {
    Appetizer *a = NULL;
    Meal *m = NULL;
    Dessert *d = NULL;
    const char *name = NULL;
    const char *main = NULL;
    const char *veggies = NULL;
    const char *side = NULL;

'''

C_APP_TMPL = '''    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "{0}";
    memcpy(a->name, name, strlen(name, '\\0'));
    add_appetizer(menu,a);
'''

C_MEAL_TMPL = '''    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "{0}";
    memcpy(m->name, name, strlen(name, '\\0'));
    main = "{1}";
    memcpy(m->main, main, strlen(main, '\\0'));
    veggies = "{2}";
    memcpy(m->veggies, veggies, strlen(veggies, '\\0'));
    side = "{3}";
    memcpy(m->side, side, strlen(side, '\\0'));
    add_meal(menu, m);
'''

C_DES_TMPL = '''    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "{0}";
    memcpy(d->name, name, strlen(name, '\\0'));
    add_dessert(menu,d);
'''

C_FOOT='''
}

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
from menu import Appetizer, Meal, Dessert, Menu

def get_initial_menu():
  a = []
  m = []
  d = []
'''

PY_APP_TMPL = '''  a.append(Appetizer(name="{0}"))
'''
PY_MEAL_TMPL = '''  m.append(Meal(name="{0}", main="{1}", veggie="{2}", side="{3}"))
'''
PY_DES_TMPL = '''  d.append(Dessert(name="{0}"))
'''

PY_FOOT = '''

  return Menu(appetizers=a, meals=m, desserts=d)

'''

def build(f_name, count):
    c_file_name = "{0}.c".format(f_name)
    py_file_name = "{0}.py".format(f_name)

    # generate random info
    appetizers = []
    for ap in range(count):
        appetizers.append(Appetizer())
    meals = []
    for me in range(count):
        meals.append(Meal())
    desserts = []
    for de in range(count):
        desserts.append(Dessert())

    # write out C file
    with open(c_file_name,"wb") as f:
        f.write(C_HEAD)
        for a in appetizers:
            f.write(C_APP_TMPL.format(a.name))

        for m in meals:
            f.write(C_MEAL_TMPL.format(m.name,
                                        m.main,
                                        m.veggie,
                                        m.side))

        for d in desserts:
            f.write(C_DES_TMPL.format(d.name))

        f.write(C_FOOT)

    # write out PY file
    with open(py_file_name,"wb") as f:
        f.write(PY_HEAD)
        for a in appetizers:
            f.write(PY_APP_TMPL.format(a.name))

        for m in meals:
            f.write(PY_MEAL_TMPL.format(m.name,
                                        m.main,
                                        m.veggie,
                                        m.side))

        for d in desserts:
            f.write(PY_DES_TMPL.format(d.name))

        f.write(PY_FOOT)


def main():
    build("todays_menu", 50)


if __name__=="__main__":
    main()
