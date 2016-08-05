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
#include <cstdio.h>
#include <cstring.h>
#include "audiotrack.h"
#include "comp32.h"
#include "compfour.h"
#include "compeight.h"
#include "fxgain.h"
#include "fxpan.h"
#include "fxreverb.h"
#include "interface.h"

static const char menuMainPrompt[] = \
    "1) New track...\n" \
    "2) Import track\n" \
    "3) Export...\n" \
    "4) List tracks\n" \
    "5) Change gain [track] [hundredths]\n" \
    "6) Change pan [track] [hundredths]\n" \
    "7) Combine/split [track] [?track]\n" \
    "8) Effects...\n" \
    "9) Quit\n";
static const char menuEffectsPrompt[] = \
    "1) Apply gain [track] [hundredths]\n" \
    "2) Apply pan [track] [hundredths]\n" \
    "3) Echo [track] [delay in samples]\n" \
    "4) Add silence [track] [number of samples]\n" \
    "5) Cancel\n";
static const char menuExportPrompt[] = \
    "1) Uncompressed 32-bit signed\n" \
    "2) Compressed 4-bit\n" \
    "3) Compressed 8-bit\n" \
    "4) Cancel\n";
static const char menuNewPrompt[] = \
    "1) Silence [number of samples]\n" \
    "2) Sine Wave [number of samples] [HZ]\n" \
    "3) Square Wave [number of samples] [HZ]\n" \
    "4) White Noise [number of samples]\n" \
    "5) Cancel\n";

Interface::Interface()
{
}

Interface::~Interface()
{
}

void Interface::run()
{
    menuMain();
}

bool Interface::menuMain()
{
    AudioTrack *track, *other;
    int value;
    char line[100], *word, *buf;
    while (true)
    {
        fwrite(menuMainPrompt, strlen(menuMainPrompt), stdout);
        if (freaduntil(line, sizeof(line), '\n', stdin) < 0)
            return false;

        if (line[0] == '9')
            break;
        buf = line;
        word = strsep(&buf, " ");
        switch(line[0])
        {
        case '1':
            if (!menuNew())
                return false;
            break;
        case '2':
            if (!importAudio())
                return false;
            break;
        case '3':
            if (!menuExport())
                return false;
            break;
        case '4':
            listTracks();
            break;
        case '5':
            word = strsep(&buf, " ");
            if (word == NULL)
            {
                fprintf(stdout, "Missing track\n");
                continue;
            }
            value = strtol(word, NULL, 10);
            track = mixer.getTrack(value);
            if (track == NULL)
            {
                fprintf(stdout, "Invalid track\n");
                continue;
            }
            word = strsep(&buf, " ");
            if (word == NULL)
            {
                fprintf(stdout, "Missing gain\n");
                continue;
            }
            value = strtol(word, NULL, 10);
            if (value < -1000 || value > 1000)
            {
                fprintf(stdout, "Invalid gain (-10.00...10.00)\n");
                continue;
            }

            track->setGain(Gain::fromRational(value, 100));
            break;
        case '6':
            word = strsep(&buf, " ");
            if (word == NULL)
            {
                fprintf(stdout, "Missing track\n");
                continue;
            }
            value = strtol(word, NULL, 10);
            track = mixer.getTrack(value);
            if (track == NULL)
            {
                fprintf(stdout, "Invalid track\n");
                continue;
            }
            word = strsep(&buf, " ");
            if (word == NULL)
            {
                fprintf(stdout, "Missing pan\n");
                continue;
            }
            value = strtol(word, NULL, 10);
            if (value < -100 || value > 100)
            {
                fprintf(stdout, "Invalid pan (-1.00...1.00)\n");
                continue;
            }

            if (value == 100)
                track->setPan(INT32_MAX);
            else
                track->setPan((double)value / 100 * INT32_MAX);
            break;
        case '7':
            word = strsep(&buf, " ");
            if (word == NULL)
            {
                fprintf(stdout, "Missing track 1\n");
                continue;
            }
            value = strtol(word, NULL, 10);
            track = mixer.getTrack(value);
            if (track == NULL)
            {
                fprintf(stdout, "Invalid track 1\n");
                continue;
            }

            word = strsep(&buf, " ");
            if (word != NULL)
            {
                value = strtol(word, NULL, 10);
                other = mixer.getTrack(value);
                if (other == NULL)
                {
                    fprintf(stdout, "Invalid track 2\n");
                    continue;
                }
            }
            else
            {
                other = NULL;
            }

            if (other == NULL)
            {
                if (!track->getStereo())
                {
                    fprintf(stdout, "Cannot split a mono track\n");
                    continue;
                }
                mixer.splitTrack(track->id);
            }
            else
            {
                if (track->getStereo() || other->getStereo())
                {
                    fprintf(stdout, "Cannot combine a stereo track\n");
                    continue;
                }
                mixer.combineTracks(track->id, other->id);
            }
            break;
        case '8':
            menuEffects();
            break;
        default:
            fprintf(stdout, "Invalid choice\n");
            break;
        }
    }
    fprintf(stdout, "Thank you for trying out Grit! Please leave us a nice review on the app store.\n");
    return true;
}

