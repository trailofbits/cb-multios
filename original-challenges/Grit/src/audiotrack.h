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
#include <cstdlib.h>
#include "audiostream.h"
#include "gain.h"

class AudioTrack
{
public:
    AudioTrack(AudioStream *);
    AudioTrack(AudioStream *, AudioStream *);
    ~AudioTrack();

    inline unsigned int getLength() const
    {
        return channels[0]->getLength();
    }
    inline bool getStereo() const
    {
        return stereo;
    }
    inline AudioStream *getChannel(unsigned int i) const
    {
        if (i == 0)
            return channels[0];

        if (stereo)
            return channels[1];
        else
            return NULL;
    }

    void setLength(unsigned int length);
    inline void setGain(Gain level)
    {
        gain = level;
    }
    inline void setPan(int32_t value)
    {
        pan = value;
    }
    inline void setMute(bool value)
    {
        mute = value;
    }
    inline AudioTrack *toMono()
    {
        if (!stereo)
            return NULL;

        stereo = false;
        return new AudioTrack(channels[1]);
    }
    bool toStereo(AudioTrack *other);
    void mix(const AudioTrack &src);
public:
    unsigned int id;
private:
    AudioTrack();

    bool stereo;
    AudioStream *channels[2];
    Gain gain;
    int32_t pan;
    bool mute;
};
