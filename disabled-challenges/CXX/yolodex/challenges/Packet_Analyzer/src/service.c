/*

Author: Debbie Nuttall <debbie@cromulence.co>

Copyright (c) 2015 Cromulence LLC

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
#include "cgc_service.h"
#include "cgc_stdlib.h"
#include "cgc_packet_analysis.h"
#include "cgc_packet_io.h"
#include "cgc_io.h"

int main(int cgc_argc, char *cgc_argv[]) {
  SystemState state;
  
  // Initialize Parser
  if (cgc_ReceiveAndVerifyInitializationPacket(&state) != 0) {
    return -1;
  }

  // Setup Filters
  if (cgc_ReceiveAndVerifyFilters(&state) != 0) {
    return -1;
  }

  // Parse packets
  switch (state.mode) {
    case MODE_FILE: {
      cgc_ReceiveAndProcessFile(&state);
      break;
    }
    case MODE_STREAM: {
      cgc_ReceiveAndProcessStream(&state);
      break;
    }
    default: {
      break;
    }
  } 

  // Display statistics
  if (state.display_flags & DISPLAY_STATS) {
    cgc_DisplayStatistics(&state);
  }
  cgc_TransmitFormattedBytes("Goodbye.\n");

  return 0;
}