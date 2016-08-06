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

unsigned short (*swap_short)(unsigned short);
unsigned (*swap_word)(unsigned);

int main(void) {

unsigned ret_code;
unsigned short SOM;
unsigned short marker;
unsigned short segment_size;
unsigned short tagMark;
unsigned short byte_align;    
unsigned char *tiff_header;
unsigned char *xif_data;
void *tmp_ptr;
void *gps_info_ptr;
unsigned offset;
TIFF_Hdr_Type *tiff_hdr;
IFD_Type *IFD;
IFD_Type *xif_ifd_ptr;
unsigned char *endofsegment_ptr;

int i;


    swap_short = 0;
    swap_word = 0;

    // read the first two bytes and check for the Start of Message marker
    ret_code = receive_bytes((unsigned char *)&SOM, sizeof(SOM));

    if (ret_code == -1 ) {

        printf("did not receive bytes\n");
        _terminate(-1);
    }

    if (SOM != 0xFFF8) {

        puts("Did not find SOM marker");
        _terminate(-1);
    }
    else {

        puts("SOM marker found");
    }

    // Now look for the next marker, which can be SAP0 or SAP1 
    ret_code = receive_bytes((unsigned char *)&marker, sizeof(marker));

    if (ret_code == -1 ) {

        printf("did not receive bytes\n");
        _terminate(-1);
    }

    // SAP0
    if (marker == 0xFFF0) {

        printf("SAP0 marker found\n");

        ret_code = receive_bytes((unsigned char *)&segment_size, sizeof(segment_size));

        if (ret_code == -1 ) {

            printf("did not receive bytes\n");
            _terminate(-1);
        }

        if (segment_size <=2) {

            printf("Invalid segment size\n", segment_size);
            _terminate(-1);
        }


        // now read and discard the rest of the SAP0 header
        xif_data = malloc(segment_size-sizeof(segment_size));

        if ((int)xif_data == 0) {

            printf("Unable to allocate memory\n");
            _terminate(-1);
        }

        // read the rest of SAP0 and discard
        ret_code=receive_bytes((unsigned char *)xif_data, segment_size-sizeof(segment_size));

        if (ret_code == -1) {

            printf("unable to read SAP0 segment\n");
            _terminate(-1);
        }

        free(xif_data);
        xif_data = 0;

        // now read the next marker, which should be SAP1
        ret_code = receive_bytes((unsigned char *)&marker, sizeof(marker));

        if (ret_code == -1 ) {

            printf("did not receive bytes\n");
            _terminate(-1);
        }

    } // SAP0 header

    // look for the SAP1 marker now
    if (marker != 0xffF1) {

        printf("Did not find SAP1 marker\n");
        _terminate(-1);

    }
    else {

        printf("SAP1 marker found\n");

    }

    // read the length of the overall segment
    ret_code = receive_bytes((unsigned char *)&segment_size, sizeof(segment_size));

    if (ret_code == -1 ) {

        printf("did not receive bytes\n");
        _terminate(-1);
    }

    printf("sizeof section is @d\n", segment_size);

    if (segment_size <= 0) {

        printf("Invalid segment size\n");
        _terminate(-1);
    }
    
    xif_data = malloc(segment_size);

    if ((int)xif_data == 0) {

        printf("Unable to allocate memory\n");
        _terminate(-1);
    }

    ret_code=receive_bytes((unsigned char *)xif_data, segment_size);

    if (ret_code == -1) {

        printf("unable to read SAP1 segment\n");
        _terminate(-1);
    }

    // tiff header + xif header + the count of IFD segments
    if (segment_size < sizeof(TIFF_Hdr_Type) + 6 + 2) {

        printf("not enough data received\n");
        _terminate(-1);
    }

    tiff_hdr = (TIFF_Hdr_Type *)(xif_data+6);

    endofsegment_ptr = (unsigned char *)xif_data + segment_size;

    if (tiff_hdr->Byte_Order == 0x4949) {

        printf("Intel formatted integers\n");

        swap_short = intel_swap_short;
        swap_word = intel_swap_word;
    }

    else if (tiff_hdr->Byte_Order == 0x4d4d) {

        printf("Motorola formatted integers\n");

        swap_short = motorola_swap_short;
        swap_word = motorola_swap_word;
    }
#ifdef PATCHED
    else {
        printf("Invalid header values\n");
        _terminate(-1);
    }
#endif

    printf("TagMark = @x\n", swap_short(tiff_hdr->Fixed));

    offset = swap_word(tiff_hdr->Offset_to_IFD);

    printf("Offset = @x\n", swap_word(tiff_hdr->Offset_to_IFD));

    if (offset > segment_size) {

        printf("Invalid offset\n");
        _terminate(-1);
    }

    IFD = (void *)(tiff_hdr) + swap_word(tiff_hdr->Offset_to_IFD);


    // how many array entries are there
    IFD->Count = swap_short(IFD->Count);

    printf("# of compatility arrays: @d\n", IFD->Count);

    if (IFD->Count * 12 > segment_size - sizeof(TIFF_Hdr_Type) - 6 - 2) {

        printf("Invalid number of IFD entries\n");
        _terminate(-1);
    }

    // loop through all of the entries in the array
    for (i=0; i< (IFD->Count); ++i) {

        printf("Tag: @x (", swap_short(IFD->Entry[i].Tag));
        print_tag_text(swap_short(IFD->Entry[i].Tag));
        printf(")\n");
        printf("Type: @x (", swap_short(IFD->Entry[i].Type));
        print_type(swap_short(IFD->Entry[i].Type));
        printf(")\n");
        printf("Count: @d\n", swap_word(IFD->Entry[i].Count));

        if (swap_short(IFD->Entry[i].Type) == 2) {

            if (swap_word(IFD->Entry[i].Value) < segment_size - 8 && swap_word(IFD->Entry[i].Value) > 0)
#ifdef PATCHED
		{
		if ( strlen( (char *)(tiff_hdr) + swap_word(IFD->Entry[i].Value)) > 2048) {
			((char *)(tiff_hdr))[swap_word(IFD->Entry[i].Value)+2048] = '\x00';
		}
#endif
                printf("Value: @s\n", (char *)(tiff_hdr) + swap_word(IFD->Entry[i].Value));
#ifdef PATCHED
		}
#endif

            else

                printf("Value: 0\n");
        }
        else {

             printf("Value: @u\n", swap_word(IFD->Entry[i].Value));

        }

        if (swap_short(IFD->Entry[i].Tag) == 0x8825) {

            gps_info_ptr = (void *)tiff_hdr + swap_word(IFD->Entry[i].Value);

            process_gps_ifd(gps_info_ptr, tiff_hdr, segment_size, endofsegment_ptr);

        }
        else if (swap_short(IFD->Entry[i].Tag) == 0x8769) {

            xif_ifd_ptr = (void *)tiff_hdr + swap_word(IFD->Entry[i].Value);

            process_xif_ifd(xif_ifd_ptr, tiff_hdr, segment_size, endofsegment_ptr);

        }
    }
 
    puts("Finished processing");

}  // main  

