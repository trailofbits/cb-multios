/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#define PI 3.14159265358979323846
#define TRIG_NUM_TERMS 20
#define EXP_NUM_TERMS 80
#define LN_NUM_TERMS 40

/**
* Calculate the natural log of a number
* 
* @param x The number to calculate the natural log of
*
* @return The natural log of the number
*/
double cgc_ln(double x);

/**
* Calculate e to an exponent
* 
* @param x The exponent
*
* @return The result of e to the exponent
*/
double cgc_exponential(double x);

/**
* Calculate x to the n'th power
* 
* @param x The number to calculate the exponent of
* @param n The exponent of x to calculate
*
* @return x to the n'th power
*/
double cgc_pow(double x, double n);

/**
* Calculate the cosine of a number
* 
* @param x The number to calculate the cosine of
*
* @return The cosine of x
*/
double cgc_cosine(double x);

/**
* Calculate the sine of a number
* 
* @param x The number to calculate the sine of
*
* @return The sine of x
*/
double cgc_sine(double x);

/**
* Calculate the square root of a number
* 
* @param x The number to calculate the square root of
*
* @return The square root of x
*/
double cgc_sqrt(double x);

/**
* Calculate the arctan of a number
* 
* @param x The number to calculate the arctan of
*
* @return The arctan of x
*/
double cgc_atan(double x);

/**
* Calculate the arctan2 of a number
* 
* @param x The number to calculate the arctan2 of
*
* @return The arctan2 of x
*/
double cgc_atanTwo(double y, double x);
