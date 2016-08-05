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
#include "malloc.h"
#include "memcmp.h"
#include "list.h"
#include "bst.h"

#include "mail.h"
#include "address.h"
#include "postage.h"

static const char CMD_BUY_POSTAGE[4] 			= {'\x03','\x03','\x03','\x03'};
static const char CMD_ADD_ADDRESS[4]			= {'\x05','\x05','\x05','\x05'};
static const char CMD_RECEIVE_MAIL[4] 			= {'\x10','\x10','\x10','\x10'};
static const char CMD_SORT_MAIL[4]				= {'\x11','\x11','\x11','\x11'};
static const char CMD_LIST_ADDRESSES[4]			= {'\x12','\x12','\x12','\x12'};
static const char CMD_LIST_UNDELIVERABLE_MAIL[4]= {'\x13','\x13','\x13','\x13'};
static const char CMD_DELIVER_MAIL[4] 			= {'\x14','\x14','\x14','\x14'};
static const char CMD_RETURN_TO_SENDER[4]		= {'\x15','\x15','\x15','\x15'};
static const char CMD_LIST_LOST_MAIL[4] 		= {'\x16','\x16','\x16','\x16'};
static const char CMD_DESTROY_LOST_MAIL[4] 		= {'\x17','\x17','\x17','\x17'};
static const char CMD_QUIT[4]                   = {'\x00','\x0F','\xF0','\xFF'};

typedef bst_node_t mailbox_t;

mailbox_t sorted_box;			// box of sorted mail
mailbox_t undeliverable_box;	// box of undeliverable mail
mailbox_t lost_box;				// box of lost mail
mailbox_t received_box;			// box of received mail
// bst holding mailbox's (key = address, data = ptr to linked list of mail items)
bst_t mailboxes;

/**
 * Determine if address is in the address list.
 *
 * @param addr 		Address to test
 * @return TRUE if found, else FALSE
 */
static unsigned char address_exists(unsigned short addr) {
	return NULL_NODE != bst_search(&mailboxes, addr);
}

/**
 * Get the mailbox for the given address
 *
 * @param addr 		Address of mailbox to find.
 *
 * @return VA of mailbox node, else NULL_NODE if not found
 */
static mailbox_t *get_mailbox_for_address(unsigned short addr) {
	return bst_search(&mailboxes, addr);
}

/**
 * Get the undeliverable mailbox
 *
 * @return VA of mailbox node
 */
static mailbox_t *get_undeliverable_mailbox(void) {
	return &undeliverable_box;
}

/**
 * Get the lost mailbox
 *
 * @return VA of mailbox node
 */
static mailbox_t *get_lost_mailbox(void) {
	return &lost_box;
}

/**
 * Get the received mailbox
 *
 * @return VA of mailbox node
 */
static mailbox_t *get_received_mailbox(void) {
	return &received_box;
}

/**
 * Get the sorted mailbox
 *
 * @return VA of mailbox node
 */
static mailbox_t *get_sorted_mailbox(void) {
	return &sorted_box;
}

/**
 * Delete a piece of mail
 *
 * @param mail_item 	Pointer to a piece of mail to delete
 */
static void delete_mail(void *mail_item) {
	free(mail_item);
}

/**
 * Determine if a mailbox is empty
 *
 * @param m 	Pointer to a mailbox
 * @return TRUE if empty, else FALSE
 */
static int is_mailbox_empty(mailbox_t *m) {
	return (NULL == m->data) || (0 == list_length(m->data));
}

/**
 * Put a piece of mail into a mailbox
 *
 * @param mail_item A piece of mail
 * @param box 		A mailbox to hold the piece of mail
 */
static void put_mail_in_mailbox(mail_t *mail_item, mailbox_t *box) {

	if (NULL == box->data) {
		box->data = malloc(sizeof(struct list));
		MALLOC_OK(box->data);
		list_init(box->data, NULL);
	}

	list_insert_at_end(box->data, mail_item);
}

/**
 * Remove a piece of mail from a mailbox.
 *
 * @param box 		A mailbox holiding pieces of mail
 */
static mail_t *pop_mail_from_mailbox(mailbox_t *box) {

	if (0 == list_length(box->data)) {
		return NULL;
	}

	struct node *n = list_pop(box->data);
	mail_t *res = n->data;
	list_destroy_node(box->data, &n);

	return res;
}

