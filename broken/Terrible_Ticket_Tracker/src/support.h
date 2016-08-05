#pragma once

#include <cstdint.h>
#include "ticket.h"

class Support
{
  public:
    Support(uint32_t contact_info, PRIORITY max_priority = HIGH);
    ~Support();

    bool AssignTicket(Ticket *ticket);
    bool UpdateTicket(STATUS status);
    Ticket *CurrentTicket();
    Ticket *RemoveTicket();
    void Display(void);

    uint32_t id();
    uint32_t contact_info();
    PRIORITY max_priority();
  private:
    Ticket *ticket_;
    uint32_t support_id_;
    uint32_t contact_info_;
    PRIORITY max_priority_;
};
