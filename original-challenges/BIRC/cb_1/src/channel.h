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
#ifndef CHANNEL_H_
#define CHANNEL_H_

#define CHAN_MAX_LENGTH 64

#include "array_wrapper.h"
#include "user.h"
#include "chat.h"

class User;
class Chat;

class Channel {
  public:
    Channel(const char *name, int name_length, User *creator);
    const char *name();
    const unsigned short name_length();
    User *creator();
    bool IsAdmin(User *user);
    bool IsBanned(User *user);
    bool CompareName(const char *name, unsigned short length);
    bool AddUserToAdmins(User *user);
    bool AddUserToChannel(User *user);
    void AddChatToChannel(const Chat &chat);
    bool RemoveUserFromChannel(User *user);
    bool RemoveUserAsAdmin(User *user);
    bool FindUser(User *user);
    bool BanUser(User *user);
    bool RemoveBan(User *user);
    void DeleteChannel();
    User **GetUserList(unsigned short *num_users);
  private:
    char name_[CHAN_MAX_LENGTH];
    unsigned short name_length_;
    User *creator_;
    ArrayWrapper<User *> admins_;
    ArrayWrapper<User *> users_;
    ArrayWrapper<User *> banned_users_;
    ArrayWrapper<Chat> messages_;
};

#undef CHAN_MAX_LENGTH

#endif /* CHANNEL_H_ */
