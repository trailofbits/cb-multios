/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef LIB_MIXOLOGY_H
#define LIB_MIXOLOGY_H
#include "cgc_zoom.h"
#include "cgc_libcompound.h"

#define MAX_MIX_N 8

typedef struct compounds_sample {
	unsigned int *sample;
	unsigned int sample_size;
} compounds_sample_t;

typedef struct command {
	int n_calls;
	char * cmd_name;
	int (*cmd_func)(char *);


} command_t;

const static int MAX_NEW_CMPND_SZ = 128;

typedef struct mixed_compound{
	char compound_name[MAX_NEW_CMPND_SZ];
	unsigned int moles;

}mixed_compound_t;
const static unsigned int SUPER_MASSIVE_THRESH = 0xFF000000;
const static int NUM_CMDS = 4;
const static char CMD_DELIM = ' ';
const static int CMDFAIL = 1;
const static int CMDOKAY = 0;
const static int TXFAIL = -1;
const static int CMDBADARG = 2;
const static int CMDBADNUMERIC = 3;
const static int CMDNEGNUMERIC = 4;
const static int PAGE_SZ = 25;


const static cgc_size_t PREPSAMPLESZ = 1000;
const static cgc_size_t SAMPLESZ = 25;

static char last_compound[MAX_NEW_CMPND_SZ];
unsigned int cgc_get_npages(); 

int cgc_transmit_compound_list(unsigned int from, unsigned int to);
char * cgc_zoom_buf(compounds_sample_t *s);
compounds_sample_t *cgc_sample_compounds(const char *seed, const cgc_size_t sample_size);
void cgc_free_sample_st(compounds_sample_t *p);
int cgc_transmit_compound_sample_zoom(compounds_sample_t *s);
zoom_filter_t * cgc_make_compound_sample_zoom(compounds_sample_t *s);
int cgc_check_compound_idx_in_zoom(zoom_filter_t *zf, int compound_idx);
void * cgc_get_command_from_input(char *input);
int cgc_transmit_compound_list_page(unsigned int pg_num);
char * cgc_get_sample_name_at_idx(compounds_sample_t *s, unsigned int idx);
void cgc_free_zoombuf(char *zb);
int cgc_check_compound_idx_in_sample(compounds_sample_t *s, int idx);
int cgc_set_sample_at_idx(compounds_sample_t *s, int idx,  int ref);
void cgc_transmit_line_nl(const char *buf);

int cgc_mix_cmd(char *args);
int cgc_list_cmd(char *args);
int cgc_prep_cmd(char *args);
int cgc_quit_cmd(char *args);

static command_t commands[NUM_CMDS] = {
	{MAX_MIX_N, "MIX", &cgc_mix_cmd},
	{512, "LIST", &cgc_list_cmd},
	{MAX_MIX_N, "PREP", &cgc_prep_cmd},
	{1, "QUIT", &cgc_quit_cmd},
};

#endif