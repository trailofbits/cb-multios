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
 
#include "libc.h"
#include <libcgc.h>
#include "libcompound.h"
#include "libmixology.h"
#include "zoom.h"
#include "asciiencode.h"

compounds_sample_t *alloc_sample_st(const size_t sample_size){


	compounds_sample_t * p = (compounds_sample_t *) malloc(sizeof(compounds_sample_t));
	if(p == NULL)
		return p;
	p->sample = (unsigned int *) malloc(sample_size * sizeof(unsigned int));
	if(p->sample == NULL)
		return NULL;
	p->sample_size = sample_size;
	return p;
}

chem_formula_t * get_compound_by_idx(unsigned int idx){
	if(idx > N_FORMULAS-1)
		return NULL;

	return &(chem_formulas[idx]);
}

char * get_sample_name_at_idx(compounds_sample_t *s, unsigned int idx){
	unsigned int sample_idx = s->sample[idx];

	return chem_formulas[sample_idx].compound_name;
}

int get_chem_ref_at_idx(compounds_sample_t *s, int idx){
	return (int) s->sample[idx];

}

// do not use this unless sure you have a non-null sample!
int set_sample_at_idx(compounds_sample_t *s, int idx, int ref){
	s->sample[idx] = ref;
	return 0;

}

int check_compound_idx_in_sample(compounds_sample_t *s, int idx){
	for(int i = 0; i < s->sample_size; ++i){
		if(get_chem_ref_at_idx(s, i) ==  (unsigned int) idx)
			return 1;
	}
	return 0;

}

compounds_sample_t *reconstruct_sample_from_zoom(zoom_filter_t *zf){
	// traverse twice, once to get sz, other to get members
	int total_count = 0;
	int bs = 0;
	for(int i = 0; i < N_FORMULAS-1; ++i){

		total_count += check_compound_idx_in_zoom(zf, i);
		if(total_count == 1)
			bs+=1;


	}
	if(total_count == 0)
		return NULL;

	compounds_sample_t *sc = alloc_sample_st(total_count);
	
	if(sc == NULL)
		return NULL;
	int sample_idx = 0;

	// todo this is realll inefficient
	for(int i = 0; i < N_FORMULAS-1; ++i){
		int zc = check_compound_idx_in_zoom(zf, i);
		if(zc == 1){
			set_sample_at_idx(sc, sample_idx, i);

			sample_idx += 1;
		}

	}

	return sc;



}



unsigned int get_npages(){
	return pos_ceil((double) N_FORMULAS / (double) PAGE_SZ);
}

// tx string and add newline, expect null term

void * get_command_from_input(char *input){
	char * possible_cmd = strtok(input, CMD_DELIM);
	if(possible_cmd == NULL)
		return NULL;
	for(int i = 0; i < NUM_CMDS; ++i){
		if(memcmp(commands[i].cmd_name, possible_cmd, strlen(commands[i].cmd_name)) == 0 && commands[i].n_calls > 0){
			commands[i].n_calls = commands[i].n_calls - 1;
			return commands[i].cmd_func;
		}
	}
	return NULL;

}

void copy_new_comp_name(mixed_compound_t *mc, char *newcomp){

#ifndef PATCHED
	memcpy(mc->compound_name, newcomp, MAX_NEW_CMPND_SZ);
#endif

#ifdef PATCHED
	memcpy(mc->compound_name, newcomp, MAX_NEW_CMPND_SZ-1);
#endif


}

char * gen_chem_name(mixed_compound_t *mc, compounds_sample_t *rcs){
	// todo +1 in patched version

	unsigned int block_sz = 8;

	for(int i =0; i < rcs->sample_size; ++i){
		if(block_sz*i == MAX_NEW_CMPND_SZ)
			break;

		chem_formula_t *cf = get_compound_by_idx(get_chem_ref_at_idx(rcs, i));
		if(cf == NULL)
			return NULL;
		size_t cpsz = strlen(cf->compound_name);
		if(cpsz > block_sz)
			cpsz = block_sz;
		
		memcpy(&(mc->compound_name[block_sz*i]), cf->compound_name, cpsz);
	}
	char *outname = malloc(MAX_NEW_CMPND_SZ);
	memcpy(outname, mc->compound_name, MAX_NEW_CMPND_SZ);

	return outname;


}


