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
#include "deque.h"
#include <cstdlib.h>
#include <cstring.h>
#include <cstdio.h>

Deque::Deque()
{
    idx_0_ = 0;
    size_ = 0;
    cap_ = 8;
    tickets_ = new Ticket*[cap_];
}

Deque::~Deque()
{
    for (int i = 0; i < size_; i++)
    {
        int idx = (idx_0_ + i) % cap_;
        Ticket::DeleteTicket(tickets_[idx]);
    }
    delete tickets_;
}

Ticket* Deque::Find(uint32_t ID)
{
  for (size_t i = 0; i < cap_; i++)
  {
    if (tickets_[i] && tickets_[i]->id() == ID)
    {
      return tickets_[i];
    }
  }

  return nullptr;
}

bool Deque::Remove(Ticket* ticket)
{
  return false;
}

void Deque::Append(Ticket *ticket)
{
    if (!ticket)
        return;

    if (size_ == cap_)
        Expand();

    uint32_t idx_f = (idx_0_ + size_) % cap_;
    tickets_[idx_f] = ticket;
    ++size_;
}

void Deque::AppendLeft(Ticket *ticket)
{
    if (!ticket)
        return;

    if (size_ == cap_)
        Expand();

    idx_0_ = (idx_0_ + (cap_ - 1)) % cap_;
    tickets_[idx_0_] = ticket;
    ++size_;
}

Ticket *Deque::Pop()
{
    if (!size_)
        return nullptr;

    uint32_t idx_f = (idx_0_ + (size_ - 1)) % cap_;
    Ticket *ticket = tickets_[idx_f];
    --size_;
    TryShrink();
    return ticket;
}

Ticket *Deque::PopLeft()
{
    if (!size_)
      return nullptr;
    Ticket *ticket = tickets_[idx_0_];
    idx_0_ = (idx_0_ + 1) % cap_;
    --size_;
    TryShrink();
    return ticket;
}

uint32_t Deque::Count()
{
    return size_;
}

void Deque::Expand()
{
    uint32_t new_cap = cap_ << 1;
    Ticket **new_array = new Ticket*[new_cap];

    if (idx_0_ + size_ > cap_)
    {
        memcpy(new_array, &tickets_[idx_0_], sizeof(Ticket *) * (cap_ - idx_0_));
        memcpy(&new_array[cap_ - idx_0_], tickets_, sizeof(Ticket *) * (size_ - (cap_ - idx_0_)));
    }
    else
    {
        memcpy(new_array, &tickets_[idx_0_], sizeof(Ticket *) * size_);
    }
    delete tickets_;
    tickets_ = new_array;
    idx_0_ = 0;
    cap_ = new_cap;
}

void Deque::TryShrink()
{
    if (size_ >= (cap_ >> 1) || cap_ <= 8)
        return;

    uint32_t new_cap = cap_ >> 1;
    Ticket **new_array = new Ticket*[new_cap];

    if (idx_0_ + size_ > cap_)
    {
        memcpy(new_array, &tickets_[idx_0_], sizeof(Ticket *) * (cap_ - idx_0_));
        memcpy(&new_array[cap_ - idx_0_], tickets_, sizeof(Ticket *) * (size_ - (cap_ - idx_0_)));
    }
    else
    {
        memcpy(new_array, &tickets_[idx_0_], sizeof(Ticket *) * size_);
    }

    delete tickets_;
    tickets_ = new_array;
    idx_0_ = 0;
    cap_ = new_cap;
}
