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
#include "cgc_cstring.h"
#include "cgc_fxreverb.h"

FxReverb::FxReverb(unsigned int delay_) : delay(delay_)
{
}

void FxReverb::apply(AudioTrack &track) const
{
    apply(*track.getChannel(0));
    if (track.getStereo())
        apply(*track.getChannel(1));
}

void FxReverb::apply(AudioStream &stream) const
{
    Gain gain = Gain::fromRational(-50, 100);
    int32_t *buffer = new int32_t[delay];
    cgc_memset(buffer, 0, sizeof(int32_t) * delay);

    for (unsigned int i = 0; i < stream.getLength(); i++)
    {
        long long sample = gain.adjustSample(buffer[i % delay]); // mix-in delayed audio
        sample += stream.getSample(i); // mix-in original audio
        if (sample > INT32_MAX)
            sample = INT32_MAX;
        else if (sample < INT32_MIN)
            sample = INT32_MIN;
        buffer[i % delay] = sample; // put mix back into the buffer
        stream.setSample(i, sample); // put mix into audio stream
    }

    delete buffer;
}
