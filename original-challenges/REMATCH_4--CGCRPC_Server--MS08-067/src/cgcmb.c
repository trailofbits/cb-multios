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
#include "string.h"
#include "malloc.h"
#include "transport.h"
#include "cgcmb.h"
#include "fs.h"
#include "cgcrpc.h"
#include "user.h"


CGCMB_ServerState *mbServerState;

void AddToData(CGCMB_Data *data, uint8_t *source, uint32_t count)
{
  if (data == NULL) 
  {
    return;
  }
  if (data->data == NULL)
  {
    data->data = calloc(count);
    data->count = count;
    memcpy(data->data, source, count);
  } 
  else 
  { 
    uint8_t *newdata = calloc(data->count + count);
    memcpy(newdata, data->data, data->count);
    memcpy(newdata + data->count, source, count);
    data->count += count;
    free(data->data);
    data->data = newdata;
  }
}      


int ReceiveCGCMBMessage(TransportMessage *tpMessage, CGCMB_Message **pmbMessage)
{
  if (tpMessage == NULL) 
  {
    return -1;
  }

  CGCMB_Message *mbMessage = CreateBlankCGCMBMessage();
  // Process Header
  CGCMB_Header *header = mbMessage->header;
  if (ReadFromTransportMessage(tpMessage, (uint8_t *)&header->protocol, sizeof(header->protocol)) != 0)
  {
    goto FAIL;
  }
  if (ReadFromTransportMessage(tpMessage, (uint8_t *)&header->command, sizeof(header->command)) != 0)
  {
    goto FAIL;
  }
  if (ReadFromTransportMessage(tpMessage, (uint8_t *)&header->status, sizeof(header->status)) != 0)
  {
    goto FAIL;
  }
  if (ReadFromTransportMessage(tpMessage, (uint8_t *)&header->flags, sizeof(header->flags)) != 0)
  {
    goto FAIL;
  }
  if (ReadFromTransportMessage(tpMessage, (uint8_t *)&header->security, sizeof(header->security)) != 0)
  {
    goto FAIL;
  }
  // Process Parameters
  CGCMB_Data *params = mbMessage->parameters;
  if (ReadFromTransportMessage(tpMessage, (uint8_t *)&params->count, sizeof(params->count)) != 0)
  {
    goto FAIL;
  }
  if (params->count != 0)
  {
    params->data = calloc(params->count);
    if (ReadFromTransportMessage(tpMessage, (uint8_t *)params->data, params->count) != 0)
    {
      goto FAIL;
    }
  }
  // Process Data
  CGCMB_Data *data = mbMessage->data;
  if (ReadFromTransportMessage(tpMessage, (uint8_t *)&data->count, sizeof(data->count)) != 0)
  {
    goto FAIL;
  }
  if (data->count != 0)
  {
    data->data = calloc(data->count);
    if (ReadFromTransportMessage(tpMessage, (uint8_t *)data->data, data->count) != 0)
    {
      goto FAIL;
    }
  }

  *pmbMessage = mbMessage;
  return 0;

FAIL:
  DestroyCGCMBMessage(&mbMessage);
  return -1;
}

void SendErrorResponse(uint32_t errorCode)
{
  CGCMB_Message *mbMessage = CreateBlankCGCMBMessage();
  mbMessage->header->command = CGCMB_ERROR_RESPONSE;
  AddToData(mbMessage->data, (uint8_t *)&errorCode, sizeof(errorCode));
  TransmitCGCMBMessage(mbMessage);
  DestroyCGCMBMessage(&mbMessage);
}       

int ReadFromData(uint8_t *dest, CGCMB_Data *source, uint32_t length)
{
  if (((dest == NULL) || (source == NULL)) || (source->data == NULL)) 
  {
    return -1;
  }
  if (length == 0)
  {
    return 0;
  }
  if ((int) source->currentOffset + (int)length > (int)source->count)
  {
    return -1;
  }
  memcpy(dest, source->data + source->currentOffset, length);
  source->currentOffset += length;
  return 0;
}

