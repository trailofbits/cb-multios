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
#include <cstdlib.h>
#include <cstdio.h>
#include <cstring.h>

#include "array_wrapper.h"
#include "client_commands.h"
#include "debug_brc.h"
#include "client_backend.h"

#define CLIENT_FD 3
#define SERVER_FD 4

#define SESSION_TIMEOUT_VAL 30
#define MAX_USERS 256

#define LOGIN_CMD_ID 8711
#define LOGOUT_CMD_ID 8719

#define CLIENT_SUCCESS 1234
#define CLIENT_FAIL 4321

#define CLIENT_LOGOUT_ALERT 8791
#define CLIENT_SESSION_TIMEOUT_ALERT 2431

#ifdef PATCHED_1
#define READ_PARAM(_input, _length, _parambuf) \
    do { \
        fread(_input, 2, stdin); \
        _length = *((unsigned short *)(_input)); \
        if (_length <= 1024) { \
            fread(_input, _length, stdin); \
            _parambuf = new char[_length]; \
            memcpy(_parambuf, _input, _length); \
        } else {\
            _length = 0; \
        } \
    } while(0)
#else
#define READ_PARAM(_input, _length, _parambuf) \
    do { \
        fread(_input, 2, stdin); \
        _length = *((unsigned short *)(_input)); \
        if (_length <= 1048) { \
            fread(_input, _length, stdin); \
            _parambuf = new char[_length]; \
            memcpy(_parambuf, _input, _length); \
        } else {\
            _length = 0; \
        } \
    } while(0)
#endif

#define READ_PARAM_G_INPUT(_length) \
    do { \
        fread(g_input, 2, stdin); \
        _length = *((unsigned short *)(g_input)); \
        if (_length <= 1024) { \
            fread(g_input, _length, stdin); \
        } else {\
            _length = 0; \
        } \
    } while(0)

User *g_cur_user = (User *)NULL;
char g_input[1024];
User g_all_users_array[10];
ArrayWrapper<User> g_all_users(g_all_users_array, 10);

bool DeleteCurUser() {
    for (int i = 0; i < g_all_users.length(); i++) {
        if (g_all_users.Get(i).Equals(g_cur_user)) {
            g_all_users.Remove(i, &User().DeleteStatic);
            g_cur_user = (User *)NULL;
            return true;
        }
    }
    return false;
}

bool FindCachedUser(char *name, unsigned short name_length) {
    for (int i = 0; i < g_all_users.length(); i++) {
        if (g_all_users.Get(i).CompareName(name, name_length)) {
            g_cur_user = (User *)(&(g_all_users.Get(i)));
            return true;
        }
    }
    return false;
}

void WriteClientNeedsReauth() {
    unsigned short session_timeout_alert = CLIENT_SESSION_TIMEOUT_ALERT;
    fwrite(&session_timeout_alert, sizeof(session_timeout_alert), stdout);
}

void WriteClientSuccess() {
    unsigned short client_success = CLIENT_SUCCESS;
    fwrite(&client_success, sizeof(client_success), stdout);
}

void WriteClientFail() {
    unsigned short client_fail = CLIENT_FAIL;
    fwrite(&client_fail, sizeof(client_fail), stdout);
}

void WriteClientLogoutAlert() {
    unsigned short client_logout_alert = CLIENT_LOGOUT_ALERT;
    fwrite(&client_logout_alert, sizeof(client_logout_alert), stdout);
}

bool UserLogin() {
    if(g_cur_user) {
        WriteClientFail();
        return false;
    }

    bool success = false;
    User *user = (User *)NULL;
    unsigned short user_length = 0, pass_length = 0;
    char *user_name = (char*)NULL, *password = (char*)NULL;

    READ_PARAM(g_input, user_length, user_name);
    if (!user_length || !user_name)
        goto error;
    READ_PARAM(g_input, pass_length, password);
    if (!pass_length || !password)
        goto error;

    user = new User(user_name, user_length, password, pass_length);
    if (!FindCachedUser(user_name, user_length)) {
        if (BrcClient::VerifyPassword(user, password, pass_length)) {
            PRINTF("Logged in user gets added to the cache\n");
            if (g_all_users.IsFull())
                g_all_users.Remove(0, &User().DeleteStatic);
            g_all_users.Append(*user);
            g_cur_user = (User *)(&(g_all_users.Get(g_all_users.length() - 1)));
        } else {
            PRINTF("The passwords did NOT match\n");
            goto error;
        }
    }

    WriteClientSuccess();
    PRINTF("Successfully logged in\n");
    success = true;
    goto cleanup;
error:
    PRINTF("User name/password did not match our records\n");
    WriteClientFail();
    PRINTF("\n");
cleanup:
    if (user)
        delete user;
    if (user_name)
        delete[] user_name;
    if (password)
        delete[] password;
    return success;
}

