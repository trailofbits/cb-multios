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
#include <cstdio.h>
#include "server_backend.h"
#include "array_wrapper.h"
#include "user.h"
#include "debug_brc.h"
#include "brc_token.h"

#define MAX_ARRAY_SIZE 256

#define ADMIN_NAME {12, 34, 56, 78 }

namespace {

ArrayWrapper<User *> RegisteredUsers(MAX_ARRAY_SIZE);
ArrayWrapper<Channel *> RegisteredChannels(MAX_ARRAY_SIZE);
unsigned char g_admin_name[] = ADMIN_NAME;
const int *g_secret;
unsigned int prng1, prng2;

bool CheckIfAdmin(const char *name, unsigned short length) {
    User *user = RegisteredUsers.Get(0);
    return (user->CompareName(name, length));
}

bool CheckIfAdminToken(const char *token, unsigned short length) {
    if (length != TokenGenerator::GetTokenLength())
        return false;

    return (memcmp(TokenGenerator::GetToken(), token, length) == 0);
}


User *FindUser(const char *name, unsigned short length, int *idx) {
    for (int i = 1; i < RegisteredUsers.length(); i++) {
        User *user = RegisteredUsers.Get(i);
        if (user->CompareName(name, length)) {
            *idx = i;
            return user;
        }
    }

    *idx = -1;
    return (User *)NULL;
}


Channel *FindChannel(const char *name, unsigned short length, int *idx) {
    for (int i = 0; i < RegisteredChannels.length(); i++) {
        Channel *channel = RegisteredChannels.Get(i);
        if (channel->CompareName(name, length)) {
            *idx = i;
            return channel;
        }
    }

    *idx = -1;
    return (Channel *)NULL;
}

bool AddChannel(User *creator, const char *name, unsigned short length) {
    if (!creator || !name || !length)
        return false;

    if (!Backend::CheckIfChannelExists(name, length)) {
        RegisteredChannels.Append(new Channel(name, length, creator));
        return true;
    }
    return false;
}

}

