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
#include "pizzabowl.h"
#define BOWL_PREP_TIME (120)

extern "C" {
#include <stdlib.h>
}

#define BREAD_CALORIES 180
#define BREAD_CARBS 26

PizzaBowl::PizzaBowl(bool _side_of_bread)
{
    side_of_bread = _side_of_bread;
}

PizzaBowl::~PizzaBowl()
{
}

void PizzaBowl::add_side_of_bread()
{
    side_of_bread = true;
}

void PizzaBowl::remove_side_of_bread()
{
    side_of_bread = false;
}

int PizzaBowl::get_calories()
{
    size_t bread_calories = side_of_bread ? BREAD_CALORIES : 0;
    return Pizza::get_calories() + bread_calories;
}


int PizzaBowl::get_carbs()
{
    size_t bread_carbs = side_of_bread ? BREAD_CARBS : 0;
    return Pizza::get_carbs() + bread_carbs;
}

int PizzaBowl::get_prep_time()
{
    return Pizza::get_prep_time() + BOWL_PREP_TIME;
}

void PizzaBowl::print_pizza()
{
    const char *bread_side = "WHOOPS";
    if (side_of_bread)
        bread_side = "Yep";
    else
        bread_side = "Nah";

    printf("The Famous Pizza Bowl. Bread on the side? - %s\n", bread_side);
    Pizza::print_pizza();
}
