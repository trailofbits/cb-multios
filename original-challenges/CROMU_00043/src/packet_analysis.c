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


#include <libcgc.h>
#include "service.h"
#include "packet_analysis.h"
#include "io.h"

enum authorities {SELF, LAW_ENFORCEMENT, UNIVERSITY, EMPLOYER, NETWORK_PROVIDER, NUM_AUTHORITIES};
char *authority_names[NUM_AUTHORITIES] = {"Self", "Law Enforcement", "University", "Employer", "Network Provider"};
enum physical_types {WIRE, RADIO, RAW, NUM_PHYSICAL_TYPES};
char *physical_type_names[NUM_PHYSICAL_TYPES] = {"Wire", "Radio", "Raw"};
char *physical_wire_speeds[4] = {"1,000", "10,000", "100,000", "1,000,000"};
char *debug_type_names[6] = {"PING", "PONG", "TRACEROUTE", "QUERY", "CONNECT", "REPLY"};

void DisplayFormatted(SystemState *state, int layer, char *format, ...) {
  if (state->display_flags & layer) {
    va_list arg_list;
    va_start(arg_list, format);
    vTransmitFormattedBytes(format, arg_list);
    va_end(arg_list);
  }
}

void TransmitOptionHeader(OptionHeader *header) {
  switch(header->type) {
    case OPTION_TYPE_STRING: {
#ifdef PATCHED
      TransmitBytes(header->value, strlen(header->value));
#else
      TransmitFormattedBytes(header->value);
#endif
      TransmitBytes("\n", 1);
      break;
    }
    case OPTION_TYPE_LOCATION: {
      // lat\x00long or address
      if (count_strings(header->value) == 2) {
        TransmitFormattedBytes("GPS Coordinates: +s Latitude, +s Longitude\n", header->value, next_string(header->value));
      } else {
        TransmitFormattedBytes("Address: +s\n", header->value);
      }
      break;
    }
    case OPTION_TYPE_AUTHORITY: {
      int authority = atoi(header->value);
      if ((authority < NUM_AUTHORITIES) && (authority >= 0)) {
        TransmitFormattedBytes("Capturing Authority: +s\n", authority_names[authority]);
      } else {
        TransmitFormattedBytes("Capturing Authority Unknown\n");
      }
      break;
    }
    case OPTION_TYPE_DATE: {
      TransmitFormattedBytes("Capture Date: +s\n", header->value);
      break;
    }
    case OPTION_TYPE_SHARING: {
      int sharing_allowed = atoi(header->value);
      if (sharing_allowed == 1) {
        TransmitFormattedBytes("Sharing Allowed: True\n");
      } else {
        TransmitFormattedBytes("Sharing Allowed: False\n");
      }
      break;
    }
    case OPTION_TYPE_MODIFIED: {
      int modified = atoi(header->value);
      if (modified == 1) {
        TransmitFormattedBytes("This content has been modified\n");
      } else {
        TransmitFormattedBytes("This content has not been modified from the original\n");
      }
      break;
    }
    case OPTION_TYPE_DEVICE: {
      TransmitFormattedBytes("Capturing Device: +s\n", header->value);
      break;
    }
    default: {
      break;
    }
  }
}

// Display statistics gathered during packet analysis
void DisplayStatistics(SystemState *state) {
  TransmitFormattedBytes("Final Statistics:\n");
  TransmitFormattedBytes("\tTotal Packets: +d\n", state->stats->num_packets);
  TransmitFormattedBytes("\tStart Time: +x\n", state->stats->start_time);
  TransmitFormattedBytes("\tEnd Time: +x\n", state->stats->end_time);
  TransmitFormattedBytes("\tLargest Packet: +d\n", state->stats->largest_packet);
  TransmitFormattedBytes("\tSmallest Packet: +d\n", state->stats->smallest_packet);
  TransmitFormattedBytes("\tNumber of malformed packets: +d\n", state->stats->num_malformed);
  TransmitFormattedBytes("\tNumber of packets shown +d\n", state->stats->num_packets_shown);
  TransmitFormattedBytes("Option Headers:\n");
  OptionHeader *header = state->stats->option_headers;
  while(header != NULL) {
    TransmitOptionHeader(header);
    header = header->next;
  }
  TransmitBytes("\n", 1);
}

