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

#include <libcgc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readuntil.h"
#include "otp.h"

int main()
{
    otp_t *o = NULL;
    unsigned int cmd = 0;

    fbuffered(stdout, 1);

    while (1)
    {
        if (read_n(STDIN, (char *)&cmd, sizeof(unsigned int)) != sizeof(unsigned int))
            return 0;
        if (cmd == 0x4b414853)          // SHAK
            otp_handshake(&o);
        else if (cmd == 0x4f4e4547)     // GENO
            otp_generate_otp(o);
        else if (cmd == 0x444e5458)     // XTND
            otp_extend_session(o);
        else if (cmd == 0x44454553)     // SEED
            otp_set_seeds(o);
        else if (cmd == 0x49524556)     // VERI
            otp_verify_otp(o);
        else if (cmd == 0x54495551)     // QUIT
        {
            fwrite("\x00", 1, stdout);
            fflush(stdout);
            _terminate(0);
        }
        else
            fwrite("\xFF", 1, stdout);
    }
    return 0;
}
