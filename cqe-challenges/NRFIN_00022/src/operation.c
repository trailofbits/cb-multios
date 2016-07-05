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
#include <libcgc.h>
#include "libc.h"
#include "operation.h"
#if TEST_COMMON_H == 1
#include "t_operation.h"
#endif

list_t *haiku_list = NULL;
uint32_t next_haiku_id = INIT_HAIKU_ID;

/*
 * Receive 4 bytes as a uint32_t.
 *
 * Returns:
 *  uint32_t >= 0
 */
uint32_t recv_uint32() {
    uint32_t num[1] = {0};
    RECV(num, sizeof(uint32_t));
	return num[0];
}

/*
 * Receive 2 bytes as a uint16_t.
 *
 * Returns:
 *  uint16_t >= 0
 */
uint32_t recv_uint16() {
    uint16_t num[1] = {0};
    RECV(num, sizeof(uint16_t));
	return num[0];
}

/*
 * Test to see if the haiku list exists.
 *
 * Returns:
 *  exists: TRUE
 *  not exists: FALSE
 */
uint8_t haiku_list_exists() {
	if (NULL == haiku_list) {
		return FALSE;
	} else {
		return TRUE;
	}
}

/*
 * Test to see if the haiku list is empty.
 *
 * Assumes haiku_list exists.
 *
 * Returns:
 *  is empty: TRUE
 *  not empty: FALSE
 */
