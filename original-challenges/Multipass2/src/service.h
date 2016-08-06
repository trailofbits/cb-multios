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


#ifndef SERVICE_H
#define SERVICE_H
#include <libcgc.h>
#include "libc.h"


#define LIST_PUSH_MSG "Failed to extend list."
#define LIST_RM_MSG "Failed to remove node from list."
#define ALLOC_MSG "Failed to allocate memory."
#define DEALLOC_MSG "Failed to deallocate memory."
#define PURCHASE_ISF_MSG "Insuffient funds for purchase."
#define RECHARGE_FULL_MSG "Unable to recharge card. Balance near max."
#define REFUND_FULL_MSG "Unable to refund card. Balance near max."
#define NO_HISTORY_MSG "No matching transaction history."
#define INVALID_OPCODE_MSG "Invalid OP_CODE."
#define INVALID_PKT_TYPE_MSG "Invalid PKT_TYPE."
#define INVALID_V_TYPE_MSG "Invalid VENDOR_TYPE."
#define NO_AUTH_MSG "Transaction has not completed AUTH."
#define NO_INIT_MSG "Transaction has not completed INIT."
#define NO_OPS_MSG "Transaction has not completed OPS."
#define NOT_FOUND_MSG "Card or transaction not found."
#define INVALID_CARD_MSG "Invalid card or auth code."
#define RECV_FAIL_MSG "Receive failed."
#define UNK_ERROR_MSG "Unknown Error."

#define ALLOC(len, is_x, addr) \
		if (SUCCESS != (allocate(len, is_x, addr))) \
			{ return ERRNO_MP_ALLOC; }

#define RET_ON_FAIL(ret_val) \
		if(SUCCESS != ret_val) \
			{return ret_val;}


// this enum is used as 1 byte (0-255)
typedef enum {
	OK = 0,
	ERRNO_MP_LIST_PUSH,		// Failed to add node to list
	ERRNO_MP_LIST_RM,		// Failed to rm node from list
	ERRNO_MP_ALLOC,			// Failed to allocate memory
	ERRNO_MP_DEALLOC,		// Failed to deallocate memory
	ERRNO_MP_PURCHASE_ISF,		// Insufficient Funds
	ERRNO_MP_RECHARGE_FULL,	// Recharge would cause card balance to wrap
	ERRNO_MP_REFUND_FULL,	// Refund would cause card balance to wrap
	ERRNO_MP_NO_HISTORY,	// No matching transaction history in transaction list.
	ERRNO_MP_INVALID_OPCODE,	// Invalid Op_code
	ERRNO_MP_INVALID_P_TYPE,	// Invalid Packet Type
	ERRNO_MP_INVALID_V_TYPE,	// Invalid Vendor Type
	ERRNO_MP_NO_AUTH,		// Transaction did not complete AUTH step
	ERRNO_MP_NO_INIT,		// Transaction did not complete INIT step
	ERRNO_MP_NO_OPS,		// Transaction did not complete OPS step
	ERRNO_MP_NOT_FOUND,		// When the card or transaction is not in the list
	ERRNO_MP_INVALID_CARD,	// Card does not exist or is invalid
	ERRNO_MP_RECV,			// Failed to receive expected number of bytes
	ERRNO_MP_UNK			// Unknown error
} STATUS;


#endif
