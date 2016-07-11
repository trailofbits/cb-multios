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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ecc.h"
#include "buffer.h"
#include "checksum.h"
#include "frame.h"

/*
 * if decode is successful, writes the data to output
 *
 * returns status code indicate success/fail and packet end
 */
int frame_decode(buffer_t *input, buffer_t *output)
{
    uint8_t bits[ECC_SIZE];
    uint8_t data[FRAME_DATA_SIZE / 8];
    size_t i;
    uint64_t mark;
    uint8_t checksum1, checksum2, hdr, count;
    uint8_t tmp[FRAME_SIZE / 8];
    buffer_t tmpbuf;

    memset(bits, 0, sizeof(bits));
    for (i = 0; i < FRAME_SIZE; i++)
        bits[i] = buffer_read_bit(input);

    if (!ecc_decode(bits))
        return FRAME_FAIL;

    buffer_init(&tmpbuf, tmp, sizeof(tmp));

    for (i = ECC_PARITY_SIZE; i < FRAME_SIZE; i++)
        buffer_write_bit(&tmpbuf, bits[i]);
    
    mark = buffer_read_tell(&tmpbuf);
    checksum1 = checksum8(&tmpbuf, FRAME_DATA_SIZE + 4, 0);
    checksum2 = buffer_read_bits(&tmpbuf, 8);

    if (checksum1 != checksum2)
        return FRAME_FAIL;

    buffer_read_seek(&tmpbuf, mark);
    count = hdr = buffer_read_bits(&tmpbuf, 4);
    if (count > FRAME_DATA_SIZE / 8)
        count = FRAME_DATA_SIZE / 8;

    buffer_read_bytes(&tmpbuf, data, count);
    for (i = 0; i < count; i++)
        data[i] ^= 0x55;
    buffer_write_bytes(output, data, count);

    return hdr == 0xF ? FRAME_SUCCESS : FRAME_END;
}

void frame_encode(buffer_t *input, buffer_t *output)
{
    uint8_t bits[ECC_SIZE];
    uint8_t data[FRAME_DATA_SIZE / 8 + 1];
    uint64_t mark;
    size_t i, j, hdr, count;
    uint8_t checksum;
    uint8_t tmp[FRAME_SIZE / 8];
    buffer_t tmpbuf;
    buffer_t databuf;

    buffer_init(&tmpbuf, tmp, sizeof(tmp));
    buffer_init(&databuf, data, sizeof(data));
    
    count = hdr = buffer_read_remaining(input) / 8;
    if (count > FRAME_DATA_SIZE / 8)
    {
        count = FRAME_DATA_SIZE / 8;
        hdr = 0xF;
    }

    for (i = 0; i < count; i++)
    {
        uint8_t byte;
        buffer_read_bytes(input, &byte, 1);
        byte ^= 0x55;
        buffer_write_bytes(&databuf, &byte, 1);
    }
    for (; i < FRAME_DATA_SIZE / 8; i++)
    {
        uint8_t byte = 0x55;
        buffer_write_bytes(&databuf, &byte, 1);
    }

    mark = buffer_read_tell(&databuf);
    buffer_write_bits(&tmpbuf, hdr, 4);
    checksum = checksum8(&tmpbuf, 4, 0);
    checksum = checksum8(&databuf, FRAME_DATA_SIZE, checksum);
    buffer_read_seek(&databuf, mark);

    buffer_init(&tmpbuf, tmp, sizeof(tmp));
    buffer_write_bits(&tmpbuf, hdr, 4);
    buffer_write_bits(&tmpbuf, checksum, 8);

    memset(bits, 0, sizeof(bits));
    i = ECC_PARITY_SIZE;
    for (j = 0; j < 4; j++)
        bits[i++] = buffer_read_bit(&tmpbuf);
    for (j = 0; j < FRAME_DATA_SIZE; j++)
        bits[i++] = buffer_read_bit(&databuf);
    for (j = 0; j < 8; j++)
        bits[i++] = buffer_read_bit(&tmpbuf);

    ecc_encode(bits);

    for (i = 0; i < FRAME_SIZE; i++)
        buffer_write_bit(output, bits[i]);
}
