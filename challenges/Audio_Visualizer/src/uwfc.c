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

#include "cgc_uwfc.h"
#include "cgc_dft.h"
#include "cgc_string.h"

#define error_code(X) -(1 << X)

#define BAD_CHUNK_ID error_code(1)
#define BAD_CHUNK_SIZE error_code(2)
#define BAD_FORMAT error_code(3)
#define BAD_SUB_CHUNK1_ID error_code(4)
#define BAD_AUDIO_FORMAT error_code(5)
#define BAD_NUM_CHANNELS error_code(6)
#define BAD_SAMPLE_RATE error_code(7)
#define BAD_BYTE_RATE error_code(8)
#define BAD_BLOCK_ALLIGN error_code(9)
#define BAD_BITS_PER_SAMPLE error_code(10)
#define BAD_SUB_CHUNK2_ID error_code(11)

#define MAX_CHAR 127
#define MAX_SHORT 32767
#define MAX_BUCKETS 12

#define FREQ_VIS 1
#define POWER_VIS 2

#define NO_FILTER 1
#define LOW_PASS 1
#define HIGH_PASS 2

static const cgc_size_t UWFC_HEADER_SIZE = sizeof(uwfc_t) - sizeof(char *);
static int vis_multiplier = 0;

void cgc_set_vis_multiplier(char c) {
    if (c <= '9' && c >= '0') {
        vis_multiplier = c - '0';
        cgc_printf("Multiplier set to %d\n", c - '0');
    } else {
        cgc_printf("Bad multiplier argument\n");
    }
}

int cgc_get_vis_multiplier() {
    return vis_multiplier;
}

int cgc_validate_header(uwfc_t *header) {
    char *magic = "FFIR";
    char *audio_fmt = "UWFC";
    char *sub_chunk1_id = "cgc ";
    char *sub_chunk2_id = "data";

    // "FFIR"
    if (cgc_memcmp(header->chunk_id, magic, 4) != 0)
        return BAD_CHUNK_ID;

    if (header->chunk_size != (4 + (8 + header->sub_chunk1_size) + (8 + header->sub_chunk2_size)))
        return BAD_CHUNK_SIZE;

    // "UWFC"
    unsigned char *temp = &header->format[0];
    if (cgc_memcmp(temp, audio_fmt, 4) != 0)
        return BAD_FORMAT;

    // "cgc "
    if (cgc_memcmp(header->sub_chunk1_id, sub_chunk1_id, 4) != 0)
        return BAD_SUB_CHUNK1_ID;

    // Only allow uncompressed PCM
    if (header->audio_format != 1)
        return BAD_AUDIO_FORMAT;

    // Mono or Stereo only
    if (header->num_channels != 1 && header->num_channels != 2)
        return BAD_NUM_CHANNELS;

    if (header->sample_rate != 8000 && header->sample_rate != 11025 &&
        header->sample_rate != 16000 && header->sample_rate != 22050 &&
        header->sample_rate != 32000 && header->sample_rate != 44100 &&
        header->sample_rate != 48000 && header->sample_rate != 4000) /* BMC - using smaller sample rates for faster testing */
        return BAD_SAMPLE_RATE;

    if (header->byte_rate !=
        (header->sample_rate * header->num_channels * header->bits_per_sample/8))
        return BAD_BYTE_RATE;

    if (header->block_align != (header->num_channels * header->bits_per_sample/8))
        return BAD_BYTE_RATE;

    // Only allow 8 or 16 bit files
    if (header->bits_per_sample != 8 && header->bits_per_sample != 16)
        return BAD_BITS_PER_SAMPLE;

    // "data"
    if (cgc_memcmp(header->sub_chunk2_id, sub_chunk2_id, 4) != 0)
        return BAD_SUB_CHUNK2_ID;

#ifndef PATCHED
    return header->chunk_size + 8; //returns file size
#else
    return header->sub_chunk2_size; //returns track size
#endif
}

uwfc_t *cgc_init_track() {
    uwfc_t *track;
    int track_size = 0;
    cgc_size_t rx = 0, rx_count = 0;

    track = cgc_malloc(sizeof(uwfc_t));
    if (track == NULL)
        return NULL;

    if (cgc_receive(STDIN, track, UWFC_HEADER_SIZE, &rx) != 0 || rx != UWFC_HEADER_SIZE) {
        cgc_free(track);
        return NULL;
    }

#ifndef PATCHED
    track_size = cgc_validate_header(track) - UWFC_HEADER_SIZE; //size of file
#else
    track_size = cgc_validate_header(track); //track->sub_chunk2_size (size of data)
#endif

    // track_size is signed int as a mechanism to prevent huge malloc requests
    if (track_size < 0) {
        cgc_free(track);
        return NULL;
    }

    if (track_size == 0) {
        track->data = NULL;
    } else {
        track->data = cgc_malloc(track_size);
        if (track->data == NULL) {
            cgc_free(track);
            return NULL;
        }
    }

    while (cgc_receive(STDIN, &track->data[rx_count], (track->sub_chunk2_size - rx_count), &rx) == 0 &&
            (rx_count + rx) != track->sub_chunk2_size) {
        if(rx == 0) {
            cgc_free(track->data);
            cgc_free(track);
            return NULL;
        }

        rx_count += rx;
    }

    return track;
}

