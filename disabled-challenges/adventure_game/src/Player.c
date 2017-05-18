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
#include <ctype.h>

#include "Player.h"
#include "Program.h"
#include "Monster.h"

DefineClass(Player, Object)

DefineFunction(Player, void, init, unsigned int x, unsigned int y)
{
    this->m_money = 0;
    this->m_bank = new(Array);
    this->m_team = new(Array);
    this->m_icon = '*';
    $(this, move, x, y);

    $(this->m_team, push, Monster_new_random(3));
}

DefineFunction(Player, void, move, unsigned int x, unsigned int y)
{
    this->m_x = x;
    this->m_y = y;
}

DefineFunction(Player, int, is_alive)
{
    size_t i;
    for (i = 0; i < this->m_team->m_count; i++)
    {
        Monster *m = $(this->m_team, get, i);
        if (m->m_health > 0)
            return 1;
    }
    return 0;
}

DefineFunction(Player, void, heal)
{
    size_t i;
    for (i = 0; i < this->m_team->m_count; i++)
    {
        Monster *m = $(this->m_team, get, i);
        m->m_health = m->m_max_health;
    }
}

DefineFunction(Player, void, capture, Monster *wild)
{
    Monster *m = new(Monster);
    $(m, copy, wild);

    if (this->m_team->m_count < TEAM_SIZE)
    {
        $(this->m_team, push, m);
    }
    else if (this->m_bank->m_count < BANK_SIZE)
    {
        $(this->m_bank, push, m);
    }
    else
    {
        $($io, format, "No space on team or in bank. %s was abandoned.\n", m->m_name);
        delete(m);
    }
}

DefineFunction(Player, void, serialize, Buffer *buf)
{
    $(buf, write_number, this->m_x);
    $(buf, write_number, this->m_y);
    $(buf, write_u8, this->m_icon);
    $(buf, write_number, this->m_money);

    Monster_serialize_array(this->m_team, buf);
    Monster_serialize_array(this->m_bank, buf);
}

DefineFunction(Player, void, deserialize, Buffer *buf)
{
    this->m_x = $(buf, read_number);
    this->m_y = $(buf, read_number);
    this->m_icon = $(buf, read_u8);
    this->m_money = $(buf, read_number);

    this->m_team = new(Array);
    this->m_bank = new(Array);

    Monster_deserialize_array(this->m_team, buf);
    Monster_deserialize_array(this->m_bank, buf);

    ASSERT_OR_RAISE(this->m_team->m_count <= TEAM_SIZE, EXC_BAD_STATE);
    ASSERT_OR_RAISE(this->m_bank->m_count <= BANK_SIZE, EXC_BAD_STATE);
}

DefineFunction(Player, void, team_menu)
{
    Monster *m;
    while (1)
    {
        char c;
        Monster_print_array(this->m_team);
        $($io, format, "Menu: (C)ancel, (A)bandon, (S)wap\n");
        if ($($io, receive, &c, 1) == 0)
            break;
        
        if (tolower(c) == 'c')
            break;

        switch (tolower(c))
        {
        case 'a':
            if (this->m_team->m_count == 1)
            {
                $($io, format, "Cannot abandon last monster!\n");
                break;
            }

            do {
                $($io, format, "Who do you want to abandon?\n");
                if ($($io, receive, &c, 1) == 0)
                    return;
            } while ((unsigned)(c-'1') >= this->m_team->m_count);
            
            unsigned int idx = c-'1';
            m = $(this->m_team, get, idx);
            $($io, format, "Are you sure you want to abandon %s?\n", m->m_name);

            do {
                if ($($io, receive, &c, 1) == 0)
                    return;
            } while (tolower(c) != 'y' && tolower(c) != 'n');

            if (tolower(c) == 'y')
            {
                $(this->m_team, remove, idx);
                delete(m);
            }
            break;
        case 's':
            do {
                $($io, format, "Who do you want to swap (a)?\n");
                if ($($io, receive, &c, 1) == 0)
                    return;
            } while ((unsigned)(c-'1') >= this->m_team->m_count);
            unsigned int idx1 = c-'1';
            do {
                $($io, format, "Who do you want to swap (b)?\n");
                if ($($io, receive, &c, 1) == 0)
                    return;
            } while ((unsigned)(c-'1') >= this->m_team->m_count);
            unsigned int idx2 = c-'1';
            Monster *m1 = $(this->m_team, get, idx1);
            Monster *m2 = $(this->m_team, get, idx2);
            $(this->m_team, set, idx1, m2);
            $(this->m_team, set, idx2, m1);
            break;
        }
    }
}