void UserLogout() {
    if(!g_cur_user) {
        PRINTF("No user is logged in\n");
        WriteClientFail();
        PRINTF("\n");
        return;
    }

    g_cur_user = (User *)NULL;
    WriteClientSuccess();
    PRINTF("User has been logged out\n");
    WriteClientLogoutAlert();
    PRINTF("\n");
}

bool RegisterUser() {
    if(g_cur_user) {
        WriteClientFail();
        return false;
    }

    User *user = (User *)NULL;
    unsigned short read_length = 0;
    unsigned short pass_length = 0;
    READ_PARAM_G_INPUT(read_length);
    user = BrcClient::RegisterUser(g_input, read_length);
    if (user) {
        PRINTF("Successfully Registered User\n");
        if (g_all_users.IsFull())
            g_all_users.Remove(0, &User().DeleteStatic);
        g_all_users.Append(*user);
        g_cur_user = (User *)(&(g_all_users.Get(g_all_users.length() - 1)));
        WriteClientSuccess();
        PRINTF("Assigned Password Length: ");
        _PRINTF("\n");
        pass_length = g_cur_user->pass_length();
        fwrite(&pass_length, sizeof(pass_length), stdout);
        PRINTF("Assigned Password: ");
        _PRINTF("\n");
        fwrite(g_cur_user->pass(), g_cur_user->pass_length(), stdout);
        PRINTF("\n");
        delete user;
        return true;
    } else {
        PRINTF("Failed to register user\n");
        WriteClientFail();
        PRINTF("\n");
        return false;
    }
}

void SearchForUser() {
    unsigned short read_length = 0;
    READ_PARAM_G_INPUT(read_length);
    if (BrcClient::SearchForUser(g_input, read_length)) {
        PRINTF("Successfully found the user on the server\n");
        WriteClientSuccess();
    } else {
        PRINTF("Could not find user on server\n");
        WriteClientFail();
        PRINTF("\n");
    }
}

void DeleteUser() {
    if (!g_cur_user) {
        WriteClientFail();
        return;
    }

    unsigned short read_length = 0;
    READ_PARAM_G_INPUT(read_length);
    if (BrcClient::DeleteUser(g_cur_user, g_input, read_length)) {
        PRINTF("Deleted User from server\n");
        WriteClientSuccess();
        DeleteCurUser();
    } else {
        PRINTF("Failed to delete user on server\n");
        WriteClientFail();
        PRINTF("\n");
    }
}

void JoinChannel() {
    if (!g_cur_user) {
        WriteClientFail();
        return;
    }

    unsigned short read_length = 0;
    READ_PARAM_G_INPUT(read_length);
    if (BrcClient::JoinChannel(g_cur_user, g_input, read_length)) {
        PRINTF("Successfully join/created channel\n");
        WriteClientSuccess();
    } else {
        PRINTF("Could not join/create channel\n");
        WriteClientFail();
        PRINTF("\n");
    }
}

void SearchForChannel() {
    unsigned short read_length = 0;
    READ_PARAM_G_INPUT(read_length);
    if (BrcClient::SearchForChannel(g_input, read_length)) {
        PRINTF("Found the channel on the server\n");
        WriteClientSuccess();
    } else {
        PRINTF("Failed to find channel on server\n");
        WriteClientFail();
        PRINTF("\n");
    }
}

void PartChannel() {
    if (!g_cur_user) {
        WriteClientFail();
        return;
    }

    unsigned short read_length = 0;
    READ_PARAM_G_INPUT(read_length);
    if (BrcClient::PartChannel(g_cur_user, g_input, read_length)) {
        PRINTF("Successfully parted from channel\n");
        WriteClientSuccess();
    } else {
        PRINTF("Could not part from channel\n");
        WriteClientFail();
        PRINTF("\n");
    }
}

