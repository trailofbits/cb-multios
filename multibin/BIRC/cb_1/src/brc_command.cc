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
#include "brc_command.h"

BrcCommand::BrcCommand(unsigned short recv_length)
    : BrcProtocol(recv_length), username_len_(0), cmd_len_(0) {
}

BrcCommand::BrcCommand(const char *username, const char *cmd, unsigned short username_length, unsigned short cmd_length)
    : BrcProtocol(token_length() + sizeof(username_len_) + sizeof(cmd_len_) + username_length + cmd_length),
      username_len_(username_length), cmd_len_(cmd_length) {
    raw_data_ = new char[length_];
    set_token();

    char *pdata = raw_data_ + token_length();
    memcpy(pdata, &username_length, sizeof(username_length));
    pdata += sizeof(username_length);
    memcpy(pdata, &cmd_length, sizeof(cmd_length));
    pdata += sizeof(cmd_length);
    memcpy(pdata, username, username_length);
    pdata += username_length;
    memcpy(pdata, cmd, cmd_length);
}

BrcCommand::~BrcCommand() {
    username_len_ = 0;
    cmd_len_ = 0;
}

bool BrcCommand::Recv(FILE *fd_in) {
    if (!BrcProtocol::Recv(fd_in))
        return false;

    char *pdata  = raw_data_ + token_length();
    username_len_ = *((unsigned short *)pdata);
    pdata += sizeof(username_len_);
    cmd_len_ = *((unsigned short *)pdata);
    return true;
}

const unsigned int BrcCommand::protocol_id() const {
    return 2;
}

const unsigned short BrcCommand::username_length() const {
    return username_len_;
}

const unsigned short BrcCommand::cmd_length() const {
    return cmd_len_;
}

const char *BrcCommand::username() const {
    char *pdata = raw_data_ + token_length();
    pdata += sizeof(username_len_) + sizeof(cmd_len_);
    return pdata;
}

const char *BrcCommand::cmd() const {
    char *pdata = raw_data_ + token_length();
    pdata += sizeof(username_len_) + sizeof(cmd_len_) + username_len_;
    return pdata;
}

