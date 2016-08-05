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
#ifndef BRC_COMMAND_H_
#define BRC_COMMAND_H_

#include "brc_protocol.h"

class BrcCommand: public BrcProtocol {
  public:
      BrcCommand(unsigned short recv_length);
      BrcCommand(const char *username, const char *cmd, unsigned short username_len, unsigned short cmd_len);
      virtual ~BrcCommand();

      virtual bool Recv(FILE *fd_in);

      virtual const unsigned int protocol_id() const;
      const unsigned short username_length() const;
      const unsigned short cmd_length() const;
      const char *username() const;
      const char *cmd() const;
  private:
    unsigned short username_len_;
    unsigned short cmd_len_;
};

#endif /* BRC_COMMAND_H_ */
