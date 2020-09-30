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

void print_tag_text(unsigned short tag) {


    switch (tag) {

        case 0x100:

            cgc_printf("ImageWidth");
            break;
        
        case 0x101:

            cgc_printf("ImageLength");
            break;

        case 0x102:

            cgc_printf("BitsPerSample");
            break;

        case 0x103:

            cgc_printf("Compression");
            break;

        case 0x106:

            cgc_printf("PhotometricInterpretation");
            break;

        case 0x112:

            cgc_printf("Orientation");
            break;

        case 0x115:

            cgc_printf("SamplesPerPixel");
            break;

        case 0x11c:

            cgc_printf("PlanarConfiguration");
            break;

        case 0x212:

            cgc_printf("YCbCrSubSampling");
            break;

        case 0x213:

            cgc_printf("YCbCrPositioning");
            break;

        case 0x11a:

            cgc_printf("XResolution");
            break;

        case 0x11b:

            cgc_printf("YResolution");
            break;

        case 0x128:

            cgc_printf("ResolutionUnit");
            break;

        case 0x111:

            cgc_printf("StripOffsets");
            break;

        case 0x116:

            cgc_printf("RowsPerStrip");
            break;

        case 0x117:

            cgc_printf("StripByteCounts");
            break;

        case 0x201:

            cgc_printf("InterchangeFormat");
            break;

        case 0x202:

            cgc_printf("InterchangeFormatLength");
            break;

        case 0x12d:

            cgc_printf("TransferFunction");
            break;

        case 0x13e:

            cgc_printf("WhitePoint");
            break;

        case 0x13f:

            cgc_printf("PrimaryChromaticities");
            break;

        case 0x211:

            cgc_printf("YCbCrCoefficients");
            break;

        case 0x214:

            cgc_printf("ReferenceBlackWhite");
            break;

        case 0x132:

            cgc_printf("DateTime");
            break;

        case 0x10e:

            cgc_printf("ImageDescription");
            break;

        case 0x10f:

            cgc_printf("Make");
            break;

        case 0x110:

            cgc_printf("Model");
            break;

        case 0x131:

            cgc_printf("Software");
            break;

        case 0x13b:

            cgc_printf("Artist");
            break;

        case 0x8298:

            cgc_printf("Copyright");
            break;

        case 0x8825:

            cgc_printf("GPS Info");
            break;

        case 0x8769:

            cgc_printf("EXIF IFD Pointer");
            break;

        case 0xc4a5:

            cgc_printf("");
            break;

    }
}

