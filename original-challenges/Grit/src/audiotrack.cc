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
#include "audiotrack.h"

AudioTrack::AudioTrack()
{
    pan = 0;
    mute = false;
}

AudioTrack::AudioTrack(AudioStream *left) : AudioTrack()
{
    stereo = false;
    channels[0] = left;
}

AudioTrack::AudioTrack(AudioStream *left, AudioStream *right) : AudioTrack()
{
    stereo = true;
    channels[0] = left;
    channels[1] = right;

    // make sure both channels are the same length
    if (left->getLength() < right->getLength())
        left->setLength(right->getLength());
    else if (right->getLength() < left->getLength())
        right->setLength(left->getLength());
}

AudioTrack::~AudioTrack()
{
    if (channels[0])
        delete channels[0];
    if (stereo)
        if (channels[1])
            delete channels[1];
}

void AudioTrack::setLength(unsigned int length)
{
    channels[0]->setLength(length);
    if (stereo)
        channels[1]->setLength(length);
}

void AudioTrack::mix(const AudioTrack &src)
{
    if (getLength() < src.getLength())
        setLength(src.getLength());

    if (!stereo)
    {
        // XXX we don't currently support down-mixing stereo to mono
        if (src.stereo)
            return;

        // ignore pan since we are mixing mono to mono
        channels[0]->mix(*src.channels[0], src.gain);
    }
    else if (!src.stereo)
    {
        // mix src into both channels using pan
        channels[0]->mix(*src.channels[0], src.gain * Gain::fromPanLeft(src.pan));
        channels[1]->mix(*src.channels[0], src.gain * Gain::fromPanRight(src.pan));
    }
    else
    {
        // mix channels independently
        channels[0]->mix(*src.channels[0], src.gain * Gain::fromPanLeft(src.pan));
        channels[1]->mix(*src.channels[1], src.gain * Gain::fromPanRight(src.pan));
    }
}

bool AudioTrack::toStereo(AudioTrack *other)
{
    if (stereo || other->stereo)
        return false;

    stereo = true;
    channels[1] = other->channels[0];
    other->channels[0] = NULL;
    delete other;

    // make sure both channels are the same length
    if (channels[0]->getLength() < channels[1]->getLength())
        channels[0]->setLength(channels[1]->getLength());
    else if (channels[1]->getLength() < channels[0]->getLength())
        channels[1]->setLength(channels[0]->getLength());
    return true;
}