// Check if the packet matches the filter
// return 1 for match, 0 for no match
int FilterMatch(PacketFilter *filter, Packet *packet) {
  if (filter->size > packet->size) {
    return 0;
  }
  if (packet->data == NULL) {
    return 0;
  }
  for (int i = 0; i < filter->size; i++) {
    if ((packet->data[i] & filter->mask[i]) != (filter->content[i] & filter->mask[i])) {
      return 0;
    }
  }
  return 1;
}

// Check all filters for a match
void ProcessAllFilters(Packet *packet, SystemState *state, int *negative_match, int *positive_match) {
  int pos = 0;
  int neg = 0;
  for (int i=0; i < state->num_filters; i++) {
    PacketFilter *filter = state->filters[i];
    if (FilterMatch(filter, packet) == 1) {
      if (filter->type == FILTER_TYPE_INCLUDE) {
        pos += 1;
      } else {
        neg += 1;
      }
    }
  }
  *negative_match = neg;
  *positive_match = pos;
}

uint32_t CalculateChecksum(uint8_t *data, uint16_t size) {
  uint32_t checksum = 0;
  for (int i=0; i< size; i++) {
    checksum += data[i];
  }
  return checksum;
}

// Analyze the Physical layer of the packet
// Updates packet struct to 'remove' physical header
// returns 0 for success
// returns -1 for bad packet
int AnalyzePhysicalLayer(SystemState *state, Packet *packet) {
  int length = *(int *)(packet->data + 8);
  if (length > packet->size) {
    DisplayFormatted(state, DISPLAY_PHYSICAL, "Invalid Packet Length: +x (+x)\n", length, packet->size);
    return -1;
  }
  if (length < 14) {
    DisplayFormatted(state, DISPLAY_PHYSICAL, "Packet too short: +d\n", length);
    return -1;
  }
  DisplayFormatted(state, DISPLAY_PHYSICAL, "Physical Length:+d\n", length);
  uint16_t type = (*(int *)(packet->data + 12)) - 1;

  if (type >= NUM_PHYSICAL_TYPES) {
    DisplayFormatted(state, DISPLAY_PHYSICAL, "Invalid Physical Type\n");
    return -1;
  }
  DisplayFormatted(state, DISPLAY_PHYSICAL, "Physical Type: +s\n", physical_type_names[type]);
  if (type == WIRE) {
    if (length < 20) {
      DisplayFormatted(state, DISPLAY_PHYSICAL, "Packet too short: +d\n", length);
      return -1;
    }
    uint16_t wirespeed = (*(uint16_t *)(packet->data + 14)) - 1;
    if (wirespeed >= 4) {
      DisplayFormatted(state, DISPLAY_PHYSICAL, "Invalid Wire speed\n");
      return -1;
    }
    DisplayFormatted(state, DISPLAY_PHYSICAL, "Wire Speed: +s\n", physical_wire_speeds[wirespeed]);
    uint32_t checksum = (*(uint32_t *)(packet->data + 16));
    packet->data += 20;
    packet->size -= 20;
    if (CalculateChecksum(packet->data, packet->size) != checksum) {
      DisplayFormatted(state, DISPLAY_PHYSICAL, "Invalid Physical Layer Checksum: got +x, expected +x\n", checksum, CalculateChecksum(packet->data, packet->size));
      return -1;
    }
  } else if (type == RADIO) {
    if (length < 42) {
      DisplayFormatted(state, DISPLAY_PHYSICAL, "Packet too short: +d\n", length);
      return -1;
    }
    DisplayFormatted(state, DISPLAY_PHYSICAL, "Source Address: +x\n", *(int *)(packet->data + 14));
    DisplayFormatted(state, DISPLAY_PHYSICAL, "Destination Address: +x\n", *(int *)(packet->data + 18));
    DisplayFormatted(state, DISPLAY_PHYSICAL, "Transmit strength: +u\n", *(uint32_t *)(packet->data + 22));
    DisplayFormatted(state, DISPLAY_PHYSICAL, "Receive strength: +u\n", *(uint32_t *)(packet->data + 26));
    DisplayFormatted(state, DISPLAY_PHYSICAL, "Frequency: +d\n", *(uint32_t  *)(packet->data + 30));
    DisplayFormatted(state, DISPLAY_PHYSICAL, "SNR: +u\n", *(uint32_t  *)(packet->data + 34)); 
    // Checksum intentionally not verified
    packet->data += 42;
    packet->size -= 42;
  } else if (type == RAW) {
    if (state->display_flags & DISPLAY_PHYSICAL) {
      HexDump(packet->data + 14, packet->size - 14);
    }
    return -1;
  } else {
     DisplayFormatted(state, DISPLAY_PHYSICAL, "Invalid Physical Type\n", type);
    return -1;
  }
  // Verify ECC
  return 0;
}

