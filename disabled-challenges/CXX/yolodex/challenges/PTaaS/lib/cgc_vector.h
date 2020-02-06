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

#ifndef VECTOR_H_
#define VECTOR_H_

struct vector {
    double x, y, z;
};

/**
 * Construct a new vector with the given components and return it by value
 *
 * @param x The x component
 * @param y The y component
 * @param z The z component
 * @return A new vector with the given components
 */
struct vector cgc_make_vector(double x, double y, double z);

/**
 * Add two vectors and return the result
 *
 * @param a The first vector
 * @param b The second vector
 * @return The vector sum of a and b
 */
struct vector cgc_vector_add(struct vector a, struct vector b);

/**
 * Subtract two vectors and return the result
 *
 * @param a The first vector
 * @param b The second vector
 * @return The vector difference of a and b
 */
struct vector cgc_vector_sub(struct vector a, struct vector b);

/**
 * Multiply two vectors componentwise and return the result
 *
 * @param a The first vector
 * @param b The second vector
 * @return The product of the components of a and b as a vector
 */
struct vector cgc_vector_mul(struct vector a, struct vector b);

/**
 * Scale a vector by a scalar and return the result
 *
 * @param a The vector
 * @param s The scalar
 * @return a scaled by s
 */
struct vector cgc_vector_scale(struct vector a, double s);

/**
 * Find the maginitude squared of a vector
 *
 * @param a The vector
 * @return The magnitude squared of a
 */
double cgc_vector_mag_sqr(struct vector a);

/**
 * Find the magnitude of a vector
 *
 * @param a The vector
 * @return The magnitude of a
 */
double cgc_vector_mag(struct vector a);

/**
 * Normalize a vector
 *
 * @param a The vector
 * @return The normalized value of a
 */
struct vector cgc_vector_norm(struct vector a);

/**
 * Find the cross product of two vectors and return the result
 *
 * @param a The first vector
 * @param b The second vector
 * @return The cross product of a and b
 */
struct vector cgc_vector_cross(struct vector a, struct vector b);

/**
 * Find the dot product of two vectors and return the result
 *
 * @param a The first vector
 * @param b The second vector
 * @return The dot product of a and b
 */
double cgc_vector_dot(struct vector a, struct vector b);

#endif /* VECTOR_H_ */

