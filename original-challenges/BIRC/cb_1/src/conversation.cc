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
#include "conversation.h"

#define MAX_MSGS 100

Conversation::Conversation(Channel *channel)
    : messages_(MAX_MSGS) {
    channel_ = channel;
    sender_ = (User *)NULL;
}

Conversation::Conversation(User *user)
    :messages_(MAX_MSGS) {
    channel_ = (Channel *)NULL;
    sender_ = user;
}

void Conversation::AddChat(Chat chat) {
    messages_.ForceAppend(chat, Chat().Delete);
}

void Conversation::ReadMessages() {
    ClearChatMessages();
}

void Conversation::ClearChatMessages() {
    while(!messages_.IsEmpty()) {
        messages_.Remove(0, Chat().Delete);
    }
}
