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

#ifndef MATH_H_
#define MATH_H_

/**
 * Return the sign bit of d, unshifted.
 *
 * @param d The double to examine
 * @return The extracted sign bit of d
 */
unsigned long long sign(double d);

/**
 * Return the exponent bits of d, unshifted.
 *
 * @param d The double to examine
 * @return The exponent bits of d
 */
unsigned long long exponent(double d);

/**
 * Return the mantissa bits of d
 *
 * @param d The double to examine
 * @return The mantissa bits of d
 */
unsigned long long mantissa(double d);

/**
 * Return 1 if d is a NaN, 0 otherwise
 *
 * @param d The double to examine
 * @return 1 if d is a NaN, 0 otherwise
 */
int isnan(double d);

/**
 * Return 1 if d == +inf, -1 if d == -inf, 0 otherwise
 *
 * @param d The double to examine
 * @return 1 if d == +inf, -1 if d == -inf, 0 otherwise
 */
int isinf(double d);

/**
 * Return the absolute value of d as calculated by masking off sign bit.
 *
 * @param d The double to examine
 * @return The absolute value of d
 */
double abs(double d);

/**
 * Clamp the value of d between 0.0 and 1.0
 *
 * @param d The value to clamp
 * @return 0.0 if d < 0.0, 1.0 if d > 1.0, else d
 */
double clamp(double d);

#endif /* MATH_H_ */

