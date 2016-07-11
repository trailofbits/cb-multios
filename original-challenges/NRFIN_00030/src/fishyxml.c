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
#include "fishyxml.h"

/**
 * Private method to parse the xml for a single card.
 *
 * @param xml Char string with binary xml to parse
 * @param cards Array to hold the pointer to the resulting card.
 * @return Number of chars read or ERR_INVALID_CARD, 
 *	ERR_INVALID_XML on error.
 */
int parse_xml_card(char *xml, struct card *cards[]) {
	int have_rank = FALSE;
	int have_suit = FALSE;
	uint8_t rank = 0;
	uint8_t suit = 0;
	uint8_t chars_read = 8;

	if (CARD != *xml) {return ERR_INVALID_XML;}
	xml++;

	if (RANK == *xml) {
		have_rank = TRUE;
		xml++;
		rank = *xml;
		xml++;
		if (END != *xml) {return ERR_INVALID_XML;}
		xml++;
	} else if (SUIT == *xml) {
		have_suit = TRUE;
		xml++;
		suit = *xml;
		xml++;
		if (END != *xml) {return ERR_INVALID_XML;}
		xml++;
	} else {
		return ERR_INVALID_XML;
	}

	if ((RANK == *xml) && (FALSE == have_rank)) {
		xml++;
		rank = *xml;
		xml++;
		if (END != *xml) {return ERR_INVALID_XML;}
		xml++;
	} else if ((SUIT == *xml) && (FALSE == have_suit)) {
		xml++;
		suit = *xml;
		xml++;
		if (END != *xml) {return ERR_INVALID_XML;}
		xml++;
	} else {
		return ERR_INVALID_XML;
	}

	if (END != *xml) {return ERR_INVALID_XML;}

	cards[0] = create_card(suit, rank);

	if (NULL == cards[0]) {
		return ERR_INVALID_CARD;
	}

	return chars_read;
}

/**
 * Private method to generate the xml for a single card.
 *
 * @param xml Char buf to store resulting binary xml
 * @param c A card
 * @return Number of bytes written to xml char buf.
 */
uint8_t gen_xml_card(char *xml, struct card *c) {
	uint8_t bytes_written = 0;

	xml[bytes_written++] = CARD;
	xml[bytes_written++] = SUIT;
	xml[bytes_written++] = c->suit;
	xml[bytes_written++] = END;
	xml[bytes_written++] = RANK;
	xml[bytes_written++] = c->rank;
	xml[bytes_written++] = END;
	xml[bytes_written++] = END;

	return bytes_written;
}

int parse_xml_player_name(char *xml, char **player_name, uint8_t len) {
	// xml[0] = START;
	// xml[1] = GAME;
	// xml[2] = PLAYER;
	// xml[3] = NAME;
	// xml[4 thru n - 5] = player_name;
	// xml[n - 4] = END;
	// xml[n - 3] = END;
	// xml[n - 2] = END;
	// xml[n - 1] = FIN;

	if (8 >= len) {
		return ERR_INVALID_XML;
	}

	if ((START != xml[0]) ||
		(GAME != xml[1])  ||
		(PLAYER != xml[2]) ||
		(NAME != xml[3])) {
		return ERR_INVALID_XML;
	}

	char *name = NULL;
	uint8_t name_len = len - 8;
	name = calloc(name_len);

	strncpy(name, &xml[4], name_len);
	*player_name = name;

	if ((END != xml[len - 4]) ||
		(END != xml[len - 3]) ||
		(END != xml[len - 2]) ||
		(FIN != xml[len - 1])) {
		return ERR_INVALID_XML;
	}

	return SUCCESS;
}

