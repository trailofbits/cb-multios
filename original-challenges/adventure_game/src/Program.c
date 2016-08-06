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
#include "oo.h"
#include "Program.h"
#include "Buffer.h"

Program *$g;
IO *$io;

DefineClass(Program, Object)

DefineFunction(Program, void, $init)
{
    $super(Object, this, $init);
    
    // initialize global pointer
    $g = this;
    $io = this->m_io = new(IO);
    this->m_random = new(Random);
}

DefineFunction(Program, void, run)
{
    this->m_map = new(Map);
    $(this->m_map, init, 100, 50);

    while (1)
    {
        char cmd;
        size_t bytes;

        // display the map
        $(this->m_map, display);

        // wait for input
try_again:
        if ($($io, receive, &cmd, 1) == 0)
            break;

        switch (cmd)
        {
        case 'w':
            $(this->m_map, move, 0, -1);
            break;
        case 'a':
            $(this->m_map, move, -1, 0);
            break;
        case 's':
            $(this->m_map, move, 0, 1);
            break;
        case 'd':
            $(this->m_map, move, 1, 0);
            break;
        case 'x':
            $(this->m_map->m_player, team_menu);
            break;
        case '1':
            $(this, save_game);
            break;
        case '2':
            $(this, load_game);
            break;
        default:
            goto try_again;
        }
    }
}

DefineFunction(Program, void, load_game)
{
    size_t i;
    Buffer *buffer = new(Buffer);
    char *start, *strbuf = malloc(8192);
    ASSERT_ALLOC(strbuf);

    for (i = 0; i < 8191; i++)
    {
        if ($($io, receive, &strbuf[i], 1) == 0)
            goto fail;
        if (i > 0 && strbuf[i-1] == '-' && strbuf[i] == '-')
            break;
    }

    if (i == 8191)
        goto fail;

    strbuf[i-1] = 0;
    start = strchr(strbuf, '-');
    if (start == NULL || start + 1 >= &strbuf[i-1])
        goto fail;
    start++;

    if ($(buffer, dearmor, start) == 0)
        goto fail;

    $(buffer, seek, SEEK_BEGIN);
    $(this->m_map, deserialize, buffer);

fail:
    delete(buffer);
    free(strbuf);
}

DefineFunction(Program, void, save_game)
{
    Buffer *buffer = new(Buffer);
    $(this->m_map, serialize, buffer);

    char *asc = $(buffer, armor);
    if (asc)
    {
        $($io, format, "-%s--\nPress (C) to continue...\n", asc);
        $($io, wait_for, 'c');
        free(asc);
    }

    delete(buffer);
}
