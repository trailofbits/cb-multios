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
#include "client_backend.h"
#include "array_wrapper.h"
#include "user.h"
#include "debug_brc.h"
#include "brc_token.h"

#define MAX_ARRAY_SIZE 256

#define ADMIN_NAME {13, 23, 44, 28, 112, 37, 155, 14 }

namespace {

ArrayWrapper<User *> CachedUsers(MAX_ARRAY_SIZE);
const int *g_secret;

User *FindUser(const char *name, unsigned short length, int *idx) {
    for (int i = 0; i < CachedUsers.length(); i++) {
        User *user = CachedUsers.Get(i);
        if (user->CompareName(name, length)) {
            *idx = i;
            return user;
        }
    }

    *idx = -1;
    return (User *)NULL;
}

}

namespace Backend {

void InitDataStores(int secret_page_i) {
    g_secret = (const int *)secret_page_i;
}

bool CheckIfUserExists(const char *name, unsigned short length) {
    int idx = 0;
    return (FindUser(name, length, &idx) != (User *)NULL);
}

bool AddUser(User *user) {
    if (!CheckIfUserExists(user->name(), user->name_length())) {
        return CachedUsers.Append(user);
    }
    return false;
}

bool DeleteUser(User **pcur_user, const char *pass, unsigned short pass_length) {
    int idx = -1;
    User *cur_user = *pcur_user;
    User *user = FindUser(cur_user->name(), cur_user->name_length(), &idx);
    if (!user || idx == -1)
        return false;

    if (!user->VerifyPass(pass, pass_length))
        return false;

    CachedUsers.Remove(idx, &user->Delete);
    delete user;
    *pcur_user = (User *)NULL;
    return true;
}


bool VerifyPassword(User *cur_user, const char *pass, unsigned short pass_length) {
    if (!cur_user || !pass || !pass_length)
        return false;

    return cur_user->VerifyPass(pass, pass_length);
}

void DebugPrintUsers() {
    PRINTF("**Debug print all users**\n");
    for (int i = 0; i < CachedUsers.length(); i++) {
        User *user = CachedUsers.Get(i);
        PRINTF("Cached User %d\n", i+1);
        print_byte_array(user->name(), user->name_length());
        PRINTF("-- User's Password\n");
        print_byte_array(user->pass(), user->pass_length());
    }
}

}