/**
 * Receive a piece of mail from client and place it into the Received Mail box.
 *
 * @return SUCCESS on success, else -1
 */
static int do_receive_mail(void) {
	stamp_t s;
	// receive postage to pay for the mail item
	RECV(STDIN, (char *)&s, sizeof(stamp_t));

	// return -1 if postage is invalid
	if (-1 == use_stamp(&s)) return -1;

	mail_t *piece = malloc(sizeof(mail_t));
	MALLOC_OK(piece);

	// receive mail_t struct of data.
    RECV(STDIN, (char *)piece, sizeof(mail_t));

	// put piece of mail into the RECEIVED_MAIL_ADDR mailbox
    put_mail_in_mailbox(piece, get_received_mailbox());

	return SUCCESS;
}

/**
 * Send the list of addresses in incremental order.
 *
 * @return SUCCESS on success, else -1
 */
static int do_list_addresses(void) {

	unsigned short addr = 0;
	mailbox_t *m = bst_iter_start(&mailboxes, TRUE);
	if (NULL_NODE == m) return -1;

	while (NULL_NODE != m) {
		addr = m->key;
		if (addr >= MIN_CUSTOMER_ADDR) {
			SEND(STDOUT, (char *)&addr, sizeof(unsigned short));
		}

		m = bst_iter_next(&mailboxes);
	}
	return SUCCESS;
}

/**
 * Add a new address.
 *
 * @return SUCCESS on success, else -1 (address exists or invalid)
 */
static int do_add_address(void) {
	unsigned short addr = 0;

	RECV(STDIN, (char *)&addr, sizeof(unsigned short));

	if ((MIN_CUSTOMER_ADDR <= addr) && (FALSE == address_exists(addr))) {
		bst_insert(&mailboxes, addr);
		return SUCCESS;
	}

	return -1;
}

/**
 * Sort received mail. If any are undeliverable, place in undeliverable box.
 *
 * @return SUCCESS on success, else -1 if received_box if empty
 */
static int do_sort_mail(void) {
	mail_t *m;
	if (TRUE == is_mailbox_empty(get_received_mailbox())) return -1;

	while (NULL != (m = pop_mail_from_mailbox(get_received_mailbox()))) {
		if (TRUE == address_exists(m->recipient)) {
			put_mail_in_mailbox(m, get_sorted_mailbox());
		} else {
			put_mail_in_mailbox(m, get_undeliverable_mailbox());
		}
	}
	return SUCCESS;
}

/**
 * Predicate function used to sort undeliverable mail list
 *
 * @param rs1 	Recipient and sender address 1
 * @param rs2 	Recipient and sender address 2
 * @return return TRUE if first >= second, else FALSE
 */
static unsigned char udm_sort(const void *rs1, void *rs2) {
	// r2r1s2s1	
	return rs1 >= rs2;
}

/**
 * Send the list of undeliverable mail in sorted order (send recipient and sender addresses only).
 *
 * Sorted increasing by recipient, sub-sorted increasing by sender
 *
 * @return SUCCESS on success, else -1 if undeliverable_box is empty
 */
static int do_list_undeliverable_mail(void) {
	if (TRUE == is_mailbox_empty(get_undeliverable_mailbox())) return -1;

	// put 2 - 2 byte shorts into an int (the list node data pointer)
	// <2 bytes recipient>, <2 bytes sender>
	// sorting by the ints will create list sorted by recipient and sub-sorted by sender
	struct list sorted_udm;
	list_init(&sorted_udm, NULL);

	struct list *udm = (struct list *)get_undeliverable_mailbox()->data;

	// make the list
	struct node *n = list_head_node(udm);
	struct node *end = list_end_marker(udm);
	mail_t *m = NULL;
	unsigned int rs = 0;
	unsigned short *p_rs = (unsigned short *)&rs;
	// for item in udm list
	while (end != n) {
		m = (mail_t *)n->data;
		//   make int out of s and r
		p_rs[0] = m->recipient;
		p_rs[1] = m->sender;
		//   create node with int as data element		
		//   insert node into sorted_udm
		list_insert_sorted(&sorted_udm, (void *)rs, udm_sort, FALSE);
		n = list_next_node(n);
	}

	n = list_pop(&sorted_udm);
	end = NULL;
	// for item in sorted_udm list
	while (end != n) {
		//	 pop(item) from list
		rs = (unsigned int)n->data;
		//   send recipient
		SEND(STDOUT, (char *)p_rs, sizeof(unsigned short));

		//   send sender
		SEND(STDOUT, (char *)p_rs+sizeof(unsigned short), sizeof(unsigned short));

		//	 delete node
		list_destroy_node(&sorted_udm, &n);

		n = list_pop(&sorted_udm);
	}

	return SUCCESS;
}

