#pragma once
#include <cstdint.h>
#include "ticket.h"
#include "support.h"
#include "deque.h"
#include "list.h"

#define NUM_DEQUES 5

class Dispatcher
{
  public:
    Dispatcher(List *pworkers, uint32_t *secret_page);
    void AddTicket(Ticket *ticket);
    void CancelTicket(uint32_t id);
    void ViewTicket(uint32_t id);
    void ViewTickets(STATUS status);
    Ticket *GetTicket(PRIORITY max_priority);
    void RecordFinished(Support* t);

    uint32_t GetRandomTicks(uint32_t modval=1000);
  private:
    Support *FindSupportByTicketId(uint32_t id);

    Deque ticket_lists_[5];
    List *pworkers_;
    uint32_t *secret_;
};
