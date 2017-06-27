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

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_uwfc.h"
#include "cgc_dft.h"

#define error_code(X) -(1 << X)

#define INVALID_FILE error_code(1)
#define INVALID_NEW_FILE error_code(2)
#define BAD_CHOICE error_code(3)
#define BAD_INPUT error_code(4)
#define BAD_INPUT2 error_code(5)


static int filter_type = 0;
static char cgc_readopt(int fd) {
    char c = 0;
    char d = 0;
    char delim = '\n';

    cgc_size_t rx;
    if (cgc_receive(fd, &c, 1, &rx) != 0 || rx == 0)
        return -1;

    if (cgc_receive(fd, &d, 1, &rx) != 0 || rx == 0)
        return -1;

    if(d != delim) {
        while(d != delim) {
            if (cgc_receive(fd, &d, 1, &rx) != 0 || rx == 0)
                return -1;
        }
        return -1;
    }

    return c;
}

static void cgc_print_menu(uwfc_t *track) {
    if (track == NULL) {
        cgc_printf("1. Load File\n");
        cgc_printf("2. Quit\n\n");
        cgc_printf("--NO FILE LOADED--\n");
    } else {
        cgc_printf("1. Load New File\n");
        cgc_printf("2. Wave Visualizer\n");
        cgc_printf("3. EQ Visualizer\n");
        cgc_printf("4. Power Visualizer\n");
        cgc_printf("5. Enable Low Pass Filter\n");
        cgc_printf("6. Enable High Pass Filter\n");
        cgc_printf("7. Disable Filters\n");
        cgc_printf("8. Set visualization speed multiplier (0-9)\n");
        cgc_printf("9. Quit\n\n");

        cgc_printf("--Current Track: ");
        cgc_printf("Sampled @%dHz %d bit, ", track->sample_rate, track->bits_per_sample);
        if (track->num_channels == 1)
            cgc_printf("Mono - ");
        else
            cgc_printf("Stereo - ");
        cgc_printf("Data Size=%d\n", track->sub_chunk2_size);
        cgc_printf("::Options: Filter Type=");
        if(filter_type == 0)
            cgc_printf("None");
        else if(filter_type == 1)
            cgc_printf("Low Pass");
        else if(filter_type == 2)
            cgc_printf("High Pass");
        cgc_printf(" | Visualization Slowdown Multiplier=%d::\n\n", cgc_get_vis_multiplier());
    }
}

static void cgc_print_error_code(int code){
    if (code == INVALID_FILE)
        cgc_printf("ERROR: Couldn't load file, malformed file data\n");
    if (code == INVALID_NEW_FILE)
        cgc_printf("ERROR: Couldn't load new file, contains malformed file data\n");
    if (code == BAD_CHOICE)
        cgc_printf("ERROR: Bad Choice. Select another option\n");
    if (code == BAD_INPUT)
        cgc_printf("ERROR: Bad Input. Valid Options: 1, 2\n");
    if (code == BAD_INPUT2)
        cgc_printf("ERROR: Bad Input. Valid Options: 1, 2, 3, 4, 5, 6, 7, 8, 9\n");
}

void cgc_load_file(uwfc_t **track) {
    if (*track != NULL) {
        cgc_clear_track(track);
    }

    *track = cgc_init_track();
}

void cgc_quit(uwfc_t **track) {
    if (*track != NULL)
        cgc_clear_track(track);
}

int cgc_select_option(uwfc_t **track) {
    uwfc_t *current_track = *track;
    char choice = cgc_readopt(STDIN), m;

    if (choice == -1) {
        if (current_track == NULL)
            return BAD_INPUT;
        else
            return BAD_INPUT2;
    }


    if (current_track == NULL) {
        switch(choice) {
            case '1':
                cgc_load_file(track);
                if (*track == NULL) {
                    return INVALID_FILE;
                }
                break;
            case '2':
                cgc_quit(track);
                return 0;
            default:
                return BAD_CHOICE;
        }
    } else {
        switch(choice) {
            case '1':
                cgc_load_file(track);
                if (*track == NULL)
                    return INVALID_NEW_FILE;
                break;
            case '2':
                cgc_wave_vis(current_track);
                break;
            case '3':
                cgc_eq_vis(current_track, 1, filter_type);
                break;
            case '4':
                cgc_eq_vis(current_track, 2, filter_type);
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
                m = cgc_readopt(STDIN);
                cgc_set_vis_multiplier(m);
                break;
            case '9':
                cgc_quit(track);
                return 0;
            default:
                return BAD_CHOICE;
        }
    }

    return 1;
}

int main(int cgc_argc, char *cgc_argv[]) {
    uwfc_t *current_track = NULL;
    int code = 1;
    complex_t *dft_out;
    do {
        cgc_print_error_code(code);
        cgc_print_menu(current_track);
        code = cgc_select_option(&current_track);
    } while (code);

    cgc_printf("EXITING...\n");
    return 0;
}
