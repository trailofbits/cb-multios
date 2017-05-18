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

#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_election.h"

#define E_MGR_ID		10101010
#define FIRST_VOTER_ID	12341234
#define FIRST_CANDIDATE_ID 1

#define ELECTION_NAME 	"Enter election name: "
#define ELECTION_CREATED "Election Created.\n"
#define ELECTION_OPEN	"Voting Open.\n"
#define ELECTION_CLOSED "Voting Closed.\n"
#define CREATE_E_MGR 	"## Create election manager ##\n"
#define CREATE_VOTER 	"## Create voter ##\n"
#define CREATE_CANDIDATE "## Create candidate ##\n"
#define CANDIDATE_ADDED "Candidate Added.\n"
#define CANDIDATE_INVALID "New candidate invalid\n"

#define ZERO_CANDIDATES	"\tThere were zero candidates.\n"
#define CANDIDATE_ORDER "\t| Rank | Votes | Candidate Name |\n"
#define ZERO_VOTERS 	"\tThere were zero voters.\n"
#define VOTER_ORDER 	"\t| Voted? | Voter Name |\n"

#define VOTING_RESULTS 	"## Voting Results ##\n"
#define CANDIDATE_SUMMARY "## Candidate Summary ##\n"
#define VOTER_TURNOUT 	"## Voter Turnout ##\n"

#define SELECT_CANDIDATE "Select one candidate from the folloowing:\n"
#define EMPTY_CANDIDATES "There are no candidates. Go add some.\n"
#define FULL_CANDIDATES  "Not accepting additional candidates.\n"
#define INVALID_CANDIDATE "Invalid candidate. Try again.\n"

#define F_NAME 			"\tEnter first name: "
#define L_NAME 			"\tEnter last name: "

#define ENTER_ID 		"\tEnter your ID number: "
#define ENTER_AUTH_KEY	"\tEnter auth key: "
#define NEW_AUTH_KEY	"\tYour auth key is: "
#define NEW_UID			"\tYour ID number is: "

#define NUM_WINNERS_Q	"Enter number of election winners desired: "
#define MAX_CANDIDATES_Q "Enter the max number of candidates allowed: "
#define WRITE_IN_OK_Q 	"Can voters write-in new candidates? (Yy/Nn): "

#define CHOOSE 			"Choose an option: "

#define MENU_LOGIN 				"14: Login\n"
#define MENU_MAIN 				"15: Main Menu\n"
#define MENU_CREATE_ELECTION 	"17: Create Election\n"
#define MENU_OPEN_VOTING			"18. Open Voting\n"
#define MENU_CLOSE_VOTING		"20. Close Voting\n"
#define MENU_ELECTION_STATUS 	"22. Election Status\n"

#define MENU_REGISTER_VOTER		"38. Register Voter\n"
#define MENU_VOTE 				"36. Vote\n"
#define MENU_ADD_CANDIDATE  		"54. Add Candidate\n"
#define MENU_VOTING_RESULTS		"56. Voting Results\n"
#define MENU_VOTER_TURNOUT		"72. Voter Turnout\n"
#define MENU_CANDIDATE_SUMMARY 	"88. Candidate Summary\n"

#define MENU_QUIT				"95. Quit\n"


// typedef enum {
//	   INIT = 1,
//     NEW = 2,
//     OPEN = 4,
//     CLOSED = 8,
// } e_states;

// second byte encodes the state for when it is a valid operation
enum {
	C_MENU_LOGIN 				= 0x0E,
	C_MENU_MAIN					= 0x0F,

	C_MENU_CREATE_ELECTION 		= 0x11,
	C_MENU_OPEN_VOTING			= 0x12,
	C_MENU_CLOSE_VOTING			= 0x14,
	C_MENU_ELECTION_STATUS		= 0x16,

	C_MENU_VOTE 				= 0x24,
	C_MENU_REGISTER_VOTER		= 0x26,

	C_MENU_ADD_CANDIDATE		= 0x36,

	C_MENU_VOTING_RESULTS		= 0x38,
	C_MENU_VOTER_TURNOUT		= 0x48,
	C_MENU_CANDIDATE_SUMMARY	= 0x58,

	C_MENU_QUIT 				= 0x5F,
};

election_t e;


/**
 * Print login entry into menu.
 *
 *  Login when election is in any state except INIT, and no user is auth'd
 *  Goto Main Menu when election is in any state except INIT, and user is auth'd
 *
 * @param s 	Election state
 * @param cred 	Auth credential id
 */
static void cgc_print_login_menu(e_states s, auth_t cred) {

	if ((INIT != s) && 
		(NO_AUTH == cred)) {
		SEND(STDOUT, MENU_LOGIN, sizeof(MENU_LOGIN));
	}
	if ((INIT != s) && 
		(NO_AUTH != cred)) {
		SEND(STDOUT, MENU_MAIN, sizeof(MENU_MAIN));
	}
}

/**
 * Print parts of admin menu
 *
 *  Create election when election is in the INIT state
 *  Open voting when election is in the NEW state.
 *  Close voting when election is in the OPEN state.
 *
 * @param s 	Election state
 * @param cred 	Auth credential id
 */
