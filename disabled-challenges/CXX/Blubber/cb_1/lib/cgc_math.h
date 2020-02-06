#ifndef MATH_H_
#define MATH_H_

#define NAN __builtin_nan("")
#define PI 3.14159265358979323846264338327950288

static inline double fmin(double a, double b)
{
    return a < b ? a : b;
}

static inline double fmax(double a, double b)
{
    return a > b ? a : b;
}

#endif
