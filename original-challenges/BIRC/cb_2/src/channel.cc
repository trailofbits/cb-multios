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
#include "channel.h"
#include <cstring.h>

#define MAX_LENGTH 64
#define ARRAY_LEN 128

Channel::Channel(const char *name, int name_length, User *creator)
    : admins_(ARRAY_LEN), users_(ARRAY_LEN), banned_users_(ARRAY_LEN), messages_(ARRAY_LEN) {
    name_length_ = name_length < MAX_LENGTH ? name_length : MAX_LENGTH;
    memcpy(name_, name, name_length);
    name_length_ = name_length;
    creator_ = creator;
    AddUserToChannel(creator_);
}

const char *Channel::name() {
    return name_;
}

const unsigned short Channel::name_length() {
    return name_length_;
}

User *Channel::creator() {
    return creator_;
}

bool Channel::IsAdmin(User *user) {
    for (int i = 0; i < admins_.length(); i++) {
        if (user->Equals(admins_.Get(i)))
            return true;
    }
    return false;
}

bool Channel::IsBanned(User *user) {
    for (int i = 0; i < banned_users_.length(); i++) {
        if (user->Equals(banned_users_.Get(i)))
            return true;
    }
    return false;
}

bool Channel::CompareName(const char *name, unsigned short length) {
    if (!name || name_length_ != length)
        return false;
    if (memcmp(name_, name, name_length_) != 0)
        return false;
    return true;
}

bool Channel::AddUserToAdmins(User *user) {
    if (IsBanned(user))
        return false;

    for (int i = 0; i < admins_.length(); i++) {
        if (user->Equals(admins_.Get(i)))
            return false;
    }
    return admins_.Append(user);
}

bool Channel::AddUserToChannel(User *user) {
    if (IsBanned(user))
        return false;

    for (int i = 0; i < users_.length(); i++) {
        if (user->Equals(users_.Get(i)))
            return false;
    }
    return users_.Append(user);
}

void Channel::AddChatToChannel(const Chat &chat) {
    messages_.ForceAppend(chat, &Chat().Delete);
}

bool Channel::RemoveUserFromChannel(User *user) {
    for (int i = 0; i < users_.length(); i++) {
        if (user->Equals(users_.Get(i)))
            users_.Remove(i, (void (*)(User **))NULL);
        return true;
    }
    return false;
}

bool Channel::RemoveUserAsAdmin(User *user) {
    for (int i = 0; i < admins_.length(); i++) {
        if (user->Equals(admins_.Get(i)))
            admins_.Remove(i, (void (*)(User **))NULL);
            return true;
    }
    return false;
}

bool Channel::FindUser(User *user) {
    for (int i = 0; i < users_.length(); i++) {
        if (user->Equals(users_.Get(i))) {
            return true;
        }
    }
    return false;
}

bool Channel::BanUser(User *user) {
    for (int i = 0; i < banned_users_.length(); i++) {
        if (user->Equals(banned_users_.Get(i))) {
            return true;
        }
    }

    RemoveUserFromChannel(user);
    RemoveUserAsAdmin(user);
    return banned_users_.Append(user);
}

bool Channel::RemoveBan(User *user) {
    for (int i = 0; i < banned_users_.length(); i++) {
        if (user->Equals(banned_users_.Get(i)))
            banned_users_.Remove(i, (void (*)(User **))NULL);
        return true;
    }
    return false;
}

void Channel::DeleteChannel() {
    admins_.DeleteArray((void (*)(User **))NULL);
    users_.DeleteArray((void (*)(User **))NULL);
    messages_.DeleteArray(&Chat().Delete);
}

User **Channel::GetUserList(unsigned short *num_users) {
    *num_users = users_.length();
    return users_.data();
}
