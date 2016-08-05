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

#include "error.h"

const char* err_msgs[] =
{
    "",
    "Internal error.",
    "Nickname is too long.",
    "Password is too long.",
    "Team Name is too long.",
    "No such user found.",
    "No such challenge found.",
    "No such team found.",
    "The challenge is already open.",
    "Duplicate flag.",
    "Invalid flag.",
    "User already exists.",
    "Team already exists.",
    "Challenge already exists.",
    "Wrong password.",
    "Invalid value.",
};

const char* error_to_string(error_t err)
{
    switch (err)
    {
        case ERR_OK:
        case ERR_INTERNAL:
        case ERR_NICK_LONG:
        case ERR_PASS_LONG:
        case ERR_NAME_LONG:
        case ERR_NO_SUCH_USER:
        case ERR_NO_SUCH_CHAL:
        case ERR_NO_SUCH_TEAM:
        case ERR_CHAL_ALREADY_OPEN:
        case ERR_DUPLICATE_FLAG:
        case ERR_INVALID_FLAG:
        case ERR_USER_EXISTS:
        case ERR_TEAM_EXISTS:
        case ERR_CHAL_EXISTS:
        case ERR_WRONG_PASS:
        case ERR_INVALID_VALUE:
            return err_msgs[err];
            break;
        default:
            return "Unknown error.";
    }
}
