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

#include <cstring.h>

#include "mgc_file.h"
#include "print.h"
#include "mgc_header_info.h"

MgcFile::MgcFile()
{
    frames_ = (mgc_frame **)NULL;
    num_frames_ = 0;
    size_ = 0;
}

bool MgcFile::ReadMgcFile(FILE *stream)
{
    unsigned char frame_buffer[6400];
    mgc_frame temp_frame;
    do
    {
        fread(&temp_frame, sizeof(temp_frame), stream);
        if (!MgcHeaderInfo::Synced(&temp_frame) || !MgcHeaderInfo::SongV1(&temp_frame))
        {
            Clear();
            return false;
        }

        fread(frame_buffer, MgcHeaderInfo::CalcFrameSize(&temp_frame), stream);
        mgc_frame *new_frame = (mgc_frame *)malloc(sizeof(mgc_frame) + MgcHeaderInfo::CalcFrameSize(&temp_frame));
        memcpy(new_frame, &temp_frame, sizeof(temp_frame));
        memcpy(new_frame->data, frame_buffer, MgcHeaderInfo::CalcFrameSize(&temp_frame));
        AddFrame(new_frame);
    } while(temp_frame.num_frames_left);

    return true;
}

const mgc_frame *MgcFile::GetFrame(unsigned int idx) const
{
    if (idx < num_frames_)
        return frames_[idx];
    return (mgc_frame *)NULL;
}

void MgcFile::Clear()
{
    if (frames_)
    {
        for (unsigned int i = 0; i < num_frames_; i++)
            free(frames_[i]);

        delete[] frames_;
        frames_ = (mgc_frame **)NULL;
    }
    num_frames_ = 0;
    size_ = 0;
}

void MgcFile::Remix(unsigned char *mix_buf, unsigned int *idx, const unsigned int buf_size) //idx incrememts by 33
{
    for (unsigned int i = 0; i < num_frames_; i++)
    {
        for (unsigned int j = 0; j < MgcHeaderInfo::CalcFrameSize(frames_[i]); j++)
        {
            unsigned char *pframe_data = (unsigned char *)(&frames_[i]->data[j]);
            *pframe_data *= mix_buf[*idx];
            *idx = (*idx + 33) % buf_size;
        }
    }
}

void MgcFile::PrintFrameData()
{

    printf("---Raw Frames---" NL);
    for (unsigned int i = 0; i < num_frames_; i++)
    {
        PRINT_ARR_HEX(frames_[i]->data, MgcHeaderInfo::CalcFrameSize(frames_[i]));
    }
    printf(NL "----------------" NL);
    fflush(stdout);

}

unsigned MgcFile::TotalFrames()
{
    return num_frames_;
}

bool MgcFile::AddFrame(mgc_frame *mframe)
{
    if (!mframe)
        return false;

    if (!frames_)
    {
        size_ = 16;
        frames_ = new mgc_frame*[size_];
    }
    if (num_frames_ == size_)
    {
        size_ *= 2;
        mgc_frame **doubled_list = new mgc_frame*[size_];
        memcpy(doubled_list, frames_, sizeof(mgc_frame *) * num_frames_);
        delete frames_;
        frames_ = doubled_list;
    }
    frames_[num_frames_++] = mframe;
    return true;


}