/**
 * Deliver sorted mail to recipients
 *
 * @return SUCCESS on success, else -1 if sorted_box is empty
 */
static int do_deliver_mail(void) {
	mail_t *m;
	mailbox_t *box;
	if (TRUE == is_mailbox_empty(get_sorted_mailbox())) return -1;

	while (NULL != (m = pop_mail_from_mailbox(get_sorted_mailbox()))) {
		box = get_mailbox_for_address(m->recipient);
		put_mail_in_mailbox(m, box);
	}
	return SUCCESS;
}

/**
 * Process undeliverable mail and return to sender or put in lost mail box.
 *
 * @return SUCCESS on success, else -1 if sorted_box is empty
 */
static int do_return_to_sender(void) {
	mail_t *m;
	if (TRUE == is_mailbox_empty(get_undeliverable_mailbox())) return -1;

	while (NULL != (m = pop_mail_from_mailbox(get_undeliverable_mailbox()))) {
		// by default recipient does not exist, because this is undeliverable mail.

		// if sender does not exist, put into lost_mail box
		if (FALSE == address_exists(m->sender)) {
			put_mail_in_mailbox(m, get_lost_mailbox());
		} else {
			// if sender does exist,
			//  set sender as recipient and put in received_mail box
			m->recipient = m->sender;
			// put mail into received_mail box.
			put_mail_in_mailbox(m, get_received_mailbox());
		}
	}

	return SUCCESS;
}

/**
 * Generate hash of mail subject + body
 *
 * @param m 	Pointer to a piece of mail
 * @param hash 	Buffer to store hash
 */
static void hash_mail(mail_t *m, unsigned char hash[]) {
	unsigned char *hash_subj = &hash[0];
	unsigned char *hash_body = &hash[4];

	// this is completely silly, and leaves lots of room for hash collision.
	int i = 0;
	for (i = 0; i < MAX_SUBJ_LEN; i++) {
		hash_subj[i % 4] += m->subject[i];
	}

	for (i = 0; i < MAX_BODY_LEN; i++) {
		hash_body[i % 4] += m->body[i];
	}
}

/**
 * Predicate function used to sort lost mail list
 *
 * @param m1 	mail 1
 * @param m2 	mail 2
 * @return return TRUE if first >= second, else FALSE
 */
static unsigned char lm_sort(const void *m1, void *m2) {
	unsigned char hash_m1[8];
	unsigned char hash_m2[8];
	memset(hash_m1, '\0', sizeof(hash_m1));
	memset(hash_m2, '\0', sizeof(hash_m2));

	hash_mail((mail_t *)m1, hash_m1);
	hash_mail((mail_t *)m2, hash_m2);
	return (-1 != memcmp(hash_m1, hash_m2, 8));
}

/**
 * Send the list of lost mail in sorted order (send hash of subj+body).
 *
 * Sorted increasing by hash of subj and body
 *
 * @return SUCCESS on success, else -1 if lost_box is empty
 */
static int do_list_lost_mail(void) {
	mail_t *m;
	if (TRUE == is_mailbox_empty(get_lost_mailbox())) return -1;

	struct list sorted_lm;
	list_init(&sorted_lm, NULL);

	struct list *lm = (struct list *)get_lost_mailbox()->data;

	// make the list
	struct node *n = list_head_node(lm);
	struct node *end = list_end_marker(lm);
	unsigned char hash[8];

	// for item in lm list
	while (end != n) {
		m = (mail_t *)n->data;

		//   insert mail into sorted_lm
		list_insert_sorted(&sorted_lm, (void *)m, lm_sort, FALSE);
		n = list_next_node(n);
	}

	n = list_pop(&sorted_lm);
	end = NULL;
	// for item in sorted_lm list
	while (end != n) {
		//	 pop(item) from list
		m = (mail_t *)n->data;

		// create hash of subj+body
		memset(hash, '\0', sizeof(hash));
		hash_mail(m, hash);
		// send hash
		SEND(STDOUT, (char *)hash, sizeof(hash));

		//	 delete node
		list_destroy_node(&sorted_lm, &n);

		n = list_pop(&sorted_lm);
	}

	return SUCCESS;
}

