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
#include <stdlib.h>
#include <stdint.h>

#include "gb.h"
#include "util.h"

static tile_t *bg_tile(gb_t *gb, uint8_t n)
{
    if (gb->mem[IO_LCDC] & (1 << 4))
        return (tile_t *)&gb->mem[0x8000 + n * 16];
    else
        return (tile_t *)&gb->mem[0x9000 + (int8_t)n * 16];
}

static void draw_tile(gb_t *gb, uint8_t *bitmap, unsigned int span, tile_t *tile, int palette)
{
    pal_t *pal = &gb->palettes[palette];
    uint8_t x, y;
    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            unsigned int b1, b2, color;
            b1 = tile->bytes[y*2] & (1 << (7 - x));
            b2 = tile->bytes[y*2 + 1] & (1 << (7 - x));
            color = (!!b2) << 1 | (!!b1);
            if (palette == 0)
            {
                // bg
                bitmap[y * span + x] = pal->colors[color];
            }
        }
    }
}

static void update_bg(gb_t *gb)
{
    uint8_t *tilemap = (gb->mem[IO_LCDC] & (1 << 3)) ? &gb->mem[0x9C00] : &gb->mem[0x9800];
    uint8_t x, y;
    for (y = 0; y < 32; y++)
    {
        for (x = 0; x < 32; x++)
        {
            tile_t *tile = bg_tile(gb, tilemap[y * 32 + x]);
            draw_tile(gb, &gb->bg[8 * (8 * y * 32 + x)], 256, tile, 0);
        }
    }
}

static void update_screen(gb_t *gb)
{
    // update palettes
    int i;
    for (i = 0; i < 3; i++)
    {
        uint8_t data = gb->mem[0xFF47 + i];
        gb->palettes[i].colors[0] = data & 0x3;
        gb->palettes[i].colors[1] = (data & 0xC) >> 2;
        gb->palettes[i].colors[2] = (data & 0x30) >> 4;
        gb->palettes[i].colors[3] = (data & 0xC0) >> 6;
    }
    uint8_t y = gb->mem[IO_LY];
    if (gb->mem[IO_LCDC] & 1)
    {
        /* BG enabled */
        update_bg(gb);
        uint8_t scx = gb->mem[IO_SCX],
            scy = gb->mem[IO_SCY];
        uint8_t x;
        uint8_t bgy = scy + y;
        for (x = 0; x < 160; x++)
        {
            uint8_t bgx = scx + x;
            gb->screen[y * 160 + x] = gb->bg[bgy * 256 + bgx];
        }
    }
}

int lcd_tick(gb_t *gb)
{
    if (++gb->ticks_ly == 109)
        gb->ticks_ly = 0;

    if (gb->ticks_ly == 0 && gb->mem[IO_LY] < 144)
    {
        // increment vertical line
        if (++gb->mem[IO_LY] == 144)
        {
            // set Mode 1
            gb->vblank = 1;
            gb->mem[IO_STAT] &= ~0x3;
            gb->mem[IO_STAT] |= 1;
            if (gb->mem[IO_STAT] & (1 << 4))
                cpu_interrupt(gb, 1);
            cpu_interrupt(gb, 0);
        }
        else
        {
mode2:
            // set Mode 2
            gb->mem[IO_STAT] &= ~0x3;
            gb->mem[IO_STAT] |= 2;
            if (gb->mem[IO_STAT] & (1 << 5))
                cpu_interrupt(gb, 1);
            // set coincidence flag
            gb->mem[IO_STAT] &= ~0x4;
            if (gb->mem[IO_LY] == gb->mem[IO_LYC])
            {
                gb->mem[IO_STAT] |= 0x4;
                if (gb->mem[IO_STAT] & (1 << 6))
                    cpu_interrupt(gb, 1);
            }
            update_screen(gb);
        }
    }
    else if (gb->ticks_ly == 19 && gb->mem[IO_LY] < 144)
    {
        // set Mode 3
        gb->mem[IO_STAT] &= ~0x3;
        gb->mem[IO_STAT] |= 3;
    }
    else if (gb->ticks_ly == 60 && gb->mem[IO_LY] < 144)
    {
        // set Mode 0
        gb->mem[IO_STAT] &= ~0x3;
        gb->mem[IO_STAT] |= 0;
        if (gb->mem[IO_STAT] & (1 << 3))
            cpu_interrupt(gb, 1);
    }
    // VBlank handler
    else if (gb->ticks_ly == 0)
    {
        if (++gb->mem[IO_LY] == 154)
        {
            // VBlank end
            gb->mem[IO_LY] = 0;
            goto mode2;
        }
    }
    return 1;
}
