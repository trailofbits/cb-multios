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

#ifndef MGC_FILE_H_
#define MGC_FILE_H_

#include <cstdio.h>
#include "mgc_frame.h"

class MgcFile
{
  public:
    MgcFile();
    bool ReadMgcFile(FILE *stream);
    const mgc_frame *GetFrame(unsigned int idx) const;
    void Clear();
    void Remix(unsigned char *mix_buf, unsigned int *idx, unsigned int buf_size); //idx incrememts by 33
    void PrintFrameData();

    unsigned TotalFrames();
  private:
    mgc_frame **frames_;
    unsigned int num_frames_;
    unsigned int size_;

    bool AddFrame(mgc_frame *frame);
};

#endif
