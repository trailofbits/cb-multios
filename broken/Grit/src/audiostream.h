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
#include <cstdint.h>
#include "gain.h"

#define SAMPLE_RATE 8000

class AudioStream
{
public:
    ~AudioStream();
    static AudioStream *fromSilence(unsigned int samples);
    static AudioStream *fromSineWave(unsigned int samples, unsigned int hz);
    static AudioStream *fromSquareWave(unsigned int samples, unsigned int hz);

    inline unsigned int getLength() const
    {
        return length;
    }
    inline int32_t getSample(unsigned int i) const
    {
        if (i < length)
            return samples[i];
        return 0;
    }

    void setLength(unsigned int length);
    inline void setSample(unsigned int i, int32_t sample)
    {
        if (i >= length)
            setLength(i+1);
        samples[i] = sample;
    }
    void addSilence(unsigned int length);
    void mix(const AudioStream &src, Gain gain);
private:
    AudioStream(unsigned int length);
    void enlarge(unsigned int length);

    unsigned int length;
    unsigned int size;
    int32_t *samples;
};
