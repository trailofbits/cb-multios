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
#include "common.h"
#include "card.h"
#include "hand.h"
#include "gofish.h"

#include "rxtx.h"
#include "fishyxml.h"

int recv_player_name(char **player_name) {
	int ret = 0;
	int bytes_read = 0;
	int bytes_needed = 100; // max bytes for xml that includes player's name
	char xml[100] = {0};

	if (0 >= (bytes_read = recv_until_delim(STDIN, xml, bytes_needed, FIN))) {
		ret = ERRNO_RECV;
		goto bail;
	}

	ret = parse_xml_player_name(xml, player_name, bytes_read);
bail:
	return ret;
}

int send_cards(struct card *cards[], uint8_t qty) {
	int bytes_written = 0;
	uint8_t bytes_needed = 2 + (8 * qty) + 2;
	char *buf = NULL;
	int ret = 0;

	buf = calloc(bytes_needed);

	if (0 >= (bytes_written = gen_xml_cards(buf, cards, qty))) {
		ret = bytes_written;
		goto bail;
	}
	if (bytes_needed != bytes_written) {
		ret = ERR_INVALID_XML;
		goto bail;
	}
	ret = SUCCESS;
	send(buf, bytes_written);

bail:
	free(buf);

	return ret;
}

int recv_cards(struct card *r_cards[], uint8_t qty) {
	int bytes_read = 0;
	int ret = 0;

	// VULN:
	// Need to allow enough data to be read in to reach
	// the vuln in parse_xml_cards. need min 5004 bytes
	// because r_cards gets allocated adjacent to other
	// heap allocations and can hold 624 card pointers
	// before segfaulting; pointer 625 causes segfault
	// 625 * 8 + 4 = 5004
#ifdef PATCHED
	uint8_t bytes_needed = 2 + (8 * qty) + 2;
#else
	int bytes_needed = 5120;
#endif
	char *buf = NULL;

	buf = calloc(bytes_needed);

	if (0 > (bytes_read = recv_until_delim(STDIN, buf, bytes_needed, FIN))) {
		ret = bytes_read;
		goto bail;
	}
#ifdef PATCHED
	if (bytes_needed != bytes_read) {
		ret = ERRNO_RECV;
		goto bail;
	}
#endif

	// it is ok to parse 0 cards provided the xml parses correctly
	//   need that so that "show card" works when player is not supposed
	//   to show the card after going fishing.
	if (0 > (ret = parse_xml_cards(buf, r_cards, qty))) {
		goto bail;
	}
	if (qty != ret) {
		ret = ERR_INVALID_XML;
		goto bail;
	}

bail:
	free(buf);
	return ret;
}

int recv_draw_request() {
	int ret = SUCCESS;
	int bytes_read = 0;
	int bytes_needed = 4;

	char buf[4] = {0};

	bytes_read = recv_until_delim(STDIN, buf, bytes_needed, FIN);
	if (bytes_needed != bytes_read) {return ERRNO_RECV;}

	return parse_xml_draw(buf);
}

int send_hand(struct hand *h) {
	return send_cards(h->cards, h->count);
}

void send_go_fish_notice(uint8_t qty) {
	int bytes_written = 0;
	char buf[5] = {0};

	bytes_written = gen_xml_go_fish(buf, qty);
	send(buf, bytes_written);

}

int recv_go_fish_notice() {
	int ret = SUCCESS;
	int bytes_read = 0;
	int bytes_needed = 5;

	char buf[5] = {0};

	bytes_read = recv_until_delim(STDIN, buf, bytes_needed, FIN);
	if (bytes_needed != bytes_read) {return ERRNO_RECV;}

	return parse_xml_go_fish(buf);
}

int recv_fish_request() {
	int bytes_read = 0;
	int bytes_needed = 4;

	char buf[4] = {0};

	bytes_read = recv_until_delim(STDIN, buf, bytes_needed, FIN);
	if (bytes_needed != bytes_read) {return ERRNO_RECV;}

	return parse_xml_fishing(buf);
}

int recv_and_match_cards(struct card *cards[], uint8_t qty) {
	int ret = 0;
	struct card **r_cards = NULL;
	unsigned int sz = 0;

	if (0 < qty) {
		sz = qty*sizeof(struct card *);
	} else {
		sz = sizeof(struct card *);
	}

	r_cards = calloc(sz);

	if (qty != (ret = recv_cards(r_cards, qty))) {
		ret = FALSE;
	} else {
		ret = is_set_equal(r_cards, cards, qty);
	}

	free(r_cards);

	return ret;
}

int recv_ask_and_get_rank() {
	int bytes_read = 0;
	int bytes_needed = 7;

	char buf[7] = {0};

	bytes_read = recv_until_delim(STDIN, buf, bytes_needed, FIN);
	if (bytes_needed != bytes_read) {return ERRNO_RECV;}

	return parse_xml_ask(buf);
}

void send_ask(uint8_t rank) {
	int bytes_written = 0;
	char buf[7] = {0};

	bytes_written = gen_xml_ask(buf, rank);

	send(buf, bytes_written);
}

int recv_and_match_count_books_played(uint8_t count) {
	int ret = 0;
	int bytes_read = 0;
	int bytes_needed = 5;
	char buf[5] = {0};

	bytes_read = recv_until_delim(STDIN, buf, bytes_needed, FIN);
	if (bytes_needed != bytes_read) {return ERRNO_RECV;}

	ret = parse_xml_books(buf);
	if (0 > ret) {
		return ret;
	} else if (ret == count) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void send_count_books_played(uint8_t count) {
	int bytes_written = 0;
	char buf[7] = {0};

	bytes_written = gen_xml_books(buf, count);

	send(buf, bytes_written);
}

void send_turn_notice(uint8_t p_id) {
	int bytes_written = 0;
	char buf[9] = {0};

	bytes_written = gen_xml_turn(buf, p_id);

	send(buf, bytes_written);
}

int send_initial_hand_to_player(struct game_state *game) {
	return send_cards(game->p_remote->h->cards, game->p_remote->h->count);
}

void send_final_results(struct game_state *game) {
	int bytes_written = 0;
	char buf[20] = {0};

	bytes_written = gen_xml_final_results(buf, 
		game->p_remote->book_count,
		game->p_bot->book_count);

	send(buf, bytes_written);
}

void send_error(int8_t err_code) {
	int bytes_written = 0;
	char buf[5] = {0};

	bytes_written = gen_xml_error(buf, err_code);

	send(buf, bytes_written);
}