static void cgc_print_admin_menu(e_states s, auth_t cred) {
	if ((INIT == s) && 
		(NO_AUTH == cred)) {
		SEND(STDOUT, MENU_CREATE_ELECTION, sizeof(MENU_CREATE_ELECTION));
	}

	if ((NEW == s) && 
		(E_MGR == cred)) {

		SEND(STDOUT, MENU_OPEN_VOTING, sizeof(MENU_OPEN_VOTING));
	}

	if ((OPEN == s) && 
		(E_MGR == cred)) {
		SEND(STDOUT, MENU_CLOSE_VOTING, sizeof(MENU_CLOSE_VOTING));
	}

	if (((OPEN == s) || (NEW == s)) &&
	 	(E_MGR == cred)) {
			SEND(STDOUT, MENU_ELECTION_STATUS, sizeof(MENU_ELECTION_STATUS));
	}
}

/**
 * Print parts of the voting menu
 *
 * Register voter when election is in the NEW or OPEN state
 * Vote when election is in the OPEN state
 *
 * @param s 	Election state
 * @param cred 	Auth credential id
 */
static void cgc_print_voting_menu(e_states s, auth_t cred) {

	if ((OPEN == s) && 
		(VOTER == cred)) {
		SEND(STDOUT, MENU_VOTE, sizeof(MENU_VOTE));
	}

	if (((NEW == s) || (OPEN == s)) && 
		(NO_AUTH == cred)) {
		SEND(STDOUT, MENU_REGISTER_VOTER, sizeof(MENU_REGISTER_VOTER));
	}

	if ((OPEN == s) || (NEW == s)) {
		if ((E_MGR == cred) || 
			((VOTER == cred) && (1 == e.conf.write_in_ok))) {
			if (cgc_list_length(e.candidates) < e.conf.max_candidates) {
				SEND(STDOUT, MENU_ADD_CANDIDATE, sizeof(MENU_ADD_CANDIDATE));
			}
		}
	}
}

/**
 * Print parts of the results menu
 *
 * Results when an election exists in the CLOSED state.
 *	- Get voting results
 *	- Voter turnout
 *	- Candidate summary
 *
 * @param s 	Election state
 * @param cred 	Auth credential id
 */
static void cgc_print_results_menu(e_states s, auth_t cred) {

	if (CLOSED == s) {
		if ((E_MGR == cred) || (VOTER == cred)) {
			SEND(STDOUT, MENU_VOTING_RESULTS, sizeof(MENU_VOTING_RESULTS));
		}
		if (E_MGR == cred) {
			SEND(STDOUT, MENU_VOTER_TURNOUT, sizeof(MENU_VOTER_TURNOUT));
			SEND(STDOUT, MENU_CANDIDATE_SUMMARY, sizeof(MENU_CANDIDATE_SUMMARY));
		}
	}
}

/**
 * Receive letter from user
 *
 * @param l 	Pointer to char
 */
static void cgc_receive_letter(char *l) {
    char buf[2];

    RECV_DELIM(STDIN, DELIM, buf, 2);
    *l = buf[0];
}

/**
 * Receive number between 0 and MAX_UINT from user
 *
 * @param n 	Pointer to uint to store number
 * @return number of bytes stored in n, or ERRNO_CONV on error
 */
static int cgc_receive_number(unsigned int *n) {
    char buf[15];

    RECV_DELIM(STDIN, DELIM, buf, 15);
    *n = 0;
    return cgc_strtou(buf, 10, n);
}

/**
 * Prompt for and store the first and last name of the person.
 */
static void cgc_set_first_last_name(person_t *person) {

	// TODO: ensure only valid chars are entered for the name ;)
	SEND(STDOUT, F_NAME, sizeof(F_NAME));
    RECV_DELIM_TRIM(STDIN, DELIM, person->f_name, sizeof(person->f_name));

	SEND(STDOUT, L_NAME, sizeof(L_NAME));
    RECV_DELIM_TRIM(STDIN, DELIM, person->l_name, sizeof(person->l_name));
}

/**
 * Function to validate the content of a vote struct
 *
 * Validation Checks:
 * - ??
 *
 * @param v 	A vote
 * @return 	TRUE if pass validation, else FALSE
 */
static unsigned char cgc_validate_vote(void *v) {

	vote_t *cgc_vote = (vote_t *)v;

	return TRUE;
}

/**
 * Function to validate the content of a voter struct
 *
 * Validation Checks:
 * - Does the first and last name contain at least 1 letter? If not, fail.
 *
 *
 * @param v 	A voter
 * @return 	TRUE if pass validation, else FALSE
 */
static unsigned char cgc_validate_voter(void *v) {

	voter_t *voter = (voter_t *)v;

	// check: first and last name have at least 1 letter; reject empty names
	if ((0 == cgc_strlen(voter->person.f_name, TERM)) ||
		(0 == cgc_strlen(voter->person.l_name, TERM))) {
		return FALSE;
	}

	return TRUE;
}

/**
 * Function to validate the content of a candidate struct
 *
 * Validation Checks:
 * - Does the first and last name contain at least 1 letter? If not, fail.
 * - Is there an existing candidate with the same name? If so, fail.
 *
 * @param c_new 	A new candidate
 * @return 	TRUE if pass validation, else FALSE
 */
static unsigned char cgc_validate_candidate(void *c_new) {

	candidate_t *candidate = (candidate_t *)c_new;

	// check: first and last name have at least 1 letter; reject empty names
	if ((0 == cgc_strlen(candidate->person.f_name, TERM)) ||
		(0 == cgc_strlen(candidate->person.l_name, TERM))) {
		return FALSE;
	}


	struct node *end = cgc_list_end_marker(e.candidates);
	struct node *cur = cgc_list_head_node(e.candidates);
	candidate_t *c = NULL;

	// do we have any other candidates?
	if (0 == cgc_list_length(e.candidates)) {
		return TRUE;
	}

	// the following assume there is at least 1 other candidate
	// check: is there an existing candidate with the same name; reject duplicate names
	while (cur != end) {
		c = (candidate_t *)cur->data;

		if ((0 == cgc_streq(c->person.f_name, candidate->person.f_name, TERM)) &&
			(0 == cgc_streq(c->person.l_name, candidate->person.l_name, TERM))) {
			return FALSE;
		}
		cur = cgc_list_next_node(cur);
	}
	return TRUE;
}

