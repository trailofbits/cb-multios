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
#include "meat.h"

extern "C" {
#include <string.h>
#include <stdlib.h>
};

namespace {
    struct meat_lut {
        const char *name;
        int calories;
        int carbs;
        bool is_pork;
    };

    meat_lut meats[] = {
        {"Pepperoni", 222, 22, true},
        {"All beef pepperoni", 270, 12, false},
        {"Sausage", 350, 15, true},
        {"Chicken", 367, 29, false},
        {"Jerk Pork", 450, 45, true},
        {"Ground Beef", 150, 11, false}
    };

    meat_lut *find_meat_entry(const char *meat_name)
    {
        size_t i;
        for (i = 0; i < sizeof(meats) / sizeof(meats[0]); i++) {
            if (strcasecmp(meats[i].name, meat_name) == 0)
                return &meats[i];
        }

        return NULL;
    }

    void print_list()
    {
        size_t i;
        for (i = 0; i < sizeof(meats) / sizeof(meats[0]); i++)
            printf("%d. %s\n", i + 1, meats[i].name);
    }
}

Meat::Meat(const char *_name, int _calories, int _carbs, bool _is_pork)
{
    name = _name;
    calories = _calories;
    carbs = _carbs;
    is_pork = _is_pork;
}

Meat::~Meat()
{
}

Meat *Meat::add_meat(const char *meat_name)
{
    meat_lut *meat_entry = find_meat_entry(meat_name);
    if (!meat_entry)
        return NULL;

    return new Meat(meat_entry->name, meat_entry->calories, meat_entry->carbs, meat_entry->is_pork);
}

void Meat::list_options()
{
    print_list();
}
