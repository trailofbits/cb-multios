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
#include <string.h>

#include "bitwriter.h"
#include "dct.h"
#include "huffman.h"

#include "tables.c"

#define M_SOF0 0xFF00
#define M_DHT 0xFF01
#define M_SOI 0xFF02
#define M_EOI 0xFF03
#define M_SOS 0xFF04
#define M_DQT 0xFF05
#define M_APP0 0xFF06

struct {
    uint8_t qt[2][64];
    ht_t ht_dc[2];
    ht_t ht_ac[2];
    int pred[3];
    uint8_t output_buffer[128*1024];
    int output_idx;
    bitwriter_t bw;
} encoder;

typedef struct {
    uint16_t header;
    uint32_t size;
    uint16_t reserved0;
    uint16_t reserved1;
    uint32_t offset;
} __attribute__((__packed__)) bmp_file_t;

typedef struct {
    uint32_t info_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t comp;
    uint32_t data_size;
    int32_t hres;
    int32_t vres;
    uint32_t colors;
    uint32_t important_colors;
} __attribute__((__packed__)) bmp_info_t;

static int8_t tmp_y[64];
static int8_t tmp_u[64];
static int8_t tmp_v[64];

static int recvall(int fd, uint8_t *buf, size_t cnt, size_t *cntout)
{
    size_t tmp;
    *cntout = 0;
    do {
        if (receive(STDIN, buf, cnt - *cntout, &tmp) != 0 || tmp == 0)
            return 1;
        buf += tmp;
        *cntout += tmp;
    } while (*cntout < cnt);
    return 0;
}

static void encode_code(bitwriter_t *bw, ht_t *ht, int val, int run)
{
    int abs = val < 0 ? -val : val;
    int bits = 0;
    while ((1 << bits)-1 < abs)
        bits++;
    int rs = (run << 4) | bits;
    bitwriter_output(bw, ht->codes[rs], ht->sizes[rs]);
    bitwriter_output(bw, (val < 0 ? val-1 : val), bits);
}

static void encode_comp(int comp, const int8_t mb[])
{
    ht_t *ht_dc = &encoder.ht_dc[comp == 0 ? 0 : 1];
    ht_t *ht_ac = &encoder.ht_ac[comp == 0 ? 0 : 1];

    int16_t out1[64];
    dct(mb, out1, encoder.qt[comp == 0 ? 0 : 1]);

    encode_code(&encoder.bw, ht_dc, out1[ZZ[0]] - encoder.pred[comp], 0);
    encoder.pred[comp] = out1[ZZ[0]];

    int run = 0;
    int i, last = 0;
    for (i = 1; i < 64; i++)
    {
        if (out1[ZZ[i]] == 0)
        {
            run++;
        }
        else
        {
            while (run >= 16)
            {
                encode_code(&encoder.bw, ht_ac, 0, 15);
                run -= 16;
            }
            encode_code(&encoder.bw, ht_ac, out1[ZZ[i]], run);
            last = i;
            run = 0;
        }
    }

    if (last != 63)
        encode_code(&encoder.bw, ht_ac, 0, 0);
}

static int clamp(int value)
{
    if (value < 1) return 1;
    else if (value > 255) return 255;
    else return value;
}

static void set_quality(uint8_t qt[], int quality)
{
    if (quality < 0 || quality > 100)
        return;

    int S;
    if (quality < 50)
        S = 5000 / quality;
    else
        S = 200 - 2 * quality;

    int i;
    for (i = 0; i < 64; i++)
    {
        qt[i] = clamp((qt[i] * S + 50) / 100);
    }
}

static void output_byte(uint8_t byte)
{
#ifdef PATCHED
    if (encoder.output_idx >= sizeof(encoder.output_buffer))
        exit(2);
#endif
    encoder.output_buffer[encoder.output_idx++] = byte;
}

static void output_byte_stuffed(uint8_t byte)
{
    output_byte(byte);
    if (byte == 0xFF)
    {
        output_byte(0x00);
    }
}

static void output_word(uint16_t word)
{
    output_byte(word >> 8);
    output_byte(word & 0xFF);
}

static void output_bytes(const void *s, int count)
{
    int i;
    for (i = 0; i < count; i++)
        output_byte(((uint8_t*)s)[i]);
}

static void output_dqt(const uint8_t qt[], int info)
{
    output_word(M_DQT);
    output_word(3 + 64); // size
    output_byte(info); // P/T
    
    int i;
    for (i = 0; i < 64; i++)
        output_byte(qt[ZZ[i]]);
}

