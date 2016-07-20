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
#include <stdlib.h>
#include <string.h>
}

#include "veggie.h"

namespace {
    struct veggie_lut {
        const char *name;
        int calories;
        int carbs;
    };

    veggie_lut veggies[] = {
        {"Mushrooms", 40, 6},
        {"Onions", 22, 7},
        {"Olives", 70, 11},
        {"Tomatoes", 30, 5},
        {"Green Peppers", 24, 3},
        {"Red Peppers", 28, 5},
        {"Spinach", 33, 4},
        {"Arugula", 37, 6}
    };

    veggie_lut *find_veggie_entry(const char *veggie_name)
    {
        size_t i;
        for (i = 0; i < sizeof(veggies) / sizeof(veggies[0]); i++) {
            if (strcasecmp(veggies[i].name, veggie_name) == 0)
                return &veggies[i];
        }

        return NULL;
    }

    void print_list()
    {
        size_t i;
        for (i = 0; i < sizeof(veggies) / sizeof(veggies[0]); i++)
            printf("%d. %s\n", i + 1, veggies[i].name);
    }
}

Veggie::Veggie(const char *_name, int _calories, int _carbs)
{
    name = _name;
    calories = _calories;
    carbs = _carbs;
}

Veggie::~Veggie()
{
}

Veggie *Veggie::pick_veggie(const char *veggie_name)
{
    veggie_lut *veggie_entry = find_veggie_entry(veggie_name);
    if (!veggie_entry)
        return NULL;

    return new Veggie(veggie_entry->name, veggie_entry->calories, veggie_entry->carbs);
}

void Veggie::list_options()
{
    print_list();
}
