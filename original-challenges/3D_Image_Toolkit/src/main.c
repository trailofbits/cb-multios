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

#include <libcgc.h>
#include <stdio.h>
#include <malloc.h>
#include <input.h>
#include "3dc.h"
#include "compress.h"

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

void menu() {
  char choice;
  char coord;
  uint16_t val;

  char new_init[4096];
  t3DCPixel *last_shown = NULL;

#ifdef PATCHED_1
  uint8_t *out_data = malloc(MAX_FILE_SIZE);
  uint8_t *in_data = malloc(MAX_FILE_SIZE);
#else
  uint8_t out_data[3072];
  uint8_t in_data[3072];
#endif

  uint16_t compress_len = 0;
  uint8_t decompress_flag = 0;

  uint16_t pixelCount = MAGIC_PAGE_SIZE / sizeof(t3DCPixel);

  t3DCPixel **px_list = malloc(pixelCount * sizeof(t3DCPixel*));
  memset(px_list, 0, pixelCount * sizeof(t3DCPixel*));

  ReadFile(px_list);

  while(choice) {
    receive_bytes(&choice, 1);

    switch(choice) {
      case NEW_FILE:
      {
        printf("NEW_FILE selected\n");
        memset(new_init, 0, 4096);
        NewFile(px_list, new_init);
        break;
      }
      case CHECK_FILE:
      {
        printf("CHECK_FILE selected\n");
        CheckFile(px_list, MAX_PIXELS);
        break;
      }
      case SKEW_IMAGE:
      {
        printf("SKEW_IMAGE selected\n");
        receive_bytes(&coord, 1);
        receive_bytes((char*)&val, 2);

        switch(coord) {
          case X:
            RunTask(px_list, SkewX, val);
            break;
          case Y:
            RunTask(px_list, SkewY, val);
            break;
          case Z:
            RunTask(px_list, SkewZ, val);
            break;
          default:
            printf("Incorrect coordinate provided.\n");
            break;
        }
        break;
      }
      case ROTATE_IMAGE:
      {
        printf("ROTATE_IMAGE selected\n");
        receive_bytes(&coord, 1);
        receive_bytes((char*)&val, 2);
        switch(coord) {
          case X:
            RunTask(px_list, RotateX, val);
            break;
          case Y:
            RunTask(px_list, RotateY, val);
            break;
          case Z:
            RunTask(px_list, RotateZ, val);
            break;
          default:
            printf("Incorrect coordinate provided.\n");
            break;
        }
        break;
      }
      case SCALE_IMAGE:
      {
        printf("SCALE_IMAGE selected\n");
        receive_bytes((char*)&val, 2);
        RunTask(px_list, Scale, (int16_t)val);
        break;
      }
      case BRIGHTNESS:
      {
        printf("BRIGHTNESS selected\n");
        receive_bytes((char*)&val, 2);
        RunTask(px_list, Brightness, (int16_t)val);
        break;
      }
      case OPACITY:
      {
        printf("OPACITY selected\n");
        receive_bytes((char*)&val, 1);
        RunTask(px_list, Opacity, val);
        break;
      }
      case COMPRESS:
      {
        printf("COMPRESS selected\n");
        Compress(px_list, in_data, &compress_len);
        decompress_flag = 0;
        break;
      }
      case DECOMPRESS:
      {
        printf("DECOMPRESS selected\n");
        if(compress_len == 0) {
          printf("No compressed data.\n");
          break;
        } else if (decompress_flag) {
          printf("You have already decompressed the latest data.\n");
          break;
        }
        uint8_t *decompressed = malloc(MAX_FILE_SIZE);
        Decompress(in_data, decompressed, &compress_len);
        WriteOut(px_list, decompressed, compress_len);
        memcpy(out_data, decompressed, compress_len);

        free(decompressed);
        decompress_flag = 1;
        break;
      }
      case SHOW_PIXEL:
      {
        printf("SHOW_PIXEL selected\n");
        printf("Select the pixel to view:\n");
        receive_bytes((char*)&val, 2);

        if (val < pixelCount && val >= 0) {

          t3DCPixel *tmp = malloc(sizeof(t3DCPixel));
          memcpy(tmp, px_list[val], sizeof(t3DCPixel));
          ShowPixel(tmp);
          last_shown = px_list[val];
          free(tmp);

        } else if (last_shown != NULL) {

          printf("Out of range. Showing last displayed pixel.\n");
          ShowPixel(last_shown);

        } else {
          printf("No pixel to show.\n\n\n\n");
        }

        break;
      }
      case EXIT:
      {
        printf("EXIT selected\n");
        choice = 0;
        free(px_list);
        return;
      }
      default:
      {
        printf("UNKNOWN command\n");
        choice = 0;
        free(px_list);
        return;
      }
    }
  }
  free(px_list);
}

int main(void) {

    printf("3D Coordinates (3DC) Image File Format Tools\n");

    menu();

    return 0;
}