// Analyze the Transport layer of the packet
// Updates packet struct to 'remove' Transport header
// returns 0 for success
// returns -1 for bad packet
int AnalyzeTransportLayer(SystemState *state, Packet *packet) {
  if (packet->size < 4) {
    DisplayFormatted(state, DISPLAY_TRANSPORT, "Transport Layer too short\n");
    return -1;
  }
  int type = *(int *)(packet->data);
  if (type == 1) {
    // Stream
    if (packet->size < 22) {
      DisplayFormatted(state, DISPLAY_TRANSPORT, "Transport Layer too short\n");
      return -1;
    }   
    DisplayFormatted(state, DISPLAY_TRANSPORT, "Transport Type: STREAM\n");
    DisplayFormatted(state, DISPLAY_TRANSPORT, "Stream number: +u\n", *(int *)(packet->data + 4));
    DisplayFormatted(state, DISPLAY_TRANSPORT, "Sequence number: +u\n", *(int *)(packet->data + 8));
    DisplayFormatted(state, DISPLAY_TRANSPORT, "Window: +d\n", *(uint16_t *)(packet->data + 12));
    DisplayFormatted(state, DISPLAY_TRANSPORT, "Acknowledgment: +x\n", *(int *)(packet->data + 14));
    DisplayFormatted(state, DISPLAY_TRANSPORT, "Length: +d\n", *(int *)(packet->data + 18));
    packet->data += 22;
    packet->size -= 22;
  } else if (type == 2) {
    // Message
    if (packet->size < 8) {
      DisplayFormatted(state, DISPLAY_TRANSPORT, "Transport Layer too short\n");
      return -1;
    }
    DisplayFormatted(state, DISPLAY_TRANSPORT, "Transport Type: MESSAGE\n");
    DisplayFormatted(state, DISPLAY_TRANSPORT, "Length: +d\n", *(int *)(packet->data + 4));
    packet->data += 8;
    packet->size -= 8;
  } else {
    DisplayFormatted(state, DISPLAY_TRANSPORT, "Invalid Transport Type\n");
    return -1;
  } 
  return 0;
}

// Analyze the Network layer of the packet
// Updates packet struct to 'remove' Network header
// returns 0 for success
// returns -1 for bad packet
int AnalyzeNetworkLayer(SystemState *state, Packet *packet) {
  if (packet->size < 6) {
    DisplayFormatted(state, DISPLAY_NETWORK, "Network layer too short\n");
    return -1;
  }
  uint16_t network_type = *(uint16_t *)(packet->data + 4);
  if (network_type == 1) {
    DisplayFormatted(state, DISPLAY_NETWORK, "Network type: Endpoint\n");
    if (packet->size < 14) {
      DisplayFormatted(state, DISPLAY_NETWORK, "Network layer too short\n");
      return -1;
    }
    DisplayFormatted(state, DISPLAY_NETWORK, "Source Address: +x\n", *(int *)(packet->data + 6));
    DisplayFormatted(state, DISPLAY_NETWORK, "Destination Address: +x\n", *(int *)(packet->data + 10));
    packet->data += 14;
    packet->size -= 14;
  } else if (network_type == 2) {
    DisplayFormatted(state, DISPLAY_NETWORK, "Network type: Broadcast\n");
    if (packet->size < 10) {
      DisplayFormatted(state, DISPLAY_NETWORK, "Network layer too short\n");
      return -1;
    }
    DisplayFormatted(state, DISPLAY_NETWORK, "Source Address: +x\n", *(int *)(packet->data + 6));
    packet->data += 10;
    packet->size -= 10;
  } else if (network_type == 3) {
    DisplayFormatted(state, DISPLAY_NETWORK, "Network type: Debug\n");
    if (packet->size < 22) {
      DisplayFormatted(state, DISPLAY_NETWORK, "Network layer too short\n");
      return -1;
    }
    uint16_t debug_type = *(uint16_t *)(packet->data + 6) - 1;
    if (debug_type >= 6) {
      DisplayFormatted(state, DISPLAY_NETWORK, "Invalid network debug type\n");
      return -1;
    }
    DisplayFormatted(state, DISPLAY_NETWORK, "Network debug type: +s\n", debug_type_names[debug_type]);
    DisplayFormatted(state, DISPLAY_NETWORK, "Source Address: +x\n",  *(uint32_t *)(packet->data + 8)); 
    DisplayFormatted(state, DISPLAY_NETWORK, "Destination Address: +x\n",*(uint32_t *)(packet->data + 12));
    DisplayFormatted(state, DISPLAY_NETWORK, "Hop Count: +u\n", *(uint16_t *)(packet->data + 16));
    DisplayFormatted(state, DISPLAY_NETWORK, "Timestamp: +u\n", *(uint32_t *)(packet->data + 18));
    packet->data += 22;
    packet->size -= 22;
  } else {
    DisplayFormatted(state, DISPLAY_NETWORK, "Invalid network type\n");
    return -1;
  }
  return 0;
}

