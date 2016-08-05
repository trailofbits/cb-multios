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
#ifndef CLIENT_COMMANDS_H_
#define CLIENT_COMMANDS_H_

#define REGISTER_USER_CMD_ID 11382
#define SEARCH_FOR_USER_CMD_ID 11591
#define DELETE_USER_CMD_ID 11498
#define JOIN_CHANNEL_CMD_ID 22193
#define SEARCH_FOR_CHANNEL_CMD_ID 2201
#define PART_CHANNEL_CMD_ID 22881
#define DELETE_CHANNEL_CMD_ID 22117
#define CHANNEL_CHAT_CMD_ID 3190
#define USER_CHAT_CMD_ID 31900
#define EXIT_SERVER_CMD_ID 9999
#define REMOTE_ADMIN_TOKEN_REQUEST_CMD_ID 7777

#include <cstdio.h>
#include "brc_command.h"
#include "user.h"

namespace BrcClient {

//Server Interactions
void InitServerFd(FILE *fd_in, FILE *fd_out);
User *RegisterUser(const char *name, unsigned short length);
bool SearchForUser(const char *user_name, unsigned short user_length);
bool VerifyPassword(User *user, const char *pass, unsigned short pass_length);
bool DeleteUser(User *user, const char *pass, unsigned short pass_length);
bool JoinChannel(User *user, const char *chan_name, unsigned short chan_length);
bool SearchForChannel(const char *chan_name, unsigned short chan_length);
bool PartChannel(User *user, const char *chan_name, unsigned short chan_length);
bool DeleteChannel(User *user, const char *chan_name, unsigned short chan_length);
bool ChannelChat(User *user, const char *chan_name, unsigned short chan_length, const char *chat_msg, unsigned short chat_length);
bool UserChat(User *user, const char *recp_name, unsigned short recp_length, const char *chat_msg, unsigned short chat_length);
bool ExitServer();
bool RemoteAdminTokenRequest(User *user, unsigned short page_idx, int *token);

}

#endif /* CLIENT_COMMANDS_H_ */