int mix_cmd(char *args){
	
	// todo test for bad seed...
	char *rnd_seed_txt = strtok(args, CMD_DELIM);
	if(rnd_seed_txt == NULL)
		return CMDBADARG;


	char *new_name = strtok(NULL, CMD_DELIM);
	if(new_name == NULL)
		return CMDBADARG;
	
	char *bff = strtok(NULL, CMD_DELIM);
	if(bff == NULL)
		return CMDBADARG;



	if(bff == NULL || rnd_seed_txt == NULL)
		return CMDBADARG;


	zoom_filter_t *zff = load_zoom_filter(bff, get_sample_n_bits(SAMPLESZ));

	if(zff == NULL)
		return CMDFAIL;




	compounds_sample_t *rcs = reconstruct_sample_from_zoom(zff);

	// todo validate filter more ...

	if(rcs == NULL)
		return CMDFAIL;
	// int allocate(size_t length, int is_X, void **addr)/


	mixed_compound_t *mc = calloc(1, sizeof(mixed_compound_t));
    for(int j = sizeof(mixed_compound_t)-1; j < 4096; ++j)
        ((char *) mc)[j] = 0xc;
	if(mc == NULL)
		return CMDFAIL;
	
	double moles = 1.0;
	for(int i =0; i < rcs->sample_size; ++i){
		chem_formula_t *cf = get_compound_by_idx(get_chem_ref_at_idx(rcs, i));
		if(cf == NULL)
			return CMDFAIL;

		moles *= cf->mole;
		// need to activate last byte...
		// todo build up name for compound so that its 128 long


	}
	mc->moles = (unsigned int ) moles;
	if(new_name == NULL || strlen(new_name) < 3) 
		return CMDFAIL;
	copy_new_comp_name(mc, new_name);

	// todo replace strlen with MAX_NEW_CMPND_SZ in patch
	// this will fail as it overruns the malloc'd space as a result of hte overflow
	char *outmsg = "New compound: ";
	transmit_all(STDOUT, outmsg, strlen(outmsg));

	// this triggers the vuln if the compound name is right up on the edge and the multiplier is over

	
#ifndef PATCHED
	size_t cpsz = strlen(mc->compound_name);
	memcpy(last_compound, mc->compound_name, cpsz);
#endif

#ifdef PATCHED
	size_t cpsz = strlen(mc->compound_name);
	if(cpsz > MAX_NEW_CMPND_SZ)
		cpsz = MAX_NEW_CMPND_SZ;

	memcpy(last_compound, mc->compound_name, cpsz);
#endif

	// if(cpsz > MAX_NEW_CMPND_SZ)
	// 	cpsz = MAX_NEW_CMPND_SZ;


	transmit_all(STDOUT, new_name, cpsz);

	// todo tx moles tooo
	transmit_all(STDOUT, "\n", 1);
	

	// todo take reconstructed sample and mix it together to form longer compound, spit that back with strcat...
	// todo activate the vuln here...

	return CMDOKAY;
}

int list_cmd(char *args){
	// todo get page number from strtok
	size_t cmd_len = strlen(args);
	char * pg_num_txt = args;//\\\strtok(NULL, cmd_len);
	if(pg_num_txt == NULL){
		return CMDBADARG;
	}
	if(buf_is_numeric(pg_num_txt) != 1){
		return CMDBADNUMERIC;
	}

	int pg_num_i = atoi(pg_num_txt);
	if(pg_num_i < 0)
		return CMDNEGNUMERIC;

	return transmit_compound_list_page(pg_num_i);
}

int quit_cmd(char *args){
	_terminate(0);
}

