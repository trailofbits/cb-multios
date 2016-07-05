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
#include "iomanager.h"

IoManager::IoManager(size_t _line_size)
{
    line_size = _line_size;
    line_len = 0;
    line = new char[line_size];
    fd = STDIN;
}

IoManager::~IoManager()
{
    delete line;
    line_size = 0;
    line_len = 0;
}

bool IoManager::readline(size_t max_size)
{
    size_t rx, i = 0;
    max_size = max_size ? max_size : line_size;
    line_len = 0;

#ifdef PATCHED
    while (i < max_size && receive(fd, &line[i], 1, &rx) == 0 && rx == 1) {
#else
    while (receive(fd, &line[i], 1, &rx) == 0 && rx == 1 && i < max_size) {
#endif
        if(line[i] == '\n') {
            line[i] = '\0';
            break;
        }

        i++;
    }

    if (!i || i == max_size)
        return false;

    line_len = i;
    return true;
}

int IoManager::readnum(size_t max_size)
{
    size_t rx, i = 0;
    max_size = max_size ? max_size : line_size;
    line_len = 0;

#ifdef PATCHED
    while (i < max_size && receive(fd, &line[i], 1, &rx) == 0 && rx == 1) {
#else
    while (receive(fd, &line[i], 1, &rx) == 0 && rx == 1 && i < max_size) {
#endif
        if(line[i] < '0' || line[i] > '9') {
            line[i] = '\0';
            break;
        }

        i++;
    }

    if (!i || i == max_size)
        return 0;

    line_len = i;
    return strtol(&line[0], NULL, 10);
}
