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
#include "brc_chat.h"

BrcChat::BrcChat(unsigned short recv_length)
    : BrcProtocol(recv_length), chat_type_(-1), sender_name_len_(0),
      recipient_name_len_(0), chat_msg_len_(0) {
}

BrcChat::BrcChat(char *sender_name, char *recp_name, char *chat_msg, short chat_type,
        unsigned short sender_name_length, unsigned short recp_name_length,
        unsigned short chat_msg_length)
    : BrcProtocol(token_length() + sizeof(chat_type_) + sizeof(sender_name_len_) +
        sizeof(recipient_name_len_) + sizeof(chat_msg_len_) +
        sender_name_length + recp_name_length + chat_msg_length),
        chat_type_(chat_type), sender_name_len_(sender_name_length), recipient_name_len_(recp_name_length),
        chat_msg_len_(chat_msg_length) {
    raw_data_ = new char[length_];
    set_token();
    char *pdata = raw_data_ + token_length();
    memcpy(pdata, &chat_type, sizeof(chat_type));
    pdata += sizeof(chat_type);
    memcpy(pdata, &sender_name_length, sizeof(sender_name_length));
    pdata += sizeof(sender_name_length);
    memcpy(pdata, &recp_name_length, sizeof(recp_name_length));
    pdata += sizeof(recp_name_length);
    memcpy(pdata, &chat_msg_length, sizeof(chat_msg_length));
    pdata += sizeof(chat_msg_length);
    memcpy(pdata, sender_name, sender_name_length);
    pdata += sender_name_length;
    memcpy(pdata, recp_name, recp_name_length);
    pdata += recp_name_length;
    memcpy(pdata, chat_msg, chat_msg_length);
}

BrcChat::~BrcChat() {
    sender_name_len_ = 0;
    recipient_name_len_ = 0;
    chat_msg_len_ = 0;
}

bool BrcChat::Recv(FILE *fd_in) {
    if (!BrcProtocol::Recv(fd_in))
        return false;

    char *pdata  = raw_data_ + token_length();
    chat_type_ = *((short *)pdata);
    pdata += sizeof(chat_type_);
    sender_name_len_ = *((unsigned short *)pdata);
    pdata += sizeof(sender_name_len_);
    recipient_name_len_ = *((unsigned short *)pdata);
    pdata += sizeof(recipient_name_len_);
    chat_msg_len_ = *((unsigned short *)pdata);
    return true;

}

const unsigned int BrcChat::protocol_id() const {
    return 4;
}

const short BrcChat::chat_type() const {
    return chat_type_;
}

const unsigned short BrcChat::sender_name_length() const {
    return sender_name_len_;
}

const unsigned short BrcChat::recipient_name_length() const {
    return recipient_name_len_;
}

const unsigned short BrcChat::chat_msg_length() const {
    return chat_msg_len_;
}

const char *BrcChat::sender_name() const {
    char *pdata = raw_data_ + token_length();
    pdata += sizeof(chat_type_) + sizeof(sender_name_len_) + sizeof(recipient_name_len_) +
                sizeof(chat_msg_len_);
    return pdata;
}

const char *BrcChat::recp_name() const {
    char *pdata = raw_data_ + token_length();
    pdata += sizeof(chat_type_) + sizeof(sender_name_len_) + sizeof(recipient_name_len_) +
                sizeof(chat_msg_len_) + sender_name_len_;
    return pdata;
}

const char *BrcChat::chat_msg() const {
    char *pdata = raw_data_ + token_length();
    pdata += sizeof(chat_type_) + sizeof(sender_name_len_) + sizeof(recipient_name_len_) +
                sizeof(chat_msg_len_) + sender_name_len_ + recipient_name_len_;
    return pdata;
}

