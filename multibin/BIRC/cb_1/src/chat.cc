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
#include "chat.h"

#include <cstring.h>

#define MAX_MSG_LENGTH 512

Chat::Chat() {
    msg_length_ = 0;
    msg_ = (char *)NULL;
    from_ = (User *)NULL;
}

Chat::Chat(char *msg, unsigned short msg_length, User *from) {
    msg_length_ = msg_length <= MAX_MSG_LENGTH ? msg_length : MAX_MSG_LENGTH;
    msg_ = new char[msg_length_];
    memcpy(msg_, msg, msg_length_);
    from_ = from;
}

void Chat::Delete(Chat *chat) {
    if (chat->msg_) {
        delete[] chat->msg_;
        chat->msg_ = (char *)NULL;
    }
    chat->msg_length_ = 0;
    chat->from_ = (User *)NULL;
}

const char *Chat::msg() {
    return msg_;
}

const unsigned short Chat::msg_length() {
    return msg_length_;
}

const User *Chat::from() {
    return from_;
}