// Analyze the Application layer of the packet
// Updates packet struct to 'remove' Application header
// returns 0 for success
// returns -1 for bad packet
int AnalyzeApplicationLayer(SystemState *state, Packet *packet) {
  if (packet->size < 6) {
    DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
    return -1;
  }
  uint32_t application_length = *(uint32_t *)(packet->data);
  uint16_t application_type = *(uint16_t *)(packet->data + 4);
  if (application_type == 1) {
    DisplayFormatted(state, DISPLAY_APPLICATION, "Application type: Audio Stream\n");
    if (packet->size < 12) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    }
    DisplayFormatted(state, DISPLAY_APPLICATION, "Encoding type: +u\n", *(uint16_t *)(packet->data + 6));
    DisplayFormatted(state, DISPLAY_APPLICATION, "Bit rate: +u\n", *(uint32_t *)(packet->data + 8));
    packet->data += 12;
    packet->size -= 12;
  } else if (application_type == 2) {
    DisplayFormatted(state, DISPLAY_APPLICATION, "Application type: Video Stream\n");
    if (packet->size < 14) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    }
    DisplayFormatted(state, DISPLAY_APPLICATION, "X Resolution: +u\n", *(uint16_t *)(packet->data + 8));
    DisplayFormatted(state, DISPLAY_APPLICATION, "Y Resolution: +u\n", *(uint16_t *)(packet->data + 10));
    DisplayFormatted(state, DISPLAY_APPLICATION, "Video Option Headers: \n");
    uint16_t num_options = *(uint16_t *)(packet->data + 12);
    packet->data += 14;
    packet->size -= 14;
    char buffer[256];
    while ((num_options > 0) && (packet->size != 0)) {
      bzero(buffer, sizeof(buffer));
      uint8_t length = *(uint8_t *)(packet->data);
      packet->data++;
      packet->size--;
      if (length > packet->size) {
        DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
        return -1;
      }
      memcpy(buffer, (char *)packet->data, length);
      DisplayFormatted(state, DISPLAY_APPLICATION, "\t+s\n", buffer);
      packet->data += length;
      packet->size -= length;
      num_options--;
    }
  } else if (application_type == 3) {
    DisplayFormatted(state, DISPLAY_APPLICATION, "Application type: File\n");
    if (packet->size < 70) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    }
    char namebuf[33];
    bzero(namebuf, sizeof(namebuf));
    memcpy(namebuf, (char *)(packet->data + 6), 32);
    DisplayFormatted(state, DISPLAY_APPLICATION, "Filename: +s\n", namebuf);
    memcpy(namebuf, (char *)(packet->data + 6 + 32), 32);
    DisplayFormatted(state, DISPLAY_APPLICATION, "File type: +s\n", namebuf);
    packet->data += 70;
    packet->size -= 70;
  } else if (application_type == 4) {
    DisplayFormatted(state, DISPLAY_APPLICATION, "Application type: Email\n");
    packet->data += 6;
    packet->size -= 6;

    if (packet->size == 0) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    }
    uint8_t length = *(uint8_t *)packet->data;
    packet->data++;
    packet->size--;
    if (packet->size < length) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    } 
    char buffer[256];
    bzero(buffer, sizeof(buffer));
    memcpy(buffer, (char *)packet->data, length);
    DisplayFormatted(state, DISPLAY_APPLICATION, "From: +s\n", buffer);
    packet->data += length;
    packet->size -= length;

    if (packet->size == 0) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    }
    length = *(uint8_t *)packet->data;
    packet->data++;
    packet->size--;
    #ifdef PATCHED
    if (packet->size < length) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    } 
    #endif 
    bzero(buffer, sizeof(buffer));
    memcpy(buffer, (char *)packet->data, length);
    DisplayFormatted(state, DISPLAY_APPLICATION, "To: +s\n", buffer);
    packet->data += length;
    packet->size -= length;
    if (packet->size == 0) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    }
    length = *(uint8_t *)packet->data;
    packet->data++;
    packet->size--;
    #ifdef PATCHED
    if (packet->size < length) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    } 
    #endif 
    bzero(buffer, sizeof(buffer));
    memcpy(buffer, (char *)packet->data, length);
    DisplayFormatted(state, DISPLAY_APPLICATION, "Subject: +s\n", buffer);
    packet->data += length;
    packet->size -= length;

  } else if (application_type == 5) {
    DisplayFormatted(state, DISPLAY_APPLICATION, "Application type: Webpage\n");
    if (packet->size < 8) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    }
    packet->data += 6;
    packet->size -= 6;
    uint16_t url_length = *(uint16_t *)(packet->data);
    packet->data += 2;
    packet->size -= 2;
    char *url;
    if (url_length > 1024) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Invalid url\n");
      return -1;
    }
    if (url_length > packet->size) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    }
    if (allocate(url_length + 1, 0, (void **)&url) != 0) {
      _terminate(-1);
    }
    bzero(url, url_length + 1);
    memcpy(url, (char *)(packet->data), url_length);
    DisplayFormatted(state, DISPLAY_APPLICATION, "URL: +s\n", url);
    packet->data += url_length;
    packet->size -= url_length;
    deallocate(url, url_length + 1);
    if (packet->size < 2) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    }

    uint16_t header_length = *(uint16_t *)(packet->data);
    packet->data += 2;
    packet->size -= 2;
    char *header;
    if (header_length > 1024) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Invalid header length\n");
      return -1;
    }
    if (header_length > packet->size) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    }
    if (allocate(header_length + 1, 0, (void **)&header) != 0) {
      _terminate(-1);
    }
    bzero(header, header_length + 1);
    memcpy(header, (char *)(packet->data), header_length);
    DisplayFormatted(state, DISPLAY_APPLICATION, "Headers: +s\n", header);
    packet->data += header_length;
    packet->size -= header_length;
    deallocate(header, header_length + 1);
    if (packet->size < 2) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Application layer too short\n");
      return -1;
    }
    uint16_t content_length = *(uint16_t *)(packet->data);
    packet->data += 2;
    packet->size -= 2;
    if (content_length != packet->size) {
      DisplayFormatted(state, DISPLAY_APPLICATION, "Invalid webpage length\n");
      return -1;
    }

  } else {
    DisplayFormatted(state, DISPLAY_APPLICATION, "Unsupported application type\n");
    return -1;
  }

  return 0;
}

