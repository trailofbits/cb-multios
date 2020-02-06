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
#include "libcgc.h"
#include "cgc_stdint.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_malloc.h"
#include "cgc_transport.h"
#include "cgc_user.h"
#include "cgc_fs.h"
#include "cgc_cgcrpc.h"
#include "cgc_cgcmb.h"


int main(int cgc_argc, char *cgc_argv[]) 
{
  TransportMessage *tpMessage;
  CGCMB_Message *mbMessage;

  cgc_mbServerState = cgc_calloc(sizeof(CGCMB_ServerState));
  cgc_mbServerState->state = INITIAL;
  cgc_mbServerState->dialect = 0;
  cgc_mbServerState->sessionKey = 0;

  cgc_srand();
  
  cgc_GenerateUsers();
  cgc_InitializeFileSystem();
  cgc_InitializeCGCRPC();
 
TOP:
  if (cgc_ReceiveTransportMessage(&tpMessage) != 0)
  {
    goto NEXT_MSG;
  }

  if (cgc_ReceiveCGCMBMessage(tpMessage, &mbMessage) != 0)
  {
    goto NEXT_MSG;
  }

  if (cgc_ParseCGCMBMessage(mbMessage) != 0)
  {
    goto NEXT_MSG;
  }

  if (cgc_HandleCGCMBMessage(mbMessage) != 0)
  {
    return 0;
  }
    
NEXT_MSG:
  cgc_DestroyCGCMBMessage(&mbMessage);
  cgc_DestroyTransportMessage(&tpMessage);
  goto TOP;

}