/**
 * Function to validate the content of the election manager struct
 *
 * Validation Checks:
 * - Does the first and last name contain at least 1 letter? If not, fail.
 *
 * @param e 	The election manager
 * @return 	TRUE if pass validation, else FALSE
 */
static unsigned char cgc_validate_emgr(void *e) {

	e_mgr_t *e_mgr = (e_mgr_t *)e;

	// check: first and last name have at least 1 letter; reject empty names
	if ((0 == cgc_strlen(e_mgr->person.f_name, TERM)) ||
		(0 == cgc_strlen(e_mgr->person.l_name, TERM))) {
		return FALSE;
	}

	return TRUE;
}

/**
 * Prompt for and create the election manager.
 *
 * @return SUCCESS on success, else -1
 */
static int cgc_create_election_mgr(void) {
	int ret = SUCCESS;
	char outbuf[2 * (12 + sizeof(NEW_AUTH_KEY) + 4)];
	char *fmt = "%S%U\n%S%U\n";
	unsigned int bytes_used = 0;

	SEND(STDOUT, CREATE_E_MGR, sizeof(CREATE_E_MGR));

	e.manager = cgc_malloc(sizeof(e_mgr_t));
	MALLOC_OK(e.manager);

	e.manager->person.id = e.conf.e_mgr_id;
	cgc_set_first_last_name(&(e.manager->person));
	e.manager->validate = &cgc_validate_emgr;
	cgc_rand(&(e.manager->auth_key), 4);

	if (FALSE == e.manager->validate(e.manager)) {
		return -1;
	}

	// send user id and auth_key
	bytes_used = cgc_snprintf(outbuf, sizeof(outbuf), '%', TERM, fmt,
							NEW_UID,
							e.manager->person.id,
							NEW_AUTH_KEY,
							e.manager->auth_key);

	SEND(STDOUT, outbuf, bytes_used);

	return ret;
}

/**
 * Prompt for and store election name.
 */
static void cgc_get_election_name(void) {
	SEND(STDOUT, ELECTION_NAME, sizeof(ELECTION_NAME));
    RECV_DELIM_TRIM(STDIN, DELIM, e.e_name, sizeof(e.e_name));
}

/**
 * Prompt for and store the election conf
 *
 * @return SUCCESS on success, else ERRNO_CONV on error
 */
static int cgc_set_election_conf(void) {
	int ret = SUCCESS;
	unsigned int ans = 0;
	char letter = '\0';

	// define election conf
	SEND(STDOUT, NUM_WINNERS_Q, sizeof(NUM_WINNERS_Q));
	NEG_BAIL_RET(cgc_receive_number(&ans));
	e.conf.num_winners = ans & 0xFF;

	SEND(STDOUT, MAX_CANDIDATES_Q, sizeof(MAX_CANDIDATES_Q));
	NEG_BAIL_RET(cgc_receive_number(&ans));
	e.conf.max_candidates = ans & 0xFF;

	SEND(STDOUT, WRITE_IN_OK_Q, sizeof(WRITE_IN_OK_Q));
	cgc_receive_letter(&letter);
	if (('Y' == letter) || ('y' == letter)) {
		e.conf.write_in_ok = 1;
	} else {
		e.conf.write_in_ok = 0;
	}

	return SUCCESS;
}

/**
 * Return the next voter ID number and increment it for the next one.
 *
 * @return next voter ID number
 */
static unsigned int cgc_get_next_voter_id(void) {
	unsigned int vid = e.conf.next_voter_id++;
	return vid;
}

/**
 * Return the next candidate ID number and increment it for the next one.
 *
 * @return next candidate ID number
 */
static unsigned int cgc_get_next_candidate_id(void) {
	unsigned int cid = e.conf.next_candidate_id++;
	return cid;
}

/**
 * Return the vote ID number
 *
 * @param v 	Pointer to a voter
 * @return vote ID number
 */
static unsigned int cgc_get_next_vote_id(voter_t *v) {
	unsigned int vote_id = 0;
#ifdef PATCHED_1
	vote_id = v->person.id ^ 0xC0C0CAFE;
#else
	vote_id = v->person.id ^ *(unsigned int *)FLAG_PAGE;
#endif
	return vote_id;
}

/**
 * Predicate function to search for candidates in the candidate list.
 *
 * @param candidate 	A void * to a candidate struct
 * @param candidate_id 	A void * to a candidate ID
 * @return TRUE if matches, else FALSE
 */
static unsigned char cgc_is_candidate(const void *candidate, void *candidate_id) {
	return ((candidate_t *)candidate)->person.id == *(unsigned int *)candidate_id;
}

/**
 * Print the candidate list for the voter to choose from.
 *
 * @return SUCCESS on success, else -1
 */
