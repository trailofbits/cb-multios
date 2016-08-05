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
#include "user.h"

#include <cstring.h>
#define MAX_LENGTH 64
#define MAX_CHAN_SIZE 128
#define MAX_MSG_SIZE 100
#define MAX_BLOCKED_USERS 100

User::User()
    : joined_channels_(MAX_CHAN_SIZE), direct_msgs_(MAX_MSG_SIZE),
        blocked_users_(MAX_BLOCKED_USERS) {
    name_length_ = 0;
    pass_length_ = 0;
}

User::User(const char *name, const unsigned short name_length, const char *pass, const unsigned short pass_length)
    : joined_channels_(MAX_CHAN_SIZE), direct_msgs_(MAX_MSG_SIZE),
        blocked_users_(MAX_BLOCKED_USERS) {
    InitUser(name, name_length, pass, pass_length);
}


void User::InitUser(const char *name, const unsigned short name_length, const char *pass, const unsigned short pass_length) {
    name_length_ = name_length < MAX_LENGTH ? name_length : MAX_LENGTH;
    memcpy(name_, name, name_length_);
    pass_length_ = pass_length < MAX_LENGTH ? pass_length : MAX_LENGTH;
    memcpy(pass_, pass, pass_length_);
}

bool User::Equals(User *user) const {
    if (name_length_ != user->name_length())
        return false;
    if (memcmp(name_, user->name(), name_length_) != 0)
        return false;
    return true;
}

bool User::CompareName(const char *name, unsigned short length) const {
    if (!name || name_length_ != length)
        return false;
    if (memcmp(name_, name, name_length_) != 0)
        return false;
    return true;
}

bool User::VerifyPass(const char *pass, unsigned short length) const {
    if (!pass || pass_length_ != length)
        return false;
    if (memcmp(pass_, pass, pass_length_) != 0)
        return false;
    return true;
}

bool User::BlockUser(User *user) {
    for (int i = 0; i < blocked_users_.length(); i++) {
        if (user->Equals(blocked_users_.Get(i))) {
            return true;
        }
    }

    return blocked_users_.Append(user);
}

bool User::UnblockUser(User *user) {
    for (int i = 0; i < blocked_users_.length(); i++) {
        if (user->Equals(blocked_users_.Get(i)))
            blocked_users_.Remove(i, (void (*)(User **))NULL);
        return true;
    }
    return false;
}

void User::Delete(User **puser) {
    User *user = *puser;
    Conversation *convo;
    for (int i = 0; i < user->joined_channels_.length(); i++) {
        convo = user->joined_channels_.Get(i);
        convo->ClearChatMessages();
    }
    for (int i = 0; i < user->direct_msgs_.length(); i++) {
        convo = user->direct_msgs_.Get(i);
        convo->ClearChatMessages();
    }

    user->joined_channels_.DeleteArray((void (*)(Conversation **))NULL);
    user->direct_msgs_.DeleteArray((void (*)(Conversation **))NULL);
    user->blocked_users_.DeleteArray((void (*)(User **))NULL);
}

void User::DeleteStatic(User *user) {
    Conversation *convo;
    for (int i = 0; i < user->joined_channels_.length(); i++) {
        convo = user->joined_channels_.Get(i);
        convo->ClearChatMessages();
    }
    for (int i = 0; i < user->direct_msgs_.length(); i++) {
        convo = user->direct_msgs_.Get(i);
        convo->ClearChatMessages();
    }

    user->joined_channels_.DeleteArray((void (*)(Conversation **))NULL);
    user->direct_msgs_.DeleteArray((void (*)(Conversation **))NULL);
    user->blocked_users_.DeleteArray((void (*)(User **))NULL);
}

bool User::AddChannelConversation(Conversation *convo) {
    return joined_channels_.Append(convo);
}

bool User::AddUserConversation(Conversation *convo) {
    return direct_msgs_.Append(convo);
}


const char *User::name() {
    return &name_[0];
}

void User::set_name(const char *name, const unsigned short name_length) {
    name_length_ = name_length < MAX_LENGTH ? name_length : MAX_LENGTH;
    memcpy(name_, name, name_length_);
}

const unsigned short User::name_length() {
    return name_length_;
}

const char *User::pass() {
    return &pass_[0];
}

void User::set_pass(const char *pass, const unsigned short pass_length) {
    pass_length_ = pass_length < MAX_LENGTH ? pass_length : MAX_LENGTH;
    memcpy(pass_, pass, pass_length_);
}

const unsigned short User::pass_length() {
    return pass_length_;
}

