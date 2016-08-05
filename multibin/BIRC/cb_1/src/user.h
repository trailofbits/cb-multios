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
#ifndef USER_H_
#define USER_H_

#define USER_MAX_LENGTH 64

#include "array_wrapper.h"
#include "channel.h"
#include "conversation.h"

class Conversation;
class Channel;

class User {
  public:
    User(const char *name, const unsigned short name_length, const char *pass,
            const unsigned short pass_length, const bool is_admin);
    const bool IsAdmin();
    bool Equals(User *user) const;
    bool CompareName(const char *name, unsigned short length) const;
    bool VerifyPass(const char *pass, unsigned short length) const;
    bool BlockUser(User *user);
    bool UnblockUser(User *user);
    static void Delete(User **puser);
    bool AddChannelConversation(Conversation *convo);
    bool AddUserConversation(Conversation *convo);

    const char *name();
    void set_name(const char *name, const unsigned short name_length);
    const unsigned short name_length();
    const char *pass();
    void set_pass(const char *pass, const unsigned short pass_length);
    const unsigned short pass_length();


  private:
    char name_[USER_MAX_LENGTH];
    unsigned short name_length_;
    char pass_[USER_MAX_LENGTH];
    unsigned short pass_length_;
    bool is_admin_;
    ArrayWrapper<Conversation *> joined_channels_;
    ArrayWrapper<Conversation *> direct_msgs_;
    ArrayWrapper<User *> blocked_users_;
};

#undef USER_MAX_LENGTH

#endif /*USER_H_*/