void cgc_clear_track(uwfc_t **uwfc_track) {
    uwfc_t *track = *uwfc_track;
    if (track == NULL)
        return;

    if (track->data != NULL)
        cgc_free(track->data);

    if(track != NULL)
        cgc_free(track);
    *uwfc_track = NULL;
}

static void cgc_slow_vis() {
    int i = 0;
    for(i = 0; i < 200000 * vis_multiplier; i++)
        cgc_sin(i) / (cgc_cos(i) + 1);
}


static void cgc_plot_mono_wave(uwfc_t *track, unsigned char *data) {
    double normalized = 0;

    if (track->bits_per_sample == 8)
        normalized = (*data - MAX_CHAR) / (double)MAX_CHAR;
    else
        normalized = (*((short *)data)) / (double)MAX_SHORT;

    //81 width (0-80, inclusive) + null terminator = 82
    const int w = 42;
    int y = (w - 1) / 2;
    int x = (normalized * y) + y + .5;
    char line[w];
    cgc_memset(line, ' ', w);
    line[w-1] = '\0';
    line[x] = '*';
    cgc_printf("%s\n", line);

}

static void cgc_plot_stereo_wave(uwfc_t *track, unsigned char *data) {
    double normalized_l = 0;
    double normalized_r = 0;

    if (track->bits_per_sample == 8) {
        normalized_l = (*data - MAX_CHAR) / (double)MAX_CHAR;
        normalized_r = ((*(data + 1)) - MAX_CHAR) / (double)MAX_CHAR;
    } else {
        normalized_l = (*((short *)data)) / (double)MAX_SHORT;
        normalized_r = (*((short *)(data + 2))) / (double)MAX_SHORT;
    }

    //81 width (0-80, inclusive) + null terminator = 82
    const int w = 83;
    int chan_w = w / 2;
    int y = (chan_w - 2) / 2;
    int x_l = (normalized_l * y) + y + .5;
    int x_r = (normalized_r * y) + y + chan_w + 1.5;
    char line[w];
    cgc_memset(line, ' ', w);
    line[w-1] = '\0';
    line[chan_w] = '|';
    line[x_l] = '*';
    line[x_r] = '*';
    cgc_printf("%s\n", line);
}

void cgc_wave_vis(uwfc_t *track) {
    unsigned char *data = (unsigned char*)track->data;
    cgc_size_t i = 0;

    while (i < (track->sub_chunk2_size / track->block_align)) {
        if (i % track->sample_rate == 0)
            cgc_slow_vis();

        if (track->num_channels == 2)
            cgc_plot_stereo_wave(track, data);
        else if(track->num_channels == 1)
            cgc_plot_mono_wave(track, data);

        i++;
        data += track->block_align;
    }

    cgc_printf("++++END VISUALIZATION++++\n\n");
}

typedef struct {
    double total_power;
    double max_power;
    int freq_count;
} eq_bucket_t;

static void cgc_add_to_bucket(eq_bucket_t *buckets, complex_t *f, int f_i, int f_max) {
    // Usign gamma-corrected frequency range (gamma = 2 -> sqrt)
    int b_i = (int)(cgc_sqrt(f_i / (double)f_max) * MAX_BUCKETS);
    double power;
    eq_bucket_t *bucket = &buckets[b_i];

    power = cgc_pow(f->real, 2) + cgc_pow(f->imag, 2);
    //factor in noise & dft leakage
    if (power > 4)
        bucket->total_power += power;
    if (bucket->max_power < power)
        bucket->max_power = power;

    bucket->freq_count++;
}

