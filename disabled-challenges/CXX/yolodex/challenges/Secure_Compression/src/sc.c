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

#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_sc.h"

bio_t* cgc_bit_new(unsigned char *data)
{
    bio_t *bio = (bio_t *) cgc_malloc(sizeof(bio_t));
    bio->data = data;
    bio->didx = 0;
    bio->bidx = 0;

    return bio;
}

unsigned char cgc_bit_read(bio_t *bio, cgc_size_t n)
{
    cgc_size_t i;
    unsigned char b = bio->data[bio->didx], ret = 0;
    for (i = 0; i < n; ++i)
    {
        if (bio->bidx == 8)
        {
            b = bio->data[++bio->didx];
            bio->bidx = 0;
        }
        unsigned char c = (b & (1 << (8 - bio->bidx - 1))) >> (8 - bio->bidx - 1);
        ret |= (c << (n - i - 1));
        bio->bidx++;
    }
    return ret;
}

void cgc_bit_write(bio_t *bio, unsigned char data, cgc_size_t n)
{
    cgc_size_t i;
    unsigned char b = bio->data[bio->didx];
    for (i = 0; i < n; ++i)
    {
        if (bio->bidx == 8)
        {
            bio->data[bio->didx] = b;
            b = bio->data[++bio->didx];
            bio->bidx = 0;
        }
        unsigned char c = (data & (1 << (8 - i - 1))) >> (8 - i - 1);
        b |= (c << (8 - bio->bidx - 1));
        bio->bidx++;
    }
    bio->data[bio->didx] = b;
}

unsigned char *cgc__find_char(unsigned char *s, unsigned char c, cgc_size_t n)
{
    cgc_size_t i;
    unsigned char *p = s;
    for (i = 0; i < n; ++i)
        if (p[i] == c)
            return &p[i];
    return NULL;
}

int cgc__sc_compare(unsigned char *order, unsigned char *s1, unsigned char *s2, cgc_size_t n)
{
    cgc_size_t i;
    unsigned char *p1, *p2;
    for (i = 0; i < n; ++i)
    {
        if (s1[i] != s2[i])
        {
            p1 = cgc__find_char(order, s1[i], n);
            p2 = cgc__find_char(order, s2[i], n);
            if (p1 == NULL || p2 == NULL)
                return s1[i] - s2[i];
            return p1 - p2;
        }
    }
    return 0;
}

sc_obj_t* cgc_sc_new(unsigned char *key)
{
    sc_obj_t *sc = (sc_obj_t *) cgc_malloc(sizeof(sc_obj_t));
    cgc_memset(sc, 0, sizeof(sc_obj_t));
    cgc_memcpy(sc->order, key, 95);
    sc->cmp = cgc__sc_compare;
    return sc;
}

int cgc_sc_scompress(sc_obj_t *sc, unsigned char **out, cgc_size_t *outlen)
{
    if (!sc || !out || !outlen)
        return -1;

    cgc_size_t old_len = sc->data_len;
    unsigned char *buf = NULL, *old = sc->data;
    buf = cgc_sc_bwt(sc, 0, outlen);
    if (!buf)
        return -1;
    sc->data = buf;
    sc->data_len = *outlen;
    *out = cgc_sc_mtf(sc, 0, outlen);
    cgc_free(buf);
    sc->data = old;
    sc->data_len = old_len;
    if (!*out)
        return -1;
    return 0;
}

int cgc_sc_sdecompress(sc_obj_t *sc, unsigned char **out, cgc_size_t *outlen)
{
    if (!sc || !out || !outlen)
        return -1;

    int l;
    cgc_size_t old_len = sc->data_len;
    unsigned char *buf = NULL, *old = sc->data;
    buf = cgc_sc_mtf(sc, 1, outlen);
    if (!buf)
        return -1;
    sc->data = buf;
    sc->data_len = *outlen;
    *out = cgc_sc_bwt(sc, 1, outlen);
    cgc_free(buf);
    sc->data = old;
    sc->data_len = old_len;
    if (!*out)
        return -1;
    return 0;
}

int cgc_sc_set_data(sc_obj_t *sc, unsigned char *data, cgc_size_t data_len)
{
    if (!sc)
        return -1;
    if (sc->data)
        cgc_free(sc->data);
    sc->data = cgc_malloc(data_len);
    cgc_memcpy(sc->data, data, data_len);
    sc->data_len = data_len;
    return 0;
}

