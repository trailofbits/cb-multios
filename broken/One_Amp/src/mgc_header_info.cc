/*
 * Copyright (c) 2016 Kaprica Security, Inc.
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

#include "mgc_header_info.h"
#include "print.h"

namespace MgcHeaderInfo
{

bool Synced(mgc_frame *mframe)
{
    return ((0xFF & mframe->raw_header[0]) == 0xFF && (0xF0 & mframe->raw_header[1]) == 0xF0);
}

bool SongV1(mgc_frame *mframe)
{
    return (0x08 & mframe->raw_header[1]);
}

int Layer(mgc_frame *mframe)
{
    return (0x06 & mframe->raw_header[1]) >> 1;
}

int Bitrate(mgc_frame *mframe)
{
    unsigned char rate_idx = (0xF0 & mframe->raw_header[2]) >> 4;
    switch (rate_idx)
    {
    case 0x1:
        return 320000;
    case 0x2:
        return 256000;
    case 0x3:
        return 224000;
    case 0x4:
        return 192000;
    case 0x5:
        return 160000;
    case 0x6:
        return 128000;
    case 0x7:
        return 112000;
    case 0x8:
        return 96000;
    case 0x9:
        return 80000;
    case 0xA:
        return 64000;
    case 0xB:
        return 56000;
    case 0xC:
        return 48000;
    case 0xD:
        return 40000;
    case 0xE:
        return 32000;
    }

    return 0;
}

int Freq(mgc_frame *mframe)
{
    unsigned char freq_idx = mframe->raw_header[2];
    switch (((freq_idx & 0xC) >> 2))
    {
    case 0x0:
        return 44100;
    case 0x1:
        return 48000;
    case 0x2:
        return 32000;
    }

#ifdef PATCHED_1
    return 0;
#else
    return freq_idx;
#endif

}

unsigned short SamplesPerFrame(mgc_frame *mframe)
{
    int spf_idx = Layer(mframe);
    switch (spf_idx)
    {
    case 0x1:
        return 384;
    case 0x2:
        return 1152;
    case 0x3:
        return 1152;
    }
    return 0;
}

unsigned short NumAdditionalFrames(mgc_frame *mframe)
{
    return mframe->num_frames_left;
}

unsigned int CalcFrameSize(mgc_frame *mframe)
{
    if(!mframe || !Freq(mframe))
        return 0;

    unsigned int unpadded_size = ((SamplesPerFrame(mframe) / 8 * Bitrate(mframe)) / Freq(mframe));
    return (unpadded_size % 4 == 0) ? unpadded_size : unpadded_size + (4 - (unpadded_size % 4));
}

}

