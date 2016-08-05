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

#ifndef CITIZEN_H
#define CITIZEN_H 1

#include "list.h"
#include "hash_table.h"

#define TERM '\x00'
#define DELIM '\n'
#define NAME_FIELD_SZ 1024
#define MAX_SIZE 980

typedef enum {
	E_MGR 	= 1,
	VOTER 	= 2,
	NO_AUTH = 4,
} auth_t;

typedef enum {
	INIT 	= 1,
    NEW 	= 2,
    OPEN 	= 4,
    CLOSED 	= 8,
} e_states;

struct e_conf {
	void 		  *authd_user;		// pointer to currently logged in/authorized user
	unsigned int  e_mgr_id; 		// ID of election manager
	unsigned int  next_voter_id;	// ID to assign to next new voter
	unsigned int  next_candidate_id;// ID to assing to next new candidate
	unsigned char num_winners;		// number of winners desired
	unsigned char max_candidates;	// max number of candidates
	unsigned char write_in_ok;		// allow write-in candidates?
	unsigned char bogus;			// pad to 4 bytes, maybe use later?
};
typedef struct {
    unsigned int id;
    char f_name[NAME_FIELD_SZ];
    char l_name[NAME_FIELD_SZ];
} person_t;

typedef struct {
	person_t person;
    unsigned char (*validate)(void *);
    unsigned int auth_key;
} e_mgr_t;

typedef struct {
	person_t person;
    unsigned char (*validate)(void *);
    unsigned int vote_id;
} voter_t;

typedef struct {
	person_t person;
    unsigned char (*validate)(void *);
} candidate_t;

typedef struct {
    unsigned int id;
    voter_t v;  		// include full voter and candidate to create perm record
    candidate_t c;
    unsigned char (*validate)(void *);
} vote_t;

typedef struct {
    e_states state;
    char e_name[NAME_FIELD_SZ];
    struct list *candidates;
    ht_t *voters;
    ht_t *votes;
    struct e_conf conf;
    e_mgr_t *manager;
} election_t;

/**
 * Print menu
 *
 * @param cred 	Authentication credential ID
 */
void print_menu(auth_t cred);

/**
 * Process choice for main menu and dispatch as necessary.
 *
 * @param cmd_id 	ID Number of choice
 * @return 			SUCCESS on success, int < 0 on failure.
 */
int decider(unsigned char);

/**
 * Initialize the election struct.
 */
void init_election(void);

/**
 * Get users menu choice.
 *
 * @param choice 	pointer to uint which will store value chosen by user
 * @return number of bytes stored into choice if success, ERRNO_CONV on failure.
 */
int get_choice(unsigned int * choice);

#endif