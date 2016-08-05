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

#pragma once

#include "req.h"

typedef struct
{
    const char *name;
    int group;
} mission_t;

typedef struct
{
    const char *name;
} explorer_t;

typedef struct
{
    const char *name;
    CRequirement::Type counter;
    int price;
} skill_t;

mission_t g_missions[20] = {
    { "Pumping Oil!", 1 },
    { "Trash Collection", 2 },
    { "Leviathan", 2 },
    { "Silver Medal", 4 },
    { "Goliath", 3 },
    { "Trinkets", 5 },
    { "Brown Freedom", 1 },
    { "Hidden Eclipse", 2 },
    { "Green Eyes", 2 },
    { "No Mercy", 1 },
    { "Barbossa", 3 },
    { "Cyclone", 3 },
    { "Curtains Up", 4 },
    { "Avalanche", 1 },
    { "Pyramid", 5 },
    { "Jeopardy", 1 },
    { "White Champion", 1 },
    { "White Sun", 2 },
    { "Hidden Sword", 1 },
    { "Fire Fighter", 2 }
};

explorer_t g_explorers[20] = {
    { "Gurro Shiner" },
    { "Hallie Hope" },
    { "Jimmy Mcclanahan" },
    { "Freddie Haugen" },
    { "Patrina Wasson" },
    { "Salome Burrell" },
    { "Rosaria Curley" },
    { "Bertie Hodgson" },
    { "Yoko Hauser" },
    { "Eldon Buckley" },
    { "Makeda Spears" },
    { "Marget Burrow" },
    { "Hae Ledoux" },
    { "Joeann Findley" },
    { "Lupita Acosta" },
    { "Eliza Dickinson" },
    { "Aurelia Lyon" },
    { "Steffanie Mabry" },
    { "Claretha Register" },
    { "Mimi Strunk" }
};

skill_t g_skills[6] = {
    { "Whirling Burst", CRequirement::Type::GROUND_OP, 24 },
    { "Chaotic Blink", CRequirement::Type::SPECIAL_OP, 15 },
    { "Aurum Surge", CRequirement::Type::NAVAL_OP, 13 },
    { "Celestial Attack", CRequirement::Type::AERIAL_OP, 25 },
    { "Dark Calamity", CRequirement::Type::INTEL_OP, 20 },
    { "Nebula Cleave", CRequirement::Type::RESCUE_OP, 12 }
};