// Checks for filter match and displays packet data accordingly
// returns 0 for success
// returns -1 if the packet was not shown
// returns -2 if there was an error processing the packet
int AnalyzePacket(SystemState *state, Packet *packet) {
  // Process each layer and print if requested
  int negative_match = 0;
  int positive_match = 0;

  ProcessAllFilters(packet, state, &negative_match, &positive_match);

  // If negative filters exist and match, don't show packet
  if (negative_match > 0) {
    TransmitBytes("skip\n", 5);
    return -1;
  }
  // If positive filters exist, but don't match, don't show packet
  if ((state->stats->num_positive_filters > 0) && (positive_match == 0)) {

    TransmitBytes("skip\n", 5);
   return -1;
  } 
  // Otherwise, show packet 
  state->stats->num_packets_shown++;

  if (AnalyzePhysicalLayer(state, packet) == 0) {
    if (AnalyzeTransportLayer(state, packet) == 0) {
      if (AnalyzeNetworkLayer(state, packet) == 0) {
        if (AnalyzeApplicationLayer(state, packet) == 0) {
          if (state->display_flags & DISPLAY_CONTENT) {
            HexDump(packet->data, packet->size);
            TransmitBytes("\n", 1);
          }
          return 0;
        }
      }
    }
  }

  return -2;
}