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
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "endian.h"
#include "io.h"
#include "protocols.h"
#include "time.h"
#include "vault.h"

#define VAULT_SIZE 500

typedef struct {
    void *data;
    unsigned int len;
} locker_t;

typedef struct {
    unsigned long long open_time;
    unsigned int open_length;
    locker_t contents[VAULT_SIZE];
    unsigned int num_contents;
} vault_t;

vault_t *the_vault;

static void write_msg(uint8_t cmd, void *data, size_t n)
{
    uint8_t hdr[7];
    
    n++; /* for cmd byte */
    *(uint16_t *)&hdr[0] = htobe16(PROTOCOL_VAULT);
    if (n < 0x8000)
    {
        *(uint16_t *)&hdr[2] = htobe16(n);
        hdr[4] = cmd;
        write_bytes(hdr, 5);
    }
    else
    {
        *(uint32_t *)&hdr[2] = htobe32(n | 0x80000000);
        hdr[6] = cmd;
        write_bytes(hdr, 7);
    }

    write_bytes(data, n-1);
}

void init_vault()
{
    the_vault = malloc(sizeof(vault_t));
    /* 2014-12-24 23:00:00 */
    the_vault->open_time = ((2208988800ULL + 1419462000) * 1000);
    the_vault->open_length = (3600 * 1000);
    the_vault->num_contents = 0;
}

int handle_msg_vault(void *data, unsigned int n)
{
    uint8_t cmd;
    uint32_t id;

    if (n < 1)
        return 0;

    cmd = *(uint8_t *)data;
    n--;
    data++;

    if (cmd == 1) /* LIST */
    {
        int i;
        uint32_t *buf = malloc(the_vault->num_contents * 8);
        if (buf == NULL)
        {
            write_msg(1, NULL, 0);
        }
        else
        {
            for (i = 0; i < the_vault->num_contents; i++)
            {
                buf[i * 2] = htobe32((uint32_t)&the_vault->contents[i]);
                buf[i * 2 + 1] = htobe32(the_vault->contents[i].len);
            }
            
            write_msg(1, buf, the_vault->num_contents * 8);
            free(buf);
        }
    }
    else if (cmd == 2) /* STORE */
    {
        id = htobe32(store_in_vault(0, data, n));
        write_msg(2, &id, sizeof(uint32_t));
    }
    else if (cmd == 3 && n >= 4) /* UPDATE */
    {
        id = betoh32(*(uint32_t *)data);
        id = htobe32(store_in_vault(id, data + 4, n - 4));
        write_msg(3, &id, sizeof(uint32_t));
    }
    else if (cmd == 4 && n >= 4) /* RETRIEVE */
    {
        void *outdata;
        unsigned int len;
        id = betoh32(*(uint32_t *)data);
        outdata = retrieve_from_vault(id, &len);
        if (outdata == NULL)
            write_msg(4, NULL, 0);
        else
            write_msg(4, outdata, len);
        free(outdata);
    }

    return 1;
}

uint32_t store_in_vault(uint32_t id, void *data, unsigned int n)
{
    locker_t *locker;
    void *copy;

    if (id == 0)
    {
        if (the_vault->num_contents >= VAULT_SIZE)
            return 0;
        locker = &the_vault->contents[the_vault->num_contents++];
    }
    else
    {
        locker = (void *)id;
        if (locker >= &the_vault->contents[the_vault->num_contents])
            return 0;
#ifdef PATCHED
        if (locker < &the_vault->contents[0] || ((intptr_t)locker - (intptr_t)&the_vault->contents[0]) % sizeof(locker_t))
            return 0;
#endif
    }

    copy = malloc(n);
    if (copy == NULL)
        return 0;

    memcpy(copy, data, n);
    locker->data = copy;
    locker->len = n;
    return (uint32_t)locker;
}

void* retrieve_from_vault(uint32_t id, unsigned int *outlen)
{
    if (current_time >= the_vault->open_time && current_time < the_vault->open_time + the_vault->open_length)
    {
        locker_t *locker = (void *)id;
#ifdef PATCHED
        if (locker < &the_vault->contents[0] || locker >= &the_vault->contents[the_vault->num_contents] || ((intptr_t)locker - (intptr_t)&the_vault->contents[0]) % sizeof(locker_t))
            return NULL;
#endif
        void *retval = locker->data;

        *outlen = locker->len;
        locker->data = NULL;
        locker->len = 0;
        return retval;
    }

    return NULL;
}