bool Interface::menuExport()
{
    char line[100];
    while (true)
    {
        fwrite(menuExportPrompt, strlen(menuExportPrompt), stdout);
        if (freaduntil(line, sizeof(line), '\n', stdin) < 0)
            return false;

        if (line[0] == '4')
            break;
        switch(line[0])
        {
        case '1':
            exportAudio(Compression32());
            break;
        case '2':
            exportAudio(CompressionFour());
            break;
        case '3':
            exportAudio(CompressionEight());
            break;
        default:
            fprintf(stdout, "Invalid choice\n");
            continue;
        }
        break;
    }
    return true;
}

bool Interface::menuNew()
{
    char line[100], *buf, *word;
    unsigned int samples, hz;
    AudioTrack *track;
    while (true)
    {
        fwrite(menuNewPrompt, strlen(menuNewPrompt), stdout);
        if (freaduntil(line, sizeof(line), '\n', stdin) < 0)
            return false;

        if (line[0] == '5')
            break;

        buf = line;
        word = strsep(&buf, " "); // ignore command
        word = strsep(&buf, " ");
        if (word == NULL)
        {
            fprintf(stdout, "Missing samples\n");
            continue;
        }
        samples = strtoul(word, NULL, 10);
        if (samples > INT32_MAX)
        {
            fprintf(stdout, "Invalid samples\n");
            continue;
        }

        switch(line[0])
        {
        case '1':
            track = new AudioTrack(AudioStream::fromSilence(samples));
            mixer.addTrack(track);
            break;
        case '2':
        case '3':
            word = strsep(&buf, " ");
            if (word == NULL)
            {
                fprintf(stdout, "Missing frequency\n");
                continue;
            }
            hz = strtoul(word, NULL, 10);
            if (hz >= 50000)
            {
                fprintf(stdout, "Invalid frequency\n");
                continue;
            }

            if (line[0] == '2')
                track = new AudioTrack(AudioStream::fromSineWave(samples, hz));
            else
                track = new AudioTrack(AudioStream::fromSquareWave(samples, hz));
            mixer.addTrack(track);
            break;
        case '4':
            track = new AudioTrack(mixer.generateWhiteNoise(samples));
            mixer.addTrack(track);
            break;
        default:
            fprintf(stdout, "Invalid choice\n");
            continue;
        }

        break;
    }
    return true;
}

void Interface::listTracks()
{
    for (auto it = mixer.getTracks(); !it.empty(); it.next())
    {
        AudioTrack *track = it.value();
        fprintf(stdout, "%d) %s samples=%d\n", track->id, track->getStereo() ? "stereo" : "mono", track->getLength());
    }
}

void Interface::exportAudio(const Compression &comp)
{
    AudioTrack *track = mixer.exportMix();
    unsigned int size = sizeof(AudioHeader) + comp.getMaxBufferSize(*track);
    uint8_t *data = new uint8_t[size];

    AudioHeader *hdr = (AudioHeader *)data;
    hdr->magic = 0x2e617564;
    hdr->offset = sizeof(AudioHeader);
    hdr->samples = track->getLength();
    hdr->encoding = comp.getId();
    hdr->sample_rate = SAMPLE_RATE;
    hdr->channels = track->getStereo() ? 2 : 1;

    comp.compress(*track, &data[sizeof(AudioHeader)]);

    fwrite(&size, sizeof(size), stdout);
    fwrite(data, size, stdout);

    delete data;
    delete track;
}

