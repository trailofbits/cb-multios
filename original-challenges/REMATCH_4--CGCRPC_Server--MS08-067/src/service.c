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
#include "stdlib.h"
#include "stdio.h"
#include "malloc.h"
#include "transport.h"
#include "user.h"
#include "fs.h"
#include "cgcrpc.h"
#include "cgcmb.h"


int main(void) 
{
  TransportMessage *tpMessage;
  CGCMB_Message *mbMessage;

  mbServerState = calloc(sizeof(CGCMB_ServerState));
  mbServerState->state = INITIAL;
  mbServerState->dialect = 0;
  mbServerState->sessionKey = 0;

  srand();
  
  GenerateUsers();
  InitializeFileSystem();
  InitializeCGCRPC();
 
TOP:
  if (ReceiveTransportMessage(&tpMessage) != 0)
  {
    goto NEXT_MSG;
  }

  if (ReceiveCGCMBMessage(tpMessage, &mbMessage) != 0)
  {
    goto NEXT_MSG;
  }

  if (ParseCGCMBMessage(mbMessage) != 0)
  {
    goto NEXT_MSG;
  }

  if (HandleCGCMBMessage(mbMessage) != 0)
  {
    return 0;
  }
    
NEXT_MSG:
  DestroyCGCMBMessage(&mbMessage);
  DestroyTransportMessage(&tpMessage);
  goto TOP;

}
