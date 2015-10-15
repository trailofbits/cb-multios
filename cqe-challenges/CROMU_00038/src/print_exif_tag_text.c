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

            printf("ExifVersion");
            break;

        case 0xa000:

            printf("FlashpixVersion");
            break;

        case 0xa001:

            printf("ColorSpace");
            break;

        case 0x9101:

            printf("ComponentsConfiguration");
            break;

        case 0x9102:

            printf("CompressedBitsPerPixel");
            break;

        case 0xa002:

            printf("PixelXDimension");
            break;

        case 0xa003:

            printf("PixelYDimension");
            break;

        case 0x927c:

            printf("MakeNote");
            break;

        case 0x9286:

            printf("UserComment");
            break;

        case 0xa004:

            printf("RelatedSoundFile");
            break;

        case 0x9003:

            printf("DateTimeOriginal");
            break;

        case 0x9004:

            printf("DateTimeDigitized");
            break;

        case 0x9290:

            printf("SubSecTime");
            break;

        case 0x9291:

            printf("SubSecTimeOriginal");
            break;

        case 0x9292:

            printf("SubSecTimeDigitized");
            break;

        case 0xa420:

            printf("ImageUniqueID");
            break;

        case 0x829a:

            printf("ExposureTime");
            break;

        case 0x829d:

            printf("FNumber");
            break;

        case 0x8822:

            printf("ExposureProgram");
            break;

        case 0x8824:

            printf("SpectralSensitivity");
            break;

        case 0x8827:

            printf("ISOSpeedRatings");
            break;

        case 0x8828:

            printf("OECF");
            break;

        case 0x9201:

            printf("ShutterSpeedValue");
            break;

        case 0x9202:

            printf("ApertureValue");
            break;

        case 0x9203:

            printf("BrightnessValue");
            break;

        case 0x9204:

            printf("ExposureBiasValue");
            break;

        case 0x9205:

            printf("MaxApertureValue");
            break;

        case 0x9206:

            printf("SubjectDistance");
            break;

        case 0x9207:

            printf("MeteringMode");
            break;

        case 0x9208:

            printf("LightSource");
            break;

        case 0x9209:

            printf("Flash");
            break;

        case 0x920a:

            printf("FocalLength");
            break;

        case 0x9214:

            printf("SubjectArea");
            break;

        case 0xa20b:

            printf("FlashEnergy");
            break;

        case 0xa20c:

            printf("SpatialFrequencyResponse");
            break;

        case 0xa20e:

            printf("FocalPlaneXResolution");
            break;

        case 0xa20f:

            printf("FocalPlaneYResolution");
            break;

        case 0xa210:

            printf("FocalPlaneResolutionUnit");
            break;

        case 0xa214:

            printf("SubjectLocation");
            break;

        case 0xa215:

            printf("ExposureIndex");
            break;

        case 0xa217:

            printf("SensingMethod");
            break;

        case 0xa300:

            printf("FileSource");
            break;

        case 0xa301:

            printf("SceneType");
            break;

        case 0xa302:

            printf("CFAPattern");
            break;

        case 0xa401:

            printf("CustomRendered");
            break;

        case 0xa402:

            printf("ExposureMode");
            break;

        case 0xa403:

            printf("WhiteBalance");
            break;

        case 0xa404:

            printf("DigitalZoomRatio");
            break;

        case 0xa405:

            printf("FocalLengthin35mmFilm");
            break;

        case 0xa406:

            printf("SceneCaptureType");
            break;

        case 0xa407:

            printf("GainControl");
            break;

        case 0xa408:

            printf("Contrast");
            break;

        case 0xa409:

            printf("Saturation");
            break;

        case 0xa40a:

            printf("Sharpness");
            break;

        case 0xa40b:

            printf("DeviceSettingDescription");
            break;

        case 0xa40c:

            printf("SubjectDistanceRange");
            break;

    } //switch

} // print_xif_tag_text

