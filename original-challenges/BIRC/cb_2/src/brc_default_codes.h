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
#ifndef BRC_DEFAULT_CODES_H_
#define BRC_DEFAULT_CODES_H_
#include "brc_response.h"

#define CHECK_USER_CODE {2,9,1,3,1,6,2,6}
#define CHECK_CHANNEL_CODE {2,1,2,8,3,3,5,9}
#define VERIFY_PASSWORD_CODE {2,1,8,9,4,1,7,5}
#define REGISTER_CODE {1,2,3,4,5,6,7,8}
#define DELETE_USER_CODE {8,7,6,5,4,3,2,1}
#define JOIN_CHANNEL_CODE {8,3,1,1,0,1,2,3}
#define PART_CHANNEL_CODE {8,1,3,4,8,0,1,6}
#define DELETE_CHANNEL_CODE {3,2,1,0,1,1,3,8}
#define ADD_CHANNEL_ADMIN_CODE {5,3,2,4,1,2,4,7}
#define REQUEST_PASSWORD_CODE {5,1,3,5,0,6,3,4}
#define CHANNEL_CHAT_CODE {1,2,5,3,0,1,8,9}
#define USER_CHAT_CODE {9,2,5,3,0,1,8,9}
#define PING_CODE {1,1,1,1,1,1,1,1}
#define PONG_CODE {9,9,9,9,9,9,9,9}
#define SERVER_EXIT_CODE {0,0,0,0,0,0,0,0}
#define REMOTE_ADMIN_TOKEN_REQUEST_CODE {7,7,2,4,5,3,1,9}

#define EOM { 0, 0 }
#define OK_ID 8
#define OK { 8, 22 }
#define USER_EXISTS_ID 9
#define USER_EXISTS { 9, 99 }
#define FAILURE_ID 64
#define FAILURE { 64, 99 }
#define MALFORMED_DATA_ID 65
#define MALFORMED_DATA { 65, 99 }
#define EXIT_SERVER_ID 1
#define EXIT_SERVER { 1, 1 }

//All IDs >= 100 need to have the caller clean up the response, since it is not static
#define GET_PASSWORD_ID 100
#define MISC 127
#define GET_REMOTE_TOKEN_ID 7777

//GLOBAL VARIABLES
namespace BrcGlobals {



const char *check_user_code();
const char *check_channel_code();
const char *verify_password_code();
const char *register_code();
const char *delete_user_code();
const char *join_channel_code();
const char *part_channel_code();
const char *delete_channel_code();
const char *add_channel_admin_code();
const char *request_password_code();
const char *channel_chat_code();
const char *user_chat_code();
const char *ping_code();
const char *pong_code();
const char *server_exit_code();
const char *remote_admin_token_request_code();

const char *eom();
unsigned short eom_length();
const char *ok();
const char *user_exists();
const char *failure();
const char *malformed();
const char *exit_server();
BrcResponse *success_resp();
BrcResponse *user_exists_resp();
BrcResponse *failure_resp();
BrcResponse *malformed_resp();
BrcResponse *exit_server_resp();

}
//END GLOBAL VARIABLES

#endif /* BRC_DEFAULT_CODES_H_ */
