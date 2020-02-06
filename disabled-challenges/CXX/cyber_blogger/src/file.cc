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
#include "cgc_file.h"

File::File(cgc_size_t _header_size, cgc_size_t _data_size, char *_filename)
{
    cgc_size_t len;
    header_size = _header_size;
    data_size = _data_size;
    if (!_filename || !*_filename || cgc_strlen(_filename) >= sizeof(filename))
        cgc_strcpy(filename, "New File");
    else
        cgc_strcpy(filename, _filename);

    len = cgc_strlen(filename);
    if (len > 4 && filename[len - 4] == '.')
        cgc_strcpy(extension, &filename[len - 3]);
    else
        cgc_memset(extension, 0, sizeof(extension));
}

File::~File()
{
    if(raw_header)
        cgc_free(raw_header);
    if(raw_data)
        delete[] raw_data;
}

void File::clear_data_size()
{
    data_size = 0;
}

cgc_size_t File::get_header_size()
{
    return header_size;
}

cgc_size_t File::get_data_size()
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

