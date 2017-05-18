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
#include "cgc_io.h"

// Receives the initialization packet and checks format
// Returns 0 for success, -1 for failure
int cgc_ReceiveAndVerifyInitializationPacket(SystemState *state) {

  uint32_t sync;
  cgc_ReceiveBytes(&sync, sizeof(sync));
  if (sync != 0xA55AA55A) {
    cgc_FailAndTerminate("improper initialization format");
  }
  cgc_ReceiveBytes(&state->mode, sizeof(state->mode));
  if (state->mode > MODE_STREAM) {
    cgc_FailAndTerminate("unsupported mode");
  }
  cgc_ReceiveBytes(&state->display_flags, sizeof(state->display_flags));
  cgc_ReceiveBytes(&state->num_filters, sizeof(state->num_filters));
  if (state->num_filters > MAX_FILTERS) {
    cgc_FailAndTerminate("too many filters");
  }
  if (cgc_allocate(sizeof(Statistics), 1, (void **)&state->stats) != 0) {
    cgc_FailAndTerminate("Failed to allocate statistics");
  }
  cgc_bzero((char *)state->stats, sizeof(Statistics));

  return 0;
}


// Receives packet filters and checks format
// Returns 0 for success, -1 for failure
int cgc_ReceiveAndVerifyFilters(SystemState *state) {
  // While filters remain:
  for (int current_filter = 0; current_filter < state->num_filters; current_filter++) {
    // Allocate data for one filter struct
    PacketFilter *filter;
    if (cgc_allocate(sizeof(PacketFilter), 1, (void **)&filter) != 0) {
      cgc_FailAndTerminate("failed to allocate packet filter");
    }
    state->filters[current_filter] = filter;
    // Receive header data for one filter
    cgc_ReceiveBytes(&filter->size, sizeof(filter->size));
    if (filter->size > FILTER_MAX_SIZE) {
      cgc_FailAndTerminate("filter too large");
    }
    cgc_ReceiveBytes(&filter->type, sizeof(filter->type));
    if (filter->type > FILTER_TYPE_EXCLUDE) {
      cgc_FailAndTerminate("invalid filter type");
    }
    // Allocate data for mask and filter
    if (cgc_allocate(filter->size, 1, (void **)&filter->mask) != 0) {
      cgc_FailAndTerminate("failed allocating filter mask");
    }
    cgc_bzero((char *)filter->mask, filter->size);
    if (cgc_allocate(filter->size, 1, (void **)&filter->content) != 0) {
      cgc_FailAndTerminate("failed allocating filter content");
    }
    cgc_bzero((char *)filter->content, filter->size);
    // Read mask
    cgc_ReceiveBytes(filter->mask, filter->size);
    // Read filter
    cgc_ReceiveBytes(filter->content, filter->size);
    if (filter->type == FILTER_TYPE_INCLUDE) {
      state->stats->num_positive_filters++;
    }
    else {
      state->stats->num_negative_filters++;
    }
  }
  return 0;
}

// Receive entire DCAP file, analyze, and print output
// Returns 0 for success, -1 for failure
int cgc_ReceiveAndProcessFile(SystemState *state) {
  // Read file header
  uint32_t magic;
  cgc_ReceiveBytes(&magic, sizeof(magic));
  if (magic != DCAP_FILE_MAGIC) {
    cgc_FailAndTerminate("invalid DCAP file");
  }
  // Process file header and populate state variable
  cgc_ReceiveBytes(&state->stats->start_time, sizeof(state->stats->start_time));
  cgc_ReceiveBytes(&state->stats->end_time, sizeof(state->stats->end_time));
  cgc_ReceiveBytes(&state->stats->num_packets, sizeof(state->stats->num_packets));
  if (state->stats->num_packets > DCAP_FILE_MAX_PACKETS) {
    cgc_FailAndTerminate("too many packets");
  }
  cgc_ReceiveBytes(&state->stats->num_option_headers, sizeof(state->stats->num_option_headers));
  if (state->stats->num_option_headers > OPTION_HEADERS_MAX_NUM) {
    cgc_FailAndTerminate("too many option headers");
  }
  // Read optional headers
  OptionHeader *option=NULL;
  for (int num=0; num < state->stats->num_option_headers; num++) {
    if (option == NULL) {
      // Allocate first option header
      if (cgc_allocate(sizeof(OptionHeader), 1, (void **)&state->stats->option_headers) != 0) {
        cgc_FailAndTerminate("error allocating first option header");
      }
      option = state->stats->option_headers;
    } else {
      // Allocate subsequent option headers
      if (cgc_allocate(sizeof(OptionHeader), 1, (void **)&option->next) != 0) {
        cgc_FailAndTerminate("error allocating option header");
      }
      option = option->next;
    }
    cgc_bzero((void *)option, sizeof(OptionHeader));
    cgc_ReceiveBytes(&option->type, sizeof(option->type));
    cgc_ReceiveBytes(&option->length, sizeof(option->length));
    // Allow 1 extra byte to ensure null termination 
    if (cgc_allocate(option->length + 1, 1, (void **)&option->value)) {
      cgc_FailAndTerminate("failed to allocate option header value");
    }
    cgc_bzero(option->value, option->length + 1);
    cgc_ReceiveBytes(option->value, option->length);
  }

  // Receive and process all packets
  for (int num=0; num < state->stats->num_packets; num++) {
    // Get meta data
    Packet packet;
    // Receive timestamp and size
    cgc_ReceiveBytes(&packet.timestamp, sizeof(packet.timestamp));
    cgc_ReceiveBytes(&packet.size, sizeof(packet.size));
    if (packet.size > PACKET_MAX_SIZE) {
      cgc_FailAndTerminate("packet too large");
    }
    if (cgc_allocate(packet.size, 1, (void **)&packet.data) != 0) {
      cgc_FailAndTerminate("Failed allocating packet data");
    }
    cgc_ReceiveBytes(packet.data, packet.size);
    packet.original_size = packet.size;
    packet.original_data = packet.data;
    cgc_AnalyzePacket(state, &packet);
    cgc_deallocate(packet.original_data, packet.original_size);
  }
  return 0;
}

// Receive packets in loop, analyze, and print output
// Will cgc_exit upon error or receipt of special 'end packet'
// Returns 0 for success, -1 for failure
int cgc_ReceiveAndProcessStream(SystemState *state) {
  Packet packet;
  uint32_t counter = 1;
  cgc_ReceiveBytes(&packet.size, sizeof(packet.size));
  while (packet.size != 0) {
    if (packet.size > PACKET_MAX_SIZE) {
      cgc_FailAndTerminate("packet too large");
    }
    state->stats->num_packets++;
    if (cgc_allocate(packet.size, 1, (void **)&packet.data) != 0) {
      cgc_FailAndTerminate("Failed allocating packet data");
    }
    cgc_ReceiveBytes(packet.data, packet.size);
    packet.timestamp = counter++;
    packet.original_size = packet.size;
    packet.original_data = packet.data;
    cgc_AnalyzePacket(state, &packet);
    cgc_deallocate(packet.data, packet.size);
    cgc_ReceiveBytes(&packet.size, sizeof(packet.size));
  }
  return 0;
}