int cgc__gcd(int a, int b)
{
    if (b == 0)
        return a;
    return cgc__gcd(b, a % b);
}

void cgc__rot_left(unsigned char *data, cgc_size_t sz, cgc_size_t rot)
{
    int i, j, k;
    char c, tmp;

    for (i = 0; i < cgc__gcd(rot, sz); ++i)
    {
        j = i;
        tmp = data[i];
        while (1)
        {
            k = j + rot;
            if (k >= sz)
                k -= sz;
            if (k == i)
                break;
            data[j] = data[k];
            j = k;
        }
        data[j] = tmp;
    }
}

void cgc__merge(unsigned char **xs, unsigned char **ys, int lo, int mid, int hi, sc_obj_t *sc)
{
    int i, j, k;
    for (i = lo, j = mid, k = lo; i < mid && j < hi; ++k)
    {
        if (sc->cmp(sc->order, xs[i], xs[j], BLOCK_SIZE) < 0)
            ys[k] = xs[i++];
        else
            ys[k] = xs[j++];
    }
    for (; i < mid; ++i, ++k)
        ys[k] = xs[i];
    for (; j < hi; ++j, ++k)
        ys[k] = xs[j];
    cgc_memcpy(&xs[lo], &ys[lo], (hi - lo) * sizeof(unsigned char *));
}

void cgc__msort(unsigned char **xs, unsigned char **ys, int lo, int hi, sc_obj_t *sc)
{
    int mid;
    if (hi - lo > 1)
    {
        mid = lo + ((hi - lo) / 2);
        cgc__msort(xs, ys, lo, mid, sc);
        cgc__msort(xs, ys, mid, hi, sc);
        cgc__merge(xs, ys, lo, mid, hi, sc);
    }
}

void cgc__sort(unsigned char **xs, int len, sc_obj_t *sc)
{
    unsigned char **ys = cgc_malloc(sizeof(unsigned char *) * len);
    cgc__msort(xs, ys, 0, len, sc);
    cgc_free(ys);
}


unsigned char* cgc_sc_bwt(sc_obj_t *sc, int op, cgc_size_t *outlen)
{
    if (sc->data_len > MAX_DATA_SIZE)
        return NULL;

    int i, j, k;
    unsigned short oidx;
    cgc_size_t size = 0, to_copy = 0, num_blocks = 0;
    unsigned char block[BLOCK_SIZE], tmp[BLOCK_SIZE];
    num_blocks = (sc->data_len / BLOCK_SIZE) + !!(sc->data_len % BLOCK_SIZE);
    *outlen = num_blocks * sizeof(short) + sc->data_len;
    num_blocks = 0;
    unsigned char **rot_table = cgc_malloc(BLOCK_SIZE * sizeof(unsigned char *));
    unsigned char *out = cgc_malloc(*outlen);
    cgc_memset(out, 0, *outlen);

    for (i = 0; i < BLOCK_SIZE; ++i)
    {
        rot_table[i] = cgc_malloc(BLOCK_SIZE);
        cgc_memset(rot_table[i], 0, BLOCK_SIZE);
    }

    if (!op)
    {
        // Compress
        while (1)
        {
            if (size >= sc->data_len)
                break;
            to_copy = sc->data_len - size > 512 ? 512 : (sc->data_len - size);
            cgc_memset(block, 0, sizeof(block));
            cgc_memcpy(block, &sc->data[size], to_copy);

            for (i = 0; i < to_copy; ++i)
            {
                cgc_memcpy(rot_table[i], block, to_copy);
                cgc__rot_left(rot_table[i], to_copy, i);
            }
            cgc__sort(rot_table, to_copy, sc);
            for (oidx = 0; oidx < to_copy; ++oidx)
                if (cgc_memcmp(rot_table[oidx], block, to_copy) == 0)
                    break;

            *(unsigned short *)&out[size + num_blocks * sizeof(short)] = oidx;
            num_blocks++;
            for (i = 0; i < to_copy; ++i)
                out[size + i + num_blocks * sizeof(short)] = rot_table[i][to_copy - 1];
            size += to_copy;
        }
    }
    else
    {
        // Decompress
        *outlen = 0;
        while (1)
        {
            if (size >= sc->data_len)
                break;

            oidx = *(unsigned short *)&sc->data[size];
            size += sizeof(short);
            to_copy = sc->data_len - size > 512 ? 512 : (sc->data_len - size);
            *outlen += to_copy;
#ifdef PATCHED_2
            if (oidx > to_copy)
                goto fail;
#endif
            cgc_memset(block, 0, sizeof(block));
            cgc_memcpy(block, &sc->data[size], to_copy);
            for (i = 0; i < BLOCK_SIZE; ++i)
                cgc_memset(rot_table[i], 0, BLOCK_SIZE);

            for (i = to_copy - 1; i >= 0; --i)
            {
                for (j = 0; j < to_copy; ++j)
                    rot_table[j][i] = block[j];

                cgc__sort(rot_table, to_copy, sc);
            }

            num_blocks++;
            for (i = 0; i < to_copy; ++i)
                out[size + i - num_blocks * sizeof(short)] = rot_table[oidx][i];
            size += to_copy;
        }
    }
    goto cleanup;

fail:
    cgc_free(out);
    out = NULL;
cleanup:
    for (i = 0; i < BLOCK_SIZE; ++i)
        cgc_free(rot_table[i]);
    cgc_free(rot_table);

    return out;
}

