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


void print_xif_tag_text(unsigned short tag) 

{
    switch (tag) {

        case 0x9000:

            cgc_printf("ExifVersion");
            break;

        case 0xa000:

            cgc_printf("FlashpixVersion");
            break;

        case 0xa001:

            cgc_printf("ColorSpace");
            break;

        case 0x9101:

            cgc_printf("ComponentsConfiguration");
            break;

        case 0x9102:

            cgc_printf("CompressedBitsPerPixel");
            break;

        case 0xa002:

            cgc_printf("PixelXDimension");
            break;

        case 0xa003:

            cgc_printf("PixelYDimension");
            break;

        case 0x927c:

            cgc_printf("MakeNote");
            break;

        case 0x9286:

            cgc_printf("UserComment");
            break;

        case 0xa004:

            cgc_printf("RelatedSoundFile");
            break;

        case 0x9003:

            cgc_printf("DateTimeOriginal");
            break;

        case 0x9004:

            cgc_printf("DateTimeDigitized");
            break;

        case 0x9290:

            cgc_printf("SubSecTime");
            break;

        case 0x9291:

            cgc_printf("SubSecTimeOriginal");
            break;

        case 0x9292:

            cgc_printf("SubSecTimeDigitized");
            break;

        case 0xa420:

            cgc_printf("ImageUniqueID");
            break;

        case 0x829a:

            cgc_printf("ExposureTime");
            break;

        case 0x829d:

            cgc_printf("FNumber");
            break;

        case 0x8822:

            cgc_printf("ExposureProgram");
            break;

        case 0x8824:

            cgc_printf("SpectralSensitivity");
            break;

        case 0x8827:

            cgc_printf("ISOSpeedRatings");
            break;

        case 0x8828:

            cgc_printf("OECF");
            break;

        case 0x9201:

            cgc_printf("ShutterSpeedValue");
            break;

        case 0x9202:

            cgc_printf("ApertureValue");
            break;

        case 0x9203:

            cgc_printf("BrightnessValue");
            break;

        case 0x9204:

            cgc_printf("ExposureBiasValue");
            break;

        case 0x9205:

            cgc_printf("MaxApertureValue");
            break;

        case 0x9206:

            cgc_printf("SubjectDistance");
            break;

        case 0x9207:

            cgc_printf("MeteringMode");
            break;

        case 0x9208:

            cgc_printf("LightSource");
            break;

        case 0x9209:

            cgc_printf("Flash");
            break;

        case 0x920a:

            cgc_printf("FocalLength");
            break;

        case 0x9214:

            cgc_printf("SubjectArea");
            break;

        case 0xa20b:

            cgc_printf("FlashEnergy");
            break;

        case 0xa20c:

            cgc_printf("SpatialFrequencyResponse");
            break;

        case 0xa20e:

            cgc_printf("FocalPlaneXResolution");
            break;

        case 0xa20f:

            cgc_printf("FocalPlaneYResolution");
            break;

        case 0xa210:

            cgc_printf("FocalPlaneResolutionUnit");
            break;

        case 0xa214:

            cgc_printf("SubjectLocation");
            break;

        case 0xa215:

            cgc_printf("ExposureIndex");
            break;

        case 0xa217:

            cgc_printf("SensingMethod");
            break;

        case 0xa300:

            cgc_printf("FileSource");
            break;

        case 0xa301:

            cgc_printf("SceneType");
            break;

        case 0xa302:

            cgc_printf("CFAPattern");
            break;

        case 0xa401:

            cgc_printf("CustomRendered");
            break;

        case 0xa402:

            cgc_printf("ExposureMode");
            break;

        case 0xa403:

            cgc_printf("WhiteBalance");
            break;

        case 0xa404:

            cgc_printf("DigitalZoomRatio");
            break;

        case 0xa405:

            cgc_printf("FocalLengthin35mmFilm");
            break;

        case 0xa406:

            cgc_printf("SceneCaptureType");
            break;

        case 0xa407:

            cgc_printf("GainControl");
            break;

        case 0xa408:

            cgc_printf("Contrast");
            break;

        case 0xa409:

            cgc_printf("Saturation");
            break;

        case 0xa40a:

            cgc_printf("Sharpness");
            break;

        case 0xa40b:

            cgc_printf("DeviceSettingDescription");
            break;

        case 0xa40c:

            cgc_printf("SubjectDistanceRange");
            break;

    } //switch

} // print_xif_tag_text

