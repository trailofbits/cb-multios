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
#include <cstring.h>
#include <cstdio.h>
#include "brc_default_codes.h"
#include "brc_packet.h"
#include "client_commands.h"
#include "serialize.h"
#include "deserialize.h"
#include "debug_brc.h"

/* COMMAND STRUCTURE:
     2 bytes:  cmd_code_length N
     N bytes:  command_code
     2 bytes:  param1 length P1
     P1 bytes: param1
     2 bytes:  param2 length P2
     P2 bytes: param2
        .
        .
     PN bytes: paramN
     2 bytes: \x00\x00      \\end of message
*/

namespace {
    FILE *g_fd_in;
    FILE *g_fd_out;

void HandleChatPacket(BrcPacket *pkt) {
    pkt->ClearPacket();
}

bool ReceiveServerResponse(BrcPacket *pkt) {
    int recvd_bytes = 0;
    if (!pkt)
        return false;

    pkt->ClearPacket();
    do {
        PRINTF("Trying to recv a response packet\n");
        recvd_bytes = pkt->Recv();
        if (recvd_bytes == -1) {
            PRINTF("Error receiving packet\n");
            return false;
        }
        PRINTF("Recv'd %d bytes\n", recvd_bytes);

        if (pkt->protocol_id() == 4) {
            PRINTF("Received new chat message!\n");
            HandleChatPacket(pkt);
        } else if (pkt->protocol_id() == 8) {
            PRINTF("Received server response\n");
            pkt->DebugPrintPacket();
        } else {
            PRINTF("Unexpected Server Message. Ending Communication\n");
            return false;
        }
    } while (pkt->protocol_id() != 8);

    return true;
}

}

namespace BrcClient {

void InitServerFd(FILE *fd_in, FILE *fd_out) {
    g_fd_in = fd_in;
    g_fd_out = fd_out;
}

User *RegisterUser(const char *name, unsigned short name_length) {
    int sent_bytes = 0;
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;
    User *user = (User *)NULL;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::register_code()));
    ADD_LENGTH(cmd_length, name_length);
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;

    APPEND_PARAM(pcmd, BrcGlobals::register_code(), sizeof(BrcGlobals::register_code()));
    APPEND_PARAM(pcmd, name, name_length);
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand(name, cmd, name_length, cmd_length);
    pkt->SetPacket(bcmd);

    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    if (brc_resp->response_code() != GET_PASSWORD_ID) {
        PRINTF("Received a failure response trying to set new user\n");
        goto finish;
    }

    user = new User(name, name_length, brc_resp->msg(), brc_resp->msg_length());
finish:
    delete pkt;
    delete[] cmd;
    return user;
}

bool SearchForUser(const char *user_name, unsigned short user_length) {
    int sent_bytes = 0;
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::check_user_code()));
    ADD_LENGTH(cmd_length, user_length);
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;
    bool success = false;

    APPEND_PARAM(pcmd, BrcGlobals::check_user_code(), sizeof(BrcGlobals::check_user_code()));
    APPEND_PARAM(pcmd, user_name, user_length);
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand((char *)"", cmd, sizeof(""), cmd_length);
    pkt->SetPacket(bcmd);

    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    if (brc_resp->response_code() != OK_ID) {
        PRINTF("Could not find user on server\n");
        goto finish;
    }

    success = true;
finish:
    delete pkt;
    delete[] cmd;
    return success;
}

bool VerifyPassword(User *user, const char *pass, unsigned short pass_length) {
    int sent_bytes = 0;
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::verify_password_code()));
    ADD_LENGTH(cmd_length, user->name_length());
    ADD_LENGTH(cmd_length, pass_length);
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;
    bool success = false;

    APPEND_PARAM(pcmd, BrcGlobals::verify_password_code(), sizeof(BrcGlobals::verify_password_code()));
    APPEND_PARAM(pcmd, user->name(), user->name_length());
    APPEND_PARAM(pcmd, pass, pass_length);
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand(user->name(), cmd, user->name_length(), cmd_length);
    pkt->SetPacket(bcmd);

    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    if (brc_resp->response_code() != OK_ID) {
        PRINTF("Passwords did not match\n");
        goto finish;
    }

    success = true;
finish:
    delete pkt;
    delete[] cmd;
    return success;
}

bool DeleteUser(User *user, const char *pass, unsigned short pass_length) {
    int sent_bytes = 0;
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::delete_user_code()));
    ADD_LENGTH(cmd_length, user->name_length());
    ADD_LENGTH(cmd_length, pass_length);
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;
    bool success = false;


    APPEND_PARAM(pcmd, BrcGlobals::delete_user_code(), sizeof(BrcGlobals::delete_user_code()));
    APPEND_PARAM(pcmd, user->name(), user->name_length());
    APPEND_PARAM(pcmd, pass, pass_length);
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand(user->name(), cmd, user->name_length(), cmd_length);
    pkt->SetPacket(bcmd);

    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    if (brc_resp->response_code() != OK_ID) {
        PRINTF("Could not delete user\n");
        goto finish;
    }

    success = true;
