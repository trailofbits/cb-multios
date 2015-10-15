/*

Author: Bryce Kerley <bk@cromulence.co>

Copyright (c) 2014-2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#pragma once
#include "protocol.h"
// Generated at 2015-01-25 14:32:33 -0500

#define HELLO_ID 0
#define HELLO_EXPECTED_LENGTH 0
void* extract_hello(protocol_frame* frame);

#define SCRAMBLE_REQ_ID 1
#define SCRAMBLE_REQ_EXPECTED_LENGTH 2
void* extract_scramble_req(protocol_frame* frame);

#define SCRAMBLE_RESP_ID 2
#define SCRAMBLE_RESP_EXPECTED_LENGTH 0
void* extract_scramble_resp(protocol_frame* frame);

#define CHECK_REQ_ID 16
#define CHECK_REQ_EXPECTED_LENGTH 2
void* extract_check_req(protocol_frame* frame);

#define CHECK_FOUND_RESP_ID 17
#define CHECK_FOUND_RESP_EXPECTED_LENGTH 0
void* extract_check_found_resp(protocol_frame* frame);

#define CHECK_NOT_FOUND_RESP_ID 18
#define CHECK_NOT_FOUND_RESP_EXPECTED_LENGTH 0
void* extract_check_not_found_resp(protocol_frame* frame);

#define ADD_REQ_ID 32
#define ADD_REQ_EXPECTED_LENGTH 2
void* extract_add_req(protocol_frame* frame);

#define ADD_RESP_ID 33
#define ADD_RESP_EXPECTED_LENGTH 0
void* extract_add_resp(protocol_frame* frame);

#define SUBTRACT_REQ_ID 48
#define SUBTRACT_REQ_EXPECTED_LENGTH 2
void* extract_subtract_req(protocol_frame* frame);

#define SUBTRACT_RESP_ID 49
#define SUBTRACT_RESP_EXPECTED_LENGTH 0
void* extract_subtract_resp(protocol_frame* frame);

#define CLEAR_REQ_ID 64
#define CLEAR_REQ_EXPECTED_LENGTH 0
void* extract_clear_req(protocol_frame* frame);

#define CLEAR_RESP_ID 65
#define CLEAR_RESP_EXPECTED_LENGTH 0
void* extract_clear_resp(protocol_frame* frame);
