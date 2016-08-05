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
#include <cmath.h>
#include <cstring.h>
#include "audiostream.h"

AudioStream::AudioStream(unsigned int length_) : length(length_), size(length_)
{
    samples = new int32_t[size];
}

AudioStream::~AudioStream()
{
    delete samples;
}

AudioStream *AudioStream::fromSilence(unsigned int samples)
{
    AudioStream *stream = new AudioStream(samples);
    for (unsigned int i = 0; i < stream->length; i++)
        stream->samples[i] = 0;
    return stream;
}

AudioStream *AudioStream::fromSineWave(unsigned int samples, unsigned int hz)
{
    AudioStream *stream = new AudioStream(samples);
    for (unsigned int i = 0; i < stream->length; i++)
    {
        double tmp = INT32_MAX/2 * sin(PI * 2 * hz / SAMPLE_RATE * i);

        stream->samples[i] = tmp;
    }
    return stream;
}

AudioStream *AudioStream::fromSquareWave(unsigned int samples, unsigned int hz)
{
    AudioStream *stream = new AudioStream(samples);
    double rate = 2.0 * SAMPLE_RATE / hz;
    for (unsigned int i = 0; i < stream->length; i++)
    {
        int tmp = i / rate;

        stream->samples[i] = tmp % 2 ? INT32_MAX/2 : -(INT32_MAX/2);
    }
    return stream;
}

void AudioStream::enlarge(unsigned int length)
{
    if (length <= this->length)
        return;

    if (size < length)
    {
        int32_t *newsamples;
        while (size < length)
        {
            if (size < 32*1024)
                size *= 2;
            else
                size += 32*1024;
        }

        newsamples = new int32_t[size];
        memcpy(newsamples, samples, this->length * sizeof(int32_t));
        delete[] samples;
        samples = newsamples;
    }

    memset(&samples[this->length], 0, sizeof(int32_t) * (length - this->length));
    this->length = length;
}

void AudioStream::setLength(unsigned int length)
{
    if (this->length <= length)
    {
        enlarge(length);
    }
    else
    {
        this->length = length;
    }
}

void AudioStream::addSilence(unsigned int length)
{
    enlarge(this->length + length);
}

void AudioStream::mix(const AudioStream &src, Gain gain)
{
    if (getLength() < src.getLength())
        return;

    for (unsigned int i = 0; i < src.getLength(); i++)
    {
        long long x = samples[i];
        x += gain.adjustSample(src.samples[i]);
        if (x >= INT32_MAX)
            samples[i] = INT32_MAX;
        else if (x <= INT32_MIN)
            samples[i] = INT32_MIN;
        else
            samples[i] = x;
    }
}
