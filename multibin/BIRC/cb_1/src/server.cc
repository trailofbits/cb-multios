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

#include <cstdlib.h>
#include <cstdio.h>
#include <cstring.h>
#include "brc_packet.h"
#include "brc_response.h"
#include "brc_command.h"
#include "brc_chat.h"
#include "debug_brc.h"
#include "command_processor.h"
#include "server_backend.h"

#define CLIENT_FD 3
#define SERVER_FD 4

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    Backend::InitDataStores(secret_page_i);
    FILE *cb_c_in = fopen(CLIENT_FD, 0);
    FILE *cb_c_out = fopen(CLIENT_FD, 1);
    char *secret_page = (char *)secret_page_i;
    (void) secret_page;

    PRINTF("Running server code\n");
    BrcPacket *pkt = new BrcPacket(cb_c_in, cb_c_out);
    BrcResponse *resp;
    while (1) {
        int recvd_bytes = 0;
        int sent_bytes = 0;

        PRINTF("Trying to recv a packet\n");
        recvd_bytes = pkt->Recv();
        if (recvd_bytes == -1) {
            PRINTF("Error receiving packet\n");
            continue;
        } else if (recvd_bytes == -2) {
            PRINTF("EOF receiving packet\n");
            break;
        }

        PRINTF("Recv'd %d bytes\n", recvd_bytes);
        PRINTF("--- printing server packet ---\n");
        pkt->DebugPrintPacket();

        switch(pkt->protocol_id()) {
        case 2:
            PRINTF("Received a command from the client\n");
            resp = CommandProcessor::ServiceCommand((BrcCommand *)pkt->GetProtocol());
            break;
        case 4:
            PRINTF("Received a chat message from the client\n");
            resp = CommandProcessor::ServiceChat((BrcChat *)pkt->GetProtocol());
        case 8:
            PRINTF("Server doesn't accept responses messages\n");
            resp = (BrcResponse *)NULL;
            break;
        default:
            PRINTF("Invalid protocol id\n");
            resp = (BrcResponse *)NULL;
            break;
        }

        if (!resp) {
            PRINTF("Did not receive a valid response\n");
            continue;
        }
        pkt->ClearPacket();
        pkt->SetPacket(resp);
        PRINTF("Trying to send packet response\n");
        sent_bytes = pkt->Send();
        if (sent_bytes == -1) {
            PRINTF("Error sending packet\n");
            continue;
        }

        PRINTF("Sent %d bytes\n", sent_bytes);
        pkt->DebugPrintPacket();

        if (resp->response_code() == 1)
            break;
    }

    PRINTF("Exiting Server.....\n");
    delete pkt;
    return 0;
}
