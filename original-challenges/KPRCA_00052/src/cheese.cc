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
};

#include "cheese.h"

namespace {
    struct cheese_lut {
        const char *name;
        int calories;
        int carbs;
    };

    cheese_lut cheeses[] = {
        {"Mozzarella", 460, 26},
        {"Cheddar", 330, 19},
        {"Parmesan", 280, 16},
        {"Monterey", 380, 21},
        {"Provolone", 350, 22},
        {"Romano", 250, 18},
    };

    cheese_lut *find_cheese_entry(const char *cheese_name)
    {
        size_t i;
        for (i = 0; i < sizeof(cheeses) / sizeof(cheeses[0]); i++) {
            if (strcasecmp(cheeses[i].name, cheese_name) == 0)
                return &cheeses[i];
        }

        return NULL;
    }

    void print_list()
    {
        size_t i;
        for (i = 0; i < sizeof(cheeses) / sizeof(cheeses[0]); i++)
            printf("%d. %s\n", i + 1, cheeses[i].name);
    }
}

Cheese::Cheese(const char *_name, int _calories, int _carbs)
{
    name = _name;
    calories = _calories;
    carbs = _carbs;
}

Cheese::~Cheese()
{
}

Cheese *Cheese::select_cheese(const char *cheese_name)
{
    cheese_lut *cheese_entry = find_cheese_entry(cheese_name);
    if (!cheese_entry)
        return NULL;

    return new Cheese(cheese_entry->name, cheese_entry->calories, cheese_entry->carbs);
}

void Cheese::list_options()
{
    print_list();
}