static int cgc_print_select_candidate_list(void) {

	int ret = 0;
	char outbuf[1 + 12 + 2 + 2*NAME_FIELD_SZ + 1 + 1];
	char *fmt = "\t%U: %S %S\n";
	struct node *end = cgc_list_end_marker(e.candidates);
	struct node *cur = cgc_list_head_node(e.candidates);
	candidate_t *c = NULL;
	unsigned int bytes_used = 0;

	// do we have a candidate to vote for?
	if (0 == cgc_list_length(e.candidates)) {
		SEND(STDOUT, EMPTY_CANDIDATES, sizeof(EMPTY_CANDIDATES));
		return SUCCESS;
	}

	// print list of candidates as:
	// "\tID: Fname Lname\n"
	SEND(STDOUT, SELECT_CANDIDATE, sizeof(SELECT_CANDIDATE));
	while (cur != end) {
		cgc_memset(outbuf, '\0', sizeof(outbuf));
		bytes_used = 0;

		c = (candidate_t *)cur->data;
		bytes_used = cgc_snprintf(outbuf, 
							 sizeof(outbuf),
							 '%', TERM, fmt,
							 c->person.id,
							 c->person.f_name, 
							 c->person.l_name);
		SEND(STDOUT, outbuf, bytes_used);

		cur = cgc_list_next_node(cur);
	}

	return SUCCESS;
}

/*
 * Prints a voting receipt for a successful vote
 *
 * (conf#, candidate f/l name)
 *
 * @param conf 	Confirmation number
 * @param c 	Pointer to candidate
 * @return SUCCESS on success, else -1
 */
static int cgc_send_voting_receipt(unsigned int conf, candidate_t *c) {
	int ret = 0;
	char outbuf[14 + 12 + 31 + 2*NAME_FIELD_SZ + 3];
	char *fmt = "Confirmation #%U. Vote recorded for candidate: %S %S.\n";
	unsigned int bytes_used = 0;

	bytes_used = cgc_snprintf(outbuf, sizeof(outbuf), '%', TERM, fmt,
							conf,
							c->person.f_name,
							c->person.l_name);
	SEND(STDOUT, outbuf, bytes_used);
	return SUCCESS;
}

/**
 * Search the candidate list and return the candidate having id == c_id.
 *
 * @param c_id 	Candidate ID to search for
 * @param c 	Pointer to store candidate pointer.
 * @return 	SUCCESS if found, else -1
 */
static int cgc_get_candidate_by_id(unsigned int c_id, candidate_t **c) {
	struct node *cur = NULL;
	cur = cgc_list_find_node_with_data(e.candidates, &cgc_is_candidate, &c_id);
	if (NULL == cur) {
		SEND(STDOUT, INVALID_CANDIDATE, sizeof(INVALID_CANDIDATE));
		return -1;
	}
	*c = (candidate_t *)cur->data;
	return SUCCESS;
}

/**
 * Create and populate the vote struct, then insert it into votes hash table.
 *
 * @param c 		Candidate being voted for
 * @param vote_id 	Pointer to store vote ID number
 * @return 	SUCCESS on success, else -1
 */
static unsigned int cgc_create_and_insert_vote(candidate_t *c, unsigned int *vote_id) {
#ifdef PATCHED_2
#else
	char local_key[MAX_SIZE];
#endif
	int ret = 0;
	vote_t *vote = NULL;
	char *key = NULL;
	unsigned key_buf_len = 0;
	str_voidp_pair_t *pair = NULL;
	voter_t *voter = (voter_t *)e.conf.authd_user;
	unsigned int bytes_written = 0;

	// create vote struct
	vote = cgc_malloc(sizeof(vote_t));
	MALLOC_OK(vote);

	vote->id = cgc_get_next_vote_id(voter);
	vote->validate = &cgc_validate_vote;

	*vote_id = vote->id;
	voter->vote_id = vote->id;

	// save voter and candidate into vote struct
	if ((sizeof(voter_t) != cgc_memcpy(&vote->v, voter, sizeof(voter_t))) ||
		(sizeof(candidate_t) != cgc_memcpy(&vote->c, c, sizeof(candidate_t))))
		cgc__terminate(ERRNO_COPY);

	if (FALSE == vote->validate(vote)) {
		return -1;
	}

	// insert vote using key "<first name> <last name>"
	key_buf_len = cgc_strlen(voter->person.f_name, TERM) +
				  cgc_strlen(voter->person.l_name, TERM) + 2; 
	key = cgc_malloc(key_buf_len);
	MALLOC_OK(key);

#ifdef PATCHED_2
	bytes_written = cgc_snprintf(key, key_buf_len, '%', TERM, "%S %S",
							voter->person.f_name, voter->person.l_name);

	if ((key_buf_len -1) != bytes_written) {
		cgc__terminate(ERRNO_COPY);
	}
#else
	bytes_written = cgc_snprintf(local_key, key_buf_len, '%', TERM, 
							voter->person.f_name, voter->person.l_name);
	cgc_memcpy(key, local_key, bytes_written + 1);
#endif


	pair = cgc_malloc(sizeof(str_voidp_pair_t));
	MALLOC_OK(pair);

	pair->key = key;
	pair->value = vote;
	pair = cgc_ht_pair_insert(e.votes, pair);

	// check to see if this vote replaced a previous one, if so, free previous one
	if (NULL != pair) {
		cgc_free(pair->key);
		cgc_free(pair->value);
		cgc_free(pair);
		pair = NULL;
	}

	// Test votes hash table to see if it needs to grow
	if (TRUE == cgc_ht_is_re_hash_needed(e.votes)) {
		e.votes = cgc_ht_re_hash(e.votes);
	}

	return SUCCESS;
}

/**
 * Compare 2 candidates for equality (id, first name, last name).
 *
 * @param c1 	Candidate 1
 * @param c2 	Candidate 2
 * @return TRUE if equal, else FALSE
 */