bool Interface::importAudio()
{
    unsigned int size;
    if (fread(&size, sizeof(size), stdin) != sizeof(size))
        return false;
    if (size >= INT32_MAX || size <= sizeof(AudioHeader))
        return false;
    uint8_t *data = new uint8_t[size];
    if (fread(data, size, stdin) != size)
        return false;

    AudioHeader *hdr = (AudioHeader *)data;
    if (hdr->magic == 0x2e617564 && hdr->offset == sizeof(AudioHeader) && hdr->samples < INT32_MAX && hdr->sample_rate == SAMPLE_RATE)
    {
        Compression *comp = Compression::fromId(hdr->encoding);
        if (comp != NULL)
        {
            AudioTrack *track;
            if (hdr->channels == 1)
                track = new AudioTrack(AudioStream::fromSilence(hdr->samples));
            else
                track = new AudioTrack(AudioStream::fromSilence(hdr->samples), AudioStream::fromSilence(hdr->samples));
#ifdef PATCHED_1
            if (size - hdr->offset >= comp->getMaxBufferSize(*track))
#endif
            comp->decompress(*track, &data[sizeof(AudioHeader)]);
            mixer.addTrack(track);
            delete comp;
        }
    }

    delete data;
    return true;
}

bool Interface::menuEffects()
{
    char line[100], *buf, *word;
    int value;
    AudioTrack *track;
    while (true)
    {
        fwrite(menuEffectsPrompt, strlen(menuEffectsPrompt), stdout);
        if (freaduntil(line, sizeof(line), '\n', stdin) < 0)
            return false;

        if (line[0] == '5')
            break;

        buf = line;
        word = strsep(&buf, " "); // ignore command
        word = strsep(&buf, " ");
        if (word == NULL)
        {
            fprintf(stdout, "Missing track\n");
            continue;
        }
        value = strtol(word, NULL, 10);
        track = mixer.getTrack(value);
        if (track == NULL)
        {
            fprintf(stdout, "Invalid track\n");
            continue;
        }

        switch(line[0])
        {
        case '1':
            word = strsep(&buf, " ");
            if (word == NULL)
            {
                fprintf(stdout, "Missing gain\n");
                continue;
            }
            value = strtol(word, NULL, 10);
            if (value < -1000 || value > 1000)
            {
                fprintf(stdout, "Invalid gain (-10.00...10.00)\n");
                continue;
            }

            FxGain(Gain::fromRational(value, 100)).apply(*track);
            break;
        case '2':
            word = strsep(&buf, " ");
            if (word == NULL)
            {
                fprintf(stdout, "Missing pan\n");
                continue;
            }
            value = strtol(word, NULL, 10);
            if (value < -100 || value > 100)
            {
                fprintf(stdout, "Invalid pan (-1.00...1.00)\n");
                continue;
            }

            if (value == 100)
                FxPan(INT32_MAX).apply(*track);
            else
                FxPan((double)value / 100 * INT32_MAX).apply(*track);
            break;
        case '3':
            word = strsep(&buf, " ");
            if (word == NULL)
            {
                fprintf(stdout, "Missing delay\n");
                continue;
            }
            value = strtol(word, NULL, 10);
            if (value <= 0)
            {
                fprintf(stdout, "Invalid delay (>0)\n");
                continue;
            }

            FxReverb(value).apply(*track);
            break;
        case '4':
            word = strsep(&buf, " ");
            if (word == NULL)
            {
                fprintf(stdout, "Missing samples\n");
                continue;
            }
            value = strtol(word, NULL, 10);
            if (value <= 0)
            {
                fprintf(stdout, "Invalid samples (>0)\n");
                continue;
            }

            track->setLength(track->getLength() + value);
            break;
        default:
            fprintf(stdout, "Invalid choice\n");
            continue;
        }

        break;
    }
    return true;
}

