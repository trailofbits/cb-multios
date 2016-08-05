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
#include <stdint.h>
#include <errno.h>

#include "malloc.h"
#include "list.h"
#include "hash_table.h"
#include "streq.h"
#include "strlen.h"
#include "memcpy.h"
 
#define HT_MAX_FILL_PERCENTAGE 0.80		// if (pair_cnt / bucket_cnt) > this, should do re-hash

#define HASH_PRIME_SIZE 32

#ifndef FLAG_PAGE
#define FLAG_PAGE 0x4347C000
#endif

static const unsigned int ht_prime_list[HASH_PRIME_SIZE] = 
{
	2ul,			3ul,			11ul,			23ul,			53ul,
	97ul,			193ul,			389ul,			769ul,			1543ul,
	3079ul,			6151ul,			12289ul,		24593ul,		49157ul,
	98317ul,		196613ul,		393241ul,		786433ul,		1572869ul,
	3145739ul,		6291469ul,		12582917ul,		25165843ul,		50331653ul,
	100663319ul,	201326611ul,	402653189ul,	805306457ul,	1610612741ul,
	3221225473ul,	4294967291ul
};


/**
 * Get the first prime larger than size.
 *
 * If size > the last 32 bit prime, return the last 32 bit prime.
 *
 * @param size 	Number to compare with primes
 * @return 		First prime larger than size.
 */
static unsigned int get_next_largest_prime(unsigned int size) {
	for (int i = 0; i < 32; i++) {
		if (size < ht_prime_list[i]) {
			return ht_prime_list[i];
		}
	}

	return ht_prime_list[31];
}

/**
 * Hash function for 32 bit int keys
 *
 * @param key 		VA of 32 bit key
 * @param modulus 	Modulus to keep hash value in range
 * @return 			hash of key
 */
static unsigned int ht_int_hash(void *key, unsigned int modulus) {
	unsigned int k = *(unsigned int *)key;
	return k % modulus;
}

/**
 * Hash function for 32 bit int keys that uses bytes from the FLAG PAGE
 *	in the hash computation.
 *
 * @param key 		VA of 32 bit key
 * @param modulus 	Modulus to keep hash value in range
 * @return 			hash of key
 */
static unsigned int ht_int_hash_fp(void *key, unsigned int modulus) {
	unsigned int k = *(unsigned int *)key;
	unsigned int flag = *(unsigned int *)FLAG_PAGE;
	return (k ^ flag) % modulus;
}

/**
 * Hash function for variable length, null terminated, string keys
 *
 * @param key 		Pointer to string
 * @param modulus 	Modulus to keep hash value in range
 * @return 			hash of key
 */
static unsigned int ht_str_hash(void *key, unsigned int modulus) {
	char *k = (char *)key;
	unsigned int hash = 0ul;
	unsigned int multiplier = 31;

	while (*k) {
		hash = (hash + *k) * multiplier;
		k++;
	}
	return hash % modulus;
}

/**
 * Hash function for variable length, null terminated, string keys
 *	that uses bytes from the FLAG PAGE in the hash computation.
 *
 * @param key 		Pointer to string
 * @param modulus 	Modulus to keep hash value in range
 * @return 			hash of key
 */
static unsigned int ht_str_hash_fp(void *key, unsigned int modulus) {
	char *k = (char *)key;
	unsigned int hash = 0ul;
	unsigned int multiplier = 31;
	unsigned int flag = *(unsigned int *)FLAG_PAGE;

	while (*k) {
		hash = (hash + *k) * multiplier;
		k++;
	}
	return (hash ^ flag) % modulus;
}

/**
 * Key pointer resolution function for pair with 32 bit int keys
 *
 * @param pair 	pointer to (k, v) pair
 * @return 		pointer to 32 bit key
 */
static void *ht_int_key_ptr(void *pair) {
	return pair;
}

/**
 * Key pointer resolution function for pair with 
 * 	variable length, null terminated, string keys
 *
 * @param pair 	pointer to (k, v) pair
 * @return 		pointer to string key
 */
static void *ht_str_key_ptr(void *pair) {
	return (void *)*(char **)pair;
}

/**
 * Value pointer resolution function for pair with 32 bit int keys
 *
 * @param h 	pointer to hash table
 * @param pair 	pointer to (k, v) pair
 * @return 		pointer to value
 */
static void *ht_int_value_ptr(ht_t *h, void *pair) {
	return pair + sizeof(unsigned int);
}

/**
 * Value pointer resolution function for pair with
 * 	variable length, null terminated, string keys
 *
 * @param h 	pointer to hash table
 * @param pair 	pointer to (k, v) pair
 * @return 		pointer to value
 */
static void *ht_str_value_ptr(ht_t *h, void *pair) {
	return pair + sizeof(unsigned int *);
}

/**
 * Function to test if a pair contains the given 32 bit int key
 *
 * @param k1 	pointer to (k, v) pair with 32 bit key
 * @param k2 	pointer to 32 bit key
 * @return 		0 if pair->key != key, 1 if pair->key == key
 */
