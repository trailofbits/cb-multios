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
#include "components.h"
#include "assemble.h"
#include "examine.h"

enum {
// build commands
	B_CMD_INIT_PANEL = 1048,
	B_CMD_ADD_BREAKER = 1049,
	B_CMD_ADD_OUTLET = 1050,
	B_CMD_ADD_SPLITTER = 1051,
	B_CMD_ADD_LIGHT_STRING = 1052,
// examine commands
	E_CMD_PANEL_OVERLOADED = 2049,
	E_CMD_BREAKER_OVERLOADED = 2050,
	E_CMD_OUTLET_OVERLOADED = 2051,
	E_CMD_SPLITTER_OVERLOADED = 2052,
	E_CMD_LIGHT_STRING_OVERLOADED = 2053,
	E_CMD_RECEPTACLE_OVERLOADED = 2054,
};


/*
 * Send results to client.
 */
static void do_send_results(assemble_result_t *results) {
	// hard code size because sizeof(assemble_result_t) 
	//  is padded to mult of 4 (40), which is too much
	send((char *)results, 37);
}

/*
 * Recv unsigned 32 bit instruction.
 *
 * Returns:
 *  Success: uint32 instruction
 */
static uint32_t recv_uint32() {
	uint32_t command[1] = {0};
	RECV(command, 4);
	return command[0];
}

/*
 * Recv unsigned 8 bit instruction.
 *
 * Returns:
 *  Success: uint8 instruction
 */
static uint8_t recv_uint8() {
	uint8_t command[1] = {0};
	RECV(command, 1);
	return command[0];
}

/*
 * Process build commands and return the results.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_INVALID_COMMAND, ERR_INVALID_MODEL_ID, and various others (< 0) 
 */
int do_build() {

	int ret = 0;
	uint32_t target_id32 = 0;

    uint32_t command = recv_uint32();
    uint32_t model_id = 0;

    assemble_result_t result;
    memset(&result, 0, sizeof(assemble_result_t));

    switch(command) {
	case B_CMD_INIT_PANEL:
		model_id = recv_uint32();
		ret = init_electric_model(model_id);
		break;
	case B_CMD_ADD_BREAKER:
		model_id = recv_uint32();
		ret = add_breaker_to_load_center(model_id, &result);
		break;
	case B_CMD_ADD_OUTLET:
		model_id = recv_uint32();
		target_id32 = recv_uint32();
		ret = add_outlet_to_breaker(model_id, target_id32, &result);
		break;
	case B_CMD_ADD_SPLITTER:
		model_id = recv_uint32();
		target_id32 = recv_uint32();
		ret = add_n_way_splitter_to_receptacle(model_id, target_id32, &result);
		break;
	case B_CMD_ADD_LIGHT_STRING:
		model_id = recv_uint32();
		target_id32 = recv_uint32();
		ret = add_light_string_to_receptacle(model_id, target_id32, &result);
		break;
	default:
		ret = ERR_INVALID_COMMAND;
    }

    // send results if no error
    if ((ret >= 0) && (B_CMD_INIT_PANEL != command)) {
        do_send_results(&result);
    }

	return ret;
}

/*
 * Process examine commands and return the results.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_INVALID_COMMAND
 */
int do_examine() {
	int ret = SUCCESS;
	uint32_t target_id32 = 0;

    uint32_t command = recv_uint32();

    switch(command) {
	case E_CMD_PANEL_OVERLOADED:
		ret = is_electrical_panel_overloaded();
		break;
	case E_CMD_BREAKER_OVERLOADED:
		target_id32 = recv_uint32();
		ret = is_breaker_overloaded(target_id32);
		break;
	case E_CMD_OUTLET_OVERLOADED:
		target_id32 = recv_uint32();
		ret = is_outlet_overloaded(target_id32);
		break;
	case E_CMD_SPLITTER_OVERLOADED:
		target_id32 = recv_uint32();
		ret = is_splitter_overloaded(target_id32);
		break;
	case E_CMD_LIGHT_STRING_OVERLOADED:
		target_id32 = recv_uint32();
		ret = is_light_string_overloaded(target_id32);
		break;
	case E_CMD_RECEPTACLE_OVERLOADED:
		target_id32 = recv_uint32();
		ret = is_receptacle_overloaded(target_id32);
		break;
	default:
		ret = ERR_INVALID_COMMAND;
    }

    // send results if no error
    if (ret >= 0) {
    	assemble_result_t result = {0};
    	result.object_id = (uint32_t)ret;
        do_send_results(&result);
    }

	return ret;
}

/*
 * Generate a random nonce and send it to the client.
 * Read the value sent back from the client and verify that it matches the nonce.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_INVALID_NONCE
*/
int do_nonce() {
 	int ret = 0;

 	char nonce[8] = "1234567";
 	if((ret = rand(nonce, 8)) < 0) {_terminate(ERR_RAND_FAILED);}
 	SENDLL(nonce);

 	char nonce_reply[8] = "1234567";
    RECV(nonce_reply, 8);

    if (nonce[0] == nonce_reply[0]) {
    	return SUCCESS;
    } else {
    	return ERR_INVALID_NONCE;
    }
}