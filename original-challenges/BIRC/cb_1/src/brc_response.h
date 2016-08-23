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
#ifndef BRC_RESPONSE_H_
#define BRC_RESPONSE_H_
#include "brc_protocol.h"

class BrcResponse: public BrcProtocol {
  public:
    BrcResponse(unsigned short recv_length);
    BrcResponse(short response_code, char *msg, unsigned short msg_len);
    ~BrcResponse();

    virtual bool Recv(FILE *fd_in);

    virtual const unsigned int protocol_id() const;
    const int server_addr() const;
    const unsigned short response_code() const;
    const unsigned short msg_length() const;
    const char *msg() const;
  private:
    void set_server_addr();
    int server_addr_;
    short response_code_;
    unsigned short msg_length_;
};

#endif /* BRCP_RESPONSE_H_ */
