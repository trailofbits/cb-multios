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
#include <string.h>

#include "sfile.h"

int recvall(int fd, void *dst, size_t size);

SFILE *open_sfile()
{
    size_t rx, idx = 0;
    unsigned int filesize = 0;
    SFILE tmp_sfp;
    SFILE *sfp = &tmp_sfp, *new_sfp = NULL;

    if (recvall(STDIN, sfp, sizeof(SFILE)) < 0)
        goto error;

    if (memcmp(sfp->magic, "SFP", 3) != 0)
        goto error;

    if (sfp->file_type != BINARY && sfp->file_type != ASCII)
        goto error;

    if (sfp->name[15] != '\0')
        goto error;

    if (sfp->size == 0)
        goto error;

    new_sfp = malloc(sizeof(SFILE) + sfp->size + 1);
    if (!new_sfp)
        goto error;
    memcpy(new_sfp, sfp, sizeof(SFILE));


    if (recvall(STDIN, &new_sfp->data[0], sfp->size) < 0)
        goto error;
    new_sfp->data[sfp->size] = '\0';

    return new_sfp;

error:
    if (new_sfp)
        free(new_sfp);
    return NULL;
}

void close_sfile(SFILE **psfp)
{
    SFILE *sfp = *psfp;
    if (sfp)
        free(sfp);

    *psfp = NULL;
}

