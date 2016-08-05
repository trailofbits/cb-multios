/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include <cstdio.h>
#include <cstring.h>
#include "brc_response.h"

BrcResponse::BrcResponse(unsigned short recv_length)
    : BrcProtocol(recv_length), response_code_(-1), msg_length_(0) {
    set_server_addr();
}

BrcResponse::BrcResponse(short response_code, char *msg, unsigned short msg_length)
    : BrcProtocol(token_length() + sizeof(server_addr_) + sizeof(response_code_) + sizeof(msg_length_) + msg_length),
      response_code_(response_code), msg_length_(msg_length) {
    raw_data_ = new char[length_];
    set_token();
    set_server_addr();

    char *pdata = raw_data_ + token_length();
    memcpy(pdata, &server_addr_, sizeof(server_addr_));
    pdata += sizeof(server_addr_);
    memcpy(pdata, &response_code, sizeof(response_code));
    pdata += sizeof(response_code);
    memcpy(pdata, &msg_length, sizeof(msg_length));
    pdata += sizeof(msg_length);
    memcpy(pdata, msg, msg_length);
}

BrcResponse::~BrcResponse() {
    server_addr_ = 0;
    response_code_ = 0;
    msg_length_ = 0;
}

bool BrcResponse::Recv(FILE *fd_in) {
    if (!BrcProtocol::Recv(fd_in))
        return false;

    char *pdata  = raw_data_ + token_length();
    server_addr_ = *((int *)pdata);
    pdata += sizeof(server_addr_);
    response_code_ = *((short *)pdata);
    pdata += sizeof(response_code_);
    msg_length_ = *((unsigned short *)pdata);
    return true;
}

const unsigned int BrcResponse::protocol_id() const {
    return 8;
}

const int BrcResponse::server_addr() const {
    return server_addr_;
}

const unsigned short BrcResponse::response_code() const {
    return response_code_;
}

const unsigned short BrcResponse::msg_length() const {
    return msg_length_;
}

const char *BrcResponse::msg() const {
    char *pdata = raw_data_ + token_length();
    pdata += sizeof(server_addr_) + sizeof(response_code_) + sizeof(msg_length_);
    return pdata;
}

void BrcResponse::set_server_addr() {
    server_addr_ = 99999999;
}