uint8_t is_haiku_list_empty() {
	if (0 == haiku_list->count) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Initialize the haiku list.
 */
void init_haiku_list() {
	if (FALSE == haiku_list_exists()) {
		haiku_list = list_create();
	}
}

/*
 * Get the number of haiku in the list.
 *
 * Returns:
 *  Success: >= 0
 *  Failure: ERR_LIST_NOT_EXIST
 */
int get_count() {
	if (TRUE == haiku_list_exists()) {
		return haiku_list->count;
	} else {
		return ERR_LIST_NOT_EXIST;
	}
}

/*
 * Get the id number for the haiku in this node.
 *
 * Returns:
 *  Success: >= 0
 *  Failure: ERR_EMPTY_NODE
 */
uint32_t get_id_from_haiku(node_t *haiku) {
	if (NULL != haiku->data) {
		struct haiku *h = (struct haiku *) haiku->data;
		return h->id;
	} else {
		return ERR_EMPTY_NODE;
	}
}

/*
 * Get next available haiku id number.
 */
uint32_t get_next_haiku_id() {
	next_haiku_id++;
	return next_haiku_id - 1;
}

/*
 * Get a random index in the list of haiku ids.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_LIST_NOT_EXIST, ERR_LIST_EMPTY, ERR_RAND_FAILED
 */
int get_random_idx(uint32_t *idx) {
	uint32_t random_idx = 0;
	int ret = 0;
	ret = rand((char *)&random_idx, 4);
	int32_t count = get_count();

	if (ERR_LIST_NOT_EXIST == count) {
		return count;
	} else if (0 == count) {
		return ERR_LIST_EMPTY;
	} else if (0 != ret) {
		return ERR_RAND_FAILED;
	} else {
		*idx = random_idx % (uint32_t)count;
		return SUCCESS;
	}
}

/*
 * Populate array with all haiku ids.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_LIST_NOT_EXIST, ERR_LIST_EMPTY
 */
int populate_array_with_haiku_ids(uint32_t id_arr[], uint32_t count) {

	node_t *haiku_ptr = NULL;
	struct haiku *h = NULL;
	uint32_t id = 0;

	if (TRUE == haiku_list_exists()) {
		haiku_ptr = haiku_list->tail;
	} else {
		return ERR_LIST_NOT_EXIST;
	}

	if ((0 == count) || (NULL == haiku_ptr)) {
		return ERR_LIST_EMPTY;
	}

	while ((0 < count) && (NULL != haiku_ptr)) {
		h = (struct haiku *)haiku_ptr->data;
		id_arr[count - 1] = h->id;

		count--;
		haiku_ptr = haiku_ptr->prev;
	}
	return SUCCESS;
}

/*
 * Find haiku having id.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_INVALID_ID, ERR_LIST_NOT_EXIST, ERR_LIST_EMPTY
 */
int find_haiku_with_id(struct haiku **h, uint32_t id) {

	node_t *haiku_ptr = NULL;
	struct haiku *tmp = NULL;
	int count = 0;
	bool_t found = FALSE;

	count = get_count();
	if (0 < count) {
		haiku_ptr = haiku_list->head;
	} else if (0 == count) {
		return ERR_LIST_EMPTY;
	} else {
		return ERR_LIST_NOT_EXIST;
	}

	while (NULL != haiku_ptr) {
		tmp = (struct haiku *)haiku_ptr->data;
		if (id == tmp->id) {
			*h = tmp;
			found = TRUE;
			break;
		}
		haiku_ptr = haiku_ptr->next;
	}

	if (TRUE == found) {
		return SUCCESS;
	} else {
		return ERR_INVALID_ID;
	}
}

/*
 * Send the struct haiku to client.
 */
void send_haiku(struct haiku *h) {
	uint32_t id = h->id;
	char *content = h->content;
	uint16_t length = h->length;

	send((char *)&id, sizeof(uint32_t));
	send((char *)&length, sizeof(uint16_t));
	send(content, length);
}

/*
 * Send the Ester Egg haiku to client.
 */
void send_easter_egg_haiku() {

	uint32_t id = EGG_ID;
	char *content = EGG_HAIKU;
	uint16_t length = strlen(content);

	send((char *)&id, sizeof(uint32_t));
	send((char *)&length, sizeof(uint16_t));
	send(content, length);
}

/*
 * Send the id of the haiku to the client.
 */
void send_haiku_id(uint32_t id) {
	SENDUI(id);
}

/*
 * Create a new node with the haiku as its data element and insert
 *  the node into the haiku list.
 *
 * Returns:
 *  Success: SUCCESS
 */
int add_haiku_to_list(struct haiku *h) {

	node_t *nd = node_create((void *)h);
	return list_push(haiku_list, nd);
}

/*
 * Receive one haiku line from client and store it at the haiku_content_ptr.
 *
 * Returns:
 *  bytes written at haiku_content_ptr >= 0
 */
int recv_haiku_line(char *haiku_content_ptr, int16_t bytes_remaining) {

	char temp_line_buf[MAX_HAIKU_LINE_LEN] = {0};
	int16_t bytes_received = 0;
	int16_t bytes_written = 0;

	// bytes_received includes line termination char, 
	//  but line term char is not written to temp_line_buf, a null is in its place.
	bytes_received = recvline(STDIN, temp_line_buf, MAX_HAIKU_LINE_LEN);

	//  this will make the creation of POV input harder to create 
	//   since it will need line termination chars at set intervals.
	if (0 > bytes_received) {
		return ERR_INVALID_HAIKU;
	}

	// VULN HERE
	// - if bytes_remaining goes neg, MAX_HAIKU_LINE_LEN chars can be written
	//  to haiku_content_ptr for each line of input.

	// +1 for trailing null
	bytes_written = snprintf(haiku_content_ptr, bytes_remaining + 1, "~c\x07", temp_line_buf);

	return bytes_written;
}

/*
 * Receive a full haiku from the client and store it in the haiku struct.
 *
 * Returns:
 *  VA of new struct haiku 
 */
struct haiku *recv_haiku(uint16_t total_bytes) {

	struct haiku *h = NULL;
	char *haiku_content_ptr = NULL;
	int16_t bytes_remaining = 0;
	int16_t bytes_written = 0;

	bytes_remaining = (int16_t)total_bytes;

	ALLOC(sizeof(struct haiku) + total_bytes + 1, &h); // +1 for trailing null
	haiku_content_ptr = h->content;

	// VULN HERE - if something causes bytes_remaining to go negative, this loop will not stop.
#if PATCHED
	while (0 < bytes_remaining) {
#else
	while (0 != bytes_remaining) {
#endif
		bytes_written = recv_haiku_line(haiku_content_ptr, bytes_remaining);
		if (0 > bytes_written) { // ERR_INVALID_HAIKU
			return NULL;
		}

		haiku_content_ptr += bytes_written;
		bytes_remaining -= bytes_written;
	}

	h->id = get_next_haiku_id();
	h->length = total_bytes;

	return h;
}

/*
 * Receive the size of the haiku, including line termination chars.
 *
 * A Haiku has 3 lines, expect 1 line termination char at the end of each line.
 *
 * Returns:
 *  haiku size uint16 >= 0
 */
uint16_t recv_haiku_size() {
	return recv_uint16(); 
}

// Operation functions

/*
 * Add a new haiku to the list of haiku.
 *
 * Also responsible for initializing the haiku list with the first add.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_INVALID_HAIKU_LEN, ERR_INVALID_HAIKU
 */
int add_haiku() {

	int ret = SUCCESS;
	uint16_t total_bytes = 0; // number of bytes in haiku, including line termination chars.
	struct haiku *h = NULL;

	if (FALSE == haiku_list_exists()) {
		init_haiku_list();
	}

	total_bytes	= recv_haiku_size();

	if ((0 < total_bytes) && (MAX_HAIKU_LEN > total_bytes)) {
		h = recv_haiku(total_bytes);
		if (NULL == h) {
			ret = ERR_INVALID_HAIKU;
		} else {
			ret = add_haiku_to_list(h);

			send_haiku_id(h->id);			
		}
	} else {
		ret = ERR_INVALID_HAIKU_LEN;
	}

	return ret;
}

/*
 * Get the haiku having id from the list of haiku.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_INVALID_ID, ERR_LIST_NOT_EXIST, ERR_LIST_EMPTY
 */
int get_haiku_by_id() {
	struct haiku *h = NULL;
	uint32_t id = 0;
	int res = 0;

	if (TRUE == haiku_list_exists()) {

		id = recv_uint32();

		if (EGG_ID == id) {
			send_easter_egg_haiku();
		} else {
			res = find_haiku_with_id(&h, id);
			if (SUCCESS == res) {
				send_haiku(h);
			}
		}
	} else {
		res = ERR_LIST_NOT_EXIST;
	}

	return res;
}

/*
 * Get a randomly selected haiku from the list of haiku.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_INVALID_ID, ERR_LIST_NOT_EXIST, ERR_LIST_EMPTY, ERR_RAND_FAILED
 */
int get_haiku_random() {

	uint32_t random_idx = 0;
	uint32_t count = 0;
	uint32_t *id_arr = NULL;
	struct haiku *rand_haiku = NULL;
	int res = SUCCESS;

	if (TRUE == haiku_list_exists()) {
		count = get_count();
		if (0 == count) {
			return ERR_LIST_EMPTY;
		}

		ALLOC(count * sizeof(uint32_t), &id_arr);

		// these functions should not return error due to haiku_list existance or count <= 0.
		res = populate_array_with_haiku_ids(id_arr, count);
		res = get_random_idx(&random_idx);
		if (ERR_RAND_FAILED != res) {
			res = find_haiku_with_id(&rand_haiku, id_arr[random_idx]);
		}

		DEALLOC(id_arr, count * sizeof(uint32_t));

		if (SUCCESS == res) {
			send_haiku(rand_haiku);
		}

	} else {
		res = ERR_LIST_NOT_EXIST;
	}

	return res;
}

/*
 * Get the number of haiku in the list.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_LIST_NOT_EXIST
 */
int get_haiku_count() {
	uint32_t count = 0;
	if (TRUE == haiku_list_exists()) {
		count = get_count();
		SENDUI(count);
		return SUCCESS;
	} else {
		return ERR_LIST_NOT_EXIST;
	}
}

/*
 * Get the list of haiku id numbers.
 *
 * Sends to client the count of ids followed by the list of ids.
 * If count is 0, nothing is sent for the list.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_LIST_NOT_EXIST
 */
int get_haiku_ids() {
	if (TRUE == haiku_list_exists()) {
		uint32_t count = (uint32_t)get_count();
		SENDUI(count);

		node_t *hl_ptr = haiku_list->head;
		while(NULL != hl_ptr) {
			uint32_t id = get_id_from_haiku(hl_ptr);
			SENDUI(id);
			hl_ptr = hl_ptr->next;
		}
	} else {
		return ERR_LIST_NOT_EXIST;
	}

	return SUCCESS;
}
