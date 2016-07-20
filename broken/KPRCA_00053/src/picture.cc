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
#include "picture.h"

extern "C" {
#include <ctype.h>
};

Picture::Picture(void *_header, void *data, char *_filename)
: File(sizeof(PictureHeader), ((PictureHeader *)_header)->data_size, _filename)
{
    memcpy(&header, _header, sizeof(PictureHeader));
    raw_header = (void *)&header;
    raw_data = new char[get_data_size() + 1];
    memcpy(raw_data, data, get_data_size());
    raw_data[get_data_size()] = '\0';
}

Picture::~Picture()
{
    if (raw_data)
        delete[] raw_data;
    clear_data_size();
}

unsigned int Picture::get_magic()
{
    return header.magic;
}

size_t Picture::find_header_size()
{
    return sizeof(PictureHeader);
}

size_t Picture::find_data_size(void *header)
{
    return ((PictureHeader *)header)->data_size;
}

void Picture::print_picture()
{
    for (size_t i = 0; i < get_data_size(); i++) {
        if (isprint(raw_data[i]) || raw_data[i]=='\n' || raw_data[i]=='\t')
            printf("%c", raw_data[i]);
        else
            printf(" ");
    }
    printf("\n");
}