static void cgc_vis_buckets(eq_bucket_t *buckets, int vis_type) {
    int i;
    const int max_height = 90;
    char line[max_height + 1];

    cgc_slow_vis();
    if (vis_type == FREQ_VIS) {
        int h;
        for (h = max_height; h >= 0; h--) {
            cgc_printf("   ");
            for (i = 0; i < MAX_BUCKETS; i++) {
                // Because loudness of sound is logarithmic (dB), by using frequency buckets
                // the equalizer is best visualized taking the log of the max power
                // of all frequencies in a given frequency bucket
                if (h == 0) {
                    cgc_printf("|-----|");
                } else if (h <= (int)(cgc_log(buckets[i].max_power))) {
                    cgc_printf("|=====|");
                } else {
                    if( h <= 30)
                        cgc_printf("|     |");
                }
            }
            cgc_printf("\n");
        }
    } else if(vis_type == POWER_VIS) {
        double total_power = 0;
        int bar_width = 2;
        int bar_len = 0;
        for (i = 0; i < MAX_BUCKETS; i++)
            total_power += buckets[i].total_power;

        // Because loudness of sound is logarithmic (dB), the overall loudness
        // for each second (sample cycle) is best visualized taking the log of the
        // total power of all frequencies in frequency bucket
        bar_len = (int)(cgc_log(total_power + 1) * 3); // +1 to avoid cgc_log(0), cgc_log(1) is neglible
        cgc_memset(line, 0, max_height + 1);
        cgc_memset(line, '=', bar_len );

        line[bar_len] = ']';
        for(i = 0; i < bar_width; i++)
            cgc_printf("%s\n", line);
    }
}

void cgc_eq_vis(uwfc_t *track, int vis_type, int filter_type) {
    int i, j, len;
    unsigned char *data = (unsigned char*) track->data;
    double *dft_inputs_l;
    double *dft_inputs_r;
    complex_t *dft_output_l= NULL;
    complex_t *dft_output_r = NULL;
    double normalized_l;
    double normalized_r;
    eq_bucket_t freq_bars[MAX_BUCKETS];

    dft_inputs_l = cgc_malloc(track->sample_rate * sizeof(double));
    if (dft_inputs_l == NULL)
        return;

    if (track->num_channels == 2) {
        dft_inputs_r = cgc_malloc(track->sample_rate * sizeof(double));
        if (dft_inputs_r == NULL)
            return;
    }

    i=0;
    while (i < (track->sub_chunk2_size / track->block_align)) {
        for (j = 0; j < MAX_BUCKETS; j++) {
            freq_bars[j].max_power = 0;
            freq_bars[j].total_power = 0;
            freq_bars[j].freq_count = 0;
        }

        j=0;
        while(j < track->sample_rate && i < (track->sub_chunk2_size / track->block_align)) {
            if (track->bits_per_sample == 8) {
                normalized_l = (*data - MAX_CHAR) / (double)MAX_CHAR;
                if (track->num_channels == 2)
                    normalized_r = ((*(data + 1)) - MAX_CHAR) / (double)MAX_CHAR;
            } else {
                normalized_l = (*((short *)data)) / (double)MAX_SHORT;
                if (track->num_channels == 2)
                    normalized_r = (*((short *)(data + 2))) / (double)MAX_SHORT;
            }

            dft_inputs_l[j] = normalized_l;
            if (track->num_channels == 2)
                dft_inputs_r[j] = normalized_r;

            j++;
            i++;
            data += track->block_align;
        }

        dft_output_l = cgc_dft(dft_inputs_l, j, &len);
        if (track->num_channels == 2)
            dft_output_r = cgc_dft(dft_inputs_r, j, &len);

        int k;
        if (filter_type == LOW_PASS) {
            //filter out top frequencies
            for (k = (track->sample_rate*4)/20; k < j && k < (track->sample_rate*16)/20; k++) {
                dft_output_l[k].real = 0;
                dft_output_l[k].imag = 0;
                if (track->num_channels == 2) {
                    dft_output_r[k].real = 0;
                    dft_output_r[k].imag = 0;
                }
            }
        }
        else if (filter_type == HIGH_PASS) {
            //filter out bottom frequencies
            for (k = 0; k < (track->sample_rate * 2)/20 && k < j; k++) {
                dft_output_l[k].real = 0;
                dft_output_l[k].imag = 0;
                if (track->num_channels == 2) {
                    dft_output_r[k].real = 0;
                    dft_output_r[k].imag = 0;
                }
            }
            for (k = (track->sample_rate * 18)/20; k < j; k++) {
                break;
                dft_output_l[k].real = 0;
                dft_output_l[k].imag = 0;
                if (track->num_channels == 2) {
                    dft_output_r[k].real = 0;
                    dft_output_r[k].imag = 0;
                }
            }
        }
        for (k = 0; k < j/2; k++) {
            cgc_add_to_bucket(&freq_bars[0], &dft_output_l[k], k, j/2);
            if (track->num_channels == 2)
                cgc_add_to_bucket(&freq_bars[0], &dft_output_r[k], k, j/2);
        }

        cgc_vis_buckets(&freq_bars[0], vis_type);
        cgc_free(dft_output_l);

        if (track->num_channels == 2)
            cgc_free(dft_output_r);
    }

    cgc_printf("++++END VISUALIZATION++++\n\n");
}
