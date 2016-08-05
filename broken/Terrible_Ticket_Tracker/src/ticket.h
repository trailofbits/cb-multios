#pragma once
#define MAX_EMAIL 64
#define MAX_DESC 512
#include <cstdint.h>

typedef enum {
  OPEN = 1,
  IN_PROGRESS = 2,
  REJECTED = 3,
  RESOLVED = 4,
} STATUS;

typedef enum {
  LOW = 1,
  MEDIUM = 2,
  HIGH = 3,
  SEVERE = 4,
  CRITICAL = 5,
} PRIORITY;


class Ticket
{
  public:
    static Ticket *GetTicket(char *email, char *desc, uint32_t entry_time, uint32_t duration, PRIORITY priority = LOW);
    static void DeleteTicket(Ticket *ticket);
    void UpdateStatus(STATUS status);
    void WorkOn();
    bool CheckDone();
    void Display();

    uint32_t id();
    char *email();
    char *description();
    uint32_t entry_time();
    PRIORITY priority();
    STATUS status();
    uint32_t duration();
    void* prev;
  private:
    Ticket(char *email, char *desc, uint32_t entry_time, uint32_t duration, PRIORITY priority);
    ~Ticket();

    uint32_t id_;
    char email_[MAX_EMAIL];
    char desc_[MAX_DESC];
    uint32_t entry_time_;
    PRIORITY priority_; //1-5
    STATUS status_;
    uint32_t duration_;
};
