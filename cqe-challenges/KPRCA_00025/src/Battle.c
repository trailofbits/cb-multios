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
#include "Battle.h"
#include "Program.h"
#include "Monster.h"

#include <ctype.h>

DefineClass(Battle, Object)

static Monster *get_next_alive(Array *team)
{
    size_t i;
    for (i = 0; i < team->m_count; i++)
    {
        Monster *m = $(team, get, i);
        if (m->m_health > 0)
            return m;
    }
    return NULL;
}

static const attack_data_t *attack_menu(Monster *m)
{
    size_t i;
    for (i = 0; i < m->m_kind->num_attacks; i++)
    {
        const attack_data_t *atk = &m->m_kind->attacks[i];
        $($io, format, "%d. %s (%d)\n", i + 1, atk->name, atk->power);
    }

    do {
        char c;
        $($io, format, "What attack to perform?\n");
        if ($($io, receive, &c, 1) == 0)
            raise(EXC_IO);
        i = c - '1';
    } while (i > m->m_kind->num_attacks);

    return &m->m_kind->attacks[i];
}

static void apply_damage(Monster *attacker, Monster *defender, unsigned int power)
{
    int dmg = attacker->m_attack - defender->m_defense + power * attack_multiplier(attacker->m_kind, defender->m_kind) / 100;
    
    // add some randomness
    dmg = dmg * (int)$($g->m_random, randint, 110) / 100;

    if (dmg > 0)
    {
        if (dmg > defender->m_health)
            defender->m_health = 0;
        else
            defender->m_health -= dmg;
    }
}

static unsigned int calc_xp(unsigned int enemy_level)
{
    return 100 * enemy_level;
}

DefineFunction(Battle, int, run, Player *p)
{
    Monster *player_monster = NULL, *enemy_monster = NULL;

    while (1)
    {
        if (enemy_monster == NULL)
            enemy_monster = get_next_alive(this->m_enemy_team);
        if (player_monster == NULL) 
            player_monster = get_next_alive(p->m_team);

        if (enemy_monster == NULL || player_monster == NULL)
            break;

        $($io, format, "%s (Lvl %d) versus %s (Lvl %d)\n", player_monster->m_name,
            player_monster->m_level, enemy_monster->m_name, enemy_monster->m_level);

        while (enemy_monster && player_monster)
        {
            const attack_data_t *player_attack = NULL;
            char c;
            $($io, format, "\nPlayer: %s\n        Health %d / %d\n",
                player_monster->m_name, player_monster->m_health, player_monster->m_max_health);
            $($io, format, "\nEnemy:  %s\n        Health %d / %d\n",
                enemy_monster->m_name, enemy_monster->m_health, enemy_monster->m_max_health);
try_again:
            $($io, format, "Menu: (A)ttack, (D)efend, (C)apture, (R)etreat\n");
            if ($($io, receive, &c, 1) == 0)
                raise(EXC_IO);

            switch (tolower(c))
            {
            case 'r':
                if (this->m_can_retreat && $($g->m_random, randint, 100) < 30)
                {
                    $($io, format, "Successful retreat!\n");
                    return 0;
                }
                $($io, format, "Unable to retreat...\n");
                break;
            case 'a':
                player_attack = attack_menu(player_monster);
                apply_damage(player_monster, enemy_monster, player_attack->power);
                break;
            case 'd':
                $($io, format, "%s takes a defensive stance.\n", player_monster->m_name);
                break;
            case 'c':
                if (this->m_can_capture && 
                    enemy_monster->m_health * 10 < enemy_monster->m_max_health &&
                    $($g->m_random, randint, 100) < 70)
                {
                    $($io, format, "Successfully captured %s!\n", enemy_monster->m_name);
                    $(p, capture, enemy_monster);
                    $(this->m_enemy_team, remove, 0);
                    enemy_monster = NULL;
                }
                else
                {
                    $($io, format, "Unable to capture %s.\n", enemy_monster->m_name);
                }
                break;
            default:
                goto try_again;
            }

            if (enemy_monster == NULL)
                break;
            if (enemy_monster->m_health == 0)
            {
                $(player_monster, gain_xp, calc_xp(enemy_monster->m_level));
                enemy_monster = NULL;
                break;
            }

            const attack_data_t *enemy_attack = &enemy_monster->m_kind->attacks[$($g->m_random, randint, enemy_monster->m_kind->num_attacks)];
            apply_damage(enemy_monster, player_monster, enemy_attack->power * (c == 'd' ? 70 : 100) / 100);

            if (player_monster->m_health == 0)
                player_monster = NULL;
        }
    }

    return enemy_monster == NULL;
}
