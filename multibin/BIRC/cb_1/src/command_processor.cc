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
#include <cstring.h>
#include "command_processor.h"
#include "debug_brc.h"
#include "server_backend.h"
#include "brc_default_codes.h"
#include "deserialize.h"


//HELPER FUNCTIONS
namespace {

BrcResponse *RegisterUser(char *cmd) {
    char *user_name = (char *)NULL;
    unsigned short user_length = 0;
    char *pass = (char *)NULL;
    unsigned short pass_length = 0;

    bool found_eom;
    PARSE_PARAM(cmd, user_name, user_length);
    PARSE_EOM(cmd, found_eom);
    PRINT_PARAM(user_name, user_length, "User Name");
    if (!found_eom)
        return BrcGlobals::malformed_resp();

    if (Backend::CheckIfUserExists(user_name, user_length)) {
        return BrcGlobals::user_exists_resp();
    } else {
        pass = Backend::AddUser(user_name, user_length, &pass_length);
        if (pass && pass_length)
            return new BrcResponse(GET_PASSWORD_ID, pass, pass_length);
    }

    return BrcGlobals::failure_resp();
}

BrcResponse *CheckIfUserExists(char *cmd) {
    char *user_name = (char *)NULL;
    unsigned short user_length = 0;

    bool found_eom;
    PARSE_PARAM(cmd, user_name, user_length);
    PARSE_EOM(cmd, found_eom);
    PRINT_PARAM(user_name, user_length, "User Name");
    if (!found_eom)
        return BrcGlobals::malformed_resp();

    if (Backend::CheckIfUserExists(user_name, user_length)) {
        return BrcGlobals::success_resp();
    }

    return BrcGlobals::failure_resp();
}


BrcResponse *VerifyPassword(char *cmd) {
    char *user_name = (char *)NULL;
    unsigned short user_length = 0;
    char *pass = (char *)NULL;
    unsigned short pass_length = 0;

    bool found_eom;
    PARSE_PARAM(cmd, user_name, user_length);
    PARSE_PARAM(cmd, pass, pass_length);
    PARSE_EOM(cmd, found_eom);
    PRINT_PARAM(user_name, user_length, "User Name");
    PRINT_PARAM(pass, pass_length, "Password");
    if (!found_eom)
        return BrcGlobals::malformed_resp();

    if (Backend::VerifyPassword(user_name, user_length, pass, pass_length)) {
        return BrcGlobals::success_resp();
    }

    return BrcGlobals::failure_resp();
}

BrcResponse *DeleteUser(char *cmd) {
    char *user_name = (char *)NULL;
    unsigned short user_length = 0;
    char *pass = (char *)NULL;
    unsigned short pass_length = 0;

    bool found_eom;
    PARSE_PARAM(cmd, user_name, user_length);
    PARSE_PARAM(cmd, pass, pass_length);
    PARSE_EOM(cmd, found_eom);
    PRINT_PARAM(user_name, user_length, "User Name");
    PRINT_PARAM(pass, pass_length, "Password");
    if (!found_eom)
        return BrcGlobals::malformed_resp();

    if (Backend::DeleteUser(user_name, user_length, pass, pass_length)) {
        return BrcGlobals::success_resp();
    }

    return BrcGlobals::failure_resp();
}

BrcResponse *JoinChannel(char *cmd) {
    char *user_name = (char *)NULL;
    unsigned short user_length = 0;
    char *pass = (char *)NULL;
    unsigned short pass_length = 0;
    char *chan_name = (char *)NULL;
    unsigned short chan_length = 0;

    bool found_eom;
    PARSE_PARAM(cmd, user_name, user_length);
    PARSE_PARAM(cmd, pass, pass_length);
    PARSE_PARAM(cmd, chan_name, chan_length);
    PARSE_EOM(cmd, found_eom);
    PRINT_PARAM(user_name, user_length, "User Name");
    PRINT_PARAM(pass, pass_length, "Password");
    PRINT_PARAM(chan_name, chan_length, "Channel Name");
    if (!found_eom)
        return BrcGlobals::malformed_resp();

    if (Backend::JoinChannel(user_name, user_length, pass, pass_length, chan_name, chan_length)) {
        return BrcGlobals::success_resp();
    }

    return BrcGlobals::failure_resp();
}

BrcResponse *CheckIfChannelExists(char *cmd) {
    char *chan_name = (char *)NULL;
    unsigned short chan_length = 0;

    bool found_eom;
    PARSE_PARAM(cmd, chan_name, chan_length);
    PARSE_EOM(cmd, found_eom);
    PRINT_PARAM(chan_name, chan_length, "Channel Name");
    if (!found_eom)
        return BrcGlobals::malformed_resp();

    if (Backend::CheckIfChannelExists(chan_name, chan_length)) {
        return BrcGlobals::success_resp();
    }

    return BrcGlobals::failure_resp();
}

BrcResponse *PartChannel(char *cmd) {
    char *user_name = (char *)NULL;
    unsigned short user_length = 0;
    char *pass = (char *)NULL;
    unsigned short pass_length = 0;
    char *chan_name = (char *)NULL;
    unsigned short chan_length = 0;

    bool found_eom;
    PARSE_PARAM(cmd, user_name, user_length);
    PARSE_PARAM(cmd, pass, pass_length);
    PARSE_PARAM(cmd, chan_name, chan_length);
    PARSE_EOM(cmd, found_eom);
    PRINT_PARAM(user_name, user_length, "User Name");
    PRINT_PARAM(pass, pass_length, "Password");
    PRINT_PARAM(chan_name, chan_length, "Channel Name");
    if (!found_eom)
        return BrcGlobals::malformed_resp();

    if (Backend::PartChannel(user_name, user_length, pass, pass_length, chan_name, chan_length)) {
        return BrcGlobals::success_resp();
    }

    return BrcGlobals::failure_resp();
}

BrcResponse *DeleteChannel(char *cmd) {
    char *user_name = (char *)NULL;
    unsigned short user_length = 0;
    char *pass = (char *)NULL;
    unsigned short pass_length = 0;
    char *chan_name = (char *)NULL;
    unsigned short chan_length = 0;

    bool found_eom;
    PARSE_PARAM(cmd, user_name, user_length);
    PARSE_PARAM(cmd, pass, pass_length);
    PARSE_PARAM(cmd, chan_name, chan_length);
    PARSE_EOM(cmd, found_eom);
    PRINT_PARAM(user_name, user_length, "User Name");
    PRINT_PARAM(pass, pass_length, "Password");
    PRINT_PARAM(chan_name, chan_length, "Channel Name");
    if (!found_eom)
        return BrcGlobals::malformed_resp();

    if (Backend::DeleteChannel(user_name, user_length, pass, pass_length, chan_name, chan_length)) {
        return BrcGlobals::success_resp();
    }

    return BrcGlobals::failure_resp();
}

BrcResponse *ExitServer(char *cmd) {
    bool found_eom;
    PARSE_EOM(cmd, found_eom);
    if (!found_eom)
        return BrcGlobals::malformed_resp();

    return BrcGlobals::exit_server_resp();
}


BrcResponse *RemoteAdminTokenRequest(char *cmd) {
    char *auth_val = (char *)NULL;
    unsigned short auth_length = 0;
    unsigned short page_idx = 0;
    int token;

    bool found_eom;
    PARSE_PARAM(cmd, auth_val, auth_length);
    PARSE_USHORT(cmd, page_idx);
    PARSE_EOM(cmd, found_eom);
    PRINT_PARAM(auth_val, auth_length, "User Name");
    if (!found_eom) {
        return BrcGlobals::malformed_resp();
    } else {
        if (AdminTasks::RemoteAdminTokenRequest(auth_val, auth_length, page_idx, &token))
            return new BrcResponse(GET_REMOTE_TOKEN_ID, (char *)&token, sizeof(token));
    }

    return BrcGlobals::failure_resp();
}

}
//END HELPER FUCNTIONS

