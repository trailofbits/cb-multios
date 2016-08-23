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
#ifndef SERVER_BACKEND_H_
#define SERVER_BACKEND_H_
#include "user.h"

namespace Backend {

void InitDataStores(int secret_page_i);

char *AddUser(const char *name, unsigned short length, unsigned short *pass_length);
bool CheckIfUserExists(const char *name, unsigned short length);
bool VerifyPassword(const char *name, unsigned short name_length, const char *pass, unsigned short pass_length);
bool DeleteUser(const char *name, unsigned short name_length, const char *pass, unsigned short pass_length);

bool JoinChannel(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                    const char *chan_name, unsigned short chan_length);
bool CheckIfChannelExists(const char *name, unsigned short length);
bool CheckIfUserJoinedChannel(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                        const char *chan_name, unsigned short chan_length);
User *GetChannelUsers(const char *chan_name, unsigned short length);
bool PartChannel(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                    const char *chan_name, unsigned short chan_length);
bool DeleteChannel(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                    const char *chan_name, unsigned short chan_length);
bool AddChannelAdmin(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                    const char *admin_name, unsigned short admin_name_length);
char *GeneratePassword(unsigned short *new_pass_len);

void DebugPrintUsers();
void DebugPrintChannels();

}

namespace AdminTasks {

bool RemoteAdminTokenRequest(char *auth_val, unsigned int auth_val_length, unsigned short page_idx, int *token);

}

#endif /* SERVER_BACKEND_H_ */