void DeleteChannel() {
    if (!g_cur_user) {
        WriteClientFail();
        return;
    }

    unsigned short read_length = 0;
    READ_PARAM_G_INPUT(read_length);
    if (BrcClient::DeleteChannel(g_cur_user, g_input, read_length)) {
        PRINTF("Successfully deleted channel from server\n");
        WriteClientSuccess();
    } else {
        PRINTF("Could not delete channel from server\n");
        WriteClientFail();
        PRINTF("\n");
    }
}

void RemoteAdminTokenRequest() {
    if (!g_cur_user) {
        WriteClientFail();
        return;
    }

    int token = 0;
    unsigned short page_idx = 0;
    fread(g_input, 2, stdin);
    page_idx = *((unsigned short *)(g_input));
    if (BrcClient::RemoteAdminTokenRequest(g_cur_user, page_idx, &token)) {
        PRINTF("Successfully received token from server\n");
        WriteClientSuccess();
        fwrite(&token, sizeof(token), stdout);
        PRINTF("\n");
    } else {
        PRINTF("Could not retrieve token from server\n");
        WriteClientFail();
        PRINTF("\n");
    }
}

bool Reauthenticate() {
    if(!g_cur_user) {
        return false;
    }

    unsigned short read_length = 0;
    READ_PARAM_G_INPUT(read_length);
    return (BrcClient::VerifyPassword(g_cur_user, g_input, read_length));
}

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[]) {
    bool is_running = true;

    FILE *cb_s_in = fopen(SERVER_FD, 0);
    FILE *cb_s_out = fopen(SERVER_FD, 1);
    unsigned short client_cmd_id = 0;
    int session_timeout = SESSION_TIMEOUT_VAL;

    char *secret_page = (char *)secret_page_i;
    (void) secret_page;
    BrcClient::InitServerFd(cb_s_in, cb_s_out);

still_running:
    is_running = true;
    while (is_running) {
        --session_timeout;
        if (g_cur_user && session_timeout == 0) {
            WriteClientNeedsReauth();
            if (Reauthenticate()) {
                PRINTF("Successfully reauthenticated from server\n");
                WriteClientSuccess();
                session_timeout = SESSION_TIMEOUT_VAL;
            } else {
                PRINTF("Reauthentication failed\n");
                WriteClientFail();
                PRINTF("\n");

                g_cur_user = (User *)NULL;
                PRINTF("User has been logged out\n");
                WriteClientLogoutAlert();
                PRINTF("\n");

            }
        }

        if (fread(g_input, 2, stdin) != 2)
            return 0;
        client_cmd_id = *((unsigned short *)(g_input));
        PRINTF("The cmd id recv'd is: %d\n", client_cmd_id);
        switch(client_cmd_id) {
        case REGISTER_USER_CMD_ID:
            if (RegisterUser())
                session_timeout = SESSION_TIMEOUT_VAL;
            break;
        case SEARCH_FOR_USER_CMD_ID:
            SearchForUser();
            break;
        case DELETE_USER_CMD_ID:
            DeleteUser();
            break;
        case JOIN_CHANNEL_CMD_ID:
            JoinChannel();
            break;
        case SEARCH_FOR_CHANNEL_CMD_ID:
            SearchForChannel();
            break;
        case PART_CHANNEL_CMD_ID:
            PartChannel();
            break;
        case DELETE_CHANNEL_CMD_ID:
            DeleteChannel();
            break;
        case LOGIN_CMD_ID:
            if (UserLogin())
                session_timeout = SESSION_TIMEOUT_VAL;
            break;
        case LOGOUT_CMD_ID:
            UserLogout();
            break;
        case EXIT_SERVER_CMD_ID:
            is_running = false;
            break;
        case REMOTE_ADMIN_TOKEN_REQUEST_CMD_ID:
            RemoteAdminTokenRequest();
            break;
        }
    }

    if (!BrcClient::ExitServer()) {
        PRINTF("FAILURE EXITING!\n");
        goto still_running;
    }

    PRINTF("Exiting Client....\n");
    return 0;
}