static unsigned char ht_int_key_in_pair(const void *pair, void *key) {
	return *(unsigned int *)pair == *(unsigned int *)key;
}

/**
 * Function to test if a pair contains the given variable length, null terminated, string key
 *
 * @param k1 	pointer to (k, v) pair with var len, null terminated, string key
 * @param k2 	pointer to 'key' that is var len, null terminated, string
 * @return 		0 if pair->key != key, 1 if pair->key == key
 */
static unsigned char ht_str_key_in_pair(const void *pair, void *key) {
	if (0 == streq((const char *)ht_str_key_ptr((void *)pair), (const char *)key, '\0')) {
		return 1;
	}
	return 0;
}

/**
 * Function to initialize base parts of a hash table
 *
 * @param size 	Size for hash table
 * @return 		Pointer to new hash table
 */
static ht_t *ht_init(unsigned int size) {
	ht_t *h = malloc(sizeof(ht_t));
	if (NULL == h) _terminate(ERRNO_ALLOC);

	h->buckets_cnt = get_next_largest_prime(size);
	h->size = size;
	h->pair_cnt = 0;
	h->iter_idx = 0;
	h->iter_node = NULL;
	h->buckets = malloc(h->buckets_cnt * sizeof(struct list *));

	if (NULL == h->buckets) _terminate(ERRNO_ALLOC);

	return h;
}

ht_t *ht_int_init(unsigned int size) {
	ht_t *h = ht_init(size);

	h->fn_hash = &ht_int_hash;
	h->fn_key_in_pair = &ht_int_key_in_pair;
	h->fn_key_ptr = &ht_int_key_ptr;
	h->fn_value_ptr = &ht_int_value_ptr;

	return h;
}

ht_t *ht_int_init_fp(unsigned int size) {
	ht_t *h = ht_int_init(size);
	h->fn_hash = &ht_int_hash_fp;

	return h;
}


ht_t *ht_str_init(unsigned int size) {
	ht_t *h = ht_init(size);

	h->fn_hash = &ht_str_hash;
	h->fn_key_in_pair = &ht_str_key_in_pair;
	h->fn_key_ptr = &ht_str_key_ptr;
	h->fn_value_ptr = &ht_str_value_ptr;

	return h;
}

ht_t *ht_str_init_fp(unsigned int size) {
	ht_t *h = ht_str_init(size);
	h->fn_hash = &ht_str_hash_fp;

	return h;
}

void ht_destroy(ht_t *h) {
	free(h->buckets);
	free(h);
}

unsigned int ht_length(ht_t *h) {
	return h->pair_cnt;
}

void *ht_pair_insert(ht_t *h, void *pair) {

	unsigned int hash_val = h->fn_hash(h->fn_key_ptr(pair), h->buckets_cnt);

	if (NULL == h->buckets[hash_val]) {
		// create empty list for this bucket
		struct list *l = malloc(sizeof(struct list));
		if (NULL == l) _terminate(ERRNO_ALLOC);

		list_init(l, NULL);
		h->buckets[hash_val] = l;
	}

	// determine if a pair with this key is already in this list
	struct node *n = list_find_node_with_data(h->buckets[hash_val], h->fn_key_in_pair, h->fn_key_ptr(pair));

	if (NULL != n) { // pair with this key exists, so remove it
		list_remove_node(h->buckets[hash_val], n);
		h->pair_cnt--;
	}

	// add new pair to list
	list_insert_at_end(h->buckets[hash_val], pair);
	h->pair_cnt++;

	// while it might be convenient to check/do re_hash here, I've decided to
	// omit that and force the user manually check/do re_hash as they desire.

	if (NULL == n) return NULL;

	return n->data;
}

void *ht_pair_get(ht_t *h, void *key) {

	unsigned int hash_val = h->fn_hash(key, h->buckets_cnt);

	// doesn't exist
	if (NULL == h->buckets[hash_val]) return NULL;

	// determine if a pair with this key is already in this list
	struct node *n = list_find_node_with_data(h->buckets[hash_val], h->fn_key_in_pair, key);

	// doesn't exist
	if (NULL == n) return NULL;

	// does exist
	return n->data;
}

void *ht_pair_remove(ht_t *h, void *pair) {

	unsigned int hash_val = h->fn_hash(h->fn_key_ptr(pair), h->buckets_cnt);

	// doesn't exist
	if (NULL == h->buckets[hash_val]) return NULL;

	// determine if a pair with this key is in this list
	struct node *n = list_find_node_with_data(h->buckets[hash_val], h->fn_key_in_pair, h->fn_key_ptr(pair));

	// doesn't exist
	if (NULL == n) return NULL;

	// pair does exist, so get it
	void *d = n->data;

	// clean up node
	list_remove_node(h->buckets[hash_val], n);
	list_destroy_node(h->buckets[hash_val], &n);
	h->pair_cnt--;

	// if this list is empty, destroy it
	if (0 == list_length(h->buckets[hash_val])) {
		list_destroy(h->buckets[hash_val]);
		free(h->buckets[hash_val]);
		h->buckets[hash_val] = NULL;
	}

	return d;
}

