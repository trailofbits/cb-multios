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
#include <cstdio.h>
#include <cstring.h>
#include "deque.h"
#include "dispatcher.h"
#include "ticket.h"
#include "time.h"
#include "support.h"

#define COMPONENT_DELIM '|'
#define MAX_COMPONENTS 8
#define MAX_COMPONENT MAX_DESC
#define NUM_PRIOS CRITICAL

#define TOSTR(x) #x
#define WITHIN(a, b, v) ((v) >= (a) && (v) <= (b))

class Scheduler
{
  private:
    List* workers_;
    Dispatcher* dispatcher_;

  public:
    Scheduler(List* workers, Dispatcher* dispatcher);
    void Run(void);
};

Scheduler::Scheduler(List* workers, Dispatcher* dispatcher)
{
  dispatcher_ = dispatcher;
  workers_ = workers;
}

void Scheduler::Run(void)
{
  for (size_t i = 0; i < workers_->Length(); ++i)
  {
    Support* worker = workers_->Get(i);
    if (worker->CurrentTicket() == nullptr)
    {
      Ticket* ticket = dispatcher_->GetTicket(worker->max_priority());
      if (ticket != nullptr)
      {
        if (ticket->prev != worker)
        {
          worker->AssignTicket(ticket);
          ticket->UpdateStatus(IN_PROGRESS);
        }
        else
        {
          dispatcher_->AddTicket(ticket);
        }
      }
    }
    else
    {
      Ticket* ticket = worker->CurrentTicket();
      ticket->WorkOn();

      if (ticket->CheckDone())
      {
        ticket->UpdateStatus(RESOLVED);
        dispatcher_->RecordFinished(worker);
      }
      else if (dispatcher_->GetRandomTicks(10) < 2)
      {
        if (ticket->priority() > HIGH)
          continue;
        ticket->UpdateStatus(REJECTED);
        worker->RemoveTicket();
      }
      else if (dispatcher_->GetRandomTicks(10) < 3)
      {
        worker->RemoveTicket();
        dispatcher_->AddTicket(ticket);
        ticket->UpdateStatus(OPEN);
      }
    }
  }
}

List workers;
Dispatcher* dispatcher;
Scheduler* scheduler;

typedef enum
{
  COMMAND_ERROR = 0,
  ADD_TICKET,
  CANCEL_TICKET,
  LIST_SUPPORT,
  LIST_FREE_SUPPORT,
  HIRE,
  FIRE,
  VIEW,
  VSTATUS,
  QUIT,
} COMMAND;

typedef int (*handler)(FILE* in, FILE* out, char** components, size_t num_components);

int handle_command_error(FILE* in, FILE* out, char** components, size_t num_components)
{
  fprintf(out, "Invalid command" EOL);
  return 0;
}

int handle_add_command(FILE* in, FILE* out, char** components, size_t num_components)
{
  PRIORITY p = LOW;
  if (components[3])
  {
    p = (PRIORITY)strtol(components[3], nullptr, 10);
  }

  if (p < LOW || p > CRITICAL)
  {
    p = LOW;
  }

  Ticket* new_ticket = Ticket::GetTicket(
      components[1], components[2], Time::GetTime(),
      dispatcher->GetRandomTicks(100), p
  );

  if (new_ticket)
  {
    dispatcher->AddTicket(new_ticket);
  }

  return 0;
}

int handle_cancel_command(FILE* in, FILE* out, char** components, size_t num_components)
{
  uint32_t cur_id = strtol(components[1], nullptr, 10);
  dispatcher->CancelTicket(cur_id);
  return 0;
}

int handle_list_command(FILE* in, FILE* out, char** components, size_t num_components)
{
  for (size_t i = 0; i < workers.Length(); i++)
  {
    workers.Get(i)->Display();
  }

  return 0;
}

int handle_list_free_command(FILE* in, FILE* out, char** components, size_t num_components)
{
  for (size_t i = 0; i < workers.Length(); i++)
  {
    Support* s = workers.Get(i);
    if (!s->CurrentTicket())
    {
      s->Display();
    }
  }

  return 0;
}

int handle_hire_command(FILE* in, FILE* out, char** components, size_t num_components)
{
  PRIORITY p = (PRIORITY)strtol(components[1], nullptr, 10);
  if (p < LOW || p > CRITICAL)
    return 0;
  Support* s = new Support(0, p);
  workers.Append(s);
  return 0;
}

int handle_fire_command(FILE* in, FILE* out, char** components, size_t num_components)
{
  PRIORITY p = (PRIORITY)strtol(components[1], nullptr, 10);
  if (p < LOW || p > CRITICAL)
    return 0;

  for (size_t i = 0; i < workers.Length(); i++)
  {
    Support* s = workers.Get(i);
    if (s->max_priority() == p)
    {
      if (s->CurrentTicket())
      {
        dispatcher->AddTicket(s->CurrentTicket());
      }

      workers.Remove(i);
      break;
    }
  }

  return 0;
}

