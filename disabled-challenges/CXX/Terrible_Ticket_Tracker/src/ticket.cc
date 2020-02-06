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
#include "cgc_cstdlib.h"
#include "cgc_cstring.h"
#include "cgc_cstdio.h"
#include "cgc_ticket.h"
#include "cgc_time.h"
#include "cgc__defines.h"

#define MAX_PRIORITY CRITICAL

static uint32_t g_ticket_id = 1;

Ticket *Ticket::GetTicket(char *email, char *desc, uint32_t entry_time, uint32_t duration, PRIORITY priority)
{
    if (!email || !desc || !entry_time || !priority || priority > MAX_PRIORITY)
        return (Ticket *)NULL;

    return new Ticket(email, desc, entry_time, duration, priority);
}

void Ticket::DeleteTicket(Ticket *ticket)
{
    if (ticket)
        delete ticket;
}

Ticket::Ticket(char *email, char *desc, uint32_t entry_time, uint32_t duration, PRIORITY priority)
{
    id_ = g_ticket_id++;
    uint32_t email_len = cgc_strlen(email) >= MAX_EMAIL ? MAX_EMAIL - 1 : cgc_strlen(email);
    uint32_t desc_len = cgc_strlen(desc) >= MAX_EMAIL ? MAX_EMAIL - 1 : cgc_strlen(desc);
    cgc_memset(email_, 0, sizeof(email_));
    cgc_memset(desc_, 0, sizeof(desc_));
    cgc_memcpy(email_,  email, email_len);
    cgc_memcpy(desc_,  desc, desc_len);
    entry_time_ = entry_time;
    status_ = OPEN;
    duration_ = duration;
    priority_ = priority;
}

Ticket::~Ticket()
{
}

void Ticket::UpdateStatus(STATUS status)
{
    status_ = status;
}

void Ticket::WorkOn()
{
  if (duration_ > 0)
    --duration_;
}

bool Ticket::CheckDone(void)
{
  return duration_ == 0;
}


void Ticket::Display()
{
  cgc_printf("%d" EOL, id());
  cgc_printf("%s" EOL, email());
  cgc_printf("%s" EOL, description());
  cgc_printf("%d" EOL, status());
  cgc_printf("%d" EOL, priority());
  cgc_printf("%d" EOL, entry_time());
  cgc_printf("%d" EOL, duration());
}

uint32_t Ticket::id()
{
    return id_;
}

char *Ticket::email()
{
    return email_;
}

char *Ticket::description()
{
    return desc_;
}

uint32_t Ticket::entry_time()
{
    return entry_time_;
}

PRIORITY Ticket::priority()
{
    return priority_;
}

STATUS Ticket::status()
{
    return status_;
}

uint32_t Ticket::duration()
{
    return duration_;
}
