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
#ifndef BRC_CHAT_H_
#define BRC_CHAT_H_
#include "brc_protocol.h"

class BrcChat: public BrcProtocol {
  public:
    BrcChat(unsigned short recv_length);
    BrcChat(char *sender_name, char *recp_name, char *chat_msg, short chat_type,
            unsigned short sender_name_length, unsigned short recp_name_length,
            unsigned short chat_msg_length);
    virtual ~BrcChat();

    virtual bool Recv(FILE *fd_in);

    virtual const unsigned int protocol_id() const;
    const short chat_type() const;
    const unsigned short sender_name_length() const;
    const unsigned short recipient_name_length() const;
    const unsigned short chat_msg_length() const;
    const char *sender_name() const;
    const char *recp_name() const;
    const char *chat_msg() const;

  private:
    short chat_type_;
    unsigned short sender_name_len_;
    unsigned short recipient_name_len_;
    unsigned short chat_msg_len_;
};

#endif /* BRC_CHAT_H_ */

