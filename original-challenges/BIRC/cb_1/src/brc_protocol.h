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
#ifndef BRC_PROTOCOL_H_
#define BRC_PROTOCOL_H_

#include <stdio.h>

class BrcProtocol {
  public:
    BrcProtocol(unsigned short recv_length);
    BrcProtocol(char *data, unsigned short data_length);
    virtual ~BrcProtocol();

    virtual bool Recv(FILE *fd_in);
    virtual bool Send(FILE *fd_out) const;
    virtual const unsigned int protocol_id() const = 0;

    const unsigned int token_length() const;
    const unsigned int data_length() const;
    const char *token() const;
    const char *data() const;
    void DebugPrintProtocol() const;
  protected:
    void set_token();
    unsigned short length_; //does not include checksum
    char *raw_data_;
};


#endif /* BRC_PROTOCOL_H_ */

