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
#include "mixer.h"

Mixer::Mixer()
    : nextTrackId(0), tracks(LinkedList<AudioTrack *>::deleteDestructor)
{
}

Mixer::~Mixer()
{
}

unsigned int Mixer::getLength() const
{
    unsigned int length = 0;
    for (auto it = tracks.begin(); !it.empty(); it.next())
    {
        unsigned int trackLength = it.value()->getLength();
        if (trackLength > length)
            length = trackLength;
    }
    return length;
}

void Mixer::addTrack(AudioTrack *track)
{
    track->id = nextTrackId++;
    tracks.append(track);
}

AudioTrack *Mixer::getTrack(unsigned int id) const
{
    for (auto it = tracks.begin(); !it.empty(); it.next())
    {
        AudioTrack *track = it.value();
        if (track->id == id)
            return track;
    }

    return NULL;
}

void Mixer::removeTrack(unsigned int id)
{
    for (auto it = tracks.begin(); !it.empty(); it.next())
    {
        AudioTrack *track = it.value();
        if (track->id == id)
        {
            tracks.removeAt(it);
            delete track;
            return;
        }
    }
}

bool Mixer::splitTrack(unsigned int id)
{
    AudioTrack *track = getTrack(id);
    if (track == NULL || !track->getStereo())
        return false;

    track = track->toMono();
    addTrack(track);
    return true;
}

bool Mixer::combineTracks(unsigned int leftId, unsigned int rightId)
{
    AudioTrack *left, *right;
    left = getTrack(leftId);
    if (left == NULL || left->getStereo())
        return false;
    for (auto it = tracks.begin(); !it.empty(); it.next())
    {
        right = it.value();
        if (right->id == rightId)
        {
            if (right->getStereo())
                return false;
            if (!left->toStereo(right))
                return false;
            tracks.removeAt(it);
            return true;
        }
    }
    return false;
}

AudioTrack *Mixer::exportMix()
{
    unsigned int length = getLength();
    AudioTrack *output = new AudioTrack(AudioStream::fromSilence(length), AudioStream::fromSilence(length));
    for (auto it = tracks.begin(); !it.empty(); it.next())
    {
        AudioTrack *track = it.value();
        output->mix(*track);
    }
    return output;
}

AudioStream *Mixer::generateWhiteNoise(unsigned int length)
{
    rng.addEntropy((uint8_t *)0x4347C000, 0x1000);
    AudioStream *stream = AudioStream::fromSilence(length);
    for (unsigned int i = 0; i < length; i++)
    {
        stream->setSample(i, rng.randomInt32() >> 1);
    }
    return stream;
}
