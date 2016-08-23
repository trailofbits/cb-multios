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
#ifndef CLIENT_BACKEND_H_
#define CLIENT_BACKEND_H_
#include "user.h"

namespace Backend {

void InitDataStores(int secret_page_i);

bool CheckIfUserExists(const char *name, unsigned short length);
bool AddUser(User *user);
bool DeleteUser(User **puser, const char *pass, unsigned short pass_length);

bool CheckIfChannelExists(const char *name, unsigned short length);
bool JoinChannel(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                    const char *chan_name, unsigned short chan_length);
bool DeleteChannel(const char *chan_name, unsigned short chan_length, const char *user_name, unsigned short user_length,
                const char *pass, unsigned short pass_length);
bool AddChannelAdmin(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                    const char *admin_name, unsigned short admin_name_length);
bool VerifyPassword(const char *name, unsigned short name_length, const char *pass, unsigned short pass_length);

void DebugPrintUsers();
void DebugPrintChannels();

}

#endif /* CLIENT_BACKEND_H_ */
