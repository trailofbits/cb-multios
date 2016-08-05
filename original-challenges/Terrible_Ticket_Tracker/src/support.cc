/*
 * Copyright (c) 2016 Kaprica Security, Inc.
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
#include "support.h"

#include "cstdio.h"

uint32_t g_support_id = 1;

Support::Support(uint32_t contact_info, PRIORITY max_priority)
{
    support_id_ = g_support_id++;
    contact_info_ = contact_info;
    max_priority_ = max_priority;
}

bool Support::AssignTicket(Ticket *ticket)
{
    if (!ticket)
        return false;

    ticket_ = ticket;
    return true;
}

bool Support::UpdateTicket(STATUS status)
{
    if (!ticket_)
        return false;

    ticket_->UpdateStatus(status);
    return true;
}

Ticket *Support::CurrentTicket()
{
    return ticket_;
}

void Support::Display(void)
{
  printf("%d" EOL, id());
  if (CurrentTicket())
    printf("%d" EOL, CurrentTicket()->id());
  else
    printf("%s" EOL, "None");
  printf("%d" EOL, contact_info());
  printf("%d" EOL, max_priority());
}

Ticket *Support::RemoveTicket()
{
    Ticket *ticket = nullptr;
    if (ticket_)
    {
        ticket = ticket_;
        ticket_->prev = this;
        ticket_ = nullptr;
    }

    return ticket;
}

uint32_t Support::id()
{
    return support_id_;
}

uint32_t Support::contact_info()
{
    return contact_info_;
}

PRIORITY Support::max_priority()
{
    return max_priority_;
}
