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

#ifndef HASH_TABLE_H
#define HASH_TABLE_H 1

#include "cgc_list.h"

/***** Important *****

These functions are designed under the following assumptions:

1. The hash table struct is initialize with functions that are directly associated 
	with the type of the 'key'. (uint/int key -> ht_int_init, str key -> ht_str_init)
2. The type of the 'key' must be a 32bit int/uint or a pointer to a string.
	Mixing 'key' int and uint types in one hash table is not advised.
3. The type of the 'value' is only important for the ht_value_as_XYZ functions.
4. The (key, value) pair is a struct where the 'key' comes immediately before the 'value'.
	i.e.:
	struct {
		type1 key;
		type2 value;
	};
	Some exmaple struct types are defined below.
5. The hash table stores pointers to structs. (void *)
6. There are no pairs with duplicate 'key's in the hash table (prev will be replaced by new)

*/

// forward declarations
struct ht;
typedef struct ht ht_t;

/**
 * Function to test if a pair contains the given key
 *
 * @param first 	Pointer to (k, v) pair
 * @param second	Pointer to key
 * @return 			1 if equal, 0 if not
 */
typedef unsigned char (*f_key_in_pair)(const void *, void *);

/**
 * Function type used to compute the hash from the key
 *
 * @param first 	Pointer to key
 * @param second 	Modulus to bound the hash
 * @return 			Hash value
 */
typedef unsigned int (*f_hash)(void *, unsigned int);

/**
 * Function type used to resolve the key pointer in a pair
 *
 * @param second 	pointer to (k, v) pair
 * @return 			pointer to key
 */
typedef void *(*f_key_ptr)(void *);

/**
 * Function type used to resolve the value pointer in a pair
 *
 * @param first 	pointer to hash table
 * @param second 	pointer to (k, v) pair
 * @return 			pointer to value
 */
typedef void *(*f_value_ptr)(ht_t *, void *);

struct ht {
	unsigned int buckets_cnt;	// number of buckets (next prime > size)
	unsigned int size;			// number of buckets requested by user
	unsigned int pair_cnt;		// number of pairs stored in ht
	unsigned int iter_idx;		// index in buckets where iterator is
	struct node  *iter_node;	// node in list where iterator is 
	struct list **buckets;		// array with values of: default NULL, else pointer to struct list
	f_hash fn_hash;
	f_key_in_pair fn_key_in_pair;
	f_key_ptr fn_key_ptr;
	f_value_ptr fn_value_ptr;
};

/**
 * Example pair struct for unsigned int key and values
 */
typedef struct uint_uint_pair {
	unsigned int key;
	unsigned int value;
} uint_uint_pair_t;

/**
 * Example pair struct for signed int key and value
 */
typedef struct int_int_pair {
	int key;
	int value;
} int_int_pair_t;

/**
 * Example pair struct for string key and value
 */
typedef struct str_str_pair {
	char *key;
	char *value;
} str_str_pair_t;

/**
 * Example pair struct for string key and int value
 */
typedef struct str_int_pair {
	char *key;
	int value;
} str_int_pair_t;

/**
 * Example pair struct for string key and int value
 */
typedef struct str_uint_pair {
	char *key;
	unsigned int value;
} str_uint_pair_t;

/**
 * Example pair struct for int key and string value
 */
typedef struct int_str_pair {
	int key;
	char *value;
} int_str_pair_t;

/**
 * Example pair struct for unsigned int key and string value
 */
typedef struct uint_str_pair {
	unsigned int key;
	char *value;
} uint_str_pair_t;

/**
 * Example pair struct for unsigned int key and void * value
 */
typedef struct uint_voidp_pair {
	unsigned int key;
	void *value;
} uint_voidp_pair_t;

/**
 * Example pair struct for signed int key and void * value
 */
typedef struct int_voidp_pair {
	int key;
	void *value;
} int_voidp_pair_t;

/**
 * Example pair struct for char * key and void * value
 */
typedef struct str_voidp_pair {
	char *key;
	void *value;
} str_voidp_pair_t;

/**
 * Hash table with 32 bit keys (signed or unsigned int)
 *
 * @param size 	Requested number of buckets
 * @return VA of hash table struct
 */
ht_t *cgc_ht_int_init(unsigned int size);

/**
 * Hash table with 32 bit keys (signed or unsigned int)
 *	that uses the FLAG_PAGE in the hash computation.
 *
 * @param size 	Requested number of buckets
 * @return VA of hash table struct
 */
ht_t *cgc_ht_int_init_fp(unsigned int size);

/**
 * Hash table with variable length, null terminated, string keys
 *
 * @param size 	Requested number of buckets
 * @return VA of hash table struct
 */
ht_t *cgc_ht_str_init(unsigned int size);

/**
 * Hash table with variable length, null terminated, string keys
 *	that uses the FLAG_PAGE in the hash computation.
 *
 * @param size 	Requested number of buckets
 * @return VA of hash table struct
 */
