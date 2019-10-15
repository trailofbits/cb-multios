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
#include "cgc_pizza.h"

extern "C" {
#include "cgc_string.h"
#include "cgc_stdlib.h"
}

namespace {
    /* PRIVATE HELPER FUNCTIONS */
    void print_helper(void *_topping)
    {
        Topping *topping = (Topping*)_topping;
        cgc_printf("%s", topping->get_topping_name());
        if (topping->contains_pork())
            cgc_printf("**");
        else if(!topping->is_vegetarian())
            cgc_printf("*");
        cgc_printf("\n");
    }
}


Pizza::Pizza()
{
}

Pizza::~Pizza()
{
    Topping *topping;
    Sauce *sauce;

    while (toppings.pop(topping))
        delete topping;
    while (sauce_ots.pop(sauce))
        delete sauce;
}

bool Pizza::add_topping(Topping *topping)
{
    cgc_size_t i;
    for (i = 0; i < toppings.length(); i++)
        if (*toppings[i] == *topping)
            return false;

    return toppings.add(topping);
}

bool Pizza::remove_topping(cgc_size_t idx)
{
    return toppings.remove(idx);
}

bool Pizza::add_sauce(Sauce *sauce)
{
    return sauce_ots.add(sauce);
}

bool Pizza::remove_sauce(cgc_size_t idx)
{
    return sauce_ots.remove(idx);
}

void Pizza::print_toppings()
{
    if (toppings.is_empty())
        cgc_printf("\tNone\n");
    else
        toppings.print_list(&print_helper);
}

void Pizza::print_sauces()
{
    if (sauce_ots.is_empty())
        cgc_printf("\tNone\n");
    else
        sauce_ots.print_list(&print_helper);
}

cgc_size_t Pizza::get_num_toppings()
{
    return toppings.length();
}

cgc_size_t Pizza::get_num_sauces()
{
    return sauce_ots.length();
}

void Pizza::print_pizza()
{
    cgc_printf("    Selected Toppings\n");
    print_toppings();
    cgc_printf("    Sauce on the side\n");
    print_sauces();
}


int Pizza::get_calories()
{
    cgc_size_t i, calories = 0;
    for (i = 0; i < toppings.length(); i++)
        calories += toppings[i]->get_calories();

    for (i = 0; i < sauce_ots.length(); i++)
        calories += sauce_ots[i]->get_calories();

    return calories;
}

int Pizza::get_carbs()
{
    cgc_size_t i, carbs = 0;
    for (i = 0; i < toppings.length(); i++)
        carbs += toppings[i]->get_carbs();

    for (i = 0; i < sauce_ots.length(); i++)
        carbs += sauce_ots[i]->get_carbs();

    return carbs;
}

int Pizza::get_prep_time()
{
    return toppings.length()* 30 + sauce_ots.length() * 15;
}

