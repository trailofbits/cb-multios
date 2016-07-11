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

#include <libcgc.h>
#include <stdlib.h>
#include <string.h>

#include "sfile.h"
#include "differ.h"

#define MAX_INPUT 128

#define DISABLED "Disabled"
#define ENABLED "Enabled"
#define NOT_LOADED "No File Loaded"


static int readopt(int fd) {
    size_t rx, i = 0;
    char opt[MAX_INPUT];

    while (receive(fd, &opt[i], 1, &rx) == 0 && rx == 1 && i < MAX_INPUT) {
        if(opt[i] == '\n') {
            opt[i] = '\0';
            break;
        }

        i++;
    }

    if (i == MAX_INPUT)
        return 0;

    return strtol(&opt[0], NULL, 10);
}

int main()
{
    SFILE *lfile = NULL;
    SFILE *rfile = NULL;
    char *lfilename = NOT_LOADED;
    char *rfilename = NOT_LOADED;

    // Options
    int ignore_ws = 0;
    int treat_as_ascii = 0;

    int option;
    char *option_set;

    int exited = 0;

    while (!exited) {
        printf("File Comparer ver 1.0\n");
        printf("---------------------\n");
        printf("Select an option:\n");
        printf("1. Load File 1\n");
        printf("2. Load File 2\n");
        if (!ignore_ws)
            printf("3. Enable Ignore Whitespace\n");
        else
            printf("3. Disable Ignore Whitespace\n");
        if (!treat_as_ascii)
            printf("4. Treat Files as Ascii\n");
        else
            printf("4. Use Native File Type\n");
        printf("5. Compare files\n");
        printf("6. Quit\n\n");

        printf("File 1: %s <> File 2: %s\n", lfilename, rfilename);
        printf("        Options:\n");
        option_set = ignore_ws ? ENABLED : DISABLED;
        printf("Ignore Whitespace=%s\n", option_set);
        option_set = treat_as_ascii ? ENABLED : DISABLED;
        printf("Ignore File Type, Treat as Ascii=%s\n", option_set);
        printf("::-> ");

        option = readopt(STDIN);
        switch(option) {
        case 1:
            clear_cache(1);
            if (lfile)
                close_sfile(&lfile);

            lfile = open_sfile();
            if (lfile) {
                printf("Successfully Loaded File\n");
                lfilename = lfile->name;
            } else {
                printf("Error Loading File\n");
                lfilename = NOT_LOADED;
            }
            break;
        case 2:
            clear_cache(2);
            if (rfile)
                close_sfile(&rfile);

            rfile = open_sfile();
            if (rfile) {
                printf("Successfully Loaded File\n");
                rfilename = rfile->name;
            } else {
                printf("Error Loading File\n");
                rfilename = NOT_LOADED;
            }
            break;
        case 3:
            clear_cache(0);
            ignore_ws = !ignore_ws;
            break;
        case 4:
            treat_as_ascii = !treat_as_ascii;
            break;
        case 5:
            compare_files(lfile, rfile, ignore_ws, treat_as_ascii);
            break;
        case 6:
            exited = 1;
            break;
        default:
            printf("Bad selection\n");
        }
        printf("\n");
    }

    printf("Exiting...\n");
    return 0;
}