static int cgc_is_candidate_eq(candidate_t *c1, candidate_t *c2) {
	return ((c1->person.id == c2->person.id) &&
			(0 == cgc_streq(c1->person.f_name, c2->person.f_name, TERM)) &&
			(0 == cgc_streq(c1->person.l_name, c2->person.l_name, TERM)));
}

/**
 * Predicate function to determine if vote count of first pair
 * 	is greater than or equal to second pair
 *
 * @param p1 	Pair 1 (uint vote count, void *candidate)
 * @param p2 	Pair 2 (uint vote count, void *candidate)
 * @return TRUE if p1 >= p2, else FALSE
 */
static unsigned char cgc_is_pair_vote_cnt_gteq(const void *p1, void *p2) {
	uint_voidp_pair_t *pair1 = (uint_voidp_pair_t *)p1;
	uint_voidp_pair_t *pair2 = (uint_voidp_pair_t *)p2;

	return pair1->key >= pair2->key;
}

/**
 * Free function for results_list tuple (vote count, p_candidate)
 *
 * @param pair 	Tuple (vote count, p_candidate)
 */
static void cgc_free_results_list_pair(void *pair) {
	cgc_free(pair);
}

/**
 * Process votes to calculate voting results and store result tuples in results_list
 *
 * @param results_list 	Empty linked list to store result tuples (vote count, p_candidate)
 * @return SUCCESS on success, else -1
 */
static int cgc_calculate_voting_results(struct list *results_list) {

	uint_voidp_pair_t *pair = NULL;
	unsigned int vote_count = 0;
	candidate_t *c = NULL;
	vote_t *v = NULL;
	struct node *cur = cgc_list_head_node(e.candidates);
	struct node *end = cgc_list_end_marker(e.candidates);
	while ((NULL != cur) && (cur != end)) {
		c = (candidate_t *)cur->data;
		vote_count = 0;
		pair = (uint_voidp_pair_t *)cgc_ht_pair_iter_start(e.votes);
		v = pair->value;
		while (NULL != v) {
			if (TRUE == cgc_is_candidate_eq(c, &v->c)) {
				vote_count++;
			}
			pair = (uint_voidp_pair_t *)cgc_ht_pair_iter_next(e.votes);
			if (NULL == pair) {
				v = NULL;
			} else {
				v = pair->value;
			}
		}
		pair = cgc_malloc(sizeof(uint_voidp_pair_t));
		MALLOC_OK(pair);

		pair->key = vote_count;
		pair->value = c;
		cgc_list_insert_sorted(results_list, (void *)pair, &cgc_is_pair_vote_cnt_gteq, TRUE);

		cur = cgc_list_next_node(cur);
	}

	return SUCCESS;
}

/**
 * Send voting results
 *
 * 	<Rank>.	<Votes> 	<Candidate_Name>
 *
 * @param results_list 	Linked list containing result tuples (vote count, candidate)
 * @param full 			TRUE -> send results for all candidates, 
 * 						FALSE -> send results for top num_winners candidates.
 * @return SUCCESS on success, else -1
 */
static int cgc_send_voting_results(struct list *results_list, unsigned char full) {
	char outbuf[6 + 2*12 + 2*NAME_FIELD_SZ + 1];
	char *fmt = "\t%U.\t%U\t%S %S\n";
	struct node *cur = NULL;
	candidate_t *c = NULL;
	unsigned int bytes_used = 0;
	unsigned int order_count = 0;
	uint_voidp_pair_t *pair = NULL;

	// do we have candidates?
	if (0 == cgc_list_length(e.candidates)) {
		SEND(STDOUT, ZERO_CANDIDATES, sizeof(ZERO_CANDIDATES));
		return SUCCESS;
	}

	// print list of candidates as:
	// "\t<rank #>: <vote cnt> <Fname> <Lname>\n"
	SEND(STDOUT, CANDIDATE_ORDER, sizeof(CANDIDATE_ORDER));

	cur = cgc_list_head_node(results_list);
	while ((NULL != cur) && (cur != cgc_list_end_marker(results_list))) {
		pair = (uint_voidp_pair_t *)cur->data;

		if ((++order_count <= e.conf.num_winners) || (TRUE == full)) {

			cgc_memset(outbuf, '\0', sizeof(outbuf));
			bytes_used = 0;

			c = (candidate_t *)pair->value;
			bytes_used = cgc_snprintf(outbuf, 
								 sizeof(outbuf),
								 '%', TERM, fmt,
								 order_count,
								 pair->key,
								 c->person.f_name, 
								 c->person.l_name);
			SEND(STDOUT, outbuf, bytes_used);
		}
		cur = cgc_list_next_node(cur);
	}
	return SUCCESS;
}

/**
 * Send list of voters along with an indication of whether they voted or not
 *
 * @return SUCCESS on success, else -1
 */
static int cgc_send_voter_results(void) {
	char outbuf[4 +3 + 2*NAME_FIELD_SZ + 1];
	char *fmt = "\t%S\t%S %S\n";
	voter_t *v = NULL;
	uint_voidp_pair_t *cur = NULL;
	unsigned int bytes_used = 0;

	// do we have voters?
	if (0 == cgc_ht_length(e.voters)) {
		SEND(STDOUT, ZERO_VOTERS, sizeof(ZERO_VOTERS));
		return SUCCESS;
	}

	// print list of voters as:
	// "\t<voted?>\t<Fname> <Lname>\n"
	SEND(STDOUT, VOTER_ORDER, sizeof(VOTER_ORDER));

	cur = (uint_voidp_pair_t *)cgc_ht_pair_iter_start(e.voters);
	while (NULL != cur) {
		v = (voter_t *)cur->value;

		cgc_memset(outbuf, '\0', sizeof(outbuf));
		bytes_used = 0;

		if (0 == v->vote_id) {
			bytes_used = cgc_snprintf(outbuf, 
								 sizeof(outbuf),
								 '%', TERM, fmt,
								 " NO",
								 v->person.f_name,
								 v->person.l_name);
		} else {
			bytes_used = cgc_snprintf(outbuf, 
								 sizeof(outbuf),
								 '%', TERM, fmt,
								 " YES",
								 v->person.f_name,
								 v->person.l_name);
		}

		SEND(STDOUT, outbuf, bytes_used);

		cur = (uint_voidp_pair_t *)cgc_ht_pair_iter_next(e.voters);
	}
	return SUCCESS;
}

