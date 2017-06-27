/*

Copyright (c) 2016 Cromulence LLC

Authors: Dan Czarnecki <cgc@cromulence.com>

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
#include "cgc_stdio.h"
#include "cgc_malloc.h"
#include "cgc_input.h"
#include "cgc_3dc.h"
#include "cgc_compress.h"

enum {
  NO_FUNC,        // 0x00
  NEW_FILE,       // 0x01
  CHECK_FILE,     // 0x02
  SKEW_IMAGE,     // 0x03
  ROTATE_IMAGE,   // 0x04
  BRIGHTNESS,     // 0x05
  OPACITY,        // 0x06
  COMPRESS,       // 0x07
  DECOMPRESS,     // 0x08
  SHOW_PIXEL,     // 0x09
  SCALE_IMAGE,    // 0x0a
  EXIT            // 0x0b
} menuSelections;

enum {
  X,              // 0x00
  Y,              // 0x01
  Z               // 0x02
} coords;

void cgc_menu() {
  char choice;
  char coord;
  uint16_t val;

  char new_init[4096];
  t3DCPixel *last_shown = NULL;

#ifdef PATCHED_1
  uint8_t *out_data = cgc_malloc(MAX_FILE_SIZE);
  uint8_t *in_data = cgc_malloc(MAX_FILE_SIZE);
#else
  uint8_t out_data[3072];
  uint8_t in_data[3072];
#endif

  uint16_t compress_len = 0;
  uint8_t decompress_flag = 0;

  uint16_t pixelCount = MAGIC_PAGE_SIZE / sizeof(t3DCPixel);

  t3DCPixel **px_list = cgc_malloc(pixelCount * sizeof(t3DCPixel*));
  cgc_memset(px_list, 0, pixelCount * sizeof(t3DCPixel*));

  cgc_ReadFile(px_list);

  while(choice) {
    cgc_receive_bytes(&choice, 1);

    switch(choice) {
      case NEW_FILE:
      {
        cgc_printf("NEW_FILE selected\n");
        cgc_memset(new_init, 0, 4096);
        cgc_NewFile(px_list, new_init);
        break;
      }
      case CHECK_FILE:
      {
        cgc_printf("CHECK_FILE selected\n");
        cgc_CheckFile(px_list, MAX_PIXELS);
        break;
      }
      case SKEW_IMAGE:
      {
        cgc_printf("SKEW_IMAGE selected\n");
        cgc_receive_bytes(&coord, 1);
        cgc_receive_bytes((char*)&val, 2);

        switch(coord) {
          case X:
            cgc_RunTask(px_list, cgc_SkewX, val);
            break;
          case Y:
            cgc_RunTask(px_list, cgc_SkewY, val);
            break;
          case Z:
            cgc_RunTask(px_list, cgc_SkewZ, val);
            break;
          default:
            cgc_printf("Incorrect coordinate provided.\n");
            break;
        }
        break;
      }
      case ROTATE_IMAGE:
      {
        cgc_printf("ROTATE_IMAGE selected\n");
        cgc_receive_bytes(&coord, 1);
        cgc_receive_bytes((char*)&val, 2);
        switch(coord) {
          case X:
            cgc_RunTask(px_list, cgc_RotateX, val);
            break;
          case Y:
            cgc_RunTask(px_list, cgc_RotateY, val);
            break;
          case Z:
            cgc_RunTask(px_list, cgc_RotateZ, val);
            break;
          default:
            cgc_printf("Incorrect coordinate provided.\n");
            break;
        }
        break;
      }
      case SCALE_IMAGE:
      {
        cgc_printf("SCALE_IMAGE selected\n");
        cgc_receive_bytes((char*)&val, 2);
        cgc_RunTask(px_list, cgc_Scale, (int16_t)val);
        break;
      }
      case BRIGHTNESS:
      {
        cgc_printf("BRIGHTNESS selected\n");
        cgc_receive_bytes((char*)&val, 2);
        cgc_RunTask(px_list, cgc_Brightness, (int16_t)val);
        break;
      }
      case OPACITY:
      {
        cgc_printf("OPACITY selected\n");
        cgc_receive_bytes((char*)&val, 1);
        cgc_RunTask(px_list, cgc_Opacity, val);
        break;
      }
      case COMPRESS:
      {
        cgc_printf("COMPRESS selected\n");
        cgc_Compress(px_list, in_data, &compress_len);
        decompress_flag = 0;
        break;
      }
      case DECOMPRESS:
      {
        cgc_printf("DECOMPRESS selected\n");
        if(compress_len == 0) {
          cgc_printf("No compressed data.\n");
          break;
        } else if (decompress_flag) {
          cgc_printf("You have already decompressed the latest data.\n");
          break;
        }
        uint8_t *decompressed = cgc_malloc(MAX_FILE_SIZE);
        cgc_Decompress(in_data, decompressed, &compress_len);
        cgc_WriteOut(px_list, decompressed, compress_len);
        cgc_memcpy(out_data, decompressed, compress_len);

        cgc_free(decompressed);
        decompress_flag = 1;
        break;
      }
      case SHOW_PIXEL:
      {
        cgc_printf("SHOW_PIXEL selected\n");
        cgc_printf("Select the pixel to view:\n");
        cgc_receive_bytes((char*)&val, 2);

        if (val < pixelCount && val >= 0) {

          t3DCPixel *tmp = cgc_malloc(sizeof(t3DCPixel));
          cgc_memcpy(tmp, px_list[val], sizeof(t3DCPixel));
          cgc_ShowPixel(tmp);
          last_shown = px_list[val];
          cgc_free(tmp);

        } else if (last_shown != NULL) {

          cgc_printf("Out of range. Showing last displayed pixel.\n");
          cgc_ShowPixel(last_shown);

        } else {
          cgc_printf("No pixel to show.\n\n\n\n");
        }

        break;
      }
      case EXIT:
      {
        cgc_printf("EXIT selected\n");
        choice = 0;
        cgc_free(px_list);
        return;
      }
      default:
      {
        cgc_printf("UNKNOWN command\n");
        choice = 0;
        cgc_free(px_list);
        return;
      }
    }
  }
  cgc_free(px_list);
}

int main(int cgc_argc, char *cgc_argv[]) {

    cgc_printf("3D Coordinates (3DC) Image File Format Tools\n");

    cgc_menu();

    return 0;
}
