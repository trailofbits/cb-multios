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
#include "WildBattle.h"
#include "Program.h"
#include "Monster.h"

DefineClass(WildBattle, Battle)

DefineFunction(WildBattle, void, $destroy)
{
    delete(this->m_monster);
}

DefineFunction(WildBattle, void, init, unsigned int level)
{
    this->m_level = level;
    this->m_monster = Monster_new_random(level);
    this->m_can_capture = 1;
    this->m_can_retreat = 1;
}

DefineFunction(WildBattle, int, run, Player *p)
{
    Array *enemy = new(Array);
    $(enemy, push, this->m_monster);
    this->m_enemy_team = enemy;

    $($io, format, "A wild %s attacks!\n", this->m_monster->m_name);
    int battle_won = $super(Battle, this, run, p);

    this->m_enemy_team = NULL;
    delete(enemy);
    return battle_won;
}
