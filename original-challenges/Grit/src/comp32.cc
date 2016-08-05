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
#include <cstdint.h>
#include "comp32.h"

unsigned int Compression32::getId() const
{
    return COMPRESSION_32;
}

unsigned int Compression32::getMaxBufferSize(const AudioTrack &track) const
{
    return (track.getStereo() ? 2 : 1) * track.getLength() * sizeof(int32_t);
}

void Compression32::compress(const AudioTrack &track, uint8_t *dest) const
{
    int32_t *dest32 = (int32_t *)dest;
    for (unsigned int i = 0; i < track.getLength(); i++)
    {
        // interleave channels
        *dest32++ = track.getChannel(0)->getSample(i);
        if (track.getStereo())
            *dest32++ = track.getChannel(1)->getSample(i);
    }
}

void Compression32::decompress(AudioTrack &track, uint8_t *src) const
{
    int32_t *src32 = (int32_t *)src;
    for (unsigned int i = 0; i < track.getLength(); i++)
    {
        // un-interleave channels
        track.getChannel(0)->setSample(i, *src32++);
        if (track.getStereo())
            track.getChannel(1)->setSample(i, *src32++);
    }
}
