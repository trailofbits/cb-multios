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
 
#include "cgc_libc.h"
#include "libcgc.h"
#include "cgc_libcompound.h"
#include "cgc_libmixology.h"
#include "cgc_zoom.h"
#include "cgc_asciiencode.h"

compounds_sample_t *cgc_alloc_sample_st(const cgc_size_t sample_size){


	compounds_sample_t * p = (compounds_sample_t *) cgc_malloc(sizeof(compounds_sample_t));
	if(p == NULL)
		return p;
	p->sample = (unsigned int *) cgc_malloc(sample_size * sizeof(unsigned int));
	if(p->sample == NULL)
		return NULL;
	p->sample_size = sample_size;
	return p;
}

chem_formula_t * cgc_get_compound_by_idx(unsigned int idx){
	if(idx > N_FORMULAS-1)
		return NULL;

	return &(chem_formulas[idx]);
}

char * cgc_get_sample_name_at_idx(compounds_sample_t *s, unsigned int idx){
	unsigned int sample_idx = s->sample[idx];

	return chem_formulas[sample_idx].compound_name;
}

int cgc_get_chem_ref_at_idx(compounds_sample_t *s, int idx){
	return (int) s->sample[idx];

}

// do not use this unless sure you have a non-null sample!
int cgc_set_sample_at_idx(compounds_sample_t *s, int idx, int ref){
	s->sample[idx] = ref;
	return 0;

}

int cgc_check_compound_idx_in_sample(compounds_sample_t *s, int idx){
	for(int i = 0; i < s->sample_size; ++i){
		if(cgc_get_chem_ref_at_idx(s, i) ==  (unsigned int) idx)
			return 1;
	}
	return 0;

}

compounds_sample_t *cgc_reconstruct_sample_from_zoom(zoom_filter_t *zf){
	// traverse twice, once to get sz, other to get members
	int total_count = 0;
	int bs = 0;
	for(int i = 0; i < N_FORMULAS-1; ++i){

		total_count += cgc_check_compound_idx_in_zoom(zf, i);
		if(total_count == 1)
			bs+=1;


	}
	if(total_count == 0)
		return NULL;

	compounds_sample_t *sc = cgc_alloc_sample_st(total_count);
	
	if(sc == NULL)
		return NULL;
	int sample_idx = 0;

	// todo this is realll inefficient
	for(int i = 0; i < N_FORMULAS-1; ++i){
		int zc = cgc_check_compound_idx_in_zoom(zf, i);
		if(zc == 1){
			cgc_set_sample_at_idx(sc, sample_idx, i);

			sample_idx += 1;
		}

	}

	return sc;



}



unsigned int cgc_get_npages(){
	return cgc_pos_ceil((double) N_FORMULAS / (double) PAGE_SZ);
}

// tx string and add newline, expect null term

void * cgc_get_command_from_input(char *input){
	char * possible_cmd = cgc_strtok(input, CMD_DELIM);
	if(possible_cmd == NULL)
		return NULL;
	for(int i = 0; i < NUM_CMDS; ++i){
		if(cgc_memcmp(commands[i].cmd_name, possible_cmd, cgc_strlen(commands[i].cmd_name)) == 0 && commands[i].n_calls > 0){
			commands[i].n_calls = commands[i].n_calls - 1;
			return commands[i].cmd_func;
		}
	}
	return NULL;

}

void cgc_copy_new_comp_name(mixed_compound_t *mc, char *newcomp){

#ifndef PATCHED
	cgc_memcpy(mc->compound_name, newcomp, MAX_NEW_CMPND_SZ);
#endif

#ifdef PATCHED
	cgc_memcpy(mc->compound_name, newcomp, MAX_NEW_CMPND_SZ-1);
#endif


}

char * cgc_gen_chem_name(mixed_compound_t *mc, compounds_sample_t *rcs){
	// todo +1 in patched version

	unsigned int block_sz = 8;

	for(int i =0; i < rcs->sample_size; ++i){
		if(block_sz*i == MAX_NEW_CMPND_SZ)
			break;

		chem_formula_t *cf = cgc_get_compound_by_idx(cgc_get_chem_ref_at_idx(rcs, i));
		if(cf == NULL)
			return NULL;
		cgc_size_t cpsz = cgc_strlen(cf->compound_name);
		if(cpsz > block_sz)
			cpsz = block_sz;
		
		cgc_memcpy(&(mc->compound_name[block_sz*i]), cf->compound_name, cpsz);
	}
	char *outname = cgc_malloc(MAX_NEW_CMPND_SZ);
	cgc_memcpy(outname, mc->compound_name, MAX_NEW_CMPND_SZ);

	return outname;


}