/**
 * Check if there is nobody logged in
 *
 * @return 	TRUE if no user is logged in, 
 *			FALSE if any user is logged in
 */
static int cgc_is_nobody_logged_in(void) {
	return NULL == e.conf.authd_user;
}

/**
 * Check if the e-mgr is logged in
 *
 * @return 	TRUE if e-mgr is logged in,
 * 			FALSE if e-mgr is not logged in
 */
static int cgc_is_emgr_logged_in(void) {
	return e.manager == e.conf.authd_user;
}

/**
 * Check if a voter is logged in
 *
 * @return 	TRUE if a voter is logged in,
 * 			FALSE if no voter is logged in
 */
static int cgc_is_voter_logged_in(void) {
	return ((NULL != e.conf.authd_user) && (e.manager != e.conf.authd_user));
}


/**
 * Accept and verify credentials for voter or election mgr.
 *
 * @return VOTER for valid voter creds,
 *			E_MGR for valid election manager creds,
 *			NO_AUTH for invalid creds
 */
auth_t cgc_login(void) {
	unsigned int id_num;
	char last_name[NAME_FIELD_SZ];
	voter_t *v = NULL;

	if (FALSE == cgc_is_nobody_logged_in()) return NO_AUTH;

	e.conf.authd_user = NULL; // successful login -> point to voter or e_mgr

	SEND(STDOUT, ENTER_ID, sizeof(ENTER_ID));
	if (0 >= cgc_receive_number(&id_num)) return NO_AUTH;

	SEND(STDOUT, L_NAME, sizeof(L_NAME));
    RECV_DELIM_TRIM(STDIN, DELIM, last_name, sizeof(last_name));

    if ((id_num == E_MGR_ID) &&
    	(0 == cgc_streq(last_name, e.manager->person.l_name, TERM))) {
			SEND(STDOUT, ENTER_AUTH_KEY, sizeof(ENTER_AUTH_KEY));
			id_num = 0; // re-using for auth_key
			if (0 >= cgc_receive_number(&id_num)) return NO_AUTH;

			if (id_num == e.manager->auth_key) {
	    		e.conf.authd_user = e.manager;
	    		return E_MGR;
			}
    } else if (0 < cgc_ht_length(e.voters)) {
    	// search for voter with id == id_num and l_name == last_name
    	v = (voter_t *)cgc_ht_value_as_voidp(e.voters, &id_num);
    	if ((NULL != v) && 
    		(0 == cgc_streq(last_name, v->person.l_name, TERM))) {
	    		e.conf.authd_user = v;
	    		return VOTER;
		}
    }

	return NO_AUTH;
}

/**
 * Setup the election. Includes election manager account and election parameters.
 *
 * @return 	SUCCESS on success, else -1
 */
int cgc_create_election(void) {
	int ret = SUCCESS;

	FAIL_BAIL_RET(cgc_create_election_mgr());
	cgc_get_election_name();
	FAIL_BAIL_RET(cgc_set_election_conf());

	e.state = NEW;

	SEND(STDOUT, ELECTION_CREATED, sizeof(ELECTION_CREATED));

	return ret;
}

/**
 * Change the state of the election to OPEN.
 *
 * @return 	SUCCESS on success, else -1
 */
int cgc_open_voting(void) {
	if (FALSE == cgc_is_emgr_logged_in()) {
		return -1;
	}

	e.state = OPEN;
	SEND(STDOUT, ELECTION_OPEN, sizeof(ELECTION_OPEN));
	return SUCCESS;
}

/**
 * Change the state of the election to CLOSED.
 *
 * @return 	SUCCESS on success, else -1
 */
int cgc_close_voting(void) {
	if (FALSE == cgc_is_emgr_logged_in()) {
		return -1;
	}

	e.state = CLOSED;
	SEND(STDOUT, ELECTION_CLOSED, sizeof(ELECTION_CLOSED));
	return SUCCESS;
}

/**
 * Get the status of the election.
 *
 * Return the following:
 * 	Number of voters
 * 	Number of votes
 * 	Number of candidates
 *
 * @return 	SUCCESS on success, else -1
 */
int cgc_election_status(void) {
	if (FALSE == cgc_is_emgr_logged_in()) {
		return -1;
	}

	char *fmt = "\tNumber of voters: %U\n\tNumber of votes: %U\n\tNumber of candidates: %U\n";
	char outbuf[3*12 + 19 + 19 + 24 + 2];
	unsigned int bytes_used = 0;

	bytes_used = cgc_snprintf(outbuf, sizeof(outbuf), '%', TERM, fmt,
							cgc_ht_length(e.voters),
							cgc_ht_length(e.votes),
							cgc_list_length(e.candidates));
	SEND(STDOUT, outbuf, bytes_used);

	return SUCCESS;
}

/**
 * Allow the voter to record a vote.
 *  If they have already voted, the new vote will replace the previous vote.
 *
 * @return 	SUCCESS on success, else -1
 */