void *ht_value(ht_t *h, void *key) {

	// get pair with this key
	void *pair = ht_pair_get(h, key);

	// doesn't exist
	if (NULL == pair) return NULL;

	// does exist, so get ptr to value
	return h->fn_value_ptr(h, pair);
}

void *ht_value_as_voidp(ht_t *h, void *key) {
	void *v = ht_value(h, key);
	if (NULL == v) return NULL;
	return (void *)*(int *)v;
}

unsigned int ht_value_as_uint(ht_t *h, void *key) {
	return *(unsigned int *)ht_value(h, key);
}

int ht_value_as_int(ht_t *h, void *key) {
	return *(int *)ht_value(h, key);
}

void *ht_pair_iter_start(ht_t *h) {
	// reset iter state
	h->iter_idx = 0;
	h->iter_node = NULL;
	void *pair = NULL;

	if (0 == h->pair_cnt) return NULL;

	// find first bucket with a pair
	for (unsigned int i = 0; i < h->buckets_cnt; i++) {
		if ((NULL != h->buckets[i]) && (0 != list_length(h->buckets[i]))) {
			h->iter_idx = i;
			h->iter_node = list_head_node(h->buckets[i]);
			return (h->iter_node)->data;
		}
	}

	return NULL;
}

void *ht_pair_iter_next(ht_t *h) {

	void *pair = NULL;
	struct node *n = NULL;

	if (0 == h->pair_cnt) return NULL;

	// check list in current bucket to see if there is another node
	h->iter_node = list_next_node(h->iter_node);
	n = list_end_marker(h->buckets[h->iter_idx]);
	if (n != h->iter_node) {
		return (h->iter_node)->data;
	}

	// if not, start at next iter_idx and move ahead to find the next bucket in use.
	for (unsigned int i = h->iter_idx + 1; i < h->buckets_cnt; i++) {
		if ((NULL != h->buckets[i]) && (0 != list_length(h->buckets[i]))) {
			h->iter_idx = i;
			h->iter_node = list_head_node(h->buckets[i]);
			return (h->iter_node)->data;
		}
	}

	return NULL;
}

unsigned int ht_is_re_hash_needed(ht_t *h) {
	return HT_MAX_FILL_PERCENTAGE < ( (double)h->pair_cnt / (double)h->buckets_cnt );
}

ht_t *ht_re_hash(ht_t *h) {

	ht_t *h_new = NULL;
	ht_t *h_old = h;
	void *pair = NULL;
	unsigned int new_size = 2 * h_old->pair_cnt;

	// if overflow size, use max_uint
	if (h_old->size > new_size) {
		new_size = 0xFFFFFFFF;
	}

	// create new ht
	h_new = ht_init(new_size);
	h_new->fn_hash 			= h_old->fn_hash;
	h_new->fn_key_in_pair 	= h_old->fn_key_in_pair;
	h_new->fn_key_ptr		= h_old->fn_key_ptr;
	h_new->fn_value_ptr		= h_old->fn_value_ptr;

	// move all pairs from h_old to h_new
	// cannot use ht_pair_iter_next since we are changing h_old as we go.
	while (NULL != (pair = ht_pair_iter_start(h_old))) {
		if (NULL == (pair = ht_pair_remove(h_old, pair))) _terminate(ERRNO_HASH);
		ht_pair_insert(h_new, pair);
	}

	ht_destroy(h);

	return h_new;
}


uint_uint_pair_t *get_ui_ui_pair(unsigned int k, unsigned int v) {
	uint_uint_pair_t *pair = malloc(sizeof(uint_uint_pair_t));
	if (NULL == pair) _terminate(ERRNO_ALLOC);

	pair->key = k;
	pair->value = v;

	return pair;
}

int_int_pair_t *get_i_i_pair(int k, int v) {
	int_int_pair_t *pair = malloc(sizeof(int_int_pair_t));
	if (NULL == pair) _terminate(ERRNO_ALLOC);

	pair->key = k;
	pair->value = v;

	return pair;
}

str_uint_pair_t *get_s_ui_pair(char *s, unsigned int i) {
	if (NULL == s) return NULL;

	str_uint_pair_t *pair = malloc(sizeof(str_uint_pair_t));
	if (NULL == pair) _terminate(ERRNO_ALLOC);

	unsigned int len = strlen(s, '\0') + 1;
	pair->key = malloc(len * sizeof(char));
	if (NULL == pair->key) _terminate(ERRNO_ALLOC);

	memcpy(pair->key, s, len);

	pair->value = i;

	return pair;
}

str_int_pair_t *get_s_i_pair(char *s, int i) {
	if (NULL == s) return NULL;

	str_int_pair_t *pair = malloc(sizeof(str_int_pair_t));
	if (NULL == pair) _terminate(ERRNO_ALLOC);

	unsigned int len = strlen(s, '\0') + 1;
	pair->key = malloc(len * sizeof(char));
	if (NULL == pair->key) _terminate(ERRNO_ALLOC);

	memcpy(pair->key, s, len);

	pair->value = i;

	return pair;
}