/**
 * Destroy all mail in the lost mail box.
 *
 * @return SUCCESS on success, else -1 if lost_box is empty
 */
static int do_destroy_lost_mail(void) {
	mail_t *m;
	if (TRUE == is_mailbox_empty(get_lost_mailbox())) return -1;

	struct list *lm = (struct list *)get_lost_mailbox()->data;

	struct node *n = list_pop(lm);
	while (NULL != n) {
		m = (mail_t *)n->data;
		delete_mail(m);
		list_destroy_node(lm, &n);

		n = list_pop(lm);
	}

	if (0 != list_length(lm)) return -1;

	return SUCCESS;
}

/**
 * Sell postage to customers.
 *
 * @return SUCCESS on success, else -1 on error
 */
static int do_buy_postage(void) {
	stamp_t *s = get_new_stamp();
	if (NULL == s) return -1;

	SEND(STDOUT, (char *)s, STAMP_SIZE);

	return SUCCESS;
}

void setup(void) {
	init_stamp_roll();
	bst_init(&mailboxes);

	undeliverable_box.key = UNDELIVERABLE_MAIL_ADDR;
	lost_box.key = LOST_MAIL_ADDR;
	received_box.key = RECEIVED_MAIL_ADDR;
	sorted_box.key = SORTED_MAIL_ADDR;
}

short process_cmd(void) {
    char cmd[4];
    short ret = 0;

    RECV(STDIN, cmd, sizeof(cmd));

    if (0 == memcmp((void *)CMD_ADD_ADDRESS, cmd, sizeof(CMD_ADD_ADDRESS))) {
    	ret = do_add_address();
    } else if (0 == memcmp((void *)CMD_RECEIVE_MAIL, cmd, sizeof(CMD_RECEIVE_MAIL))) {
    	ret = do_receive_mail();
    } else if (0 == memcmp((void *)CMD_LIST_ADDRESSES, cmd, sizeof(CMD_LIST_ADDRESSES))) {
    	ret = do_list_addresses();
    } else if (0 == memcmp((void *)CMD_SORT_MAIL, cmd, sizeof(CMD_SORT_MAIL))) {
    	ret = do_sort_mail();
    } else if (0 == memcmp((void *)CMD_LIST_UNDELIVERABLE_MAIL, cmd, sizeof(CMD_LIST_UNDELIVERABLE_MAIL))) {
    	ret = do_list_undeliverable_mail();
    } else if (0 == memcmp((void *)CMD_DELIVER_MAIL, cmd, sizeof(CMD_DELIVER_MAIL))) {
    	ret = do_deliver_mail();
    } else if (0 == memcmp((void *)CMD_RETURN_TO_SENDER, cmd, sizeof(CMD_RETURN_TO_SENDER))) {
    	ret = do_return_to_sender();
    } else if (0 == memcmp((void *)CMD_LIST_LOST_MAIL, cmd, sizeof(CMD_LIST_LOST_MAIL))) {
    	ret = do_list_lost_mail();
    } else if (0 == memcmp((void *)CMD_DESTROY_LOST_MAIL, cmd, sizeof(CMD_DESTROY_LOST_MAIL))) {
    	ret = do_destroy_lost_mail();
    } else if (0 == memcmp((void *)CMD_BUY_POSTAGE, cmd, sizeof(CMD_BUY_POSTAGE))) {
    	ret = do_buy_postage();
    } else if (0 == memcmp((void *)CMD_QUIT, cmd, sizeof(CMD_QUIT))) {
    	ret = -2;
    } else {
    	ret = -1;
    }

	return ret;
}

void send_status(char *status_code) {
	SEND(STDOUT, status_code, 2);
}



