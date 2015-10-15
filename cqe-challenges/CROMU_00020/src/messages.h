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
// Generated at 2015-01-04 15:03:31 -0500

#define HELLO_ID 0
#define HELLO_EXPECTED_LENGTH 0
void* extract_hello(protocol_frame* frame);

#define SEED_REQ_ID 1
#define SEED_REQ_EXPECTED_LENGTH 32
void* extract_seed_req(protocol_frame* frame);

#define SEED_RESP_ID 2
#define SEED_RESP_EXPECTED_LENGTH 0
void* extract_seed_resp(protocol_frame* frame);

#define QUIT_REQ_ID 9
#define QUIT_REQ_EXPECTED_LENGTH 0
void* extract_quit_req(protocol_frame* frame);

#define RAND_REQ_ID 10
#define RAND_REQ_EXPECTED_LENGTH 1
void* extract_rand_req(protocol_frame* frame);

#define RAND_RESP_ID 11
#define RAND_RESP_EXPECTED_LENGTH -1
void* extract_rand_resp(protocol_frame* frame);

#define GUESS_REQ_ID 20
#define GUESS_REQ_EXPECTED_LENGTH 8
void* extract_guess_req(protocol_frame* frame);

#define GUESS_RESP_ID 21
#define GUESS_RESP_EXPECTED_LENGTH 0
void* extract_guess_resp(protocol_frame* frame);

#define ECHO_REQ_ID 30
#define ECHO_REQ_EXPECTED_LENGTH -1
void* extract_echo_req(protocol_frame* frame);

#define ECHO_RESP_ID 31
#define ECHO_RESP_EXPECTED_LENGTH -1
void* extract_echo_resp(protocol_frame* frame);
