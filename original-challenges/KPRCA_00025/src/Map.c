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
#include "Map.h"
#include "Program.h"
#include "EmptyObject.h"
#include "NameChangeObject.h"
#include "TrainerObject.h"
#include "TreasureObject.h"
#include "VetObject.h"
#include "WallObject.h"
#include "WildBattle.h"

static int iabs(int i)
{
    if (i < 0)
        return -i;
    return i;
}

DefineClass(Map, Object)

DefineFunction(Map, void, $init)
{
    this->m_player = new(Player);
    this->m_objects[MAP_WALL_ID] = new(WallObject)->super;
    this->m_objects[MAP_EMPTY_ID] = new(EmptyObject)->super;
}

DefineFunction(Map, void, init, unsigned int w, unsigned int h)
{
    this->m_next_id = 0;
    this->m_width = w;
    this->m_height = h;

    this->m_map = malloc(sizeof(unsigned char) * w * h);
    ASSERT_ALLOC(this->m_map);
    memset(this->m_map, MAP_WALL_ID, sizeof(unsigned char) * w * h);

    // starting point
    this->m_start_x = w/2;
    this->m_start_y = 0;

    $(this, _generate);

    $(this->m_player, init, this->m_start_x, this->m_start_y);
}

DefineFunction(Map, void, _generate)
{
    int empty, x, y;
    unsigned int farthest_dist = 0;
    unsigned char *farthest_slot = NULL;
    // generate map using a random walk from the start
    // ensure that there are a border of walls

    x = this->m_start_x;
    y = this->m_start_y;
    this->m_map[x + y * this->m_width] = $(this, new_id, new(VetObject)->super);
    empty = 1;

    while (empty < (int)(this->m_width * this->m_height * 4 / 10))
    {
        int newx = -1, newy = -1;
        do {
            int chance = $($g->m_random, randint, 4);
            if (chance == 0)
            {
                newx = x + 1;
                newy = y;
            }
            else if (chance == 1)
            {
                newx = x - 1;
                newy = y;
            }
            else if (chance == 2)
            {
                newx = x;
                newy = y + 1;
            }
            else if (chance == 3)
            {
                newx = x;
                newy = y - 1;
            }
        } while (newx <= 0 || newx >= this->m_width-1 || newy <= 0 || newy >= this->m_height-1);

        x = newx, y = newy;
        unsigned char *slot = &this->m_map[x + y * this->m_width];
        if (*slot == MAP_WALL_ID)
        {
            int chance = $($g->m_random, randint, 100);
            if (chance == 0)
            {
                TrainerObject *t = new(TrainerObject);
                unsigned int level = $(this, get_level, x, y);
                $(t, init, level);
                *slot = $(this, new_id, t->super);
            }
            else if (chance == 1)
            {
                *slot = $(this, new_id, new(TreasureObject)->super);
            }
            else
            {
                *slot = MAP_EMPTY_ID;
            }

            unsigned int dist = $(this, distance, x, y);
            if (dist > farthest_dist)
            {
                farthest_dist = dist;
                farthest_slot = slot;
            }
            empty++;
        }
    }

    if (farthest_slot)
    {
        *farthest_slot = $(this, new_id, new(NameChangeObject)->super);
    }
}

DefineFunction(Map, unsigned char, new_id, MapObject *obj)
{
    unsigned char id = this->m_next_id;
    if (id == MAP_WALL_ID || id == MAP_EMPTY_ID)
    {
        // too many objects, give up
        delete(obj);
        return MAP_EMPTY_ID;
    }

    this->m_next_id++;
    this->m_objects[id] = obj;
    return id;
}

DefineFunction(Map, void, display)
{
    int x, y;
    char *buf = calloc(this->m_height * 2, this->m_width);
    if  (!buf)
        _terminate(1);

    char *buf_w = buf;

    printf("\x1B[2J"); // clear the screen
    $($io, format, "Money: %6d\n", this->m_player->m_money);
    for (y = 0; y < this->m_height; y++)
    {
        for (x = 0; x < this->m_width; x++)
        {
            if (x == this->m_player->m_x && y == this->m_player->m_y) {
                sprintf(buf_w++, "%c", this->m_player->m_icon);
                // printf("%c", this->m_player->m_icon);
            } else {
                sprintf(buf_w++, "%c", this->m_objects[this->m_map[x + y * this->m_width]]->m_icon);
                // printf("%c", this->m_objects[this->m_map[x + y * this->m_width]]->m_icon);
            }
        }
        sprintf(buf_w++, "\n");
    }
    send_n_bytes(STDOUT, strlen(buf), buf);
    free(buf);
}