int ParseCGCMBMessage(CGCMB_Message *mbMessage)
{
  if ((mbMessage == NULL) || (mbMessage->header == NULL))
  {
    return -1;
  }

  switch (mbMessage->header->command)
  {
    case CGCMB_NEGOTIATE:  
    {
      mbMessage->parsed = calloc(sizeof(CGCMB_NEGOTIATE_Message));
      CGCMB_NEGOTIATE_Message *msg = mbMessage->parsed;
      msg->numDialects = mbMessage->data->count / 2;
      if (msg->numDialects == 0) {break;}
      msg->dialects = calloc(sizeof(msg->numDialects * 2));
      if (ReadFromData((uint8_t *)msg->dialects, mbMessage->data, msg->numDialects * 2) != 0) {break;}  
      break;
    }    
    case CGCMB_SESSION_SETUP: 
    {
      CGCMB_SESSION_SETUP_Message *msg = calloc(sizeof(CGCMB_SESSION_SETUP_Message));
      mbMessage->parsed = msg;
      if (ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0)
      {
        break;
      }
      uint16_t passwordLength;
      if (ReadFromData((uint8_t *)&passwordLength, mbMessage->parameters, sizeof(passwordLength)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->reserved, mbMessage->parameters, sizeof(msg->reserved)) != 0) {break;}
      if ((passwordLength == 0) || (passwordLength > 64)) {break;}
      msg->password = calloc(passwordLength + 1);
      if (ReadFromData(msg->password, mbMessage->data, passwordLength) != 0) {break;}
      uint16_t nameLength;
      if ((nameLength == 0) || (nameLength > 128)) {break;}
      if (ReadFromData((uint8_t *)&nameLength, mbMessage->data, sizeof(nameLength)) != 0) {break;}
      msg->accountName = calloc(nameLength + 1);
      if (ReadFromData(msg->accountName, mbMessage->data, nameLength) != 0) {break;}
      break;
    }
    case CGCMB_TREE_CONNECT:
    {
      CGCMB_TREE_CONNECT_Message *msg = calloc(sizeof(CGCMB_TREE_CONNECT_Message));
      mbMessage->parsed = msg;
      if (ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      uint16_t length;
      if (ReadFromData((uint8_t *)&length, mbMessage->data, sizeof(length)) != 0) {break;}
      if ((length == 0) || (length > 64)) {break;}
      msg->password = calloc(length + 1);
      if (ReadFromData(msg->password, mbMessage->data, length) != 0) {break;}
      if (ReadFromData((uint8_t *)&length, mbMessage->data, sizeof(length)) != 0) {break;}
      if ((length == 0) || (length > 128)) {break;}
      msg->path = calloc(length + 1);
      if (ReadFromData(msg->path, mbMessage->data, length) != 0) {break;}
      if (ReadFromData((uint8_t *)&length, mbMessage->data, sizeof(length)) != 0) {break;}
      if ((length == 0) || (length > 128))  {break;}
      msg->service = calloc(length + 1);
      if (ReadFromData(msg->service, mbMessage->data, length) != 0) {break;}
      break;
    }
    case CGCMB_TREE_DISCONNECT:
    {
      CGCMB_TREE_DISCONNECT_Message *msg = calloc(sizeof(CGCMB_TREE_DISCONNECT_Message));
      mbMessage->parsed = msg;
      if (ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      break;
    }
    case CGCMB_FILE_CREATE:  
    {
      CGCMB_FILE_CREATE_Message *msg = calloc(sizeof(CGCMB_FILE_CREATE_Message));
      mbMessage->parsed = msg;
      if (ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->mode, mbMessage->parameters, sizeof(msg->mode)) != 0) {break;}
      uint16_t length;
      if (ReadFromData((uint8_t *)&length, mbMessage->data, sizeof(length)) != 0) {break;}
      if ((length == 0) || (length > 128)) {break;}
      msg->filename = calloc(length + 1);
      if (ReadFromData(msg->filename, mbMessage->data, length) != 0) {break;}
      break;
    }
    case CGCMB_FILE_CLOSE:  
    {
      CGCMB_FILE_CLOSE_Message *msg = calloc(sizeof(CGCMB_FILE_CLOSE_Message));
      mbMessage->parsed = msg;
      if (ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->fileID, mbMessage->parameters, sizeof(msg->fileID)) != 0) {break;}
      break;
    } 
    case CGCMB_FILE_READ:  
    {
      CGCMB_FILE_READ_Message *msg = calloc(sizeof(CGCMB_FILE_READ_Message));
      mbMessage->parsed = msg;
      if (ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->fileID, mbMessage->parameters, sizeof(msg->fileID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->bytesToRead, mbMessage->data, sizeof(msg->bytesToRead)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->readOffset, mbMessage->data, sizeof(msg->readOffset)) != 0) {break;}
      break;
    }
    case CGCMB_FILE_WRITE:  
    {
      CGCMB_FILE_WRITE_Message *msg = calloc(sizeof(CGCMB_FILE_WRITE_Message));
      mbMessage->parsed = msg;
      if (ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->fileID, mbMessage->parameters, sizeof(msg->fileID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->mode, mbMessage->parameters, sizeof(msg->mode)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->bytesToWrite, mbMessage->data, sizeof(msg->bytesToWrite)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->writeOffset, mbMessage->data, sizeof(msg->writeOffset)) != 0) {break;}
      if ((msg->bytesToWrite == 0) || (msg->bytesToWrite > MAX_WRITE_SIZE)) {break;}
      msg->bytes = calloc(msg->bytesToWrite);
      if (ReadFromData(msg->bytes, mbMessage->data, msg->bytesToWrite) != 0) {break;}
      break;
    } 
    case CGCMB_TRANSACTION:    
    {
      CGCMB_TRANSACTION_Message *msg = calloc(sizeof(CGCMB_TRANSACTION_Message));
      mbMessage->parsed = msg;
      if (ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      if (ReadFromData((uint8_t *)&msg->fileID, mbMessage->parameters, sizeof(msg->fileID)) != 0) {break;}
      break;
    }
    case CGCMB_ECHO:  
    {
      break;
    }    
    case CGCMB_END_SESSION:
    {
      break;
    }
    default:
      return -1;
  }
  return 0;
}  

CGCMB_Connection *FindConnectionByID(uint32_t connectionID)
{
 for (int i=0; i< MAX_CONNECTIONS; i++)
  {
    if (mbServerState->connections[i] != NULL)
    {
      if (mbServerState->connections[i]->connectionID == connectionID)
      {
        return mbServerState->connections[i];
      }
    }
  }
  return NULL;
}

fs_file *FindFileByID(CGCMB_Connection *connection, uint32_t fileID)
{
  for (int i=0; i < MAX_OPEN_FILES; i++)
  {
    if (connection->openFiles[i] != NULL)
    {
      if (connection->openFiles[i]->fileID == fileID)
      {
        return connection->openFiles[i];
      }
    }
  }
  return NULL;
}



int HandleCGCMBMessage(CGCMB_Message *mbMessage)
{
  if (mbMessage == NULL)
  {
    return -1;
  }
  // Verify Message
  if (VerifyCGCMBMessage(mbMessage) != 0)
  {
    SendErrorResponse(CGCMB_ERROR_FORMAT);
    return 0;
  }

  // Handle Message
  switch(mbMessage->header->command)
  {
    case CGCMB_NEGOTIATE:
    {
      if (mbServerState->state != INITIAL) 
      {
        SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_NEGOTIATE_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      uint16_t count_remaining = msg->numDialects;
      uint16_t *pDialects = msg->dialects;
      if (pDialects == NULL) 
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        break;
      }
      CGCMB_Message *mbResponse = CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_NEGOTIATE_RESPONSE;
      mbServerState->state = NEGOTIATE;
      while (count_remaining > 0)
      { 
        if (*pDialects == (uint16_t)CGCMB_DIALECT_1 ||
            *pDialects == (uint16_t)CGCMB_DIALECT_2 ||
            *pDialects == (uint16_t)CGCMB_DIALECT_3 )
        {
          // Negotiation successful, setup positive response
          mbServerState->dialect = *pDialects;
          mbServerState->sessionKey = rand();
          AddToData(mbResponse->data, (uint8_t *)&mbServerState->sessionKey, sizeof(mbServerState->sessionKey));
          AddToData(mbResponse->data, (uint8_t *)&mbServerState->dialect, sizeof(mbServerState->dialect));
          break;
        } 
        else 
        {
          count_remaining--;
          pDialects++;
        }
      }  
      if (mbServerState->dialect == 0)
      {
        mbServerState->state = CLOSED;
      }
      // Transmit Response  
      TransmitCGCMBMessage(mbResponse);
      DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_SESSION_SETUP:
    {
      if (mbServerState->state != NEGOTIATE)
      {
        SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_SESSION_SETUP_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (mbServerState->sessionKey != msg->sessionKey)
      {
        SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (msg->reserved != 0)
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      mbServerState->state = SESSION;
      mbServerState->userID = LookupUser(msg->accountName, msg->password);
      CGCMB_Message *mbResponse = CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_SESSION_SETUP_RESPONSE;
      AddToData(mbResponse->data, (uint8_t *)&mbServerState->userID, sizeof(mbServerState->userID));
      uint8_t userIsGuest = mbServerState->userID == USER_GUEST;
      AddToData(mbResponse->data, &userIsGuest, 1);
      TransmitCGCMBMessage(mbResponse);
      DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_TREE_CONNECT:
    {
      if (mbServerState->state != SESSION)
      {
        SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_TREE_CONNECT_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (mbServerState->sessionKey != msg->sessionKey)
      {
        SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (mbServerState->userID != msg->userID)
      {
        SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      fs_tree *tree = FindTreeByPath(msg->userID, msg->path, msg->service);
      if (tree == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_ACCESS);
        return -1;
      }
      CGCMB_Connection *connection = NULL;
      for (int i=0; i< MAX_CONNECTIONS; i++)
      {
        if (mbServerState->connections[i] == NULL)
        {
          mbServerState->connections[i] = calloc(sizeof(CGCMB_Connection));
          connection = mbServerState->connections[i];
          break;
        }
      }
      if (connection == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_FULL);
        return -1;
      }
      connection->connectionID = rand();
      connection->state = CONNECTION_OPEN;
      connection->openTree = tree;
      CGCMB_Message *mbResponse = CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_TREE_CONNECT_RESPONSE;
      AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
      AddToData(mbResponse->data, (uint8_t *)&connection->connectionID, sizeof(connection->connectionID));
      TransmitCGCMBMessage(mbResponse);
      DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_TREE_DISCONNECT:
    {
      if (mbServerState->state != SESSION)
      {
        SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_TREE_DISCONNECT_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (mbServerState->sessionKey != msg->sessionKey)
      {
        SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (mbServerState->userID != msg->userID)
      {
        SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      for (int i=0; i < MAX_CONNECTIONS; i++)
      {
        if (mbServerState->connections[i] != NULL)
        {
          if (mbServerState->connections[i]->connectionID == msg->connectionID)
          {
            free(mbServerState->connections[i]);
            mbServerState->connections[i] = NULL;
            CGCMB_Message *mbResponse = CreateBlankCGCMBMessage();
            mbResponse->header->command = CGCMB_TREE_DISCONNECT_RESPONSE;
            AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
            AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
            AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
            TransmitCGCMBMessage(mbResponse);
            DestroyCGCMBMessage(&mbResponse);
            return 0;
          }
        }
      }
      SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
      break;
    }
    case CGCMB_FILE_CREATE:
    {
      if (mbServerState->state != SESSION)
      {
        SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_FILE_CREATE_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (mbServerState->sessionKey != msg->sessionKey)
      {
        SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (mbServerState->userID != msg->userID)
      {
        SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      CGCMB_Connection *connection = FindConnectionByID(msg->connectionID);
      if (connection == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      for (int i=0; i < MAX_OPEN_FILES; i++)
      {
        if (connection->openFiles[i] == NULL)
        {
          connection->openFiles[i] = CreateFile(connection->openTree, msg->filename, msg->userID, msg->mode);
          if (connection->openFiles[i] != NULL)
          {
            // Send affirmative response
            CGCMB_Message *mbResponse = CreateBlankCGCMBMessage();
            mbResponse->header->command = CGCMB_FILE_CREATE_RESPONSE;
            AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
            AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
            AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
            AddToData(mbResponse->parameters, (uint8_t *)&connection->openFiles[i]->fileID, sizeof(connection->openFiles[i]->fileID));
            TransmitCGCMBMessage(mbResponse);
            DestroyCGCMBMessage(&mbResponse);
            return 0;
          } else {
            SendErrorResponse(CGCMB_ERROR_FILE);
            break;
          }
        }
      }
      SendErrorResponse(CGCMB_ERROR_FULL);
      break;
    }
    case CGCMB_FILE_CLOSE:
    {
      if (mbServerState->state != SESSION)
      {
        SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_FILE_CLOSE_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (mbServerState->sessionKey != msg->sessionKey)
      {
        SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (mbServerState->userID != msg->userID)
      {
        SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      CGCMB_Connection *connection = FindConnectionByID(msg->connectionID);
      if (connection == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      fs_file *file = FindFileByID(connection, msg->fileID);
      if (file == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      CloseFile(file);
      CGCMB_Message *mbResponse = CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_FILE_CLOSE_RESPONSE;
      AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->fileID, sizeof(msg->fileID));
      TransmitCGCMBMessage(mbResponse);
      DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_FILE_READ:
    {
      if (mbServerState->state != SESSION)
      {
        SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_FILE_READ_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (mbServerState->sessionKey != msg->sessionKey)
      {
        SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (mbServerState->userID != msg->userID)
      {
        SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      CGCMB_Connection *connection = FindConnectionByID(msg->connectionID);
      if (connection == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      fs_file *file = FindFileByID(connection, msg->fileID);
      if (file == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      if ((msg->bytesToRead == 0) || (msg->bytesToRead > MAX_READ_SIZE))
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        break;
      }
      uint8_t *data = calloc(msg->bytesToRead);
      if (ReadFile(data, file, msg->readOffset, msg->bytesToRead) != 0)
      {
        SendErrorResponse(CGCMB_ERROR_FILE);
        free(data);
        break;
      }
      CGCMB_Message *mbResponse = CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_FILE_READ_RESPONSE;
      AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->bytesToRead, sizeof(msg->bytesToRead));
      AddToData(mbResponse->data, data, msg->bytesToRead);
      TransmitCGCMBMessage(mbResponse);
      free(data);
      DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_FILE_WRITE:
    {
      if (mbServerState->state != SESSION)
      {
        SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_FILE_WRITE_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (mbServerState->sessionKey != msg->sessionKey)
      {
        SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (mbServerState->userID != msg->userID)
      {
        SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      CGCMB_Connection *connection = FindConnectionByID(msg->connectionID);
      if (connection == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      fs_file *file = FindFileByID(connection, msg->fileID);
      if (file == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      if ((msg->bytesToWrite == 0) || (msg->bytesToWrite > MAX_WRITE_SIZE))
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        break;
      }
      if (WriteFile(file, msg->bytes, msg->writeOffset, msg->bytesToWrite) != 0)
      {
        SendErrorResponse(CGCMB_ERROR_FILE);
        break;
      }
      CGCMB_Message *mbResponse = CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_FILE_WRITE_RESPONSE;
      AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->fileID, sizeof(msg->fileID));
      TransmitCGCMBMessage(mbResponse);
      DestroyCGCMBMessage(&mbResponse);
      break;
    }

    case CGCMB_TRANSACTION:
    {
      if (mbServerState->state != SESSION)
      {
        SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_TRANSACTION_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (mbServerState->sessionKey != msg->sessionKey)
      {
        SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (mbServerState->userID != msg->userID)
      {
        SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      CGCMB_Connection *connection = FindConnectionByID(msg->connectionID);
      if (connection == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      if (connection->openTree == NULL) 
      {
        SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      if (strcmp(connection->openTree->serviceType, "EYEPSEE") != 0)
      {
        SendErrorResponse(CGCMB_ERROR_TRANSACTION);
        break;
      }
      fs_file *file = FindFileByID(connection, msg->fileID);
      if (file == NULL)
      {
        SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      if (file->fileID != connection->openTree->files[0]->fileID)
      {
        SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      void *pcResponse;
      uint32_t pcResponseLength;
      uint8_t errorCode;
      errorCode = HandleCGCRPCMessage(mbMessage->data->data, mbMessage->data->count, &pcResponse, &pcResponseLength);
      CGCMB_Message *mbResponse = CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_TRANSACTION_RESPONSE;
      AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
      AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
      AddToData(mbResponse->parameters, (uint8_t *)&errorCode, sizeof(errorCode));
      if ((pcResponseLength > 0) && (pcResponse != NULL))
      {
        AddToData(mbResponse->data, pcResponse, pcResponseLength);
        free(pcResponse);
      }
      TransmitCGCMBMessage(mbResponse);
      DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_ECHO:
    {
      mbMessage->header->command = CGCMB_ECHO_RESPONSE;
      TransmitCGCMBMessage(mbMessage);
      break;
    }
    case CGCMB_END_SESSION:
    {
      mbServerState->state = CLOSED;
      mbMessage->header->command = CGCMB_END_SESSION_RESPONSE;
      TransmitCGCMBMessage(mbMessage);
      return 1;
    }
    default:
    {
      SendErrorResponse(CGCMB_ERROR_MSG);
      break;
    }
  }
  return 0;
}


void DestroyCGCMBMessage(CGCMB_Message **pmbMessage)
{
  if (pmbMessage == NULL)
  {
    return;
  }
  CGCMB_Message *mbMessage = *pmbMessage;
  if (mbMessage == NULL)
  {
    return;
  }
  if (mbMessage->parsed != NULL) 
  {
    if (mbMessage->header == NULL)
    {
      _terminate(-1);
    }
    switch(mbMessage->header->command)
    {
      case CGCMB_NEGOTIATE:
      {
        CGCMB_NEGOTIATE_Message *msg = mbMessage->parsed;
        free(msg->dialects);
        break;
      }
      case CGCMB_SESSION_SETUP: 
      {
        CGCMB_SESSION_SETUP_Message *msg = mbMessage->parsed;
        if (msg != NULL)
        {
          free(msg->password);
          free(msg->accountName);
        }
        break;
      }
      case CGCMB_TREE_CONNECT:
      {
        CGCMB_TREE_CONNECT_Message *msg = mbMessage->parsed;
        if (msg != NULL)
        {
          free(msg->password);
          free(msg->path);
          free(msg->service);
        }
        break;
      }
      case CGCMB_TREE_DISCONNECT:
        break;
      case CGCMB_FILE_CREATE:  
      {
        CGCMB_FILE_CREATE_Message *msg = mbMessage->parsed;
        if (msg != NULL)
        {
          free(msg->filename);
        }
        break;
      }
      case CGCMB_FILE_CLOSE: 
        break;  
      case CGCMB_FILE_READ:  
        break;
      case CGCMB_FILE_WRITE:  
      {
        CGCMB_FILE_WRITE_Message *msg = mbMessage->parsed;
        if (msg != NULL)
        {
          free(msg->bytes);
        }
        break;
      } 
      case CGCMB_TRANSACTION:  
        break;  
      case CGCMB_ECHO: 
        break;     
      case CGCMB_END_SESSION:
        break;
      default:
      {
        _terminate(-1);
      }
    }
    free(mbMessage->parsed);
  }

  if (mbMessage->data != NULL)
  {
    free(mbMessage->data->data);
    free(mbMessage->data);
  }
  if (mbMessage->parameters != NULL)
  {
    free(mbMessage->parameters->data);
    free(mbMessage->parameters);
  }
  free(mbMessage->header);
  free(mbMessage);
  *pmbMessage = NULL;
  return;
}

CGCMB_Message *CreateBlankCGCMBMessage()
{
  CGCMB_Message *mbMessage = calloc(sizeof(CGCMB_Message));
  mbMessage->data = calloc(sizeof(CGCMB_Data));
  mbMessage->parameters = calloc(sizeof(CGCMB_Data));
  mbMessage->header = calloc(sizeof(CGCMB_Header));
  mbMessage->header->protocol = CGCMB_MAGIC;
  return mbMessage;
}

int VerifyCGCMBMessage(CGCMB_Message *mbMessage)
{
  if ((mbMessage == NULL) || (mbMessage->header == NULL)) { return -1; }
  if (mbMessage->header->protocol != CGCMB_MAGIC) { return -1; }
  if (mbMessage->data != NULL)
  {
    if ((mbMessage->data->count > 0) && (mbMessage->data->data == NULL)) { return -1; }
  }
  if (mbMessage->parameters != NULL)
  {
    if ((mbMessage->parameters->count > 0) && (mbMessage->parameters->data == NULL)) { return -1; }
  }
  return 0;
}

void TransmitCGCMBMessage(CGCMB_Message *mbMessage)
{       
  if (VerifyCGCMBMessage(mbMessage) != 0)
  {       
    return;
  }
  // Convert to transport and send
  TransportMessage *tpMessage = calloc(sizeof(TransportMessage));
  tpMessage->size = mbMessage->data->count + sizeof(mbMessage->data->count);
  tpMessage->size += mbMessage->parameters->count + sizeof(mbMessage->parameters->count);
  tpMessage->size += sizeof(mbMessage->header->security) + sizeof(mbMessage->header->flags) + sizeof(mbMessage->header->status) + sizeof(mbMessage->header->command) + sizeof(mbMessage->header->protocol);
  if (tpMessage->size > MAX_TRANSPORT_SIZE)
  {
    SendErrorResponse(CGCMB_ERROR_LENGTH);
    DestroyTransportMessage(&tpMessage);
    return;
  }
  tpMessage->data = calloc(tpMessage->size);
  uint8_t *pdata = tpMessage->data;
  memcpy(pdata, &mbMessage->header->protocol, sizeof(mbMessage->header->protocol)); pdata += sizeof(mbMessage->header->protocol);
  memcpy(pdata, &mbMessage->header->command, sizeof(mbMessage->header->command)); pdata += sizeof(mbMessage->header->command);
  memcpy(pdata, &mbMessage->header->status, sizeof(mbMessage->header->status)); pdata += sizeof(mbMessage->header->status);
  memcpy(pdata, &mbMessage->header->flags, sizeof(mbMessage->header->flags)); pdata += sizeof(mbMessage->header->flags);
  memcpy(pdata, mbMessage->header->security, sizeof(mbMessage->header->security)); pdata += sizeof(mbMessage->header->security);
  memcpy(pdata, &mbMessage->parameters->count, sizeof(mbMessage->parameters->count)); pdata += sizeof(mbMessage->parameters->count);
  if (mbMessage->parameters->count > 0)
  {
    memcpy(pdata, mbMessage->parameters->data, mbMessage->parameters->count); pdata += mbMessage->parameters->count;
  }
  memcpy(pdata, &mbMessage->data->count, sizeof(mbMessage->data->count)); pdata += sizeof(mbMessage->data->count);
  if (mbMessage->data->count > 0)
  {
    memcpy(pdata, mbMessage->data->data, mbMessage->data->count); pdata += mbMessage->data->count;
  }

  SendTransportMessage(tpMessage);
  DestroyTransportMessage(&tpMessage);

}