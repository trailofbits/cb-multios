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

#include "cgc_cstdlib.h"
#include "cgc_cstdio.h"
#include "cgc_cstring.h"
#include "cgc_brc_packet.h"
#include "cgc_brc_response.h"
#include "cgc_brc_command.h"
#include "cgc_brc_chat.h"
#include "cgc_debug_brc.h"
#include "cgc_command_processor.h"
#include "cgc_server_backend.h"

#define CLIENT_FD_W 3
#define CLIENT_FD_R 4
#define SERVER_FD_W 5
#define SERVER_FD_R 6

extern "C" int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

    Backend::InitDataStores(secret_page_i);
    FILE *cb_c_in = cgc_fopen(SERVER_FD_R, 0);
    FILE *cb_c_out = cgc_fopen(CLIENT_FD_W, 1);
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