finish:
    delete pkt;
    delete[] cmd;
    return success;
}

bool JoinChannel(User *user, const char *chan_name, unsigned short chan_length) {
    int sent_bytes = 0;
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::join_channel_code()));
    ADD_LENGTH(cmd_length, user->name_length());
    ADD_LENGTH(cmd_length, user->pass_length());
    ADD_LENGTH(cmd_length, chan_length);
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;
    bool success = false;

    APPEND_PARAM(pcmd, BrcGlobals::join_channel_code(), sizeof(BrcGlobals::join_channel_code()));
    APPEND_PARAM(pcmd, user->name(), user->name_length());
    APPEND_PARAM(pcmd, user->pass(), user->pass_length());
    APPEND_PARAM(pcmd, chan_name, chan_length);
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand(user->name(), cmd, user->name_length(), cmd_length);
    pkt->SetPacket(bcmd);

    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    if (brc_resp->response_code() != OK_ID) {
        PRINTF("Received a failure response trying to join channel\n");
        goto finish;
    }

    success = true;
finish:
    delete pkt;
    delete[] cmd;
    return success;
}

bool SearchForChannel(const char *chan_name, unsigned short chan_length) {
    int sent_bytes = 0;
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::check_channel_code()));
    ADD_LENGTH(cmd_length, chan_length);
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;
    bool success = false;

    APPEND_PARAM(pcmd, BrcGlobals::check_channel_code(), sizeof(BrcGlobals::check_channel_code()));
    APPEND_PARAM(pcmd, chan_name, chan_length);
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand((char *)"", cmd, sizeof(""), cmd_length);
    pkt->SetPacket(bcmd);

    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    if (brc_resp->response_code() != OK_ID) {
        PRINTF("Could not find channel on server\n");
        goto finish;
    }

    success = true;
finish:
    delete pkt;
    delete[] cmd;
    return success;
}

bool PartChannel(User *user, const char *chan_name, unsigned short chan_length) {
    int sent_bytes = 0;
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::part_channel_code()));
    ADD_LENGTH(cmd_length, user->name_length());
    ADD_LENGTH(cmd_length, user->pass_length());
    ADD_LENGTH(cmd_length, chan_length);
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;
    bool success = false;

    APPEND_PARAM(pcmd, BrcGlobals::part_channel_code(), sizeof(BrcGlobals::part_channel_code()));
    APPEND_PARAM(pcmd, user->name(), user->name_length());
    APPEND_PARAM(pcmd, user->pass(), user->pass_length());
    APPEND_PARAM(pcmd, chan_name, chan_length);
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand(user->name(), cmd, user->name_length(), cmd_length);
    pkt->SetPacket(bcmd);

    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    if (brc_resp->response_code() != OK_ID) {
        PRINTF("Received a failure response trying to part from a channel\n");
        goto finish;
    }

    success = true;
finish:
    delete pkt;
    delete[] cmd;
    return success;
}


bool DeleteChannel(User *user, const char *chan_name, unsigned short chan_length) {
    int sent_bytes = 0;
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::delete_channel_code()));
    ADD_LENGTH(cmd_length, user->name_length());
    ADD_LENGTH(cmd_length, user->pass_length());
    ADD_LENGTH(cmd_length, chan_length);
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;
    bool success = false;

    APPEND_PARAM(pcmd, BrcGlobals::delete_channel_code(), sizeof(BrcGlobals::delete_channel_code()));
    APPEND_PARAM(pcmd, user->name(), user->name_length());
    APPEND_PARAM(pcmd, user->pass(), user->pass_length());
    APPEND_PARAM(pcmd, chan_name, chan_length);
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand(user->name(), cmd, user->name_length(), cmd_length);
    pkt->SetPacket(bcmd);

    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    if (brc_resp->response_code() != OK_ID) {
        PRINTF("Received a failure response trying to delete channel\n");
        goto finish;
    }

    success = true;
finish:
    delete pkt;
    delete[] cmd;
    return success;
}

