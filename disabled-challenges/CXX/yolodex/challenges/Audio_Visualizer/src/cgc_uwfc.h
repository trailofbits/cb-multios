#ifndef UWFC_H_
#define UWFC_H_

#include "cgc_stdlib.h"

typedef struct {
    unsigned char chunk_id[4];
    unsigned int chunk_size;
    unsigned char format[4];
    unsigned char sub_chunk1_id[4];
    unsigned int sub_chunk1_size;
    unsigned short audio_format;
    unsigned short num_channels;
    unsigned int sample_rate;
    unsigned int byte_rate;
    unsigned short block_align;
    unsigned short bits_per_sample;

    unsigned char sub_chunk2_id[4];
    unsigned int sub_chunk2_size;
    char* data;
} uwfc_t;

int cgc_validate_header(uwfc_t *header);
uwfc_t *cgc_init_track();
void cgc_clear_track(uwfc_t **uwfc_track);

void cgc_wave_vis(uwfc_t *track);
void cgc_eq_vis(uwfc_t *track, int vis_type, int filter_type);
void low_pass_filter(uwfc_t *track);
void high_pass_filter(uwfc_t *track);
void cgc_set_vis_multiplier(char c);
int cgc_get_vis_multiplier();


#endif /* !UWFC_H_ */
