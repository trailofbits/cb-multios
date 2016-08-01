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
#include "pizzapie.h"
#define PIE_PREP_TIME (18 * 60)

extern "C" {
#include <stdlib.h>
}

namespace {
    unsigned char _pie_sz;
    size_t _pie_calories, _pie_carbs;
    enum {PIE_SMALL_CALORIES = 1000, PIE_MED_CALORIES = 1500, PIE_LG_CALORIES = 2300};
    enum {PIE_SMALL_CARBS = 222, PIE_MED_CARBS = 284, PIE_LG_CARBS = 356};

    inline void set_pie_size_helper(unsigned int _pie_size)
    {
        switch(_pie_size) {
        case LG:
            _pie_sz = LG;
            _pie_calories = PIE_LG_CALORIES;
            _pie_carbs = PIE_LG_CARBS;
            break;
        case MED:
            _pie_sz = MED;
            _pie_calories = PIE_MED_CALORIES;
            _pie_carbs = PIE_MED_CARBS;
            break;
        case SMALL:
        default:
            _pie_sz = SMALL;
            _pie_calories = PIE_SMALL_CALORIES;
            _pie_carbs = PIE_SMALL_CARBS;
            break;
        }
    }
}

PizzaPie::PizzaPie(unsigned char _pie_size)
{
    set_pie_size_helper(_pie_size);
    pie_size = _pie_sz;
    pie_calories = _pie_calories;
    pie_carbs = _pie_carbs;
}

PizzaPie::~PizzaPie()
{
}

int PizzaPie::get_calories()
{
    return Pizza::get_calories() + pie_calories;
}


int PizzaPie::get_carbs()
{
    return Pizza::get_carbs() + pie_carbs;
}

unsigned char PizzaPie::get_pie_size()
{
    return pie_size;
}

void PizzaPie::set_pie_size(unsigned char _pie_size)
{
    set_pie_size_helper(_pie_size);
    pie_size = _pie_sz;
    pie_calories = _pie_calories;
    pie_carbs = _pie_carbs;
}

int PizzaPie::get_prep_time()
{
    return Pizza::get_prep_time() + PIE_PREP_TIME;
}

void PizzaPie::print_pizza()
{
    const char *pizza_size = "WHOOPS";
    if (pie_size == SMALL)
        pizza_size = "SMALL";
    else if (pie_size == MED)
        pizza_size = "MEDIUM";
    else if (pie_size == LG)
        pizza_size = "LARGE";

    printf("Classic Pizza Pie, Size: %s\n", pizza_size);
    Pizza::print_pizza();
}
