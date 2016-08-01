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
#include "file.h"

File::File(size_t _header_size, size_t _data_size, char *_filename)
{
    size_t len;
    header_size = _header_size;
    data_size = _data_size;
    if (!_filename || !*_filename || strlen(_filename) >= sizeof(filename))
        strcpy(filename, "New File");
    else
        strcpy(filename, _filename);

    len = strlen(filename);
    if (len > 4 && filename[len - 4] == '.')
        strcpy(extension, &filename[len - 3]);
    else
        memset(extension, 0, sizeof(extension));
}

File::~File()
{
    if(raw_header)
        free(raw_header);
    if(raw_data)
        delete[] raw_data;
}

void File::clear_data_size()
{
    data_size = 0;
}

size_t File::get_header_size()
{
    return header_size;
}

size_t File::get_data_size()
{
    return data_size;
}

const ftype File::tell_filetype()
{
    unsigned int magic;
    const filetype *ft;

#ifndef PATCHED
    ft = get_filetype_e(extension);
    if (ft)
        return ft->type;
#endif

    magic = ((unsigned int *)raw_header)[0];
    ft = get_filetype_m(magic);
    if (ft)
        return ft->type;

    return BADFILE;
}

