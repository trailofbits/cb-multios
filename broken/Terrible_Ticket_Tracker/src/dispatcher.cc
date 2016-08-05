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
#include "dispatcher.h"
#include "cstdio.h"
#include "cstring.h"

uint32_t g_rand_idx = 0;

Dispatcher::Dispatcher(List *pworkers, uint32_t *secret_page)
{
  pworkers_ = pworkers;
  secret_ = secret_page;
}

void Dispatcher::AddTicket(Ticket *ticket)
{
  if(!ticket)
    return;

  if (ticket->status() == OPEN)
    ticket_lists_[ticket->priority() - 1].Append(ticket);
  else
    ticket_lists_[ticket->priority() - 1].AppendLeft(ticket);
}

void Dispatcher::CancelTicket(uint32_t id)
{
  for (int i = 0; i < NUM_DEQUES; i++)
  {
    Deque *ptickets = &ticket_lists_[i];
    uint32_t count = ptickets->Count();
    for (int j = 0; j < count; j++)
    {
      Ticket *ticket = ptickets->PopLeft();
      if (ticket->id() == id) {
        Ticket::DeleteTicket(ticket);
        continue;
      }
      ptickets->Append(ticket);
    }
  }

  Support *worker = FindSupportByTicketId(id);
  if (worker)
  {
    Ticket *ticket = worker->RemoveTicket();
    if (ticket)
      Ticket::DeleteTicket(ticket);
  }
}

void Dispatcher::ViewTicket(uint32_t id)
{
  for (int i = 0; i < NUM_DEQUES; i++)
  {
    Deque *ptickets = &ticket_lists_[i];
    for (int j = 0; j < ptickets->Count(); j++)
    {
      Ticket *ticket = ptickets->PopLeft();
      if (ticket->id() == id)
      {
        ticket->Display();
      }
      ptickets->Append(ticket);
    }
  }

  Support *worker = FindSupportByTicketId(id);
  if (worker)
    worker->CurrentTicket()->Display();
}

void Dispatcher::ViewTickets(STATUS status)
{
  for (int i = 0; i < NUM_DEQUES; i++)
  {
    Deque *ptickets = &ticket_lists_[i];
    for (int j = 0; j < ptickets->Count(); j++)
    {
      Ticket *ticket = ptickets->PopLeft();
      if (ticket->status() == status)
        ticket->Display();
      ptickets->Append(ticket);
    }
  }

  for (int i = 0; i < pworkers_->Length(); i++)
  {
    Support *worker = pworkers_->Get(i);
    Ticket *current_ticket = worker->CurrentTicket();
    if (current_ticket && current_ticket->status() == status)
      current_ticket->Display();
  }

}

void Dispatcher::RecordFinished(Support* worker)
{
  char buf[MAX_DESC + 1];
  memcpy(buf, worker->CurrentTicket()->description(), MAX_DESC);
  Ticket::DeleteTicket(worker->RemoveTicket());

  printf("Ticket Finished\n");
  printf("%d\n", worker->id());
#ifdef PATCHED_1
  printf("%s", buf);
#else
  printf(buf);
#endif
}

Ticket *Dispatcher::GetTicket(PRIORITY max_priority)
{
  for (int i = max_priority; i >= LOW; i--)
  {
    Deque *ptickets = &ticket_lists_[i - 1];
    if (ptickets->Count())
      return ptickets->PopLeft();
  }

  return nullptr;
}

uint32_t Dispatcher::GetRandomTicks(uint32_t modval)
{
  uint32_t v =  secret_[g_rand_idx] % modval;
  g_rand_idx = (g_rand_idx + 1) % (0x1000 / sizeof(uint32_t));
  return v;
}

Support *Dispatcher::FindSupportByTicketId(uint32_t id)
{
  for (int i = 0; i < pworkers_->Length(); i++)
  {
    Support *worker = pworkers_->Get(i);
    Ticket *current_ticket = worker->CurrentTicket();
    if (current_ticket && current_ticket->id() == id)
      return worker;
  }

  return nullptr;
}