ht_t *cgc_ht_str_init_fp(unsigned int size);

/**
 * Delete the hash table. Assumes hash table is empty.
 *
 * NOTE: This only deletes the hash table structure.
 * You MUST empty the hash table and free the pairs (ht_pair_remove + free)
 * yourself before destroying the hash table, else this is a huge memory leak.
 *
 * @param h 	Pointer to the hash table
 */
void cgc_ht_destroy(ht_t *h);

/**
 * Get the number of (k, v) pairs stored in the hash table
 *
 * @param h 	Pointer to the hash table
 * @return 		Number of pairs
 */
unsigned int cgc_ht_length(ht_t *h);

/**
 * Insert a (k,v) pair into the hash table
 *
 * @param h 	Pointer to the hash table
 * @param pair 	VA of struct holding key and value
 * @return 		NULL if no pre-existing pair with this key, else 
 *				VA of pre-existing pair that was removed and 
 *				replaced by this new pair
 */
void *cgc_ht_pair_insert(ht_t *h, void *pair);

/**
 * Get VA of (k, v) pair from hash table using key
 *
 * @param h 	Pointer to the hash table
 * @param key 	Pointer to key
 * @return 		VA of pair or NULL if not found
 */
void *cgc_ht_pair_get(ht_t *h, void *key);

/**
 * Remove (k, v) pair from hash table using key
 *
 * @param h 	Pointer to the hash table
 * @param pair 	VA of struct holding key and value
 * @return 		VA of pair or NULL if not found
 */
void *cgc_ht_pair_remove(ht_t *h, void *pair);

/**
 * Get VA of value from (k, v) pair from hash table using key
 *
 * @param h 	Pointer to the hash table
 * @param key 	Pointer to key
 * @return 		Pointer to value or NULL if no pair has this key
 */
void *cgc_ht_value(ht_t *h, void *key);

/**
 * Get void * value from (k, v) pair from hash table using key
 *
 * @param h 	Pointer to the hash table
 * @param key 	Pointer to key
 * @return 		Value as void *
 */
void *cgc_ht_value_as_voidp(ht_t *h, void *key);

/**
 * Get unsigned int value from (k, v) pair from hash table using key
 *
 * @param h 	Pointer to the hash table
 * @param key 	Pointer to key
 * @return 		uint value (will segfault if key is not found in hash table)
 */
unsigned int cgc_ht_value_as_uint(ht_t *h, void *key);

/**
 * Get signed int value from (k, v) pair from hash table using key
 *
 * @param h 	Pointer to the hash table
 * @param key 	Pointer to key
 * @return 		int value (will segfault if key is not found in hash table)
 */
int cgc_ht_value_as_int(ht_t *h, void *key);

/**
 * Get first pair from buckets iterator (also resets iterator)
 *
 * @param h 	Pointer to the hash table
 * @return 		VA of pair or NULL if none found.
 */
void *cgc_ht_pair_iter_start(ht_t *h);

/**
 * Get next pair from buckets iterator
 *
 * @param h 	Pointer to the hash table
 * @return 		VA of pair or NULL if none found.
 */
void *cgc_ht_pair_iter_next(ht_t *h);

/**
 * Determine if this hash table needs to be re-hashed to more evenly spread out the pairs
 *
 * @param h 	Pointer to hash table
 * @return		1 if needs re-hash, 0 if not
 */
unsigned int cgc_ht_is_re_hash_needed(ht_t *h);

/**
 * Re-hash the hash table.
 *
 * @param h 	Pointer to pointer to the hash table
 * @return 		Pointer to the new hash table.
 */
ht_t *cgc_ht_re_hash(ht_t *h);

/**
 * Create and return a new pair with the given uint key and uint value.
 *
 * @param k 	uint key
 * @param v 	uint value
 * @return		VA of new uint_uint_pair
 */
uint_uint_pair_t *cgc_get_ui_ui_pair(unsigned int k, unsigned int v);

/**
 * Create and return a new pair with the given int key and int value.
 *
 * @param k 	int key
 * @param v 	int value
 * @return		VA of new int_int_pair
 */
int_int_pair_t *cgc_get_i_i_pair(int k, int v);

/**
 * Create and return a new pair with the given char * key and uint value.
 *
 * @param k 	char * key ('\0' terminated key is copied into new pair)
 * @param v 	uint value
 * @return		VA of new str_uint_pair
 */
str_uint_pair_t *cgc_get_s_ui_pair(char *s, unsigned int i);

/**
 * Create and return a new pair with the given char * key and int value.
 *
 * @param k 	char * key ('\0' terminated key is copied into new pair)
 * @param v 	int value
 * @return		VA of new str_int_pair
 */
str_int_pair_t *cgc_get_s_i_pair(char *s, int i);


#endif

