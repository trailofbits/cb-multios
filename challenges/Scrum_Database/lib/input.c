/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "libcgc.h"


int cgc_receive_bytes (char *buffer, cgc_size_t count) 
{
cgc_size_t total;
cgc_size_t rxbytes;

    total = 0;

    while(total < count)  {

        rxbytes = 0;

        if (cgc_receive(STDIN, buffer+total, count-total, &rxbytes)==0 ) {

            total += rxbytes;

        }
        else {

            return(-1);
        }


    }

return 0;

}


cgc_size_t cgc_receive_until( char *buffer, char delim, cgc_size_t limit )
{
    cgc_size_t len = 0;
    cgc_size_t rx = 0;
    char c = 0;

    while( len < limit ) {
        buffer[len] = 0;

        if ( cgc_receive( STDIN, &c, 1, &rx ) != 0 ) {
            len = 0;
            goto end;
        }

	if (rx == 0) {
		len = 0;
		goto end;
	}

        if ( c == delim ) {
            goto end;
        }

        buffer[len] = c;
        len++;
    }
end:
    return len;
}