DefineFunction(Map, void, move, int diffx, int diffy)
{
    int newx = this->m_player->m_x + diffx, newy = this->m_player->m_y + diffy;
    if (newx < 0 || newx >= this->m_width || newy < 0 || newy >= this->m_height)
        return;

    if (!$(this->m_objects[this->m_map[newx + newy * this->m_width]], on_collide, this->m_player))
    {
        if ($($g->m_random, randint, 10) == 0)
        {
            WildBattle *battle = new(WildBattle);
            unsigned int level = $(this, get_level, newx, newy);
            $(battle, init, level);
            $(battle, run, this->m_player);
            delete(battle);
        }
        $(this->m_player, move, newx, newy);
    }

    if (!$(this->m_player, is_alive))
    {
        this->m_player->m_money /= 2;
        $(this->m_player, move, this->m_start_x, this->m_start_y);
        $(this->m_player, heal);
    }
}

DefineFunction(Map, unsigned int, distance, int x, int y)
{
    unsigned int dist = iabs(x - this->m_start_x) + iabs(y - this->m_start_y);
    return dist;
}

DefineFunction(Map, unsigned int, get_level, int x, int y)
{
    // calculate level based on distance from start
    // XXX use a distance map to get te real distance instead of manhattan dist
    // XXX also this max dist is wrong...
    unsigned int max_dist = iabs(this->m_width - this->m_start_x) + iabs(this->m_height - this->m_start_y);
    unsigned int dist = $(this, distance, x, y);
    int level = 99 * dist / max_dist;
    return level < 1 ? 1 : level;
}

DefineFunction(Map, void, serialize, Buffer *buf)
{
    int count = 0, last = -1;
    size_t i;
    $(buf, write_number, this->m_width);
    $(buf, write_number, this->m_height);
    $(buf, write_number, this->m_start_x);
    $(buf, write_number, this->m_start_y);
    $(buf, write_number, this->m_next_id);
    // encode the map with RLE
    for (i = 0; i < this->m_width * this->m_height; i++)
    {
        if (last != this->m_map[i])
        {
            if (count)
            {
                $(buf, write_number, count);
                $(buf, write_u8, last);
            }

            last = this->m_map[i];
            count = 1;
        }
        else
        {
            count++;
        }
    }
    if (count)
    {
        $(buf, write_number, count);
        $(buf, write_u8, last);
    }
    // encode the objects
    for (i = 0; i < this->m_next_id; i++)
    {
        $(this->m_objects[i], serialize, buf);
    }
    // encode the player
    $(this->m_player, serialize, buf);
}

DefineFunction(Map, void, deserialize, Buffer *buf)
{
#ifdef PATCHED
    uint8_t max_id = 0;
#endif

    size_t i;
    this->m_width = $(buf, read_number);
    this->m_height = $(buf, read_number);
    this->m_start_x = $(buf, read_number);
    this->m_start_y = $(buf, read_number);
    this->m_next_id = $(buf, read_number);

#ifdef PATCHED
    ASSERT_OR_RAISE(this->m_width < 0x1000, EXC_BAD_STATE);
    ASSERT_OR_RAISE(this->m_height < 0x1000, EXC_BAD_STATE);

    free(this->m_map);
    this->m_map = malloc(sizeof(unsigned char) * this->m_width * this->m_height);
    ASSERT_OR_RAISE(this->m_map != NULL, EXC_BAD_STATE);
#endif

    ASSERT_OR_RAISE(this->m_start_x < this->m_width, EXC_BAD_STATE);
    ASSERT_OR_RAISE(this->m_start_y < this->m_height, EXC_BAD_STATE);
    ASSERT_OR_RAISE(this->m_next_id < MAP_EMPTY_ID, EXC_BAD_STATE);

    for (i = 0; i < this->m_width * this->m_height;)
    {
        unsigned int count = $(buf, read_number);
        uint8_t id = $(buf, read_u8);

#ifdef PATCHED
        ASSERT_OR_RAISE(count <= this->m_width * this->m_height, EXC_BAD_STATE);
#endif
#ifdef PATCHED
        if (id > max_id && id != MAP_WALL_ID && id != MAP_EMPTY_ID)
            max_id = id;
#endif
        ASSERT_OR_RAISE(count + i <= this->m_width * this->m_height, EXC_BAD_STATE);

        memset(&this->m_map[i], id, count);
        i += count;
    }
    // decode the objects
    for (i = 0; i < this->m_next_id; i++)
    {
        this->m_objects[i] = MapObject_deserialize(buf);
    }
#ifdef PATCHED
    ASSERT_OR_RAISE(i >= max_id, EXC_BAD_STATE);
#endif
    // decode the player
    $(this->m_player, deserialize, buf);
}