int vote(void) {

	if (FALSE == cgc_is_voter_logged_in()) {
		return -1;
	}

	int ret = 0;
	candidate_t *c = NULL;
	unsigned int choice = 0;
	unsigned int vote_id = 0;

	// do we have a candidate to vote for?
	if (0 == cgc_list_length(e.candidates)) {
		SEND(STDOUT, EMPTY_CANDIDATES, sizeof(EMPTY_CANDIDATES));
		return SUCCESS;
	}

	// print list of candidates as:
	// "\tID: Fname Lname\n"
	FAIL_BAIL_RET(cgc_print_select_candidate_list());

	// recv candidate ID choice
	NEG_BAIL_RET(cgc_get_choice(&choice));

	// find candidate with ID == choice
	FAIL_BAIL_RET(cgc_get_candidate_by_id(choice, &c));

	FAIL_BAIL_RET(cgc_create_and_insert_vote(c, &vote_id));

	FAIL_BAIL_RET(cgc_send_voting_receipt(vote_id, c));

	return SUCCESS;
}

/**
 * Register a new voter.
 *
 * @return 	SUCCESS on success, else -1
 */
int cgc_register_voter(void) {

	if (FALSE == cgc_is_nobody_logged_in()) {
		return -1;
	}

	char outbuf[12 + sizeof(NEW_UID) + 2];
	voter_t *v = NULL;
	uint_voidp_pair_t *ret_p = NULL;
	uint_voidp_pair_t *pair = NULL;
	char *fmt = "%S%U\n";
	unsigned int bytes_used = 0;

	SEND(STDOUT, CREATE_VOTER, sizeof(CREATE_VOTER));

	v = cgc_malloc(sizeof(voter_t));
	MALLOC_OK(v);

	v->person.id = cgc_get_next_voter_id();
	v->vote_id = 0;
	v->validate = &cgc_validate_voter;
	cgc_set_first_last_name(&(v->person));

	if (FALSE == v->validate(v)) return -1;

	// add voter to voters hash table
	pair = cgc_malloc(sizeof(uint_voidp_pair_t));
	MALLOC_OK(pair);

	pair->key = v->person.id;
	pair->value = v;
	ret_p = (uint_voidp_pair_t *)cgc_ht_pair_insert(e.voters, pair);
	if (NULL != ret_p) {
		cgc_free(ret_p->value);
		cgc_free(ret_p);
	}

	// send user id
	bytes_used = cgc_snprintf(outbuf, sizeof(outbuf), '%', TERM, fmt, NEW_UID, v->person.id);
	SEND(STDOUT, outbuf, bytes_used);

	// Test voters hash table to see if it needs to grow
	if (TRUE == cgc_ht_is_re_hash_needed(e.voters)) {
		e.voters = cgc_ht_re_hash(e.voters);
	}

	return SUCCESS;
}

/**
 * Add a candidate to the list of candidates
 *
 * @return 	SUCCESS on success, else -1
 */
int cgc_add_candidate(void) {

	if ((TRUE == cgc_is_nobody_logged_in()) ||
		((TRUE == cgc_is_voter_logged_in()) && (FALSE == e.conf.write_in_ok))) {
		return -1;
	}

	if (cgc_list_length(e.candidates) >= e.conf.max_candidates) {
		SEND(STDOUT, FULL_CANDIDATES, sizeof(FULL_CANDIDATES));
		return SUCCESS;
	}

	char outbuf[12];
	candidate_t *c = NULL;

	SEND(STDOUT, CREATE_CANDIDATE, sizeof(CREATE_CANDIDATE));

	c = cgc_malloc(sizeof(candidate_t));
	MALLOC_OK(c);

	cgc_set_first_last_name(&(c->person));
	c->validate = &cgc_validate_candidate;

	if (FALSE == c->validate(c)) {
		cgc_free(c);
		SEND(STDOUT, CANDIDATE_INVALID, sizeof(CANDIDATE_INVALID));
		return SUCCESS;
	}

	// set ID - do after validate, so don't have to revert the next ID if fail validate
	c->person.id = cgc_get_next_candidate_id();

	// add candidate to candidates list
	cgc_list_insert_at_end(e.candidates, c);

	SEND(STDOUT, CANDIDATE_ADDED, sizeof(CANDIDATE_ADDED));

	return SUCCESS;
}

/**
 * List winning candidate(s) along with vote count.
 * 	Ordered from highest to lowest vote count.
 *
 * @return 	SUCCESS on success, else -1
 */
int cgc_voting_results(void) {
	if (TRUE == cgc_is_nobody_logged_in()) {
		return -1;
	}

	SEND(STDOUT, VOTING_RESULTS, sizeof(VOTING_RESULTS));

	if (0 == cgc_list_length(e.candidates)) {
		SEND(STDOUT, ZERO_CANDIDATES, sizeof(ZERO_CANDIDATES));
		return SUCCESS;
	}

	int ret = 0;
	struct list results;
	cgc_list_init(&results, &cgc_free_results_list_pair);

	FAIL_BAIL_RET(cgc_calculate_voting_results(&results)); // populate results with tuples (vote count, candidate)

	FAIL_BAIL_RET(cgc_send_voting_results(&results, FALSE));
	cgc_list_destroy(&results);

	return SUCCESS;
}

/**
 * List number of votes, number of voters, and names of all voters.
 *
 * @return 	SUCCESS on success, else -1
 */
