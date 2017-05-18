/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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
#include "MonsterData.h"

const kind_data_t builtin_kinds[NUM_BUILTIN_KINDS] = {
    {
        0, // id
        TYPE_EARTH, // type
        "Pheapxalm", // name
        100, // base health
         90, // base attack
        100, // base defense
        2, // number of attacks
        { // attacks
            { "Scratch", 20 },
            { "Cutting Leaf", 30 },
        }
    },
    {
        1, // id
        TYPE_WIND, // type
        "Eashtel", // name
        110, // base health
         90, // base attack
         90, // base defense
        2, // number of attacks
        { // attacks
            { "Scratch", 20 },
            { "Tornado", 40 },
        }
    },
    {
        2, // id
        TYPE_FIRE, // type
        "Tacalm", // name
        120, // base health
        100, // base attack
         60, // base defense
        2, // number of attacks
        { // attacks
            { "Scratch", 20 },
            { "Bonfire", 50 },
        }
    },
};

unsigned int attack_multiplier(const kind_data_t *attacker, const kind_data_t *defender)
{
    // strengths
    if (attacker->type == TYPE_EARTH && defender->type == TYPE_WIND)
        return 200;
    if (attacker->type == TYPE_WIND && defender->type == TYPE_FIRE)
        return 200;
    if (attacker->type == TYPE_FIRE && defender->type == TYPE_EARTH)
        return 200;

    // weaknesses
    if (attacker->type == TYPE_EARTH && defender->type == TYPE_FIRE)
        return 50;
    if (attacker->type == TYPE_WIND && defender->type == TYPE_EARTH)
        return 50;
    if (attacker->type == TYPE_FIRE && defender->type == TYPE_WIND)
        return 50;

    return 100;
}
