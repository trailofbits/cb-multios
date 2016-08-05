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

#ifndef __3dc_h
#define __3dc_h

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <input.h>
#include <string.h>
#include <math.h>
#include <prng.h>

#define MAGIC_PAGE      0x4347C000
#define MAGIC_PAGE_SIZE 4096

#define MAX_PIXELS      (MAGIC_PAGE_SIZE / sizeof(t3DCPixel))
#define MAX_FILE_SIZE   (MAX_PIXELS) * sizeof(t3DCPixel)

#define MIN(a,b)        ((a > b) ? a : b)
#define MAX(a,b)        ((a < b) ? a : b)

#pragma pack (1)
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} t3DCPixel;

typedef void (*task_callback)(t3DCPixel*,int16_t);

// Data functions
void Push(t3DCPixel **px_list, t3DCPixel *px);
t3DCPixel* Pop(t3DCPixel **px_list);
void RunTask(t3DCPixel **px_list, task_callback pFunc, int16_t fptr_arg);
void ReadFile(t3DCPixel **px_list);

void NewFile(t3DCPixel **px_list, char *buf);

void ShowPixel(t3DCPixel *px);

void CheckFile(t3DCPixel **px, int16_t num);

// Image functions
void RotateX(t3DCPixel *px, int16_t rotate_val);
void RotateY(t3DCPixel *px, int16_t rotate_val);
void RotateZ(t3DCPixel *px, int16_t rotate_val);

void SkewX(t3DCPixel *px, int16_t skew_val);
void SkewY(t3DCPixel *px, int16_t skew_val);
void SkewZ(t3DCPixel *px, int16_t skew_val);

void Scale(t3DCPixel *px, int16_t scale_val);

void Brightness(t3DCPixel *px, int16_t bright_val);

void Opacity(t3DCPixel *px, int16_t opacity_val);

// math helpers
int32_t multiply(double a, double b);
int16_t divide(double a, double b);
int16_t degree_to_radian(int16_t a);

double cosine(int16_t a);
double sine(int16_t a);

#endif