namespace AdminTasks {

bool RemoteAdminTokenRequest(char *auth_val, unsigned int auth_val_length, unsigned short page_idx, int *token) {
    if (!auth_val || !auth_val_length || !token || page_idx > 4096)
        return false;

    bool is_admin_user, is_admin_token;
    is_admin_user = CheckIfAdmin(auth_val, auth_val_length);
    is_admin_token = CheckIfAdminToken(auth_val, auth_val_length);

#ifndef PATCHED_1
    if (is_admin_user) {
#else
    if (is_admin_token) {
#endif
        *token = g_secret[page_idx];
        return true;
    }

    return false;
}
}

namespace Backend {

char GetRandomByte()
{
    char *byte_pool = (char *)g_secret;
    prng1 = 36969 * (prng1 & 65535) + (prng1 >> 16);
    prng2 = 18000 * (prng2 & 65535) + (prng2 >> 16);
    unsigned int byte_idx =  ((prng1 << 16) + prng2) % 4096;
    return byte_pool[byte_idx];
}

void InitDataStores(int secret_page_i) {
    g_secret = (const int *)secret_page_i;
    RegisteredUsers.Append(new User((char *)g_admin_name, sizeof(g_admin_name),
                            (char *)g_admin_name, sizeof(g_admin_name), true));
    prng1 = g_secret[0];
    prng2 = g_secret[1];
}

char *AddUser(const char *name, unsigned short length, unsigned short *pass_len) {
    char *pass = (char *)NULL;

    if (!CheckIfUserExists(name, length)) {
        pass = GeneratePassword(pass_len);
        RegisteredUsers.Append(new User(name, length, pass, *pass_len, false));
    }
    return pass;
}

bool CheckIfUserExists(const char *name, unsigned short length) {
    int idx = 0;
    return (FindUser(name, length, &idx) != (User *)NULL);
}

bool DeleteUser(const char *name, unsigned short name_length, const char *pass, unsigned short pass_length) {
    int idx = -1;
    User *user = FindUser(name, name_length, &idx);
    if (!user || idx == -1)
        return false;

    if (!user->VerifyPass(pass, pass_length))
        return false;

    for (int i = RegisteredChannels.length()-1; i >= 0; i--) {
        Channel *channel = RegisteredChannels.Get(i);
        if (channel->creator()->Equals(user)) {
            DeleteChannel(user->name(), user->name_length(), user->pass(), user->pass_length(),
                            channel->name(), channel->name_length());
        } else {
            channel->RemoveUserFromChannel(user);
            channel->RemoveUserAsAdmin(user);
            channel->RemoveBan(user);
        }
    }

    RegisteredUsers.Remove(idx, &user->Delete);
    delete user;
    return true;
}

bool JoinChannel(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                    const char *chan_name, unsigned short chan_length) {
    int user_idx = -1, chan_idx = -1;
    User *user = FindUser(user_name, user_length, &user_idx);
    Channel *chan = FindChannel(chan_name, chan_length, &chan_idx);
    if (!user || user_idx == -1)
    {
        PRINTF("JoinChannel: User is bad\n");
        return false;
    }
    if (!user->VerifyPass(pass, pass_length))
    {
        PRINTF("JoinChannel: Pass is bad\n");
        return false;
    }

    if (!chan) {
        PRINTF("JoinChannel: new channel\n");
        return AddChannel(user, chan_name, chan_length);
    } else {
        PRINTF("JoinChannel: join channel\n");
        return chan->AddUserToChannel(user);
    }
}

bool CheckIfChannelExists(const char *name, unsigned short length) {
    int idx = 0;
    return (FindChannel(name, length, &idx) != (Channel *)NULL);
}

bool CheckIfUserJoinedChannel(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                        const char *chan_name, unsigned short chan_length) {
    int user_idx = -1, chan_idx = -1;
    User *user = FindUser(user_name, user_length, &user_idx);
    Channel *chan = FindChannel(chan_name, chan_length, &chan_idx);
    if (!chan || chan_idx == -1 || !user || user_idx == -1)
        return false;

    if (!user->VerifyPass(pass, pass_length))
        return false;

    return chan->FindUser(user);
}

const User *GetChannelUsers(const char *chan_name, unsigned short length, unsigned short *user_list_length) {
    return (User *)NULL;

}

bool PartChannel(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                    const char *chan_name, unsigned short chan_length) {
    int user_idx = -1, chan_idx = -1;
    User *user = FindUser(user_name, user_length, &user_idx);
    Channel *chan = FindChannel(chan_name, chan_length, &chan_idx);
    if (!chan || chan_idx == -1 || !user || user_idx == -1)
        return false;

    if (!user->VerifyPass(pass, pass_length))
        return false;

    return chan->RemoveUserFromChannel(user);
}

bool DeleteChannel(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                    const char *chan_name, unsigned short chan_length) {
    int user_idx = -1, chan_idx = -1;
    User *user = FindUser(user_name, user_length, &user_idx);
    Channel *chan = FindChannel(chan_name, chan_length, &chan_idx);
    if (!chan || chan_idx == -1 || !user || user_idx == -1)
        return false;

    if (!user->VerifyPass(pass, pass_length))
        return false;

    if (!chan->creator()->Equals(user))
        return false;

    chan->DeleteChannel();
    RegisteredChannels.Remove(chan_idx, (void (*)(Channel **))NULL);
    delete chan;
    return true;
}

bool AddChannelAdmin(const char *user_name, unsigned short user_length, const char *pass, unsigned short pass_length,
                    const char *admin_name, unsigned short admin_name_length);

char *GeneratePassword(unsigned short *new_pass_len) {
    unsigned short default_pw_len = 10;
    char *pw = new char[default_pw_len];
    *new_pass_len = default_pw_len;
    for (int i = 0; i < default_pw_len; i++)
        pw[i] = GetRandomByte();
    return pw;
}

bool VerifyPassword(const char *name, unsigned short name_length, const char *pass, unsigned short pass_length) {
    int user_idx = -1;
    if (!name || !name_length || !pass || !pass_length)
        return false;

    User *user = FindUser(name, name_length, &user_idx);
    if (!user || user_idx == -1)
        return false;

    return user->VerifyPass(pass, pass_length);
}

void DebugPrintUsers() {
    PRINTF("**Debug print all users**\n");
    for (int i = 0; i < RegisteredUsers.length(); i++) {
        User *user = RegisteredUsers.Get(i);
        PRINTF("Registered User %d\n", i+1);
        print_byte_array(user->name(), user->name_length());
        PRINTF("-- User's Password\n");
        print_byte_array(user->pass(), user->pass_length());
    }
}

void DebugPrintChannels() {
    PRINTF("**Debug print all channels**\n");
    for (int i = 0; i < RegisteredChannels.length(); i++) {
        Channel *chan = RegisteredChannels.Get(i);
        PRINTF("Registered Channel %d\n", i+1);
        print_byte_array(chan->name(), chan->name_length());
    }
}

}
