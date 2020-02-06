/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_libdupe.h"
#include "cgc_cablegrind.h"

int main(int cgc_argc, char *cgc_argv[]) {
    int i;
    uint32_t filesize;
    uint8_t *data;
    uint8_t *warmup;
    dupefile_t *f;

    //we want to warmup the heap for performance or something
    //actually just to ensure heap corruption is a bit easier
    for(i = 1024; i > 0; i--) {
        warmup = cgc_malloc((i+1)*2);
        cgc_free(warmup);
    }


    cgc___stack_cookie_init();

    RECV(sizeof(uint32_t),(char *)&filesize);

    if (filesize > MAX_DUPE_SIZE)
        return 1;

    cgc_setheap(0);
    data = cgc_malloc(filesize);

    if (!data)
        return 2;

    RECV(filesize,(char *)data);

    f = cgc_dupe_open(data);

    if (!f || f->caplen != filesize-sizeof(dupefile_t)) {
        LOG("Bad file.")
        return 3;
    }

    cgc_process_dupe(f);

    cgc_setheap(0);
    cgc_dupe_close(f);

    return 0;
}
