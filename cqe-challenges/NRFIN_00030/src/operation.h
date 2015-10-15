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


#ifndef OPERATION_H
#define OPERATION_H 1

/**
 * Process a full game.
 *
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_HAND_FULL,
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK, ERR_INVALID_QTY,
 *	ERR_INVALID_XML, ERRNO_RECV, ERR_INVALID_RANK, ERR_INVALID_CARD, 
 *	ERR_UNINITIALIZED_ARRAY, ERR_HAND_EMPTY on error
 */
extern int play_game();

#endif
 