int parse_xml_cards(char *xml, struct card *cards[], uint8_t qty) {
	char *idx = xml;
	int count = 0;
	int ret = 0;
	struct card *card[1] = {0};

	if (START != *idx) {return ERR_INVALID_XML;}
	idx++;
	if (CARDS != *idx) {return ERR_INVALID_XML;}
	idx++;

	// VULN: not checking against expected qty or any upper bound, 
	// 		so could send too many cards and overrun cards[] array.
#ifdef PATCHED
	while ((END != *idx) && (count < qty)) {
#else
	while (END != *idx) {
#endif
		ret = parse_xml_card(idx, card);
		if (0 > ret) {return ret;} 
		idx += ret;

		cards[count] = card[0];
		count++;
	}
	if (END != *idx) {return ERR_INVALID_XML;}
	idx++;
	if (FIN != *idx) {return ERR_INVALID_XML;}
	idx++;

	return count;
}

int gen_xml_cards(char *xml, struct card *cards[], uint8_t qty) {
	uint8_t bytes_written = 0;
	uint8_t cards_written = 0;
	uint8_t bytes_needed = 2 + (qty * 8) + 2;

	xml[bytes_written++] = START;
	xml[bytes_written++] = CARDS;
	while ((0 < qty) && (bytes_needed > (bytes_written + 2))) {
		bytes_written += gen_xml_card(&xml[bytes_written], cards[cards_written++]);
	}
	xml[bytes_written++] = END;
	xml[bytes_written++] = FIN;

	return bytes_written;
}

int parse_xml_draw(char *xml) {
	if ((START != xml[0]) ||
		(DRAW != xml[1]) ||
		(END != xml[2]) ||
		(FIN != xml[3])) {
		return ERR_INVALID_XML;
	}

	return SUCCESS;
}

int parse_xml_go_fish(char *xml) {
	if ((START != xml[0]) ||
		(GO_FISH != xml[1]) ||
		(END != xml[3]) ||
		(FIN != xml[4])) {
		return ERR_INVALID_XML;
	}

	return xml[2];
}

int gen_xml_go_fish(char *xml, uint8_t qty) {
	// alloc(5, xml);
	xml[0] = START;
	xml[1] = GO_FISH;
	xml[2] = qty;
	xml[3] = END;
	xml[4] = FIN;

	return 5;
}

int parse_xml_ask(char *xml) {
	if ((START != xml[0]) ||
		(ASK != xml[1]) ||
		(RANK != xml[2])) {
		return ERR_INVALID_XML;
	}

	int8_t rank = (int8_t)xml[3];
	if (FALSE == is_valid_rank(rank)) {return ERR_INVALID_RANK;}

	if ((END != xml[4]) ||
		(END != xml[5]) ||
		(FIN != xml[6])) {
		return ERR_INVALID_XML;
	}

	return rank;
}

int gen_xml_ask(char *xml, uint8_t rank) {
	// alloc(7, xml);
	xml[0] = START;
	xml[1] = ASK;
	xml[2] = RANK;
	xml[3] = rank;
	xml[4] = END;
	xml[5] = END;
	xml[6] = FIN;

	return 7;
}

int parse_xml_fishing(char *xml) {
	if ((START != xml[0]) ||
		(FISHING != xml[1]) ||
		(END != xml[2]) ||
		(FIN != xml[3])) {
		return ERR_INVALID_XML;
	}

	return SUCCESS;
}

int parse_xml_books(char *xml) {
	if ((START != xml[0]) ||
		(BOOKS != xml[1])) {
		return ERR_INVALID_XML;
	}

	uint8_t books = (uint8_t)xml[2];

	if ((END != xml[3]) ||
		(FIN != xml[4])) {
		return ERR_INVALID_XML;
	}

	return books;
}

int gen_xml_books(char *xml, uint8_t count) {
	// alloc(5, xml);
	xml[0] = START;
	xml[1] = BOOKS;
	xml[2] = count;
	xml[3] = END;
	xml[4] = FIN;

	return 5;
}

int gen_xml_turn(char *xml, uint8_t player_id) {
	// alloc(9, xml);
	xml[0] = START;
	xml[1] = TURN;
	xml[2] = PLAYER;
	xml[3] = ID;
	xml[4] = player_id;
	xml[5] = END;
	xml[6] = END;
	xml[7] = END;
	xml[8] = FIN;

	return 9;
}

int gen_xml_final_results(char *xml, uint8_t p0_books, uint8_t p1_books) {
	// alloc(20, xml);
	xml[0] = START;
	xml[1] = GAME;

	xml[2] = PLAYER;
	xml[3] = ID;
	xml[4] = (uint8_t)0;
	xml[5] = END;
	xml[6] = BOOKS;
	xml[7] = p0_books;
	xml[8] = END;
	xml[9] = END;

	xml[10] = PLAYER;
	xml[11] = ID;
	xml[12] = (uint8_t)1;
	xml[13] = END;
	xml[14] = BOOKS;
	xml[15] = p1_books;
	xml[16] = END;
	xml[17] = END;

	xml[18] = END;
	xml[19] = FIN;

	return 20;
}

int gen_xml_error(char *xml, int8_t err_code) {
	// alloc(5, xml);
	xml[0] = START;
	xml[1] = ERROR;
	xml[2] = err_code;
	xml[3] = END;
	xml[4] = FIN;

	return 5;
}