int cgc_voter_turnout(void) {
	if (FALSE == cgc_is_emgr_logged_in()) {
		return -1;
	}

	SEND(STDOUT, VOTER_TURNOUT, sizeof(VOTER_TURNOUT));

	int ret = 0;
	char *fmt = "\tNumber of voters: %U\n\tNumber of votes: %U\n";
	char outbuf[3*12 + 19 + 19 + 2];
	unsigned int bytes_used = 0;

	if (0 == cgc_ht_length(e.voters)) {
		SEND(STDOUT, ZERO_VOTERS, sizeof(ZERO_VOTERS));
		return SUCCESS;
	} else {
		bytes_used = cgc_snprintf(outbuf, sizeof(outbuf), '%', TERM, fmt,
								cgc_ht_length(e.voters),
								cgc_ht_length(e.votes));
		SEND(STDOUT, outbuf, bytes_used);
	}

	FAIL_BAIL_RET(cgc_send_voter_results());

	return SUCCESS;
}

/**
 * List number of candidates, names of all candidates and 
 *	the associated vote counts.
 *
 * @return 	SUCCESS on success, else -1
 */
int cgc_candidate_summary(void) {
	if (FALSE == cgc_is_emgr_logged_in()) {
		return -1;
	}

	SEND(STDOUT, CANDIDATE_SUMMARY, sizeof(CANDIDATE_SUMMARY));

	unsigned int candidate_count = cgc_list_length(e.candidates);
	char *fmt = "\tNumber of candidates: %U\n";
	char outbuf[12 + 25 + 2];
	unsigned int bytes_used = 0;

	if (0 == candidate_count) {
		SEND(STDOUT, ZERO_CANDIDATES, sizeof(ZERO_CANDIDATES));
		return SUCCESS;
	} else {
		bytes_used = cgc_snprintf(outbuf, sizeof(outbuf), '%', TERM, fmt,
							  cgc_list_length(e.candidates));
		SEND(STDOUT, outbuf, bytes_used);
	}

	int ret = 0;
	struct list results;
	cgc_list_init(&results, &cgc_free_results_list_pair);

	FAIL_BAIL_RET(cgc_calculate_voting_results(&results)); // populate results with tuples (vote count, candidate)

	FAIL_BAIL_RET(cgc_send_voting_results(&results, TRUE));
	cgc_list_destroy(&results);

	return SUCCESS;
}

int cgc_decider(unsigned char choice) {
	int ret = SUCCESS;

	// ensure a choice is only accepted if it is valid for the current state
	if (0 == (e.state & choice))
		return -1;

	switch (choice) {
	case C_MENU_LOGIN:
		ret = cgc_login();
		break;
	case C_MENU_CREATE_ELECTION:
		ret = cgc_create_election();
		e.conf.authd_user = NULL;
		break;
	case C_MENU_OPEN_VOTING:
		ret = cgc_open_voting();
		e.conf.authd_user = NULL;
		break;
	case C_MENU_CLOSE_VOTING:
		ret = cgc_close_voting();
		e.conf.authd_user = NULL;
		break;
	case C_MENU_ELECTION_STATUS:
		ret = cgc_election_status();
		e.conf.authd_user = NULL;
		break;

	case C_MENU_VOTE:
		ret = vote();
		e.conf.authd_user = NULL;
		break;
	case C_MENU_REGISTER_VOTER:
		ret = cgc_register_voter();
		e.conf.authd_user = NULL;
		break;
	case C_MENU_ADD_CANDIDATE:
		ret = cgc_add_candidate();
		e.conf.authd_user = NULL;
		break;

	case C_MENU_VOTING_RESULTS:
		ret = cgc_voting_results();
		e.conf.authd_user = NULL;
		break;
	case C_MENU_VOTER_TURNOUT:
		ret = cgc_voter_turnout();
		e.conf.authd_user = NULL;
		break;
	case C_MENU_CANDIDATE_SUMMARY:
		ret = cgc_candidate_summary();
		e.conf.authd_user = NULL;
		break;

	case C_MENU_MAIN:
		ret = SUCCESS;
		e.conf.authd_user = NULL;
		break;
	case C_MENU_QUIT:
		ret = 2;
		e.conf.authd_user = NULL;
		break;
	default:
		ret = -1;
		e.conf.authd_user = NULL;
	}

	return ret;
}

void cgc_init_election(void) {
	e.state = INIT;

	e.conf.e_mgr_id = E_MGR_ID;
	e.conf.next_voter_id = FIRST_VOTER_ID;
	e.conf.next_candidate_id = FIRST_CANDIDATE_ID;
	e.conf.authd_user = NULL;

	// store candidates in linked list (have to iterate often)
	// init candidate list
	e.candidates = cgc_malloc(sizeof(struct list));
	MALLOC_OK(e.candidates);
	cgc_list_init(e.candidates, NULL);

	// store voters in hash table, key is voter.id (have to look up often)
	// init voters hash table
	e.voters = cgc_ht_int_init(50);

	// store votes in hash table, key is voter's name "<first name> <last name>". (want easy lookup by voter's name if they want to change their vote)
	// init votes hash table
	e.votes = cgc_ht_str_init(50);
}

void cgc_print_menu(auth_t cred) {

	cgc_print_login_menu(e.state, cred);

	cgc_print_admin_menu(e.state, cred);

	cgc_print_voting_menu(e.state, cred);

	cgc_print_results_menu(e.state, cred);

	SEND(STDOUT, MENU_QUIT, sizeof(MENU_QUIT));
}

int cgc_get_choice(unsigned int *choice) {
    SEND(STDOUT, CHOOSE, sizeof(CHOOSE));
	return cgc_receive_number(choice);
}

