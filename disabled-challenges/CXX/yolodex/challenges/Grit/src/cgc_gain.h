/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#pragma once

class Gain
{
public:
    inline Gain() : value(0)
    {
    }
    static inline Gain fromDouble(double d)
    {
        // only positive values are valid
        if (d < 0)
            return Gain(0);
        if (d <= 0.01)
            return Gain(INT32_MIN);
        if (d >= 10.0)
            return Gain(INT32_MAX);
        if (d >= 1)
            return Gain((d-1) / 10 * INT32_MAX);
        else
            return Gain(((1/d) - 1) / 10 * -INT32_MAX);
    }
    static inline Gain fromRational(int16_t numerator, int16_t denominator)
    {
        double tmp = (double)numerator / (double)denominator;
        tmp /= 10;
        tmp *= INT32_MAX;
        return Gain((int)tmp);
    }
    static inline Gain fromPanLeft(int32_t pan)
    {
        if (pan <= 0)
            return Gain(0);
        else
            return Gain(-pan);
    }
    static inline Gain fromPanRight(int32_t pan)
    {
        if (pan >= 0)
            return Gain(0);
        else
            return Gain(pan);
    }
    inline Gain operator*(const Gain &b) const
    {
        return fromDouble(toDouble() * b.toDouble());
    }
    inline Gain operator+(const Gain &b) const
    {
        long long tmp = value;
        tmp += b.value;
        if (tmp > INT32_MAX)
            tmp = INT32_MAX;
        if (tmp < INT32_MIN)
            tmp = INT32_MIN;
        return tmp;
    }
    inline int32_t adjustSample(int32_t sample) const
    {
        double tmp = sample * toDouble();
        if (tmp >= INT32_MAX)
            return INT32_MAX;
        if (tmp <= INT32_MIN)
            return INT32_MIN;
        return tmp;
    }
    inline double toDouble() const
    {
        double tmp = value;
        tmp *= 10.0 / INT32_MAX;
        if (tmp >= 0)
            return (tmp + 1);
        else
            return 1 / (-tmp + 1);
    }
private:
    inline Gain(int32_t value_) : value(value_)
    {
    }
    int32_t value;
};
