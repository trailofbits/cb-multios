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

#include "cgc_cstdlib.h"
#include "cgc_cstdio.h"
#include "cgc_cstring.h"
#include "cgc_engine.h"
#include "cgc_interface.h"

extern "C" int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

    char *secret_page = (char *)secret_page_i;
    (void) secret_page;

    unsigned char ruleset[128 + 9];
    unsigned char *data = NULL;
    unsigned int cksum = 0;
    unsigned int len;
    Engine eng;
    Interface intf(eng);

    *(unsigned int *)&ruleset[0] = 0;
    *(unsigned char *)&ruleset[4] = 0;
    *(unsigned int *)&ruleset[5] = 128;
    cgc_memcpy(&ruleset[9], secret_page, 128);

    for (unsigned int i = 4; i < sizeof(ruleset); i++)
        cksum -= ruleset[i];
    *(unsigned int *)&ruleset[0] = cksum - 0x12345678;

    if (!eng.update_rules(ruleset, sizeof(ruleset)))
    {
        cgc_fprintf(cgc_stderr, "failed to add secret rule\n");
        return 0;
    }

    do {
        if (cgc_fread(&len, 4, cgc_stdin) != 4) break;
        if (len > 0x40000000) break;

        cgc_free(data);
        data = (unsigned char *)cgc_malloc(len);
        if (data == NULL || cgc_fread(data, len, cgc_stdin) != len) break;
    } while (intf.process(data, len));

    cgc_free(data);
    return 0;
}
