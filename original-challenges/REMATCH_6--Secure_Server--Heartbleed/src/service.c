/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2016 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <libcgc.h>
#include "stdint.h"
#include "stdio.h"
#include "malloc.h"
#include "sls.h"
#include "msls.h"
#include "application.h"

int main(void)
{
  // Setup server state
  SERVER_STATE *state = calloc(sizeof(SERVER_STATE));

  state->functions =  msls_get_sls_functions();
  state->functions->set_cookie(state);
  state->is_initialized = 1;

  // Run Server
  while (!state->should_exit)
  {
    SLS_MESSAGE *msg = state->functions->receive_msg(state);

    if (msg == NULL)
    {
      debug_print("Skipping invalid MSG\n");
      continue;
    }

    CLIENT_CONTEXT *connection = state->functions->lookup_context(state, msg->connection_id);

    switch(msg->type)
    {
      case SLS_TYPE_CHANGESPEC:
        if (connection && connection->is_connected)
        {
          state->functions->handle_changespec(state, connection, msg);
        }
        break;
      case SLS_TYPE_ERROR:
        state->functions->handle_error(state, msg);
        break;
      case SLS_TYPE_HANDSHAKE:
        state->functions->handle_handshake(state, msg);
        break;
      case SLS_TYPE_APPLICATION:
        if (connection && connection->is_connected)
        {
          state->functions->handle_application(state, connection, msg);
        }
        break;
      case SLS_TYPE_HEARTBEAT:
        if (!connection || !connection->in_handshake)
        {
          state->functions->handle_heartbeat(msg);
        }
        break;
      case SLS_TYPE_SHUTDOWN:
      {
        state->should_exit = 1;
        break;
      }
      default:
        break;
    }
    free(msg->message);
    free(msg);
  }
  state->functions->cleanup(state);
  free(state);
  return 0;
}
