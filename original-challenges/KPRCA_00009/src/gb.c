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
#include <string.h>
#include <ctype.h>

#include "gb.h"
#include "util.h"

static void copy_title(char *dst, const hdr_t *hdr);
static void update_joypad(gb_t *gb);

static int gb_init(gb_t *gb)
{
    // XXX one-byte buffer in case of 2-byte store/load to 0xFFFF
    if (allocate(MEM_SIZE + 1, 0, (void**)&gb->mem) != 0)
        return 0;
    gb->rom = &gb->mem[ADDR_ROM0];

    if (allocate(160*144, 0, (void**)&gb->screen) != 0)
        return 0;

    if (allocate(256*256, 0, (void**)&gb->bg) != 0)
        return 0;

    return 1;
}

void gb_reset(gb_t *gb)
{
    // Registers
    gb->R_AF = 0x01B0;
    gb->R_BC = 0x0013;
    gb->R_DE = 0x00D8;
    gb->R_HL = 0x014D;
    gb->R_SP = 0xFFFE;
    gb->R_PC = 0x0100;

    // I/O memory
    gb->mem[IO_TIMA] = 0x00;
    gb->mem[IO_TMA] = 0x00;
    gb->mem[IO_TAC] = 0x00;
    gb->mem[IO_NR10] = 0x80;
    gb->mem[IO_NR11] = 0xBF;
    gb->mem[IO_NR12] = 0xF3;
    gb->mem[IO_NR14] = 0xBF;
    gb->mem[IO_NR21] = 0x3F;
    gb->mem[IO_NR22] = 0x00;
    gb->mem[IO_NR24] = 0xBF;
    gb->mem[IO_NR30] = 0x7F;
    gb->mem[IO_NR31] = 0xFF;
    gb->mem[IO_NR32] = 0x9F;
    gb->mem[IO_NR33] = 0xBF;
    gb->mem[IO_NR41] = 0xFF;
    gb->mem[IO_NR42] = 0x00;
    gb->mem[IO_NR43] = 0x00;
    gb->mem[IO_NR44] = 0xBF;
    gb->mem[IO_NR45] = 0x77;
    gb->mem[IO_NR51] = 0xF3;
    gb->mem[IO_NR52] = 0xF1;
    gb->mem[IO_LCDC] = 0x90;
    gb->mem[IO_SCY] = 0x00;
    gb->mem[IO_SCX] = 0x00;
    gb->mem[IO_LYC] = 0x00;
    gb->mem[IO_BGP] = 0xFC;
    gb->mem[IO_OBP0] = 0xFF;
    gb->mem[IO_OBP1] = 0xFF;
    gb->mem[IO_WY] = 0x00;
    gb->mem[IO_WX] = 0x00;
    gb->mem[IO_IE] = 0x00;

    // used internally
    gb->mem[IO_DMA] = 0xFF;

    // timers
    gb->ticks = 0;
    gb->ticks_ly = 0;
    gb->ticks_divider = 0;
    gb->ticks_timer = 0;
    gb->ticks_skip = 0;

    gb->input = 0;
    gb->halted = 0;
    gb->speed = 8.0;
    gb->vblank = 0;
}

gb_t *gb_new()
{
    gb_t *gb;
    if (allocate(sizeof(gb_t), 0, (void **)&gb) != 0)
        return NULL;
    if (!gb_init(gb))
        return NULL;
    return gb;
}

int gb_load(gb_t *gb, uint8_t *cartridge)
{
    memcpy(gb->rom, cartridge, ROM_SIZE);

    hdr_t *hdr = (hdr_t *)&gb->rom[0x100];
    copy_title(gb->title, hdr);
    ERR("Loading %s", gb->title);

    if (hdr->rom_size != ROM_32KB || hdr->ram_size != RAM_NONE)
    {
        ERR("Incompatible cartridge.");
        return 0;
    }

    return 1;
}

int gb_tick(gb_t *gb)
{
    update_joypad(gb);

    if (!cpu_tick(gb))
        return 0;

    if (!lcd_tick(gb))
        return 0;

    if (++gb->ticks == TICKS_MAX)
    {
        ERR("Game Over");
        return 0;
    }

    // DMA
    if (gb->mem[IO_DMA] != 0xFF)
    {
        // XXX instant DMA?
        memcpy(&gb->mem[0xFE00], &gb->mem[gb->mem[IO_DMA] << 8], 0xA0);
        gb->mem[IO_DMA] = 0xFF;
    }

    if (++gb->ticks_divider == TICKS_DIVIDER)
    {
        gb->mem[IO_DIV]++;
        gb->ticks_divider = 0;
    }

    if (gb->mem[IO_TAC] & (1 << 2))
    {
        // timer ON
        unsigned int total_ticks;
        switch(gb->mem[IO_TAC] & 3)
        {
        case 0:
            total_ticks = 244;
            break;
        case 1:
            total_ticks = 4;
            break;
        case 2:
            total_ticks = 15;
            break;
        case 3:
            total_ticks = 61;
            break;
        }
        if (++gb->ticks_timer >= total_ticks)
        {
            gb->ticks_timer = 0;
            if (gb->mem[IO_TIMA]++ == 0xFF)
            {
                //overflow
                gb->mem[IO_TIMA] = gb->mem[IO_TMA];
                cpu_interrupt(gb, 2);
            }
        }
    }
    return 1;
}

static void copy_title(char *dst, const hdr_t *hdr)
{
    // should be strictly UPPERCASE ASCII
    // some new cartridges put flags in title
    size_t i;
    for (i = 0; isupper(hdr->title[i]); i++)
        if (i < TITLE_SIZE)
            dst[i] = hdr->title[i];
#ifdef PATCHED
        else
            return;
#endif
    dst[i] = 0;
}

static void update_joypad(gb_t *gb)
{
    gb->mem[IO_JOYP] |= 0xF;
    if (!(gb->mem[IO_JOYP] & (1 << 4)))
    {
        // direction keys
        gb->mem[IO_JOYP] &= ~(gb->input & 0xf);
    }
    if (!(gb->mem[IO_JOYP] & (1 << 5)))
    {
        // button keys
        gb->mem[IO_JOYP] &= ~(gb->input >> 4);
    }
}

