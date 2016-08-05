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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sc.h"

bio_t* bit_new(unsigned char *data)
{
    bio_t *bio = (bio_t *) malloc(sizeof(bio_t));
    bio->data = data;
    bio->didx = 0;
    bio->bidx = 0;

    return bio;
}

unsigned char bit_read(bio_t *bio, size_t n)
{
    size_t i;
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

void bit_write(bio_t *bio, unsigned char data, size_t n)
{
    size_t i;
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

unsigned char *_find_char(unsigned char *s, unsigned char c, size_t n)
{
    size_t i;
    unsigned char *p = s;
    for (i = 0; i < n; ++i)
        if (p[i] == c)
            return &p[i];
    return NULL;
}

int _sc_compare(unsigned char *order, unsigned char *s1, unsigned char *s2, size_t n)
{
    size_t i;
    unsigned char *p1, *p2;
    for (i = 0; i < n; ++i)
    {
        if (s1[i] != s2[i])
        {
            p1 = _find_char(order, s1[i], n);
            p2 = _find_char(order, s2[i], n);
            if (p1 == NULL || p2 == NULL)
                return s1[i] - s2[i];
            return p1 - p2;
        }
    }
    return 0;
}

sc_obj_t* sc_new(unsigned char *key)
{
    sc_obj_t *sc = (sc_obj_t *) malloc(sizeof(sc_obj_t));
    memset(sc, 0, sizeof(sc_obj_t));
    memcpy(sc->order, key, 95);
    sc->cmp = _sc_compare;
    return sc;
}

int sc_scompress(sc_obj_t *sc, unsigned char **out, size_t *outlen)
{
    if (!sc || !out || !outlen)
        return -1;

    size_t old_len = sc->data_len;
    unsigned char *buf = NULL, *old = sc->data;
    buf = sc_bwt(sc, 0, outlen);
    if (!buf)
        return -1;
    sc->data = buf;
    sc->data_len = *outlen;
    *out = sc_mtf(sc, 0, outlen);
    free(buf);
    sc->data = old;
    sc->data_len = old_len;
    if (!*out)
        return -1;
    return 0;
}

int sc_sdecompress(sc_obj_t *sc, unsigned char **out, size_t *outlen)
{
    if (!sc || !out || !outlen)
        return -1;

    int l;
    size_t old_len = sc->data_len;
    unsigned char *buf = NULL, *old = sc->data;
    buf = sc_mtf(sc, 1, outlen);
    if (!buf)
        return -1;
    sc->data = buf;
    sc->data_len = *outlen;
    *out = sc_bwt(sc, 1, outlen);
    free(buf);
    sc->data = old;
    sc->data_len = old_len;
    if (!*out)
        return -1;
    return 0;
}

int sc_set_data(sc_obj_t *sc, unsigned char *data, size_t data_len)
{
    if (!sc)
        return -1;
    if (sc->data)
        free(sc->data);
    sc->data = malloc(data_len);
    memcpy(sc->data, data, data_len);
    sc->data_len = data_len;
    return 0;
}

int _gcd(int a, int b)
{
    if (b == 0)
        return a;
    return _gcd(b, a % b);
}

void _rot_left(unsigned char *data, size_t sz, size_t rot)
{
    int i, j, k;
    char c, tmp;

    for (i = 0; i < _gcd(rot, sz); ++i)
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

void _merge(unsigned char **xs, unsigned char **ys, int lo, int mid, int hi, sc_obj_t *sc)
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
    memcpy(&xs[lo], &ys[lo], (hi - lo) * sizeof(unsigned char *));
}

void _msort(unsigned char **xs, unsigned char **ys, int lo, int hi, sc_obj_t *sc)
{
    int mid;
    if (hi - lo > 1)
    {
        mid = lo + ((hi - lo) / 2);
        _msort(xs, ys, lo, mid, sc);
        _msort(xs, ys, mid, hi, sc);
        _merge(xs, ys, lo, mid, hi, sc);
    }
}

void _sort(unsigned char **xs, int len, sc_obj_t *sc)
{
    unsigned char **ys = malloc(sizeof(unsigned char *) * len);
    _msort(xs, ys, 0, len, sc);
    free(ys);
}


unsigned char* sc_bwt(sc_obj_t *sc, int op, size_t *outlen)
{
    if (sc->data_len > MAX_DATA_SIZE)
        return NULL;

    int i, j, k;
    unsigned short oidx;
    size_t size = 0, to_copy = 0, num_blocks = 0;
    unsigned char block[BLOCK_SIZE], tmp[BLOCK_SIZE];
    num_blocks = (sc->data_len / BLOCK_SIZE) + !!(sc->data_len % BLOCK_SIZE);
    *outlen = num_blocks * sizeof(short) + sc->data_len;
    num_blocks = 0;
    unsigned char **rot_table = malloc(BLOCK_SIZE * sizeof(unsigned char *));
    unsigned char *out = malloc(*outlen);
    memset(out, 0, *outlen);

    for (i = 0; i < BLOCK_SIZE; ++i)
    {
        rot_table[i] = malloc(BLOCK_SIZE);
        memset(rot_table[i], 0, BLOCK_SIZE);
    }

    if (!op)
    {
        // Compress
        while (1)
        {
            if (size >= sc->data_len)
                break;
            to_copy = sc->data_len - size > 512 ? 512 : (sc->data_len - size);
            memset(block, 0, sizeof(block));
            memcpy(block, &sc->data[size], to_copy);

            for (i = 0; i < to_copy; ++i)
            {
                memcpy(rot_table[i], block, to_copy);
                _rot_left(rot_table[i], to_copy, i);
            }
            _sort(rot_table, to_copy, sc);
            for (oidx = 0; oidx < to_copy; ++oidx)
                if (memcmp(rot_table[oidx], block, to_copy) == 0)
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
            memset(block, 0, sizeof(block));
            memcpy(block, &sc->data[size], to_copy);
            for (i = 0; i < BLOCK_SIZE; ++i)
                memset(rot_table[i], 0, BLOCK_SIZE);

            for (i = to_copy - 1; i >= 0; --i)
            {
                for (j = 0; j < to_copy; ++j)
                    rot_table[j][i] = block[j];

                _sort(rot_table, to_copy, sc);
            }

            num_blocks++;
            for (i = 0; i < to_copy; ++i)
                out[size + i - num_blocks * sizeof(short)] = rot_table[oidx][i];
            size += to_copy;
        }
    }
    goto cleanup;

fail:
    free(out);
    out = NULL;
cleanup:
    for (i = 0; i < BLOCK_SIZE; ++i)
        free(rot_table[i]);
    free(rot_table);

    return out;
}

unsigned char* sc_mtf(sc_obj_t *sc, int op, size_t *outlen)
{
    int i, j, k;
    unsigned char list[256];

    if (!op)
    {
        // Do MTF
        unsigned char *out = malloc(sc->data_len);
        unsigned char *out_c = malloc(sc->data_len * 2 + 4);
        *(size_t *)out_c = sc->data_len;
        memset(out, 0, sc->data_len);

        for (i = 0; i < 32; ++i)
            list[i] = (unsigned char) i;
        memcpy(&list[32], sc->order, 95);
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
            memmove(&list[1], list, j);
            *list = sc->data[i];
        }
        memset(out_c + 4, 0, sc->data_len * 2);
        bio_t *bio = bit_new(out_c + 4);
        for (i = 0; i < sc->data_len; ++i)
        {
            if (out[i] > 0x0F)
            {
                bit_write(bio, '\x00', 1);
                bit_write(bio, out[i], 8);
            }
            else
            {
                bit_write(bio, '\x80', 1);
                bit_write(bio, out[i] << 4, 4);
            }
        }
        *outlen = bio->didx + 4 + (bio->bidx > 0);

        free(bio);
        free(out);
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
        size_t sz = *(size_t *)sc->data;
        if (sz > MAX_DATA_SIZE)
            return NULL;
        unsigned char *out_d = malloc(sz);
        memset(out, 0, sizeof(out));

        bio_t *bio = bit_new(sc->data + 4);
        for (i = 0; i < sz; ++i)
        {
            if (bit_read(bio, 1) == 0)
                out[i] = bit_read(bio, 8);
            else
                out[i] = bit_read(bio, 4);
        }

        for (i = 0; i < 32; ++i)
            list[i] = (unsigned char) i;
        memcpy(&list[32], sc->order, 95);
        for (i = 127; i < sizeof(list); ++i)
            list[i] = (unsigned char) i;

        for (i = 0; i < sz; ++i)
        {
            out_d[i] = list[out[i]];
            memmove(&list[1], list, out[i]);
            *list = out_d[i];
        }
        *outlen = sz;
        free(bio);
        bio = NULL;
        return out_d;
    }
}