int prep_cmd(char *args){
	// todo send back bloom filter and n_bits of bloom sz ... nbits hasn't been done yet
	// part of vuln will be that person has to prep before mix and we can only have N preparations
	char *rnd_seed_txt = args;
	if(buf_is_numeric(rnd_seed_txt) != 1){
		return CMDBADARG;
	}

	// part of the vuln is that we can bring up the seed size pretty easily from numeric ... give them more to reason about

	compounds_sample_t *samp = sample_compounds(rnd_seed_txt, PREPSAMPLESZ);
	if(samp == NULL)
		return CMDFAIL;

	int res = transmit_compound_sample_zoom(samp);
	// todo keep sample seed around?

	free_sample_st(samp);
	// we don't care which direction this overflows in because the hash will bring us back

	return res;
}



int transmit_compound_list_page(unsigned int pg_num){
	unsigned int n_pages = get_npages();

	if(pg_num >= n_pages){
		return CMDBADARG;
	}

	unsigned int start = pg_num * PAGE_SZ;
	unsigned int end = (start + PAGE_SZ);
	if(end > N_FORMULAS-1)
		end = N_FORMULAS-1;

	return transmit_compound_list(start, end);

}


void transmit_line_nl(const char *buf){
	transmit_all(STDOUT, buf, strlen(buf) );
	transmit_all(STDOUT, "\n", 1);
}

int transmit_compound_list(unsigned int from, unsigned int to){
	if( to <= from || from > N_FORMULAS-1 || to > N_FORMULAS-1)
		return TXFAIL;

	for(int i = from; i < to; i++){
		transmit_line_nl(chem_formulas[i].compound_name);
	}

	return CMDOKAY;

}


zoom_filter_t * make_compound_sample_zoom(compounds_sample_t *s){
	zoom_filter_t *zf = new_zoom_filter(n_elements_from_sampsz(s->sample_size));
	if(zf == NULL){
		char * m = "failed new zdf";
		transmit_all(STDOUT, m, strlen(m));
		return NULL;
	}


	for(int i =0; i < s->sample_size; ++i){
		int sample_idx = get_chem_ref_at_idx(s, i);
		if(sample_idx > N_FORMULAS-1 ){
			// todo free zf
			char * m = "failed new zdf2";
			transmit_all(STDOUT, m, strlen(m));
			zoom_free(zf);
			return NULL;
		}

		char * cn = chem_formulas[sample_idx].compound_name;
		hash_pair_t *hp = hash_pair_buf(cn, strlen(cn) );
		zoom_add(hp, zf);
		
		// todo check number transmitted


	}
	return zf;
}

void free_zoombuf(char *zb){
	free(zb);
}

char * zoom_buf(compounds_sample_t *s){
	zoom_filter_t *zf = make_compound_sample_zoom(s);
	if(zf == NULL)

		return NULL;


	char * tx_buf = encode((char *) zf->data, zf->data_len);
	zoom_free(zf);
	return tx_buf;
}

int transmit_compound_sample_zoom(compounds_sample_t *s){


	// encode bloom and mark
	char *tx_buf = zoom_buf(s);

	if(tx_buf == NULL)
		return -1;
	transmit_line_nl(tx_buf);

	free(tx_buf);
	return 0;

}

int check_compound_idx_in_zoom(zoom_filter_t *zf, int compound_idx){
	char * cn = chem_formulas[compound_idx].compound_name;
	int sl = strlen(cn);
	hash_pair_t * hp = hash_pair_buf(cn, sl);
	int zc = zoom_check(hp, zf);
	free(hp);
	return zc;
}






void free_sample_st(compounds_sample_t *p){
	free(p->sample);
	free(p);
}

compounds_sample_t *sample_compounds(const char *seed, const size_t sample_size){
	if(sample_size > N_FORMULAS-1)
		return NULL;
	unsigned int h = crazy_hash(seed, strlen(seed), 0xcafeb4b4);

	compounds_sample_t *sample = alloc_sample_st(sample_size);
	// todo check alloc
	if(sample == NULL)
		return NULL;
	for(int i =0; i < sample_size; ++i){
		set_sample_at_idx(sample, i,  (h % (N_FORMULAS-1)));
		
		h = crazy_hash((const char *) &h, sizeof(h), h);
	}

	return sample;
}

// want to process command of form LIST RND NUM
// int process_list_command(char **args){

// 	transmit_compound_list()
// }