DefineFunction(Player, void, name_change_menu)
{
    Buffer *buf;
    char *new_name;
    unsigned int idx;
    Monster *m;

    buf = new(Buffer);
    $($io, format, "Hello! I am the monster name changer.\n");
    while (1)
    {
        char c;
        
        Monster_print_array(this->m_team);

        do {
            $($io, format, "Choose a monster to rename, or (c)ancel:\n");
            if ($($io, receive, &c, 1) == 0)
                goto done;
            if (tolower(c) == 'c')
                goto done;
        } while ((unsigned)(c-'1') >= this->m_team->m_count);
        
        idx = c-'1';
        m = $(this->m_team, get, idx);

        $(buf, seek, SEEK_BEGIN);
        $($io, format, "What is the new name for %s?\n", m->m_name);
        do {
            if ($($io, receive, &c, 1) == 0)
                goto done;
            if (isalnum(c) || ispunct(c))
                $(buf, write_u8, c);
            else
                break;
        } while (1);

        $(buf, write_u8, '\0');
        new_name = (char *)buf->m_buf;

try_again_yn:
        $($io, format, "Are you sure you want to rename %s to %s? [y/n]\n", m->m_name, new_name);

        if ($($io, receive, &c, 1) == 0)
            break;
        
        if (tolower(c) == 'y')
        {
            $(m, set_name, new_name);
        }
        else if (tolower(c) == 'n')
        {
            /* continue */
        }
        else
        {
            goto try_again_yn;
        }
    }

done:
    delete(buf);
}

DefineFunction(Player, void, vet_menu)
{
    unsigned int idx;
    Monster *m;

    $($io, format, "Welcome to Vet Center! How can we help you?\n");
    while (1)
    {
        char c;
        $($io, format, "Menu: (G)ood-bye, (H)eal, (S)tore a Monster, (W)ithdraw a Monster\n");
        if ($($io, receive, &c, 1) == 0)
            break;
        
        if (tolower(c) == 'g')
            break;

        switch (tolower(c))
        {
        case 'h':
            $(this, heal);
            $($io, format, "Your animals have been healed!\n");
            break;
        case 's':
            if (this->m_team->m_count == 1)
            {
                $($io, format, "Team must have at least one monster!\n");
                break;
            }
            if (this->m_bank->m_count == BANK_SIZE)
            {
                $($io, format, "Monster bank is full!\n");
                break;
            }
            
            Monster_print_array(this->m_team);

            do {
                $($io, format, "Who do you want to store?\n");
                if ($($io, receive, &c, 1) == 0)
                    return;
            } while ((unsigned)(c-'1') >= this->m_team->m_count);
            
            idx = c-'1';
            m = $(this->m_team, get, idx);
            $(this->m_team, remove, idx);
            $(this->m_bank, push, m);
            break;
        case 'w':
            if (this->m_team->m_count == TEAM_SIZE)
            {
                $($io, format, "Team is already full!\n");
                break;
            }
            if (this->m_bank->m_count == 0)
            {
                $($io, format, "Monster bank is empty!\n");
                break;
            }
            
            Monster_print_array(this->m_bank);

            do {
                $($io, format, "Who do you want to withdraw?\n");
                if ($($io, receive, &c, 1) == 0)
                    return;
            } while ((unsigned)(c-'1') >= this->m_bank->m_count);
            
            idx = c-'1';
            m = $(this->m_bank, get, idx);
            $(this->m_bank, remove, idx);
            $(this->m_team, push, m);
            break;
        }
    }
}
