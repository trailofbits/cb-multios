/*
 * Author: Sagar Momin <sagar.momin@kapricasecurity.com>
 *
 * Copyright (c) 2014 Kaprica Security, Inc.
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

#include "uwfc.h"
#include "dft.h"

#define error_code(X) -(1 << X)

#define INVALID_FILE error_code(1)
#define INVALID_NEW_FILE error_code(2)
#define BAD_CHOICE error_code(3)
#define BAD_INPUT error_code(4)
#define BAD_INPUT2 error_code(5)


static int filter_type = 0;
static char readopt(int fd) {
    char c = 0;
    char d = 0;
    char delim = '\n';

    size_t rx;
    if (receive(fd, &c, 1, &rx) != 0 || rx == 0)
        return -1;

    if (receive(fd, &d, 1, &rx) != 0 || rx == 0)
        return -1;

    if(d != delim) {
        while(d != delim) {
            if (receive(fd, &d, 1, &rx) != 0 || rx == 0)
                return -1;
        }
        return -1;
    }

    return c;
}

static void print_menu(uwfc_t *track) {
    if (track == NULL) {
        printf("1. Load File\n");
        printf("2. Quit\n\n");
        printf("--NO FILE LOADED--\n");
    } else {
        printf("1. Load New File\n");
        printf("2. Wave Visualizer\n");
        printf("3. EQ Visualizer\n");
        printf("4. Power Visualizer\n");
        printf("5. Enable Low Pass Filter\n");
        printf("6. Enable High Pass Filter\n");
        printf("7. Disable Filters\n");
        printf("8. Set visualization speed multiplier (0-9)\n");
        printf("9. Quit\n\n");

        printf("--Current Track: ");
        printf("Sampled @%dHz %d bit, ", track->sample_rate, track->bits_per_sample);
        if (track->num_channels == 1)
            printf("Mono - ");
        else
            printf("Stereo - ");
        printf("Data Size=%d\n", track->sub_chunk2_size);
        printf("::Options: Filter Type=");
        if(filter_type == 0)
            printf("None");
        else if(filter_type == 1)
            printf("Low Pass");
        else if(filter_type == 2)
            printf("High Pass");
        printf(" | Visualization Slowdown Multiplier=%d::\n\n", get_vis_multiplier());
    }
}

static void print_error_code(int code){
    if (code == INVALID_FILE)
        printf("ERROR: Couldn't load file, malformed file data\n");
    if (code == INVALID_NEW_FILE)
        printf("ERROR: Couldn't load new file, contains malformed file data\n");
    if (code == BAD_CHOICE)
        printf("ERROR: Bad Choice. Select another option\n");
    if (code == BAD_INPUT)
        printf("ERROR: Bad Input. Valid Options: 1, 2\n");
    if (code == BAD_INPUT2)
        printf("ERROR: Bad Input. Valid Options: 1, 2, 3, 4, 5, 6, 7, 8, 9\n");
}

void load_file(uwfc_t **track) {
    if (*track != NULL) {
        clear_track(track);
    }

    *track = init_track();
}

void quit(uwfc_t **track) {
    if (*track != NULL)
        clear_track(track);
}

int select_option(uwfc_t **track) {
    uwfc_t *current_track = *track;
    char choice = readopt(STDIN), m;

    if (choice == -1) {
        if (current_track == NULL)
            return BAD_INPUT;
        else
            return BAD_INPUT2;
    }


    if (current_track == NULL) {
        switch(choice) {
            case '1':
                load_file(track);
                if (*track == NULL) {
                    return INVALID_FILE;
                }
                break;
            case '2':
                quit(track);
                return 0;
            default:
                return BAD_CHOICE;
        }
    } else {
        switch(choice) {
            case '1':
                load_file(track);
                if (*track == NULL)
                    return INVALID_NEW_FILE;
                break;
            case '2':
                wave_vis(current_track);
                break;
            case '3':
                eq_vis(current_track, 1, filter_type);
                break;
            case '4':
                eq_vis(current_track, 2, filter_type);
                break;
            case '5':
                filter_type = 1;
                break;
            case '6':
                filter_type = 2;
                break;
            case '7':
                filter_type = 0;
                break;
            case '8':
                m = readopt(STDIN);
                set_vis_multiplier(m);
                break;
            case '9':
                quit(track);
                return 0;
            default:
                return BAD_CHOICE;
        }
    }

    return 1;
}

int main() {
    uwfc_t *current_track = NULL;
    int code = 1;
    complex_t *dft_out;
    do {
        print_error_code(code);
        print_menu(current_track);
        code = select_option(&current_track);
    } while (code);

    printf("EXITING...\n");
    return 0;
}
