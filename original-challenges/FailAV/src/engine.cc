/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#include <cstdlib.h>
#include <cstdint.h>
#include <cstdio.h>
#include <cstring.h>
#include "engine.h"

typedef struct
{
    uint16_t magic;
    uint16_t format;
    uint16_t width;
    uint16_t height;
    uint8_t comment[32];
} bmp_hdr_t;

typedef struct
{
    uint32_t magic;
    uint32_t ip;
    uint32_t ro_addr;
    uint32_t ro_size;
    uint32_t rw_addr;
    uint32_t rw_size;
    uint32_t zero_addr;
    uint32_t zero_size;
} exe_hdr_t;

Engine::Engine()
{
    if (allocate(Emulator::HEAP_SIZE, 0, (void **)&d_heap) != 0)
        _terminate(1);
}

Engine::~Engine()
{
}

bool Engine::process(unsigned char *data, unsigned int len)
{
    d_malware = false;

    // test for whitelist
    if (d_whitelist.query(data, len))
        return false;

    // test original data against rules
    if (d_db.query(data, len))
        d_malware = true;

    // test bmp heuristics
    if (is_bmp(data, len))
        process_bmp(data, len);

    // test exe heuristics
    if (is_exe(data, len))
        process_exe(data, len);

    return d_malware;
}

bool Engine::update_rules(unsigned char *data, unsigned int len)
{
    unsigned int cksum = 0x12345678;

    if (len < 8)
        return false;

    // verify checksum
    for (unsigned int i = 4; i < len; i++)
        cksum += data[i];
    cksum += *(unsigned int *)data;
    if (cksum != 0)
        return false;

    // process rules
    for (unsigned int i = 4; i < len - 4; )
    {
        bool to_remove;
        unsigned int rlen;

        if (data[i] == 0)
            to_remove = false;
        else if (data[i] == 1)
            to_remove = true;
        else
            return false;
        i++;

        rlen = *(unsigned int *)&data[i];
        i += 4;

        if (rlen > len || (i + rlen) > len)
            return false;

        if (to_remove)
            d_db.remove(&data[i], rlen);
        else
            d_db.add(&data[i], rlen);
        i += rlen;
    }

    return true;
}

bool Engine::is_bmp(unsigned char *data, unsigned int len)
{
    bmp_hdr_t *hdr = (bmp_hdr_t *)data;
    if (len < sizeof(bmp_hdr_t))
        return false;
    return hdr->magic == 0xA9C0;
}

void Engine::process_bmp(unsigned char *data, unsigned int len)
{
    bmp_hdr_t *hdr = (bmp_hdr_t *)data;

    if (hdr->magic != 0xA9C0)
        return;

    if (hdr->format == 0 && hdr->width * hdr->height * 3 != len - sizeof(bmp_hdr_t))
        // detected invalid bitmap
        d_malware = true;
}

bool Engine::is_exe(unsigned char *data, unsigned int len)
{
    exe_hdr_t *hdr = (exe_hdr_t *)data;
    if (len < sizeof(exe_hdr_t))
        return false;
    return hdr->magic == 0x4E269472;
}

void Engine::process_exe(unsigned char *data, unsigned int len)
{
    exe_hdr_t *hdr = (exe_hdr_t *)data;
    unsigned char stack[Emulator::STACK_SIZE];
    Emulator e(stack, d_heap);

    // clear heap and registers
    e.reset();

    data += sizeof(exe_hdr_t);
    len -= sizeof(exe_hdr_t);

    // validate header information
    if (hdr->magic != 0x4E269472 || (hdr->ip >> 30) != 0)
        return;

    // initialize heap from data
    if ((hdr->ro_addr >> 30) != 0 || ((hdr->ro_addr + hdr->ro_size) >> 30) != 0 || hdr->ro_size > len)
        return;
    memcpy(d_heap + hdr->ro_addr, data, hdr->ro_size);
    data += hdr->ro_size;
    len -= hdr->ro_size;

    if ((hdr->rw_addr >> 30) != 0 || ((hdr->rw_addr + hdr->rw_size) >> 30) != 0 || hdr->rw_size > len)
        return;
    memcpy(d_heap + hdr->rw_addr, data, hdr->rw_size);
    data += hdr->rw_size;
    len -= hdr->rw_size;

    if ((hdr->zero_addr >> 30) != 0 || ((hdr->zero_addr + hdr->zero_size) >> 30) != 0)
        return;
    memset(d_heap + hdr->zero_addr, 0, hdr->zero_size);

    // initialize IP
    e.set_ip(hdr->ip);

    for (unsigned int i = 0; i < 10000; i++)
    {
        if (!e.step())
            break;
        if (e.last_instruction().d_type == INS_popa)
            break;
    }

    e.traverse_dirty([this] (int mem) {
        if (d_db.query(d_heap + mem, mem == 0x40000000 - 0x1000 ? 0x1000 : 0x2000))
            d_malware = true;
    });
    if (d_db.query((unsigned char *)stack, Emulator::STACK_SIZE))
        d_malware = true;
}

void Engine::whitelist(unsigned char *data, unsigned int len)
{
    d_whitelist.add(data, len);
}
