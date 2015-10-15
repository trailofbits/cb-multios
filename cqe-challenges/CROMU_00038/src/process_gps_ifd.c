/*

Author: Steve Wood <swood@cromulence.co>

Copyright (c) 2014 Cromulence LLC

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

#include <libcgc.h>
#include "stdlib.h"
#include "service.h"


extern unsigned short (*swap_short)(unsigned short);
extern unsigned (*swap_word)(unsigned);


void process_gps_ifd(IFD_Type *ifd_ptr, TIFF_Hdr_Type * tiff_hdr, unsigned short segment_size, unsigned char *endofsegment_ptr) {
	
int i;
unsigned short count;
unsigned int remaining_size;


    if ((unsigned char *)ifd_ptr > endofsegment_ptr) {

        _terminate(-1);
    }

    if ((unsigned char *)ifd_ptr < (unsigned char *)tiff_hdr) {

        _terminate(-1);
    }	

    count = swap_short(ifd_ptr->Count);

    remaining_size = endofsegment_ptr - (unsigned char *)ifd_ptr;

    if (remaining_size > segment_size)
        _terminate(-1);

    if (count *12 + sizeof(count) > remaining_size) {

        printf("Invalid GPS_IFD count value\n");
        _terminate(-1);
    }

	printf("# of arrays: @d\n", count);

    for (i=0; i< count; ++i) {

        printf("Tag: @x (", swap_short(ifd_ptr->Entry[i].Tag));
        print_gps_tag_text(swap_short(ifd_ptr->Entry[i].Tag));
        printf(")\n");

        printf("Type: @x (", swap_short(ifd_ptr->Entry[i].Type));
        print_type(swap_short(ifd_ptr->Entry[i].Type));
        printf(")\n");
        printf("Count: @x\n", swap_word(ifd_ptr->Entry[i].Count));
        printf("Value: @u\n", swap_word(ifd_ptr->Entry[i].Value));

    }

}