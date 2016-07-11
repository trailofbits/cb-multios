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
#include "TrainerObject.h"
#include "Program.h"
#include "TrainerBattle.h"

#define NUM_TRAINER_NAMES 15

// XXX all names must be shorter than TRAINER_NAME_LEN-1
static const char *trainer_names[NUM_TRAINER_NAMES] = {
    "Tony",
    "Gabriel",
    "Fiona",
    "Carly",
    "Billy",
    "Dustin",
    "Julie",
    "Susan",
    "Leroy",
    "Travis",
    "Katie",
    "Lilly",
    "Jay",
    "Brent",
    "Sylvia"
};

static const char *random_trainer_name()
{
    return trainer_names[$($g->m_random, randint, NUM_TRAINER_NAMES)];
}

DefineClass(TrainerObject, MapObject)

DefineFunction(TrainerObject, void, $init)
{
    this->m_icon = 'T';
    this->m_player_won = 0;
    this->m_team = new(Array);
    strcpy(this->m_name, random_trainer_name());
}

DefineFunction(TrainerObject, void, init, unsigned int level)
{
    this->m_level = level;
    this->m_reward = ($($g->m_random, randint, 4) + level) * 100;

    int i, count = $($g->m_random, randint, 4) + 1;
    for (i = 0; i < count; i++)
    {
        int mlevel = $($g->m_random, randint, 4) + level - count;
        Monster *m = Monster_new_random(mlevel > 0 ? mlevel : 1);
        $(this->m_team, push, m);
    }
}

DefineFunction(TrainerObject, int, on_collide, Player *p)
{
    if (this->m_player_won)
        return 0;

    // fully heal the team
    int i;
    for (i = 0; i < this->m_team->m_count; i++)
    {
        Monster *m = $(this->m_team, get, i);
        m->m_health = m->m_max_health;
    }

    TrainerBattle *battle = new(TrainerBattle);
    $(battle, init, this);
    this->m_player_won = $(battle, run, p);
    delete(battle);

    if (this->m_player_won)
    {
        p->m_money += this->m_reward;
        this->m_icon = ' ';
    }

    return !this->m_player_won;
}

DefineFunction(TrainerObject, void, serialize, Buffer *buf)
{
    $(buf, write_number, 2); // used by MapObject_deserialize
    $(buf, write_number, this->m_icon);
    $(buf, write_number, this->m_player_won);
    $(buf, write_number, this->m_reward);
    $(buf, write_string, this->m_name);
    Monster_serialize_array(this->m_team, buf);
}

DefineFunction(TrainerObject, void, deserialize, Buffer *buf)
{
    char *name;
    unsigned int type;
    free(this->m_team);

    type = $(buf, read_number);
    ASSERT_OR_RAISE(type == 2, EXC_BAD_STATE);
    this->m_icon = $(buf, read_number);
    this->m_player_won = $(buf, read_number);
    this->m_reward = $(buf, read_number);

    name = $(buf, read_string);
    if (strlen(name)+1 > TRAINER_NAME_LEN)
        raise(EXC_BAD_STATE);

    strcpy(this->m_name, name);
    free(name);
    
    this->m_team = new(Array);
    Monster_deserialize_array(this->m_team, buf);
}
