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
#include "stdlib.h"
#include "stdint.h"
#include "malloc.h"
#include "error.h"
#include "tree.h"
#include "page.h"
#include "command.h"

// Decode the data
int DecodeData(uint8_t *data, int decoded_size, char *encoded_data, int encoded_size) {
  char *start = (char *)data;
  data++[0] = (encoded_data[0] >> 1) & 0x7f;
  for (int i = 1; i <= decoded_size; i++) {
    *data++ = 0x7f & ((*encoded_data << (7 - i%8)) | ((*(encoded_data + 1) & 0xff) >> (i%8 + 1)));
    if (i%8 != 7) {
      encoded_data++;
    }
  }
  return 0;
}

// Delete the dynamic memory owned by this command structure
void DestroyCommand(CommandStruct *command) {
  if (command->data != NULL) {
    free(command->data);
    command->data = NULL;
  }
  command->command = NO_COMMAND;
  memset(command->name, 0, sizeof(command->name));
  command->data_size = 0;
}

// Receives an incoming command and parses it into a CommandStruct
// Returns 0 on success, -1 on receive error, -2 on invalid command format
// May allocate memory for the data portion of a command which should later
// be freed by calling DestroyCommand()
int ReceiveCommand(CommandStruct *command, int *more_commands) {
  if (command->data != NULL) {
    DestroyCommand(command);
  }
  char buffer[64];
  size_t bytes_received;
  bytes_received = receive_fixed(buffer, 7);
  if (bytes_received != 7) {
    return -1;
  }
  if (strncmp(buffer, "ACS+0.1", 7) == 0) {
    *more_commands = 1;
  } else if (strncmp(buffer, "ACS-0.1", 7) == 0) {
    *more_commands = 0;
  } else {
    return -2;
  }
  bytes_received = receive_until(buffer, ':', sizeof(buffer));
  if (bytes_received == 0) {
    return -1;
  }
  if (buffer[0] != '[') {
    return -2;
  }
  if (strncmp(&buffer[1], "REQUEST", strlen("REQUEST")) == 0) {
    command->command = REQUEST;
  } else if (strncmp(&buffer[1], "QUERY", strlen("QUERY")) == 0) {
    command->command = QUERY;
  } else if (strncmp(&buffer[1], "SEND", strlen("SEND")) == 0) {
    command->command = SEND;
  } else if (strncmp(&buffer[1], "REMOVE", strlen("REMOVE")) == 0) {
    command->command = REMOVE;
  } else if (strncmp(&buffer[1], "VISUALIZE", strlen("VISUALIZE")) == 0) {
    command->command = VISUALIZE;
  } else if (strncmp(&buffer[1], "INTERACT", strlen("INTERACT")) == 0) {
    command->command = INTERACT;
  } else {
    return -2;
  }
  bytes_received = receive_until(buffer, ':', sizeof(buffer));
  if (bytes_received > sizeof(command->name)) {
    return -1;
  }
  if (bytes_received > 0) {
    strncpy(command->name, buffer, bytes_received);
  }
  bytes_received = receive_until(buffer, ':', sizeof(buffer));
  if (bytes_received > 6) {
    return -1;
  }
  if (bytes_received > 0) {
    command->data_size = atoi(buffer);
  }
  if (command->data_size > 0) {
    // Data is not encoded
    command->data = calloc(command->data_size + 1, 1);
    VerifyPointerOrTerminate(command->data, "command->data during parsing");
    uint8_t *command_data = command->data;
    bytes_received = receive_fixed((char *)command->data, command->data_size);
    if (bytes_received != command->data_size) {
      return -1;
    }
  } else if (command->data_size == -1) {
    // Data is encoded
    int encoded_size;
    int decoded_size;
    bytes_received = receive_fixed((char *)&encoded_size, sizeof(encoded_size));
    if (bytes_received != sizeof(encoded_size)) {
      return -1;
    }
    decoded_size = (encoded_size * 8) / 7;
    #ifdef PATCHED
    if (decoded_size <= 0) {
      return -1;
    }
    #endif 
    command->data = calloc(decoded_size + 1, 1);
    VerifyPointerOrTerminate(command->data, "command->data during parsing");
    char *encoded_data;
    encoded_data = calloc(encoded_size + 1, 1);
    VerifyPointerOrTerminate(encoded_data, "encoded_data during parsing");
    bytes_received = receive_fixed(encoded_data, encoded_size);
    if (bytes_received != encoded_size) {
      free(encoded_data);
      return -1;
    }
    // Decode the data
    if (DecodeData(command->data, decoded_size, encoded_data, encoded_size) != 0) {
      free(encoded_data);
      return -1;
    }
    if (command->data[decoded_size-1] == '\0') {
      command->data_size = decoded_size -1;
    } else {
      command->data_size = decoded_size;
    }
    // Deallocate the encoded data
    free(encoded_data);
  }
  bytes_received = receive_fixed(buffer, 1);
  if (bytes_received != 1) {
    return -1;
  }
  if (buffer[0] != ']') {
    return -2;
  }
  return 0;

}

void HandleCommand(CommandStruct *command) {
  switch (command->command) {
    case REQUEST: {
      TreeNode *node = LookupNode(command->name);
      if (node == NULL) {
        printf("Page not found: @s\n", command->name);
      } else {
        ServePage(node->page, node->page_size);
      }
      break;
    }
    case QUERY: {
      PrintTree(command->name);
      break;
    }
    case SEND: {
      TreeNode *new_node = calloc(sizeof(TreeNode), 1);
      VerifyPointerOrTerminate(command->data, "new_node during SEND");
      memcpy(new_node->name, command->name, sizeof(new_node->name));
      new_node->page = (char *) command->data;
      new_node->page_size = command->data_size;
      if (InsertNodeInTree(new_node) == 0) {
        command->data = NULL;
        command->data_size = 0;
        printf("SUCCESS: Page uploaded to server\n");
      } else {
        free(new_node);
        printf("ERROR: Unable to upload page\n");
      }
      break;
    }
    case REMOVE: {
      if (DeleteNode(command->name) == 0) {
        printf("SUCCESS: Page deleted\n");
      } else {
        printf("ERROR: Unable to delete page\n");
      }
      break;
    }
    case VISUALIZE: {
      ServePage((char *)command->data, command->data_size);
      break;
    }
    case INTERACT: {
      TreeNode *node = LookupNode(command->name);
      if (node == NULL) {
        printf("Page not found: @s\n", command->name);
      } else {
        InteractWithPage(node->page, node->page_size, (char *)command->data);
      }
      break;
    }
    default:
      printf("Unsupported Command\n");
      printf("Command type: @x\n", command->command);
      printf("File name: @s\n", command->name);
      printf("Data length: @d\n", command->data_size);
      if (command->data != NULL) {
        printf("Data: @s\n", command->data);
      }
      break;
  }
}