int main()
{
    bmp_file_t bmp_file;
    bmp_info_t bmp_info;
    size_t rx;

    if (recvall(STDIN, (uint8_t*)&bmp_file, sizeof(bmp_file), &rx) != 0 || rx != sizeof(bmp_file))
        goto error;
    if (bmp_file.header != 0x4743)
        goto error;
    if (bmp_file.size < sizeof(bmp_file) + sizeof(bmp_info))
        goto error;
    if (bmp_file.offset != sizeof(bmp_info) + sizeof(bmp_file))
        goto error;

    if (recvall(STDIN, (uint8_t*)&bmp_info, sizeof(bmp_info), &rx) != 0 || rx != sizeof(bmp_info))
        goto error;
    if (sizeof(bmp_info) != bmp_info.info_size)
        goto error;
    if (bmp_info.width % 8)
        goto error;
    if (bmp_info.height % 8)
        goto error;
    if (bmp_info.comp != 0)
        goto error;
    if (bmp_info.planes != 1 || (bmp_info.bpp != 24 && bmp_info.bpp != 32))
        goto error;
    size_t data_size = bmp_file.size - bmp_file.offset;
    if (data_size != bmp_info.data_size)
        goto error;
    if (bmp_info.width * bmp_info.height * (bmp_info.bpp / 8) != data_size)
        goto error;
    if (1ULL * bmp_info.width * bmp_info.height > 256*256)
        goto error;

    uint8_t *data = malloc(data_size);
    if (data == NULL)
        goto error;
    if (recvall(STDIN, (uint8_t*)data, data_size, &rx) != 0 || rx != data_size)
        goto error;

    int quality = 20;
    if (bmp_file.reserved0 > 0 && bmp_file.reserved0 <= 100)
        quality = bmp_file.reserved0;

    encoder.output_idx = 0;
    bitwriter_init(&encoder.bw, output_byte_stuffed);
    huffman_decode_table(&encoder.ht_dc[0], HT_DC_L);
    huffman_decode_table(&encoder.ht_dc[1], HT_DC_C);
    huffman_decode_table(&encoder.ht_ac[0], HT_AC_L);
    huffman_decode_table(&encoder.ht_ac[1], HT_AC_C);
    memcpy(encoder.qt[0], Q50_L, 64);
    memcpy(encoder.qt[1], Q50_C, 64);
    set_quality(encoder.qt[0], quality);
    set_quality(encoder.qt[1], quality);
    
    output_word(M_SOI);

    output_word(M_APP0);
    output_word(16); // size
    output_bytes("ACGC", 5); // APP0 type
    output_word(0xAACC); // version
    output_byte(1); // units
    output_word(72); // density x
    output_word(72); // density y
    output_byte(0); // x thumbnail
    output_byte(0); // y thumbnail

    output_dqt(encoder.qt[0], 0);
    output_dqt(encoder.qt[1], 1);

    output_word(M_SOF0);
    output_word(17); // size
    output_byte(8); // precision
    output_word(bmp_info.width); // x res
    output_word(bmp_info.height); // y res
    output_byte(3); // number of components
    output_byte(1); // comp id
    output_byte(0x11); // Horz / Vert
    output_byte(0); // comp qt
    output_byte(2); // comp id
    output_byte(0x11); // Horz / Vert
    output_byte(1); // comp qt
    output_byte(3); // comp id
    output_byte(0x11); // Horz / Vert
    output_byte(1); // comp qt

    output_word(M_DHT);
    output_word(3 + sizeof(HT_DC_L)); // size
    output_byte(0x00); // htInfo
    output_bytes(HT_DC_L, sizeof(HT_DC_L));

    output_word(M_DHT);
    output_word(3 + sizeof(HT_DC_C)); // size
    output_byte(0x01); // htInfo
    output_bytes(HT_DC_C, sizeof(HT_DC_C));

    output_word(M_DHT);
    output_word(3 + sizeof(HT_AC_L)); // size
    output_byte(0x10); // htInfo
    output_bytes(HT_AC_L, sizeof(HT_AC_L));

    output_word(M_DHT);
    output_word(3 + sizeof(HT_AC_C)); // size
    output_byte(0x11); // htInfo
    output_bytes(HT_AC_C, sizeof(HT_AC_C));

    output_word(M_SOS);
    output_word(12); // size
    output_byte(3); // nr components
    output_byte(0x01); // comp id
    output_byte(0x00); // AC / DC
    output_byte(0x02); // comp id
    output_byte(0x11); // AC / DC
    output_byte(0x03); // comp id
    output_byte(0x11); // AC / DC
    output_byte(0); // Ss (0 for sequential DCT)
    output_byte(63); // Se (63 for sequential DCT)
    output_byte(0); // Ah/Al (0 for sequential DCT)

    encoder.pred[0] = 0;
    encoder.pred[1] = 0;
    encoder.pred[2] = 0;

    int u, v;
    for (u = bmp_info.height-8; u >= 0; u -= 8)
    {
        for (v = 0; v < bmp_info.width; v += 8)
        {
            int i, j;
            for (j = 0; j < 8; j++)
            {
                for (i = 0; i < 8; i++)
                {
                    uint8_t *pixel = &data[((u+7-j) * bmp_info.width + (v+i)) * (bmp_info.bpp / 8)];
                    tmp_y[j * 8 + i] = -128.0 + 0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];
                    tmp_u[j * 8 + i] = 0.0 - 0.168736 * pixel[2] - 0.331264 * pixel[1] + 0.5 * pixel[0];
                    tmp_v[j * 8 + i] = 0.0 + 0.5 * pixel[2] - 0.418688 * pixel[1] - 0.081312 * pixel[0];
                }
            }
            encode_comp(0, tmp_y);
            encode_comp(1, tmp_u);
            encode_comp(2, tmp_v);
        }
    }
    bitwriter_flush(&encoder.bw, 1);

    output_word(M_EOI);

    size_t tx;
    if (writeall(STDOUT, encoder.output_buffer, encoder.output_idx) == encoder.output_idx)
        return 0;
error:
    return 1;
}
