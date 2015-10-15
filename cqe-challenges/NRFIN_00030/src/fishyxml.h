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


#ifndef FISHYXML_H
#define FISHYXML_H 1


/*
### FISHYXML Grammar ###

* '*' means zero or more
* optional elements are enclosed in '[' and ']'

start = START body FIN
body = element
element = TAG [ *content END ]
content = element | data | error
data = uint8
error = int16

# global tokens (uint8) #
* END = 0x27
* START = 0x28
* FIN = 0x29

# global tags (TAG) (uint8) #
* GAME = 0x42
* PLAYER = 0x43
* CARDS = 0x44
* CARD = 0x45
* SUIT = 0x46
* RANK = 0x47
* ERROR = 0x48
* ID = 0x49
* DRAW = 0x50
* GO_FISH = 0x51
* FISHING = 0x52 
* ASK = 0x53
* BOOKS = 0x54
* TURN = 0x55
* NAME = 0x56
*/


enum {
	// tokens
	END = 0x27,
	START = 0x28,
	FIN = 0x29,
	// tags
	GAME = 0x42,
	PLAYER = 0x43,
	CARDS = 0x44,
	CARD = 0x45,
	SUIT = 0x46,
	RANK = 0x47,
	ERROR = 0x48,
	ID = 0x49,
	DRAW = 0x50,
	GO_FISH = 0x51,
	FISHING = 0x52,
	ASK = 0x53,
	BOOKS = 0x54,
	TURN = 0x55,
	NAME = 0x56,
};


/**
 * Parse binary xml to extract the remote player's name.
 *
 * "START GAME PLAYER NAME <data> END END END FIN"
 *
 * @param xml Char buf containing binary xml to parse
 * @param player_name Pointer to assign to char buf containing player's name
 * @param len Length of xml char buf
 * @return SUCCESS or ERR_INVALID_XML on error
 */
extern int parse_xml_player_name(char *xml, char **player_name, uint8_t len);

/**
 * Parse binary xml to extract cards.
 *
 * "START CARDS (CARD RANK <data> END SUIT <data> END END)* END FIN"
 *
 * RANK and SUIT can be in either order.
 *
 * @param xml Char buf containing binary xml to parse
 * @param cards Array of card pointers to store extracted cards.
 * @param qty Quantity of cards expected to extract from xml.
 * @return Number of cards extracted or ERR_INVALID_XML,
 *	ERR_INVALID_CARD on error
 */
extern int parse_xml_cards(char *xml, struct card *cards[], uint8_t qty);

/**
 * Generate binary xml containing cards from cards array.
 *
 * "START CARDS (CARD SUIT <data> END RANK <data> END END)* END FIN"
 *
 * SUIT and RANK always in this order.
 *
 * @param xml Char buf to store resultant binary xml
 * @param cards Array of card pointers to convert to xml
 * @param qty Quantity of cards to convert.
 * @return Length of xml char string
 */
extern int gen_xml_cards(char *xml, struct card *cards[], uint8_t qty);

/**
 * Parse binary xml to extract draw request.
 *
 * "START DRAW END FIN"
 *
 * @param xml Char buf containing binary xml to parse
 * @return SUCCESS or ERR_INVALID_XML on error
 */
extern int parse_xml_draw(char *xml);

/**
 * Parse binary xml to extract go fish notice.
 *
 * "START GO_FISH <data> END FIN"
 *
 * @param xml Char buf containing binary xml to parse
 * @return Count of cards being sent or ERR_INVALID_XML on error
 */
extern int parse_xml_go_fish(char *xml);

/**
 * Generate binary xml containing go fish notice.
 *
 * "START GO_FISH <data> END FIN"
 *
 * @param xml Char buf to store resultant binary xml
 * @param qty Number of cards player is giving; 0 means "Go Fish"
 * @return Length of xml char string.
 */
extern int gen_xml_go_fish(char *xml, uint8_t qty);

/**
 * Parse binary xml to extract ask 
 *
 * "START ASK RANK <data> END END FIN"
 *
 * @param xml Char buf containing binary xml to parse
 * @return Card rank or ERR_INVALID_XML, ERR_INVALID_RANK on error
 */
extern int parse_xml_ask(char *xml);

/**
 * Generate binary xml containing ask for card of rank.
 *
 * "START ASK RANK <data> END END FIN"
 *
 * @param xml Char buf to store resultant binary xml
 * @param rank Rank of card
 * @return Length of xml char string
 */
extern int gen_xml_ask(char *xml, uint8_t rank);

/**
 * Parse binary xml to extract fishing request
 *
 * "START FISHING END FIN"
 *
 * @param xml Char buf containing binary xml to parse
 * @return SUCCESS or ERR_INVALID_XML on error
 */
extern int parse_xml_fishing(char *xml);

/**
 * Parse binary xml to extract book count notice
 *
 * "START BOOKS <data> END FIN"
 *
 * @param xml Char buf containing binary xml to parse
 * @return Number of books or ERR_INVALID_XML on error
 */
extern int parse_xml_books(char *xml);

/**
 * Generate binary xml containing book count notice
 *
 * "START BOOKS <data> END FIN"
 *
 * @param xml Char buf to store resultant binary xml
 * @param count Number of books
 * @return Length of xml char string
 */
extern int gen_xml_books(char *xml, uint8_t count);

/**
 * Generate binary xml containing turn notice.
 *
 * "START TURN PLAYER ID <data> END END END FIN"
 *
 * @param xml Char buf to store resultant binary xml
 * @param player_id ID of player whos turn it is
 * @return Length of xml char string.
 */
extern int gen_xml_turn(char *xml, uint8_t player_id);

/**
 * Generate binary xml containing final game results
 *
 * "START GAME PLAYER ID <data> END BOOKS <data> END END \
 *             PLAYER ID <data> END BOOKS <data> END END END FIN"
 *
 * @param xml Char buf to store resultant binary xml
 * @param p0_books Number of books remote player had
 * @param p1_books Number of books bot player had
 * @return Length of xml char string
 */
extern int gen_xml_final_results(char *xml, uint8_t p0_books, uint8_t p1_books);

/**
 * Generate binary xml containing error code
 *
 * "START ERROR <error> END FIN"
 *
 * @param xml Char buf to store resultant binary xml
 * @param err_code Error code
 * @return Length of xml char string
 */
extern int gen_xml_error(char *xml, int8_t err_code);

#endif