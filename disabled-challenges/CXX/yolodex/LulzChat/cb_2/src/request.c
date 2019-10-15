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

#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_request.h"
#include "cgc_packet.h"

#define SFD_SERVER_W 3
#define SFD_SERVER_R 4
#define SFD_CLIENT_W 5
#define SFD_CLIENT_R 6

void cgc_send_request(void *req, enum cmd_t cmd)
{
  packet_t *packet = cgc_new_packet(T_REQUEST, cmd);
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
  packet->body = cgc_malloc(packet->body_len);
  if (packet->body)
  {
    cgc_size_t size;
    if (cmd == CMD_SEND)
    {
      char *pb = packet->body;
      send_req_t *sr = (send_req_t *)req;
      size = sizeof(send_req_t) - sizeof(message_t *);
      cgc_memcpy(pb, (char *)req, size);
      pb += size;
      size = sizeof(message_t) - sizeof(char *);
      cgc_memcpy(pb, (char *)(sr->msg), size);
      pb += size;
      cgc_memcpy(pb, sr->msg->text, sr->msg->text_len);
    }
    else
    {
      cgc_memcpy(packet->body, (char *)req, packet->body_len);
    }
    packet->checksum = cgc_calc_checksum(packet);
    size = sizeof(packet_t) - sizeof(char *);
    cgc_transmit(SFD_CLIENT_W, (char *)packet, size, NULL);
    cgc_transmit(SFD_CLIENT_W, packet->body, packet->body_len, NULL);
  }

done:
  cgc_free_packet(packet);
}
