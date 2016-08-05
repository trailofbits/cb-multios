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
#ifndef BRC_PACKET_H_
#define BRC_PACKET_H_
#include <stdio.h>
#include "brc_protocol.h"

class BrcPacket {
  public:
    BrcPacket(FILE *fd_in, FILE *fd_out);
    ~BrcPacket();

    int Recv();
    int Send() const;
    bool SetPacket(BrcProtocol *brc_msg);
    const BrcProtocol *GetProtocol() const;
    void ClearPacket();
    const unsigned short protocol_id() const;
    void DebugPrintPacket() const;

  private:
    bool IsValidProtocolId() const;
    bool IsValidPacket() const;
    unsigned int CalcChecksum() const;
    BrcProtocol *MatchRecvdProtocol() const;

    FILE *fd_in_;
    FILE *fd_out_;
    unsigned short protocol_id_;
    unsigned short length_;
    BrcProtocol *brc_msg_;
    unsigned int checksum_;
};

#endif /* BRC_PACKET_H_ */


