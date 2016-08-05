#pragma once

#include <cstdint.h>
#include "ticket.h"

class Deque
{
  public:
    Deque();
    ~Deque();
    void Append(Ticket *ticket);
    void AppendLeft(Ticket *ticket);
    Ticket *Find(uint32_t ID);
    bool Remove(Ticket* ticket);
    Ticket *Pop();
    Ticket *PopLeft();
    uint32_t Count();
  private:
    void Expand();
    void TryShrink();

    Ticket **tickets_;
    uint32_t idx_0_;
    uint32_t size_;
    uint32_t cap_;
};
