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


#ifndef COMMON_H
#define COMMON_H 1

enum {
	// player
	ERR_UNINITIALIZED_PLAYER = -15,
	// hand
	ERR_HAND_FULL = -22,
	ERR_UNINITIALIZED_HAND = -23,
	ERR_HAND_EMPTY = -24,
	// deck
	ERR_UNINITIALIZED_DECK = -32,
	// card
	ERR_INVALID_CARD = -42,
	ERR_NULL_CARD = -43,
	ERR_INVALID_RANK = -44,
	ERR_UNINITIALIZED_CARD = -45,
	// game-wide
	ERR_INVALID_QTY = -52,
	ERR_UNINITIALIZED_ARRAY = -53,
	ERR_UNINITIALIZED_GAME = -54,
	// parsing
	ERR_INVALID_XML = -62,

};

#endif