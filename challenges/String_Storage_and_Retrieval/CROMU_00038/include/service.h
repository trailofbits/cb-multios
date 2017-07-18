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

#ifndef SERVICE_H
#define SERVICE_H


typedef struct __attribute__((__packed__)) IFD_Array {

	unsigned short Tag;
	unsigned short Type;
	unsigned Count;
	unsigned Value;

} IFD_Array_Type;

typedef struct __attribute__((__packed__))IFD {

	unsigned short Count;
	IFD_Array_Type Entry[];

} IFD_Type;

typedef struct TIFF_Hdr {

	unsigned short Byte_Order;
	unsigned short Fixed;
	unsigned Offset_to_IFD;

}  TIFF_Hdr_Type;


void print_tag_text(unsigned short);
void print_xif_tag_text(unsigned short);
void print_gps_tag_text(unsigned short);
void process_xif_ifd(IFD_Type *, TIFF_Hdr_Type *, unsigned short, unsigned char *);
void process_gps_ifd(IFD_Type *, TIFF_Hdr_Type *, unsigned short, unsigned char *);
void print_type(unsigned short);


unsigned short motorola_swap_short(unsigned short);
unsigned motorola_swap_word(unsigned);
unsigned short intel_swap_short(unsigned short);
unsigned intel_swap_word(unsigned);


#endif