int handle_view_command(FILE* in, FILE* out, char** components, size_t num_components)
{
  STATUS s = (STATUS)0;
  if (num_components == 2)
  {
    s = (STATUS)strtol(components[1], nullptr, 10);
    if (s > RESOLVED)
      s = (STATUS)0;
  }

  if (s)
  {
    dispatcher->ViewTickets(s);
  }
  else
  {
    for (size_t i = OPEN; i < RESOLVED; i++)
    {
      dispatcher->ViewTickets((STATUS)i);
    }
  }

  return 0;
}

int handle_status_command(FILE* in, FILE* out, char** components, size_t num_components)
{
  uint32_t tid = strtol(components[1], nullptr, 10);
  dispatcher->ViewTicket(tid);
  return 0;
}

int handle_quit(FILE* in, FILE* out, char** components, size_t num_components)
{
  fprintf(out, "TERMINATING TERRIBLE TICKET TRACKER" EOL);
  return -1;
}

handler command_handlers[] = {
  handle_command_error,
  handle_add_command,
  handle_cancel_command,
  handle_list_command,
  handle_list_free_command,
  handle_hire_command,
  handle_fire_command,
  handle_view_command,
  handle_status_command,
  handle_quit,
};


COMMAND read_command(FILE* f, char*** components, size_t* num_components)
{
  COMMAND c = COMMAND_ERROR;
  char* component = nullptr;
  char** comps = *components;
  *num_components = 0;

  for (size_t i = 0; i < MAX_COMPONENTS; ++i)
  {
    component = new char[MAX_COMPONENT + 1];
    memset(component, 0, MAX_COMPONENT + 1);
    c = COMMAND_ERROR;

    int ret = freaduntil(component, MAX_COMPONENT, COMPONENT_DELIM, f);

    if (ret > 1) // So two successive COMPONENT_DELIM ends command
    {
      comps[i] = component;
      *num_components = i + 1;
    }
    else
    {
      delete component;
      break;
    }
  }

  if (comps[0] == nullptr)
  {
    goto done;
  }

  if (strcmp(comps[0], TOSTR(ADD_TICKET)) == 0)
  {
    if (!WITHIN(3, 4, *num_components))
      goto done;

    c = ADD_TICKET;
  }
  else if (strcmp(comps[0], TOSTR(CANCEL_TICKET)) == 0)
  {
    if (!WITHIN(2, 2, *num_components))
      goto done;

    c = CANCEL_TICKET;
  }
  else if (strcmp(comps[0], TOSTR(LIST_SUPPORT)) == 0)
  {
    if (!WITHIN(1, 1, *num_components))
      goto done;

    c = LIST_SUPPORT;
  }
  else if (strcmp(comps[0], TOSTR(LIST_FREE_SUPPORT)) == 0)
  {
    if (!WITHIN(1, 1, *num_components))
      goto done;

    c = LIST_FREE_SUPPORT;
  }
  else if (strcmp(comps[0], TOSTR(HIRE)) == 0)
  {
    if (!WITHIN(2, 2, *num_components))
      goto done;

    c = HIRE;
  }
  else if (strcmp(comps[0], TOSTR(FIRE)) == 0)
  {
    if (!WITHIN(2, 2, *num_components))
      goto done;

    c = FIRE;
  }
  else if (strcmp(comps[0], TOSTR(VIEW)) == 0)
  {
    if (!WITHIN(1, 2, *num_components))
      goto done;

    c = VIEW;
  }
  else if (strcmp(comps[0], TOSTR(VSTATUS)) == 0)
  {
    if (!WITHIN(2, 2, *num_components))
      goto done;

    c = VSTATUS;
  }
  else if (strcmp(comps[0], TOSTR(QUIT)) == 0)
  {
    c = QUIT;
  }

done:
  return c;
}

void run_server(FILE* in, FILE* out, unsigned char* secrets)
{
  COMMAND command;
  size_t num_components;
  char** components = new char*[MAX_COMPONENTS];

  Time::Reset();
  dispatcher = new Dispatcher(&workers, (uint32_t*)(secrets));
  scheduler = new Scheduler(&workers, dispatcher);


  // Setup two starter workers
  char *commands[2] = {(char *)"HIRE", (char *)"3"};
  handle_hire_command(in, out, commands, 2);
  commands[1] = (char *)"5";
  handle_hire_command(in, out, commands, 2);

  fprintf(out, "Welcome to the terrible ticket tracker" EOL);
  for (;;)
  {
    // Tick
    Time::GetTime();
    scheduler->Run();

    // Clear previous components
    for (size_t i = 0; i < MAX_COMPONENTS; ++i)
    {
      if (components[i] != nullptr)
      {
        delete components[i];
        components[i] = nullptr;
      }
    }

    // Read components
    fprintf(out, "$ ");
    command = read_command(in, &components, &num_components);

    // Dispatch command
    int ret = command_handlers[command](in, out, components, num_components);
    if (ret != 0)
    {
      break;
    }

    fprintf(out, "OK" EOL);
  }
}

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    unsigned char *secret_page = (unsigned char *)secret_page_i;
    fxlat(stdin, "EREH_EULAV_MODNAR");
    fxlat(stdout, "EREH_EULAV_MODNAR");
    run_server(stdin, stdout, secret_page);
    return 0;
}
