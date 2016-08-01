/*
 * Author: Andrew Wesie <andrew.wesie@kapricasecurity.com>
 *
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
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "gb.h"
#include "util.h"

// reduce screen refresh rate
// rate = simulated refresh rate (~60Hz) / REFRESH_DIVIDER
#define REFRESH_DIVIDER 30

// scaledown the screen (2x3 -> 1x1)
#define SCALEDOWN

// scaledown using braille symbols instead of pixel mean
// #define BRAILLE

static void usage(char *progname)
{
    printf("Usage: %s rom-file\n", progname);
}

static int recvall(int fd, uint8_t *buf, size_t cnt)
{
    while (cnt > 0)
    {
        size_t n;
        if (receive(fd, buf, cnt, &n) != 0 || n == 0)
            break;
        cnt -= n;
        buf += n;
    }

    return cnt == 0;
}

static int load_rom(gb_t *gb)
{
    uint8_t rom[ROM_SIZE];
    if (!recvall(STDIN, rom, ROM_SIZE))
        return 0;
    return gb_load(gb, rom);
}

static void print_reg(gb_t *gb)
{
    ERR("AF = %04X, BC = %04X, DE = %04X, HL = %04X",
        gb->R_AF, gb->R_BC, gb->R_DE, gb->R_HL);
    ERR("SP = %04X, PC = %04X",
        gb->R_SP, gb->R_PC);
}

static char *block_6px_char(uint8_t *bitmap, unsigned int span)
{
#ifndef BRAILLE
    unsigned int avg = bitmap[0 * span + 0] + bitmap[0 * span + 1] +
        bitmap[1 * span + 0] + bitmap[1 * span + 1] +
        bitmap[2 * span + 0] + bitmap[2 * span + 1];
    switch (avg / 6)
    {
    case 0:
        return " ";
    case 1:
        return "-";
    case 2:
        return "X";
    case 3:
        return "#";
    }
    return " ";
#else
    static char buf[4];
    unsigned int v = ((bitmap[0 * span + 0] > 0) << 0) |
        ((bitmap[1 * span + 0] > 0) << 1) |
        ((bitmap[2 * span + 0] > 0) << 2) |
        ((bitmap[0 * span + 1] > 0) << 3) |
        ((bitmap[1 * span + 1] > 0) << 4) |
        ((bitmap[2 * span + 1] > 0) << 5);
    v += 0x2800;
    buf[0] = 0xE0 | (v >> 12);
    buf[1] = 0x80 + ((v >> 6) & 0x3f);
    buf[2] = 0x80 + ((v >> 0) & 0x3f);
    buf[3] = 0;
    return buf;
#endif
}

static void draw_screen(gb_t *gb)
{
    size_t bytes;
    if ((gb->mem[IO_LCDC] & 0x80) == 0)
    {
        /* LCD disabled */
        return;
    }

    transmit(STDOUT, "\x1B[H", 3, &bytes);

#ifndef SCALEDOWN
    static char buf[144 * 161 + 1];
    uint8_t x, y;
    for (y = 0; y < 144; y++)
    {
        for (x = 0; x < 160; x++)
        {
            switch (gb->screen[y * 160 + x])
            {
            case 0:
                buf[y * 161 + x] = ' ';
                break;
            case 1:
                buf[y * 161 + x] = '-';
                break;
            case 2:
                buf[y * 161 + x] = 'X';
                break;
            case 3:
                buf[y * 161 + x] = '#';
                break;
            }
        }
        buf[y * 161 + x] = '\n';
    }
    buf[y * 161 + 0] = '\n';
    transmit(STDOUT, buf, sizeof(buf), &bytes);
#else
    uint8_t x, y;
    for (y = 0; y < 144; y += 3)
    {
        for (x = 0; x < 160; x += 2)
        {
            char *ch = block_6px_char(&gb->screen[y * 160 + x], 160);
            transmit(STDOUT, ch, strlen(ch), &bytes);
        }
        transmit(STDOUT, "\n", 1, &bytes);
    }
    transmit(STDOUT, "\n", 1, &bytes);
#endif
}

int process_input(gb_t *gb)
{
    char ch;
    size_t bytes;

    if (receive(STDIN, &ch, 1, &bytes) != 0 || bytes != 1)
        return 0;

    switch(ch)
    {
    case 'w':
        gb->input |= INPUT_UP;
        break;
    case 'W':
        gb->input &= ~INPUT_UP;
        break;
    case 'a':
        gb->input |= INPUT_LEFT;
        break;
    case 'A':
        gb->input &= ~INPUT_LEFT;
        break;
    case 's':
        gb->input |= INPUT_DOWN;
        break;
    case 'S':
        gb->input &= ~INPUT_DOWN;
        break;
    case 'd':
        gb->input |= INPUT_RIGHT;
        break;
    case 'D':
        gb->input &= ~INPUT_RIGHT;
        break;
    case 'j':
        gb->input |= INPUT_A;
        break;
    case 'J':
        gb->input &= ~INPUT_A;
        break;
    case 'k':
        gb->input |= INPUT_B;
        break;
    case 'K':
        gb->input &= ~INPUT_B;
        break;
    case 'u':
        gb->input |= INPUT_SELECT;
        break;
    case 'U':
        gb->input &= ~INPUT_SELECT;
        break;
    case 'i':
        gb->input |= INPUT_START;
        break;
    case 'I':
        gb->input &= ~INPUT_START;
        break;
    case 'q':
        ERR("Good-Bye");
        return 0;
    case 'h':
    case '?':
        ERR("HELP: (q)uit, (h)elp, (wasd) direction keys, (j) A, (k) B, (u) SELECT, (i) START");
        break;
    }

    return 1;
}

int check_input(gb_t *gb)
{
    fd_set fds;
    int readyfds = 0;
    struct timeval tv;

    FD_ZERO(&fds);
    FD_SET(STDIN, &fds);
    tv.tv_sec = 0;
    tv.tv_usec = SLEEP_US;

    if (fdwait(STDIN+1, &fds, NULL, &tv, &readyfds) != 0)
        return 0;

    if (readyfds)
    {
        return process_input(gb);
    }
    return 1;
}

int main()
{
    gb_t *gb = gb_new();
    if (gb == NULL)
    {
        ERR("Unable to allocate memory.");
        exit(1);
    }

    // clear the screen
    printf("\x1B[2J");

    if (!load_rom(gb))
    {
        ERR("Unable to load ROM.");
        exit(2);
    }

    // hide the cursor
    printf("\x1B[?25l");

    gb_reset(gb);

    unsigned int ticks_sleep = 0;
    unsigned int vblanks = 0;
    for (;;)
    {
        if (!gb_tick(gb))
            break;

        if (gb->vblank)
        {
            if ((++vblanks % REFRESH_DIVIDER) == 0)
                draw_screen(gb);
            gb->vblank = 0;
        }

        if (ticks_sleep++ == TICKS_SLEEP * gb->speed)
        {
            if (!check_input(gb))
                break;
            ticks_sleep = 0;
        }
    }
    print_reg(gb);

    return 0;
}