unsigned char* cgc_sc_mtf(sc_obj_t *sc, int op, cgc_size_t *outlen)
{
    int i, j, k;
    unsigned char list[256];

    if (!op)
    {
        // Do MTF
        unsigned char *out = cgc_malloc(sc->data_len);
        unsigned char *out_c = cgc_malloc(sc->data_len * 2 + 4);
        *(cgc_size_t *)out_c = sc->data_len;
        cgc_memset(out, 0, sc->data_len);

        for (i = 0; i < 32; ++i)
            list[i] = (unsigned char) i;
        cgc_memcpy(&list[32], sc->order, 95);
        for (i = 127; i < sizeof(list); ++i)
            list[i] = (unsigned char) i;

        for (i = 0; i < sc->data_len; ++i)
        {
            for (j = 0; j < sizeof(list); ++j)
            {
                if (sc->data[i] == list[j])
                {
                    out[i] = j;
                    break;
                }
            }
            cgc_memmove(&list[1], list, j);
            *list = sc->data[i];
        }
        cgc_memset(out_c + 4, 0, sc->data_len * 2);
        bio_t *bio = cgc_bit_new(out_c + 4);
        for (i = 0; i < sc->data_len; ++i)
        {
            if (out[i] > 0x0F)
            {
                cgc_bit_write(bio, '\x00', 1);
                cgc_bit_write(bio, out[i], 8);
            }
            else
            {
                cgc_bit_write(bio, '\x80', 1);
                cgc_bit_write(bio, out[i] << 4, 4);
            }
        }
        *outlen = bio->didx + 4 + (bio->bidx > 0);

        cgc_free(bio);
        cgc_free(out);
        bio = NULL;
        out = NULL;
        return out_c;
    }
    else
    {
        // Undo MTF
#ifdef PATCHED_1
        unsigned char out[MAX_DATA_SIZE];
#else
        unsigned char out[MAX_DATA_SIZE/2];
#endif
        cgc_size_t sz = *(cgc_size_t *)sc->data;
        if (sz > MAX_DATA_SIZE)
            return NULL;
        unsigned char *out_d = cgc_malloc(sz);
        cgc_memset(out, 0, sizeof(out));

        bio_t *bio = cgc_bit_new(sc->data + 4);
        for (i = 0; i < sz; ++i)
        {
            if (cgc_bit_read(bio, 1) == 0)
                out[i] = cgc_bit_read(bio, 8);
            else
                out[i] = cgc_bit_read(bio, 4);
        }

        for (i = 0; i < 32; ++i)
            list[i] = (unsigned char) i;
        cgc_memcpy(&list[32], sc->order, 95);
        for (i = 127; i < sizeof(list); ++i)
            list[i] = (unsigned char) i;

        for (i = 0; i < sz; ++i)
        {
            out_d[i] = list[out[i]];
            cgc_memmove(&list[1], list, out[i]);
            *list = out_d[i];
        }
        *outlen = sz;
        cgc_free(bio);
        bio = NULL;
        return out_d;
    }
}