int cgc_mix_cmd(char *args){
	
	// todo test for bad seed...
	char *rnd_seed_txt = cgc_strtok(args, CMD_DELIM);
	if(rnd_seed_txt == NULL)
		return CMDBADARG;


	char *new_name = cgc_strtok(NULL, CMD_DELIM);
	if(new_name == NULL)
		return CMDBADARG;
	
	char *bff = cgc_strtok(NULL, CMD_DELIM);
	if(bff == NULL)
		return CMDBADARG;



	if(bff == NULL || rnd_seed_txt == NULL)
		return CMDBADARG;


	zoom_filter_t *zff = cgc_load_zoom_filter(bff, cgc_get_sample_n_bits(SAMPLESZ));

	if(zff == NULL)
		return CMDFAIL;




	compounds_sample_t *rcs = cgc_reconstruct_sample_from_zoom(zff);

	// todo validate filter more ...

	if(rcs == NULL)
		return CMDFAIL;
	// int cgc_allocate(cgc_size_t length, int is_X, void **addr)/


	mixed_compound_t *mc = cgc_calloc(1, sizeof(mixed_compound_t));
    for(int j = sizeof(mixed_compound_t)-1; j < 4096; ++j)
        ((char *) mc)[j] = 0xc;
	if(mc == NULL)
		return CMDFAIL;
	
	double moles = 1.0;
	for(int i =0; i < rcs->sample_size; ++i){
		chem_formula_t *cf = cgc_get_compound_by_idx(cgc_get_chem_ref_at_idx(rcs, i));
		if(cf == NULL)
			return CMDFAIL;

		moles *= cf->mole;
		// need to activate last byte...
		// todo build up name for compound so that its 128 long


	}
	mc->moles = (unsigned int ) moles;
	if(new_name == NULL || cgc_strlen(new_name) < 3) 
		return CMDFAIL;
	cgc_copy_new_comp_name(mc, new_name);

	// todo replace cgc_strlen with MAX_NEW_CMPND_SZ in patch
	// this will fail as it overruns the malloc'd space as a result of hte overflow
	char *outmsg = "New compound: ";
	cgc_transmit_all(STDOUT, outmsg, cgc_strlen(outmsg));

	// this triggers the vuln if the compound name is right up on the edge and the multiplier is over

	
#ifndef PATCHED
	cgc_size_t cpsz = cgc_strlen(mc->compound_name);
	cgc_memcpy(last_compound, mc->compound_name, cpsz);
#endif

#ifdef PATCHED
	cgc_size_t cpsz = cgc_strlen(mc->compound_name);
	if(cpsz > MAX_NEW_CMPND_SZ)
		cpsz = MAX_NEW_CMPND_SZ;

	cgc_memcpy(last_compound, mc->compound_name, cpsz);
#endif

	// if(cpsz > MAX_NEW_CMPND_SZ)
	// 	cpsz = MAX_NEW_CMPND_SZ;


	cgc_transmit_all(STDOUT, new_name, cpsz);

	// todo tx moles tooo
	cgc_transmit_all(STDOUT, "\n", 1);
	

	// todo take reconstructed sample and mix it together to form longer compound, spit that back with strcat...
	// todo activate the vuln here...

	return CMDOKAY;
}

int cgc_list_cmd(char *args){
	// todo get page number from strtok
	cgc_size_t cmd_len = cgc_strlen(args);
	char * pg_num_txt = args;//\\\strtok(NULL, cmd_len);
	if(pg_num_txt == NULL){
		return CMDBADARG;
	}
	if(cgc_buf_is_numeric(pg_num_txt) != 1){
		return CMDBADNUMERIC;
	}

	int pg_num_i = cgc_atoi(pg_num_txt);
	if(pg_num_i < 0)
		return CMDNEGNUMERIC;

	return cgc_transmit_compound_list_page(pg_num_i);
}

int cgc_quit_cmd(char *args){
	cgc__terminate(0);
}

