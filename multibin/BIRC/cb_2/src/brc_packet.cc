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
#include "brc_packet.h"
#include "brc_command.h"
#include "brc_chat.h"
#include "brc_response.h"
#include "debug_brc.h"

#define MAGIC_SIZE 6
#define MAX_MSG_LEN (1024 * 32)
#define MAGIC { 86, 41, 137, 206, 115, 196 }

namespace {
    const unsigned char magic[] = MAGIC;
}


BrcPacket::BrcPacket(FILE *fd_in, FILE *fd_out) {
    if (fd_in) {
        fd_in_ = fd_in;
        fbuffered(fd_in_, 0);
    }

    if (fd_out) {
        fd_out_ = fd_out;
        fbuffered(fd_out_, 0);
    }

    protocol_id_ = -1;
    length_ = 0;
    brc_msg_ = (BrcProtocol *)NULL;
    checksum_ = 0;
}

BrcPacket::~BrcPacket() {
    fd_in_ = (FILE *)NULL;
    fd_out_ = (FILE *)NULL;
    ClearPacket();
}

int BrcPacket::Recv() {
    if (!fd_in_)
        goto error;

    for (int i = 0; i < MAGIC_SIZE; i++) {
        unsigned char m;
        fread(&m, 1, fd_in_);

        if (m != magic[i])
            goto error;
    }
    fread(&protocol_id_, sizeof(protocol_id_), fd_in_);
    if (!IsValidProtocolId())
        goto error;
    fread(&length_, sizeof(length_), fd_in_);
    if (length_ > MAX_MSG_LEN)
        goto error;
    brc_msg_ = MatchRecvdProtocol();
    if (!brc_msg_->Recv(fd_in_))
        goto error;
    fread(&checksum_, sizeof(checksum_), fd_in_);
    if (checksum_ != CalcChecksum())
        goto error;

    return (sizeof(magic) + sizeof(protocol_id_) + sizeof(length_) + length_ + sizeof(checksum_));

error:
    ClearPacket();
    return -1;
}

int BrcPacket::Send() const {
    const unsigned char magic[] = MAGIC;
    if (!IsValidPacket())
        goto error;

    if (fwrite(magic, sizeof(magic), fd_out_) != sizeof(magic))
        goto error;
    if (fwrite(&protocol_id_, sizeof(protocol_id_), fd_out_) != sizeof(protocol_id_))
        goto error;
    if (fwrite(&length_, sizeof(length_), fd_out_) != sizeof(length_))
        goto error;
    if (!brc_msg_->Send(fd_out_))
        goto error;
    if (fwrite(&checksum_, sizeof(checksum_), fd_out_) != sizeof(checksum_))
        goto error;

    return (sizeof(magic) + sizeof(protocol_id_) + sizeof(length_) + length_ + sizeof(checksum_));

error:
    return -1;
}

bool BrcPacket::SetPacket(BrcProtocol *brc_msg) {
    if (!brc_msg)
        return false;

    protocol_id_ = (unsigned int) brc_msg->protocol_id();
    length_ = (unsigned int) brc_msg->token_length() + (unsigned int) brc_msg->data_length();
    brc_msg_ = brc_msg;
    checksum_ = CalcChecksum();
    return true;
}

const BrcProtocol *BrcPacket::GetProtocol() const {
    return brc_msg_;
}

void BrcPacket::ClearPacket() {
    protocol_id_ = -1;
    length_ = 0;
    if (brc_msg_) {
        delete brc_msg_;
        brc_msg_ = (BrcProtocol *)NULL;
    }
    checksum_ = 0;
}

const unsigned short BrcPacket::protocol_id() const {
    return protocol_id_;
}

void BrcPacket::DebugPrintPacket() const {
    const unsigned char magic[] = MAGIC;
#ifdef SERVER
    PRINTF("SERVER PACKET DEBUG:\n");
#endif
#ifdef CLIENT
    PRINTF("CLIENT PACKET DEBUG:\n");
#endif
    PRINTF("Magic: ");
    for (int i = 0; i < sizeof(magic); i++)
        _PRINTF("0x%02x ", magic[i]);
    _PRINTF("\n");
    PRINTF("Protocol Id: %d\n", protocol_id_);
    PRINTF("Length     : %d\n", length_);
    PRINTF("-Printing Protocol-\n");
    brc_msg_->DebugPrintProtocol();
    PRINTF("\n");
    PRINTF("Checksum   : %d\n", checksum_);
    PRINTF("\n");
}

bool BrcPacket::IsValidProtocolId() const {
    return (
        protocol_id_ != 2 ||
        protocol_id_ != 4 ||
        protocol_id_ != 8
    );
}

bool BrcPacket::IsValidPacket() const {
   return (
        IsValidProtocolId() &&
        length_ < MAX_MSG_LEN &&
        brc_msg_
    );
}

unsigned int BrcPacket::CalcChecksum() const {
    if (!brc_msg_)
        return 0;

    char *pbytes;
    const char *token = brc_msg_->token();
    const char *data = brc_msg_->data();
    const unsigned char magic[] = MAGIC;
    if (!data)
        return 0;

    unsigned int checksum =  0;
    pbytes = (char *)magic;
    for (int i = 0; i < MAGIC_SIZE; i++)
        checksum += pbytes[i];
    pbytes = (char *)&protocol_id_;
    for (int i = 0; i < sizeof(protocol_id_); i++)
        checksum += pbytes[i];
    pbytes = (char *)&length_;
    for (int i = 0; i < sizeof(length_); i++)
        checksum += pbytes[i];
    pbytes = (char *)token;
    for (int i = 0; i < brc_msg_->token_length(); i++)
        checksum += pbytes[i];
    pbytes = (char *)data;
    for (int i = 0; i < brc_msg_->data_length(); i++)
        checksum += pbytes[i];

    return ((unsigned int) ~checksum);
}

BrcProtocol *BrcPacket::MatchRecvdProtocol() const {
    switch(protocol_id_) {
    case 2:
        return new BrcCommand(length_);
    case 4:
        return new BrcChat(length_);
    case 8:
        return new BrcResponse(length_);
    default:
        return (BrcProtocol *)NULL;
    }
}