bool ChannelChat(User *user, const char *chan_name, unsigned short chan_length, const char *chat_msg, unsigned short chat_length) {
    int sent_bytes = 0;
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::channel_chat_code()));
    ADD_LENGTH(cmd_length, user->name_length());
    ADD_LENGTH(cmd_length, user->pass_length());
    ADD_LENGTH(cmd_length, chan_length);
    ADD_LENGTH(cmd_length, chat_length);
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;
    bool success = false;

    APPEND_PARAM(pcmd, BrcGlobals::channel_chat_code(), sizeof(BrcGlobals::channel_chat_code()));
    APPEND_PARAM(pcmd, user->name(), user->name_length());
    APPEND_PARAM(pcmd, user->pass(), user->pass_length());
    APPEND_PARAM(pcmd, chan_name, chan_length);
    APPEND_PARAM(pcmd, chat_msg, chat_length);
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand(user->name(), cmd, user->name_length(), cmd_length);
    pkt->SetPacket(bcmd);

    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    if (brc_resp->response_code() != OK_ID) {
        PRINTF("Received a failure response trying to delete channel\n");
        goto finish;
    }

    success = true;
finish:
    delete pkt;
    delete[] cmd;
    return success;
}


bool UserChat(User *user, const char *recp_name, unsigned short recp_length, const char *chat_msg, unsigned short chat_length) {
    int sent_bytes = 0;
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::user_chat_code()));
    ADD_LENGTH(cmd_length, user->name_length());
    ADD_LENGTH(cmd_length, user->pass_length());
    ADD_LENGTH(cmd_length, recp_length);
    ADD_LENGTH(cmd_length, chat_length);
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;
    bool success = false;

    APPEND_PARAM(pcmd, BrcGlobals::user_chat_code(), sizeof(BrcGlobals::user_chat_code()));
    APPEND_PARAM(pcmd, user->name(), user->name_length());
    APPEND_PARAM(pcmd, user->pass(), user->pass_length());
    APPEND_PARAM(pcmd, recp_name, recp_length);
    APPEND_PARAM(pcmd, chat_msg, chat_length);
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand(user->name(), cmd, user->name_length(), cmd_length);
    pkt->SetPacket(bcmd);

    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    if (brc_resp->response_code() != OK_ID) {
        PRINTF("Received a failure response trying to delete channel\n");
        goto finish;
    }

    success = true;
finish:
    delete pkt;
    delete[] cmd;
    return success;
}

bool ExitServer() {
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;
    bool exitted = false;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::server_exit_code()));
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;

    APPEND_PARAM(pcmd, BrcGlobals::server_exit_code(), sizeof(BrcGlobals::server_exit_code()));
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand((char *)"", cmd, sizeof(""), cmd_length);
    pkt->SetPacket(bcmd);

    int sent_bytes = 0;
    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    pcmd = (char *)brc_resp->msg();
    if (brc_resp->response_code() != EXIT_SERVER_ID) {
        PRINTF("Received a failure response trying to exit\n");
        goto finish;
    }
    exitted = true;

finish:
    delete pkt;
    delete[] cmd;
    return exitted;
}

bool RemoteAdminTokenRequest(User *user, unsigned short page_idx, int *token) {
    int sent_bytes = 0;
    BrcPacket *pkt = new BrcPacket(g_fd_in, g_fd_out);
    BrcResponse *brc_resp = (BrcResponse *)NULL;

    unsigned short cmd_length = 0;
    ADD_LENGTH(cmd_length, sizeof(BrcGlobals::remote_admin_token_request_code()));
    ADD_LENGTH(cmd_length, user->name_length());
    cmd_length += sizeof(page_idx);
    ADD_EOM_LENGTH(cmd_length);
    char *cmd = new char[cmd_length];
    char *pcmd = cmd;
    bool success = false;

    APPEND_PARAM(pcmd, BrcGlobals::remote_admin_token_request_code(), sizeof(BrcGlobals::remote_admin_token_request_code()));
    APPEND_PARAM(pcmd, user->name(), user->name_length());
    memcpy(pcmd, &page_idx, sizeof(page_idx));
    pcmd += sizeof(page_idx);
    APPEND_EOM(pcmd);
    BrcCommand *bcmd = new BrcCommand(user->name(), cmd, user->name_length(), cmd_length);
    pkt->SetPacket(bcmd);

    PRINTF("Trying to send a command packet\n");
    sent_bytes = pkt->Send();
    if (sent_bytes == -1) {
        PRINTF("Error sending packet\n");
        goto finish;
    }
    PRINTF("Sent %d bytes\n", sent_bytes);
    PRINTF(" --- printing client packet --- \n");
    pkt->DebugPrintPacket();

    if (!ReceiveServerResponse(pkt)) {
        PRINTF("BAD SERVER RESPONSE\n");
        goto finish;
    }

    brc_resp = (BrcResponse *)pkt->GetProtocol();
    if (brc_resp->response_code() != GET_REMOTE_TOKEN_ID) {
        PRINTF("Received a failure response trying to delete channel\n");
        goto finish;
    }

    memcpy(token, brc_resp->msg(), sizeof(*token));
    success = true;
finish:
    delete pkt;
    delete[] cmd;
    return success;
}

}
