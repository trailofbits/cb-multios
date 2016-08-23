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
#include "brc_protocol.h"
#include "debug_brc.h"
#include "brc_token.h"

BrcProtocol::BrcProtocol(unsigned short recv_length) {
    length_ = recv_length;
    raw_data_ = (char *)NULL;
}

BrcProtocol::BrcProtocol(char *data, unsigned short data_length) {
    set_token();
    length_ = data_length + TokenGenerator::GetTokenLength();
    raw_data_ = new char[length_];
    memcpy(&raw_data_[TokenGenerator::GetTokenLength()], data, data_length);
}

BrcProtocol::~BrcProtocol() {
    length_ = 0;
    if (raw_data_)
        delete[] raw_data_;
    raw_data_ = (char *)NULL;
}

bool BrcProtocol::Recv(FILE *fd_in) {
    if (!fd_in)
        return false;

    if (raw_data_)
        delete[] raw_data_;
    raw_data_ = new char[length_];
    return (fread(raw_data_, length_, fd_in) == length_);
}

bool BrcProtocol::Send(FILE *fd_out) const {
    if (!fd_out|| !raw_data_ || !length_)
        return false;
    return (fwrite(raw_data_, length_, fd_out) == length_);
}

const unsigned int BrcProtocol::token_length() const {
    return TokenGenerator::GetTokenLength();
}

const unsigned int BrcProtocol::data_length() const {
    return length_ - TokenGenerator::GetTokenLength();
}

const char *BrcProtocol::token() const {
    if (!raw_data_)
        return (char *)NULL;
    return &raw_data_[0];
}

const char *BrcProtocol::data() const {
    if (!raw_data_)
        return (char *)NULL;
    return &raw_data_[TokenGenerator::GetTokenLength()];
}

void BrcProtocol::DebugPrintProtocol() const {
    print_byte_array(raw_data_, length_);
}

void BrcProtocol::set_token() {
    const char *token = TokenGenerator::GetToken();
    memcpy(raw_data_, token, TokenGenerator::GetTokenLength());
}

