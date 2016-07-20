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
extern "C" {
#include <string.h>
#include <stdlib.h>
}

#include "sauce.h"

namespace {
    struct sauce_lut {
        const char *name;
        int calories;
        int carbs;
    };

    sauce_lut sauces[] = {
        {"Tomato", 222, 22},
        {"Balsamic", 270, 12},
        {"Italian", 350, 15},
        {"Ceasar", 367, 29},
        {"Ranch", 450, 45},
        {"Lite Italian", 150, 11},
        {"Lite Ceasar", 250, 20},
        {"Lite Ranch", 300, 30}
    };

    sauce_lut *find_sauce_entry(const char *sauce_name)
    {
        size_t i;
        for (i = 0; i < sizeof(sauces) / sizeof(sauces[0]); i++) {
            if (strcasecmp(sauces[i].name, sauce_name) == 0)
                return &sauces[i];
        }

        return NULL;
    }

    void print_list()
    {
        size_t i;
        for (i = 0; i < sizeof(sauces) / sizeof(sauces[0]); i++)
            printf("%d. %s\n", i + 1, sauces[i].name);
    }
}

Sauce::Sauce(const char *_name, int _calories, int _carbs)
{
    name = _name;
    calories = _calories;
    carbs = _carbs;
}

Sauce::~Sauce()
{
}

Sauce *Sauce::pour_sauce(const char *sauce_name)
{
    sauce_lut *sauce_entry = find_sauce_entry(sauce_name);
    if (!sauce_entry)
        return NULL;

    return new Sauce(sauce_entry->name, sauce_entry->calories, sauce_entry->carbs);
}

void Sauce::list_options()
{
    print_list();
}
