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
#include "pizzasub.h"
#define SUB_PREP_TIME (240)

extern "C" {
#include <stdlib.h>
}

namespace {
    unsigned char _sub_size;
    size_t _sub_calories, _sub_carbs;
    enum {SUB_REG_CALORIES = 900, SUB_LG_CALORIES = 1800};
    enum {SUB_REG_CARBS = 222, SUB_LG_CARBS = 356};

    inline void set_sub_size_helper(unsigned int _sub_sz)
    {
        switch(_sub_sz) {
        case TWELVEINCH:
            _sub_size = TWELVEINCH;
            _sub_calories = SUB_LG_CALORIES;
            _sub_carbs = SUB_LG_CARBS;
            break;
        case SIXINCH:
        default:
            _sub_size = SIXINCH;
            _sub_calories = SUB_REG_CALORIES;
            _sub_carbs = SUB_REG_CARBS;
            break;
        }
    }
}

PizzaSub::PizzaSub(unsigned char _sub_size, unsigned char _bread_type)
{
    set_sub_size_helper(_sub_size);
    sub_size = _sub_size;
    sub_calories = _sub_calories;
    sub_carbs = _sub_carbs;

    switch(_bread_type) {
    case WHITE:
    case WHEAT:
        bread_type = _bread_type; break;
    default:
        bread_type = WHITE; break;
    }
}

PizzaSub::~PizzaSub()
{
}

int PizzaSub::get_calories()
{
    return Pizza::get_calories() + sub_calories;
}


int PizzaSub::get_carbs()
{
    return Pizza::get_carbs() + sub_carbs;
}

unsigned char PizzaSub::get_sub_size()
{
    return sub_size;
}

void PizzaSub::set_sub_size(unsigned char _sub_size)
{
    set_sub_size_helper(_sub_size);
    sub_size = _sub_size;
    sub_calories = _sub_calories;
    sub_carbs = _sub_carbs;
}

int PizzaSub::get_prep_time()
{
    return Pizza::get_prep_time() + SUB_PREP_TIME;
}

void PizzaSub::print_pizza()
{
    const char *pizza_size = "WHOOPS";
    const char *pizza_bread = "WHOOPS";
    if (sub_size == SIXINCH)
        pizza_size = "6 Inch";
    else if (sub_size == TWELVEINCH)
        pizza_size = "12 Inch";

    if (bread_type == WHITE)
        pizza_bread = "White";
    else if (bread_type == WHEAT)
        pizza_bread = "Wheat";

    printf("Pizza Sub, Size: %s %s\n", pizza_size, pizza_bread);
    Pizza::print_pizza();
}
