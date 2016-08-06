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
#ifndef PACKET_ANALYSIS_H
#define PACKET_ANALYSIS_H

#include "stdlib.h"
#include "service.h"


#define FILTER_TYPE_INCLUDE 1
#define FILTER_TYPE_EXCLUDE 2

#define PACKET_MAX_SIZE 4096
#define FILTER_MAX_SIZE PACKET_MAX_SIZE

#define DCAP_FILE_MAGIC 0xDCAFDCA9
#define DCAP_FILE_MAX_PACKETS 2048
#define OPTION_HEADERS_MAX_NUM 50

#define OPTION_TYPE_STRING 1
#define OPTION_TYPE_LOCATION 2
#define OPTION_TYPE_AUTHORITY 3
#define OPTION_TYPE_DATE 4
#define OPTION_TYPE_SHARING 5
#define OPTION_TYPE_MODIFIED 6
#define OPTION_TYPE_DEVICE 7
#define OPTION_TYPE_LAST 8


typedef struct Statistics_s {
  uint32_t num_packets;
  uint32_t start_time;
  uint32_t end_time;
  uint32_t largest_packet;
  uint32_t smallest_packet;
  uint32_t num_positive_filters;
  uint32_t num_negative_filters;
  uint32_t num_packets_shown;
  uint32_t num_malformed;
  uint8_t num_option_headers;
  struct OptionHeader_s *option_headers;
} Statistics;

typedef struct PacketFilter_s {
  uint16_t size;
  uint8_t type;
  uint8_t *mask;
  uint8_t *content;
} PacketFilter;

typedef struct Packet_s {
  uint32_t timestamp;
  uint16_t size;
  uint8_t *data;
  uint16_t original_size;
  uint8_t *original_data;
} Packet;

typedef struct OptionHeader_s {
  uint8_t type;
  uint8_t length;
  struct OptionHeader_s *next;
  char *value;
} OptionHeader;


void TransmitOptionHeader(OptionHeader *header);
void DisplayStatistics(SystemState *state);
int AnalyzePacket(SystemState *state, Packet *packet);
void ProcessAllFilters(Packet *packet, SystemState *state, int *negative_match, int *positive_match);
int FilterMatch(PacketFilter *filter, Packet *packet);
#endif