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
#include "brc_default_codes.h"

namespace {

const char check_user_code_[] = CHECK_USER_CODE;
const char check_channel_code_[] = CHECK_CHANNEL_CODE;
const char verify_password_code_[] = VERIFY_PASSWORD_CODE;
const char register_code_[] = REGISTER_CODE;
const char delete_user_code_[] = DELETE_USER_CODE;
const char join_channel_code_[] = JOIN_CHANNEL_CODE;
const char part_channel_code_[] = PART_CHANNEL_CODE;
const char delete_channel_code_[] = DELETE_CHANNEL_CODE;
const char add_channel_admin_code_[] = ADD_CHANNEL_ADMIN_CODE;
const char request_password_code_[] = REQUEST_PASSWORD_CODE;
const char channel_chat_code_[] = CHANNEL_CHAT_CODE;
const char user_chat_code_[] = USER_CHAT_CODE;
const char ping_code_[] = PING_CODE;
const char pong_code_[] = PONG_CODE;
const char server_exit_code_[] = SERVER_EXIT_CODE;
const char remote_admin_token_request_code_[] = REMOTE_ADMIN_TOKEN_REQUEST_CODE;

const char eom_[] = EOM;
const char ok_[] = OK;
BrcResponse *success_resp_ = new BrcResponse(OK_ID, (char *)ok_, sizeof(ok_));
const char user_exists_[] = USER_EXISTS;
BrcResponse *user_exists_resp_ = new BrcResponse(USER_EXISTS_ID, (char *)user_exists_, sizeof(user_exists_));
const char failure_[] = FAILURE;
BrcResponse *failure_resp_ = new BrcResponse(FAILURE_ID, (char *)failure_, sizeof(failure_));
const char malformed_[] = MALFORMED_DATA;
BrcResponse *malformed_resp_ = new BrcResponse(MALFORMED_DATA_ID, (char *)malformed_, sizeof(malformed_));
const char exit_server_[] = EXIT_SERVER;
BrcResponse *exit_server_resp_ = new BrcResponse(EXIT_SERVER_ID, (char *)exit_server_, sizeof(exit_server_));

}

namespace BrcGlobals {

const char *check_user_code() { return check_user_code_; }
const char *check_channel_code() { return check_channel_code_; }
const char *verify_password_code() { return verify_password_code_; }
const char *register_code() { return register_code_; }
const char *delete_user_code() { return delete_user_code_; }
const char *join_channel_code() { return join_channel_code_; }
const char *part_channel_code() { return part_channel_code_; }
const char *delete_channel_code() { return delete_channel_code_; }
const char *add_channel_admin_code() { return add_channel_admin_code_; }
const char *request_password_code() { return request_password_code_; }
const char *channel_chat_code() { return channel_chat_code_; }
const char *user_chat_code() { return user_chat_code_; }
const char *ping_code() { return ping_code_; }
const char *pong_code() { return pong_code_; }
const char *server_exit_code() { return server_exit_code_; }
const char *remote_admin_token_request_code() { return remote_admin_token_request_code_; }

const char *eom() { return eom_; }
unsigned short eom_length() { return sizeof(eom_); }
const char *ok() { return ok_; }
const char *user_exists() { return user_exists_; }
const char *failure() { return failure_; };
const char *malformed() { return malformed_; }
const char *exit_server() { return exit_server_; }
BrcResponse *success_resp() { return success_resp_; }
BrcResponse *user_exists_resp() { return  user_exists_resp_; }
BrcResponse *failure_resp() { return failure_resp_; }
BrcResponse *malformed_resp() { return malformed_resp_; }
BrcResponse *exit_server_resp() { return exit_server_resp_; }

}

