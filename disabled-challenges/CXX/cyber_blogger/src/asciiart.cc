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
#include "cgc_asciiart.h"

extern "C" {
#include "cgc_ctype.h"
#include "cgc_string.h"
};

AsciiArt::AsciiArt(void *_header, void *data, char *_filename)
: File(sizeof(AsciiArtHeader), find_data_size(_header), _filename)
{
    cgc_memcpy(&header, _header, sizeof(AsciiArtHeader));
    raw_header = (void *)&header;

    raw_data = new char[get_data_size() + 1];
    cgc_memcpy(raw_data, data, get_data_size());
    raw_data[get_data_size()] = '\0';

    if (!is_ascii((char *) data)) {
        header.line_width = 0;
        header.num_lines = 0;

        if (raw_data)
            delete[] (raw_data);
        raw_data = NULL;
        clear_data_size();
    }
}

AsciiArt::~AsciiArt()
{
    if (raw_data)
        delete[] raw_data;
    raw_data = NULL;
    clear_data_size();
}

unsigned int AsciiArt::get_magic()
{
    return header.magic;
}

bool AsciiArt::is_ascii(char *stream)
{
    char *line = NULL;
    char *_stream = new char[cgc_strlen(stream) + 1];
    cgc_strcpy(_stream, stream);
    int num_lines = 0;
    cgc_size_t len, i;
    while ((line = cgc_strsep(&_stream, "\n")) && num_lines < header.num_lines) {
        len = cgc_strlen(line) + 1;
        if (len != header.line_width) {
            return false;
        } else {
            num_lines++;
        }

        for (i = 0; i < len - 1; i++) {
            if (!cgc_isprint(line[i])) {
                delete[] _stream;
                return false;
            }
        }
    }

    delete[] _stream;
    if (num_lines != header.num_lines)
        return false;

    return true;
}

cgc_size_t AsciiArt::find_header_size()
{
    return sizeof(AsciiArtHeader);
}

cgc_size_t AsciiArt::find_data_size(void *header)
{
    AsciiArtHeader *pheader = (AsciiArtHeader *)header;
    return (cgc_size_t)(pheader->line_width) * pheader->num_lines;
}

void AsciiArt::print_asciiart()
{
    if (raw_data && get_data_size()) {
        if(!is_ascii(raw_data)) {
            cgc_printf("-------------------------------\n");
            cgc_printf("--Ascii Art file is corrupted--\n");
            cgc_printf("-------------------------------\n");
            return;
        } else {
            cgc_printf("%s\n", raw_data);
        }
    }
}