int cgc_prep_cmd(char *args){
	// todo send back bloom filter and n_bits of bloom sz ... nbits hasn't been done yet
	// part of vuln will be that person has to prep before mix and we can only have N preparations
	char *rnd_seed_txt = args;
	if(cgc_buf_is_numeric(rnd_seed_txt) != 1){
		return CMDBADARG;
	}

	// part of the vuln is that we can bring up the seed size pretty easily from numeric ... give them more to reason about

	compounds_sample_t *samp = cgc_sample_compounds(rnd_seed_txt, PREPSAMPLESZ);
	if(samp == NULL)
		return CMDFAIL;

	int res = cgc_transmit_compound_sample_zoom(samp);
	// todo keep sample seed around?

	cgc_free_sample_st(samp);
	// we don't care which direction this overflows in because the hash will bring us back

	return res;
}



int cgc_transmit_compound_list_page(unsigned int pg_num){
	unsigned int n_pages = cgc_get_npages();

	if(pg_num >= n_pages){
		return CMDBADARG;
	}

	unsigned int start = pg_num * PAGE_SZ;
	unsigned int end = (start + PAGE_SZ);
	if(end > N_FORMULAS-1)
		end = N_FORMULAS-1;

	return cgc_transmit_compound_list(start, end);

}


void cgc_transmit_line_nl(const char *buf){
	cgc_transmit_all(STDOUT, buf, cgc_strlen(buf) );
	cgc_transmit_all(STDOUT, "\n", 1);
}

int cgc_transmit_compound_list(unsigned int from, unsigned int to){
	if( to <= from || from > N_FORMULAS-1 || to > N_FORMULAS-1)
		return TXFAIL;

	for(int i = from; i < to; i++){
		cgc_transmit_line_nl(chem_formulas[i].compound_name);
	}

	return CMDOKAY;

}


zoom_filter_t * cgc_make_compound_sample_zoom(compounds_sample_t *s){
	zoom_filter_t *zf = cgc_new_zoom_filter(cgc_n_elements_from_sampsz(s->sample_size));
	if(zf == NULL){
		char * m = "failed new zdf";
		cgc_transmit_all(STDOUT, m, cgc_strlen(m));
		return NULL;
	}


	for(int i =0; i < s->sample_size; ++i){
		int sample_idx = cgc_get_chem_ref_at_idx(s, i);
		if(sample_idx > N_FORMULAS-1 ){
			// todo free zf
			char * m = "failed new zdf2";
			cgc_transmit_all(STDOUT, m, cgc_strlen(m));
			cgc_zoom_free(zf);
			return NULL;
		}

		char * cn = chem_formulas[sample_idx].compound_name;
		hash_pair_t *hp = cgc_hash_pair_buf(cn, cgc_strlen(cn) );
		cgc_zoom_add(hp, zf);
		
		// todo check number transmitted


	}
	return zf;
}

void cgc_free_zoombuf(char *zb){
	cgc_free(zb);
}

char * cgc_zoom_buf(compounds_sample_t *s){
	zoom_filter_t *zf = cgc_make_compound_sample_zoom(s);
	if(zf == NULL)

		return NULL;


	char * tx_buf = cgc_encode((char *) zf->data, zf->data_len);
	cgc_zoom_free(zf);
	return tx_buf;
}

int cgc_transmit_compound_sample_zoom(compounds_sample_t *s){


	// encode bloom and mark
	char *tx_buf = cgc_zoom_buf(s);

	if(tx_buf == NULL)
		return -1;
	cgc_transmit_line_nl(tx_buf);

	cgc_free(tx_buf);
	return 0;

}

int cgc_check_compound_idx_in_zoom(zoom_filter_t *zf, int compound_idx){
	char * cn = chem_formulas[compound_idx].compound_name;
	int sl = cgc_strlen(cn);
	hash_pair_t * hp = cgc_hash_pair_buf(cn, sl);
	int zc = cgc_zoom_check(hp, zf);
	cgc_free(hp);
	return zc;
}






void cgc_free_sample_st(compounds_sample_t *p){
	cgc_free(p->sample);
	cgc_free(p);
}

compounds_sample_t *cgc_sample_compounds(const char *seed, const cgc_size_t sample_size){
	if(sample_size > N_FORMULAS-1)
		return NULL;
	unsigned int h = cgc_crazy_hash(seed, cgc_strlen(seed), 0xcafeb4b4);

	compounds_sample_t *sample = cgc_alloc_sample_st(sample_size);
	// todo check alloc
	if(sample == NULL)
		return NULL;
	for(int i =0; i < sample_size; ++i){
		cgc_set_sample_at_idx(sample, i,  (h % (N_FORMULAS-1)));
		
		h = cgc_crazy_hash((const char *) &h, sizeof(h), h);
	}

	return sample;
}

// want to process command of form LIST RND NUM
// int process_list_command(char **args){

// 	transmit_compound_list()
// }