namespace CommandProcessor {

BrcResponse *ServiceCommand(BrcCommand *brc_cmd) {
    BrcResponse *resp = BrcGlobals::failure_resp();
    if (!brc_cmd)
        return resp;

    char *cmd = (char *)brc_cmd->cmd();
    unsigned short cmd_id_len = 0;
    char *cmd_id = (char *)NULL;
    PARSE_PARAM(cmd, cmd_id, cmd_id_len);

    if (memcmp(cmd_id, BrcGlobals::register_code(), cmd_id_len) == 0) {
        resp = RegisterUser(cmd);
    } else if (memcmp(cmd_id, BrcGlobals::check_user_code(), cmd_id_len) == 0) {
        resp = CheckIfUserExists(cmd);
    } else if (memcmp(cmd_id, BrcGlobals::verify_password_code(), cmd_id_len) == 0) {
        resp = VerifyPassword(cmd);
    } else if (memcmp(cmd_id, BrcGlobals::delete_user_code(), cmd_id_len) == 0) {
        resp = DeleteUser(cmd);
    } else if (memcmp(cmd_id, BrcGlobals::join_channel_code(), cmd_id_len) == 0) {
        resp = JoinChannel(cmd);
    } else if (memcmp(cmd_id, BrcGlobals::check_channel_code(), cmd_id_len) == 0) {
        resp = CheckIfChannelExists(cmd);
    } else if (memcmp(cmd_id, BrcGlobals::part_channel_code(), cmd_id_len) == 0) {
        resp = PartChannel(cmd);
    } else if (memcmp(cmd_id, BrcGlobals::delete_channel_code(), cmd_id_len) == 0) {
        resp = DeleteChannel(cmd);
    } else if (memcmp(cmd_id, BrcGlobals::server_exit_code(), cmd_id_len) == 0) {
        resp = ExitServer(cmd);
    } else if (memcmp(cmd_id, BrcGlobals::remote_admin_token_request_code(), cmd_id_len) == 0) {
        resp = RemoteAdminTokenRequest(cmd);
    }

    return resp;
}


BrcResponse *ServiceChat(BrcChat *brc_chat) {
    BrcResponse *resp = BrcGlobals::failure_resp();
    if (!brc_chat)
        return resp;

    char *chat = (char *)brc_chat->chat_msg();
    unsigned short chat_msg_length = brc_chat->chat_msg_length();

    if (!chat || chat_msg_length)
        goto finish;

    if (brc_chat->chat_type() == CHANNEL_CHAT)  {

    } else if (brc_chat->chat_type() == USER_CHAT) {
    }

finish:
    return resp;

}
}

