/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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

#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "packet.h"

#define SFD_SERVER  3
#define SFD_CLIENT 4

void send_request(void *req, enum cmd_t cmd)
{
  packet_t *packet = new_packet(T_REQUEST, cmd);
  if (packet == NULL)
    return;

  switch (cmd)
  {
    case CMD_REGISTER:
      packet->body_len = sizeof(register_req_t);
      break;
    case CMD_LOGIN:
      packet->body_len = sizeof(login_req_t);
      break;
    case CMD_LIST:
      packet->body_len = sizeof(list_req_t);
      break;
    case CMD_VIEW:
      packet->body_len = sizeof(view_req_t);
      break;
    case CMD_SEND:
      {
        send_req_t *sr = (send_req_t *)req;
        packet->body_len = sizeof(send_req_t) - sizeof(message_t *) + sizeof(message_t) - sizeof(char *) + sr->msg->text_len;
      }
      break;
    case CMD_DELETE:
      packet->body_len = sizeof(delete_req_t);
      break;
    case CMD_QUIT:
      packet->body_len = sizeof(quit_req_t);
      break;
    default:
      goto done;
  }
  packet->body = malloc(packet->body_len);
  if (packet->body)
  {
    size_t size;
    if (cmd == CMD_SEND)
    {
      char *pb = packet->body;
      send_req_t *sr = (send_req_t *)req;
      size = sizeof(send_req_t) - sizeof(message_t *);
      memcpy(pb, (char *)req, size);
      pb += size;
      size = sizeof(message_t) - sizeof(char *);
      memcpy(pb, (char *)(sr->msg), size);
      pb += size;
      memcpy(pb, sr->msg->text, sr->msg->text_len);
    }
    else
    {
      memcpy(packet->body, (char *)req, packet->body_len);
    }
    packet->checksum = calc_checksum(packet);
    size = sizeof(packet_t) - sizeof(char *);
    transmit(SFD_CLIENT, (char *)packet, size, NULL);
    transmit(SFD_CLIENT, packet->body, packet->body_len, NULL);
  }

done:
  free_packet(packet);
}
