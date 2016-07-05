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
#include "Monster.h"
#include "Program.h"

DefineClass(Monster, Object)

DefineFunction(Monster, void, $destroy)
{
}

DefineFunction(Monster, void, $init)
{
    this->m_kind = NULL;
}

DefineFunction(Monster, void, init, const kind_data_t *kind, unsigned int level)
{
    this->m_level = level;
    this->m_kind = kind;
    $(this, set_name, kind->name);
    
    this->m_max_health = kind->max_health + level * LEVEL_HEALTH_MULTIPLIER / 100;
    this->m_attack = kind->attack + level * LEVEL_ATTACK_MULTIPLIER / 100;
    this->m_defense = kind->defense + level * LEVEL_DEFENSE_MULTIPLIER / 100;
    this->m_xp = 0;

    this->m_health = this->m_max_health;
}

DefineFunction(Monster, void, copy, Monster *other)
{
    $(this, set_name, other->m_name);

    this->m_kind = other->m_kind;
    this->m_level = other->m_level;
    this->m_xp = other->m_xp;
    this->m_health = other->m_health;
    this->m_max_health = other->m_max_health;
    this->m_attack = other->m_attack;
    this->m_defense = other->m_defense;
}

DefineFunction(Monster, void, set_name, const char *name)
{
#if PATCHED
    if (strlen(name)+1 > MONSTER_NAME_LEN)
        raise(EXC_BAD_STATE);
#endif
    strcpy(this->m_name, name);
}

DefineFunction(Monster, void, level_up)
{
    if (this->m_level >= MAX_LEVEL)
        return;

    unsigned int bonus = $($g->m_random, randint, 299);

    this->m_level++;
    this->m_max_health += (LEVEL_HEALTH_MULTIPLIER + bonus) / 100;
    this->m_attack += (LEVEL_ATTACK_MULTIPLIER + bonus) / 100;
    this->m_defense += (LEVEL_DEFENSE_MULTIPLIER + bonus) / 100;

    // full heal
    this->m_health = this->m_max_health;
}

DefineFunction(Monster, int, gain_xp, unsigned int xp)
{
    unsigned int req_xp = 100 * this->m_level * this->m_level / 4;
    this->m_xp += xp;

    if (this->m_xp > req_xp)
    {
        this->m_xp -= req_xp;
        $(this, level_up);
    }

    return 0;
}

DefineFunction(Monster, void, serialize, Buffer *buf)
{
    $(buf, write_string, this->m_name);
    $(buf, write_number, this->m_kind->id);
    $(buf, write_number, this->m_level);
    $(buf, write_number, this->m_xp);
    $(buf, write_number, this->m_health);
    $(buf, write_number, this->m_max_health);
    $(buf, write_number, this->m_attack);
    $(buf, write_number, this->m_defense);
}

DefineFunction(Monster, void, deserialize, Buffer *buf)
{
    char *name;
    unsigned kind_id;

    name = $(buf, read_string);
    $(this, set_name, name);
    free(name);

    kind_id = $(buf, read_number);
    ASSERT_OR_RAISE(kind_id < NUM_BUILTIN_KINDS, EXC_BAD_STATE);
    this->m_kind = &builtin_kinds[kind_id];

    this->m_level = $(buf, read_number);
    this->m_xp = $(buf, read_number);
    this->m_health = $(buf, read_number);
    this->m_max_health = $(buf, read_number);
    this->m_attack = $(buf, read_number);
    this->m_defense = $(buf, read_number);
}

// static functions
void Monster_print_array(Array *arr)
{
    size_t i;
    for (i = 0; i < arr->m_count; i++)
    {
        Monster *m = $(arr, get, i);
        $($g->m_io, format, "%2d. %s (%s)\n    Level: %2d    XP: %d\n    Health: %d / %d\n", 
            i + 1, m->m_name, m->m_kind->name, m->m_level, m->m_xp, m->m_health, m->m_max_health);
    }
}

Monster *Monster_new_random(unsigned int level)
{
    unsigned int kind_id = $($g->m_random, randint, NUM_BUILTIN_KINDS);
    Monster *m = new(Monster);
    $(m, init, &builtin_kinds[kind_id], level);
    return m;
}

void Monster_deserialize_array(Array *arr, Buffer *buf)
{
    size_t i, count;
    count = $(buf, read_number);

    for (i = 0; i < count; i++)
    {
        Monster *m = new(Monster);
        $(m, deserialize, buf);
        $(arr, push, m);
    }
}

void Monster_serialize_array(Array *arr, Buffer *buf)
{
    size_t i;
    $(buf, write_number, arr->m_count);

    for (i = 0; i < arr->m_count; i++)
    {
        Monster *m = $(arr, get, i);
        $(m, serialize, buf);
    }
}
