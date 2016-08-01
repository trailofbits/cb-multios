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

void process_xif_ifd(IFD_Type *ifd_ptr, TIFF_Hdr_Type *tiff_hdr, unsigned short segment_size, unsigned char *endofsegment_ptr)  {
	
int i;
unsigned short entry_count;
unsigned short tag;
unsigned short type;
unsigned count;
unsigned value;
unsigned int remaining_size;



	remaining_size = endofsegment_ptr - (unsigned char *)ifd_ptr;

    if (remaining_size > segment_size)
        _terminate(-1);

    entry_count=swap_short(ifd_ptr->Count);

    if (entry_count *12 + sizeof(entry_count) > remaining_size) {

        printf("Invalid IFD count value\n");
        _terminate(-1);
    }

	printf("# of arrays: @d\n", entry_count);

    for (i=0; i< entry_count; ++i) {

    	tag = swap_short(ifd_ptr->Entry[i].Tag);
    	type = swap_short(ifd_ptr->Entry[i].Type);
    	count = swap_word(ifd_ptr->Entry[i].Count);
    	value = swap_word(ifd_ptr->Entry[i].Value);

        printf("Tag: @x (", tag);
        print_xif_tag_text(tag);
        printf(")\n");
        printf("Type: @x (", type);
        print_type(type);
        printf(")\n");

        printf("Count: @d\n", count);

#ifdef PATCHED

        if (type==2) {

            if ( ((char *)ifd_ptr+value > (char *)tiff_hdr+segment_size) ||
                ((char *)ifd_ptr+value < (char *)ifd_ptr ))
        {

                printf("Value: 0\n");
                return;
            }
        }
#endif

        if (type == 2) {
#ifdef PATCHED
	    if ( strlen( (char*)(ifd_ptr) + value ) > 2048 ) {
		((char*)(ifd_ptr))[value+2048] = '\x00';
	    }
#endif

            printf("Value: @s\n", (char *)(ifd_ptr) + value);
        }
        else {
            printf("Value: @u\n", value);
        }

    }
}
