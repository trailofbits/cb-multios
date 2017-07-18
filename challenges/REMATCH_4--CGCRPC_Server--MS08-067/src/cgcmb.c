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
#include "cgc_string.h"
#include "cgc_malloc.h"
#include "cgc_transport.h"
#include "cgc_cgcmb.h"
#include "cgc_fs.h"
#include "cgc_cgcrpc.h"
#include "cgc_user.h"


CGCMB_ServerState *cgc_mbServerState;

void cgc_AddToData(CGCMB_Data *data, uint8_t *source, uint32_t count)
{
  if (data == NULL) 
  {
    return;
  }
  if (data->data == NULL)
  {
    data->data = cgc_calloc(count);
    data->count = count;
    cgc_memcpy(data->data, source, count);
  } 
  else 
  { 
    uint8_t *newdata = cgc_calloc(data->count + count);
    cgc_memcpy(newdata, data->data, data->count);
    cgc_memcpy(newdata + data->count, source, count);
    data->count += count;
    cgc_free(data->data);
    data->data = newdata;
  }
}      


int cgc_ReceiveCGCMBMessage(TransportMessage *tpMessage, CGCMB_Message **pmbMessage)
{
  if (tpMessage == NULL) 
  {
    return -1;
  }

  CGCMB_Message *mbMessage = cgc_CreateBlankCGCMBMessage();
  // Process Header
  CGCMB_Header *header = mbMessage->header;
  if (cgc_ReadFromTransportMessage(tpMessage, (uint8_t *)&header->protocol, sizeof(header->protocol)) != 0)
  {
    goto FAIL;
  }
  if (cgc_ReadFromTransportMessage(tpMessage, (uint8_t *)&header->command, sizeof(header->command)) != 0)
  {
    goto FAIL;
  }
  if (cgc_ReadFromTransportMessage(tpMessage, (uint8_t *)&header->status, sizeof(header->status)) != 0)
  {
    goto FAIL;
  }
  if (cgc_ReadFromTransportMessage(tpMessage, (uint8_t *)&header->flags, sizeof(header->flags)) != 0)
  {
    goto FAIL;
  }
  if (cgc_ReadFromTransportMessage(tpMessage, (uint8_t *)&header->security, sizeof(header->security)) != 0)
  {
    goto FAIL;
  }
  // Process Parameters
  CGCMB_Data *params = mbMessage->parameters;
  if (cgc_ReadFromTransportMessage(tpMessage, (uint8_t *)&params->count, sizeof(params->count)) != 0)
  {
    goto FAIL;
  }
  if (params->count != 0)
  {
    params->data = cgc_calloc(params->count);
    if (cgc_ReadFromTransportMessage(tpMessage, (uint8_t *)params->data, params->count) != 0)
    {
      goto FAIL;
    }
  }
  // Process Data
  CGCMB_Data *data = mbMessage->data;
  if (cgc_ReadFromTransportMessage(tpMessage, (uint8_t *)&data->count, sizeof(data->count)) != 0)
  {
    goto FAIL;
  }
  if (data->count != 0)
  {
    data->data = cgc_calloc(data->count);
    if (cgc_ReadFromTransportMessage(tpMessage, (uint8_t *)data->data, data->count) != 0)
    {
      goto FAIL;
    }
  }

  *pmbMessage = mbMessage;
  return 0;

FAIL:
  cgc_DestroyCGCMBMessage(&mbMessage);
  return -1;
}

void cgc_SendErrorResponse(uint32_t errorCode)
{
  CGCMB_Message *mbMessage = cgc_CreateBlankCGCMBMessage();
  mbMessage->header->command = CGCMB_ERROR_RESPONSE;
  cgc_AddToData(mbMessage->data, (uint8_t *)&errorCode, sizeof(errorCode));
  cgc_TransmitCGCMBMessage(mbMessage);
  cgc_DestroyCGCMBMessage(&mbMessage);
}       

int cgc_ReadFromData(uint8_t *dest, CGCMB_Data *source, uint32_t length)
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
  cgc_memcpy(dest, source->data + source->currentOffset, length);
  source->currentOffset += length;
  return 0;
}

int cgc_ParseCGCMBMessage(CGCMB_Message *mbMessage)
{
  if ((mbMessage == NULL) || (mbMessage->header == NULL))
  {
    return -1;
  }

  switch (mbMessage->header->command)
  {
    case CGCMB_NEGOTIATE:  
    {
      mbMessage->parsed = cgc_calloc(sizeof(CGCMB_NEGOTIATE_Message));
      CGCMB_NEGOTIATE_Message *msg = mbMessage->parsed;
      msg->numDialects = mbMessage->data->count / 2;
      if (msg->numDialects == 0) {break;}
      msg->dialects = cgc_calloc(sizeof(msg->numDialects * 2));
      if (cgc_ReadFromData((uint8_t *)msg->dialects, mbMessage->data, msg->numDialects * 2) != 0) {break;}  
      break;
    }    
    case CGCMB_SESSION_SETUP: 
    {
      CGCMB_SESSION_SETUP_Message *msg = cgc_calloc(sizeof(CGCMB_SESSION_SETUP_Message));
      mbMessage->parsed = msg;
      if (cgc_ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0)
      {
        break;
      }
      uint16_t passwordLength;
      if (cgc_ReadFromData((uint8_t *)&passwordLength, mbMessage->parameters, sizeof(passwordLength)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->reserved, mbMessage->parameters, sizeof(msg->reserved)) != 0) {break;}
      if ((passwordLength == 0) || (passwordLength > 64)) {break;}
      msg->password = cgc_calloc(passwordLength + 1);
      if (cgc_ReadFromData(msg->password, mbMessage->data, passwordLength) != 0) {break;}
      uint16_t nameLength;
      if ((nameLength == 0) || (nameLength > 128)) {break;}
      if (cgc_ReadFromData((uint8_t *)&nameLength, mbMessage->data, sizeof(nameLength)) != 0) {break;}
      msg->accountName = cgc_calloc(nameLength + 1);
      if (cgc_ReadFromData(msg->accountName, mbMessage->data, nameLength) != 0) {break;}
      break;
    }
    case CGCMB_TREE_CONNECT:
    {
      CGCMB_TREE_CONNECT_Message *msg = cgc_calloc(sizeof(CGCMB_TREE_CONNECT_Message));
      mbMessage->parsed = msg;
      if (cgc_ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      uint16_t length;
      if (cgc_ReadFromData((uint8_t *)&length, mbMessage->data, sizeof(length)) != 0) {break;}
      if ((length == 0) || (length > 64)) {break;}
      msg->password = cgc_calloc(length + 1);
      if (cgc_ReadFromData(msg->password, mbMessage->data, length) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&length, mbMessage->data, sizeof(length)) != 0) {break;}
      if ((length == 0) || (length > 128)) {break;}
      msg->path = cgc_calloc(length + 1);
      if (cgc_ReadFromData(msg->path, mbMessage->data, length) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&length, mbMessage->data, sizeof(length)) != 0) {break;}
      if ((length == 0) || (length > 128))  {break;}
      msg->service = cgc_calloc(length + 1);
      if (cgc_ReadFromData(msg->service, mbMessage->data, length) != 0) {break;}
      break;
    }
    case CGCMB_TREE_DISCONNECT:
    {
      CGCMB_TREE_DISCONNECT_Message *msg = cgc_calloc(sizeof(CGCMB_TREE_DISCONNECT_Message));
      mbMessage->parsed = msg;
      if (cgc_ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      break;
    }
    case CGCMB_FILE_CREATE:  
    {
      CGCMB_FILE_CREATE_Message *msg = cgc_calloc(sizeof(CGCMB_FILE_CREATE_Message));
      mbMessage->parsed = msg;
      if (cgc_ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->mode, mbMessage->parameters, sizeof(msg->mode)) != 0) {break;}
      uint16_t length;
      if (cgc_ReadFromData((uint8_t *)&length, mbMessage->data, sizeof(length)) != 0) {break;}
      if ((length == 0) || (length > 128)) {break;}
      msg->filename = cgc_calloc(length + 1);
      if (cgc_ReadFromData(msg->filename, mbMessage->data, length) != 0) {break;}
      break;
    }
    case CGCMB_FILE_CLOSE:  
    {
      CGCMB_FILE_CLOSE_Message *msg = cgc_calloc(sizeof(CGCMB_FILE_CLOSE_Message));
      mbMessage->parsed = msg;
      if (cgc_ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->fileID, mbMessage->parameters, sizeof(msg->fileID)) != 0) {break;}
      break;
    } 
    case CGCMB_FILE_READ:  
    {
      CGCMB_FILE_READ_Message *msg = cgc_calloc(sizeof(CGCMB_FILE_READ_Message));
      mbMessage->parsed = msg;
      if (cgc_ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->fileID, mbMessage->parameters, sizeof(msg->fileID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->bytesToRead, mbMessage->data, sizeof(msg->bytesToRead)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->readOffset, mbMessage->data, sizeof(msg->readOffset)) != 0) {break;}
      break;
    }
    case CGCMB_FILE_WRITE:  
    {
      CGCMB_FILE_WRITE_Message *msg = cgc_calloc(sizeof(CGCMB_FILE_WRITE_Message));
      mbMessage->parsed = msg;
      if (cgc_ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->fileID, mbMessage->parameters, sizeof(msg->fileID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->mode, mbMessage->parameters, sizeof(msg->mode)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->bytesToWrite, mbMessage->data, sizeof(msg->bytesToWrite)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->writeOffset, mbMessage->data, sizeof(msg->writeOffset)) != 0) {break;}
      if ((msg->bytesToWrite == 0) || (msg->bytesToWrite > MAX_WRITE_SIZE)) {break;}
      msg->bytes = cgc_calloc(msg->bytesToWrite);
      if (cgc_ReadFromData(msg->bytes, mbMessage->data, msg->bytesToWrite) != 0) {break;}
      break;
    } 
    case CGCMB_TRANSACTION:    
    {
      CGCMB_TRANSACTION_Message *msg = cgc_calloc(sizeof(CGCMB_TRANSACTION_Message));
      mbMessage->parsed = msg;
      if (cgc_ReadFromData((uint8_t *)&msg->sessionKey, mbMessage->parameters, sizeof(msg->sessionKey)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->userID, mbMessage->parameters, sizeof(msg->userID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->connectionID, mbMessage->parameters, sizeof(msg->connectionID)) != 0) {break;}
      if (cgc_ReadFromData((uint8_t *)&msg->fileID, mbMessage->parameters, sizeof(msg->fileID)) != 0) {break;}
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

CGCMB_Connection *cgc_FindConnectionByID(uint32_t connectionID)
{
 for (int i=0; i< MAX_CONNECTIONS; i++)
  {
    if (cgc_mbServerState->connections[i] != NULL)
    {
      if (cgc_mbServerState->connections[i]->connectionID == connectionID)
      {
        return cgc_mbServerState->connections[i];
      }
    }
  }
  return NULL;
}

fs_file *cgc_FindFileByID(CGCMB_Connection *connection, uint32_t fileID)
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



int cgc_HandleCGCMBMessage(CGCMB_Message *mbMessage)
{
  if (mbMessage == NULL)
  {
    return -1;
  }
  // Verify Message
  if (cgc_VerifyCGCMBMessage(mbMessage) != 0)
  {
    cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
    return 0;
  }

  // Handle Message
  switch(mbMessage->header->command)
  {
    case CGCMB_NEGOTIATE:
    {
      if (cgc_mbServerState->state != INITIAL) 
      {
        cgc_SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_NEGOTIATE_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      uint16_t count_remaining = msg->numDialects;
      uint16_t *pDialects = msg->dialects;
      if (pDialects == NULL) 
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        break;
      }
      CGCMB_Message *mbResponse = cgc_CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_NEGOTIATE_RESPONSE;
      cgc_mbServerState->state = NEGOTIATE;
      while (count_remaining > 0)
      { 
        if (*pDialects == (uint16_t)CGCMB_DIALECT_1 ||
            *pDialects == (uint16_t)CGCMB_DIALECT_2 ||
            *pDialects == (uint16_t)CGCMB_DIALECT_3 )
        {
          // Negotiation successful, setup positive response
          cgc_mbServerState->dialect = *pDialects;
          cgc_mbServerState->sessionKey = cgc_rand();
          cgc_AddToData(mbResponse->data, (uint8_t *)&cgc_mbServerState->sessionKey, sizeof(cgc_mbServerState->sessionKey));
          cgc_AddToData(mbResponse->data, (uint8_t *)&cgc_mbServerState->dialect, sizeof(cgc_mbServerState->dialect));
          break;
        } 
        else 
        {
          count_remaining--;
          pDialects++;
        }
      }  
      if (cgc_mbServerState->dialect == 0)
      {
        cgc_mbServerState->state = CLOSED;
      }
      // Transmit Response  
      cgc_TransmitCGCMBMessage(mbResponse);
      cgc_DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_SESSION_SETUP:
    {
      if (cgc_mbServerState->state != NEGOTIATE)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_SESSION_SETUP_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (cgc_mbServerState->sessionKey != msg->sessionKey)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (msg->reserved != 0)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      cgc_mbServerState->state = SESSION;
      cgc_mbServerState->userID = cgc_LookupUser(msg->accountName, msg->password);
      CGCMB_Message *mbResponse = cgc_CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_SESSION_SETUP_RESPONSE;
      cgc_AddToData(mbResponse->data, (uint8_t *)&cgc_mbServerState->userID, sizeof(cgc_mbServerState->userID));
      uint8_t userIsGuest = cgc_mbServerState->userID == USER_GUEST;
      cgc_AddToData(mbResponse->data, &userIsGuest, 1);
      cgc_TransmitCGCMBMessage(mbResponse);
      cgc_DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_TREE_CONNECT:
    {
      if (cgc_mbServerState->state != SESSION)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_TREE_CONNECT_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (cgc_mbServerState->sessionKey != msg->sessionKey)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (cgc_mbServerState->userID != msg->userID)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      fs_tree *tree = cgc_FindTreeByPath(msg->userID, msg->path, msg->service);
      if (tree == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_ACCESS);
        return -1;
      }
      CGCMB_Connection *connection = NULL;
      for (int i=0; i< MAX_CONNECTIONS; i++)
      {
        if (cgc_mbServerState->connections[i] == NULL)
        {
          cgc_mbServerState->connections[i] = cgc_calloc(sizeof(CGCMB_Connection));
          connection = cgc_mbServerState->connections[i];
          break;
        }
      }
      if (connection == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FULL);
        return -1;
      }
      connection->connectionID = cgc_rand();
      connection->state = CONNECTION_OPEN;
      connection->openTree = tree;
      CGCMB_Message *mbResponse = cgc_CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_TREE_CONNECT_RESPONSE;
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
      cgc_AddToData(mbResponse->data, (uint8_t *)&connection->connectionID, sizeof(connection->connectionID));
      cgc_TransmitCGCMBMessage(mbResponse);
      cgc_DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_TREE_DISCONNECT:
    {
      if (cgc_mbServerState->state != SESSION)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_TREE_DISCONNECT_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (cgc_mbServerState->sessionKey != msg->sessionKey)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (cgc_mbServerState->userID != msg->userID)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      for (int i=0; i < MAX_CONNECTIONS; i++)
      {
        if (cgc_mbServerState->connections[i] != NULL)
        {
          if (cgc_mbServerState->connections[i]->connectionID == msg->connectionID)
          {
            cgc_free(cgc_mbServerState->connections[i]);
            cgc_mbServerState->connections[i] = NULL;
            CGCMB_Message *mbResponse = cgc_CreateBlankCGCMBMessage();
            mbResponse->header->command = CGCMB_TREE_DISCONNECT_RESPONSE;
            cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
            cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
            cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
            cgc_TransmitCGCMBMessage(mbResponse);
            cgc_DestroyCGCMBMessage(&mbResponse);
            return 0;
          }
        }
      }
      cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
      break;
    }
    case CGCMB_FILE_CREATE:
    {
      if (cgc_mbServerState->state != SESSION)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_FILE_CREATE_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (cgc_mbServerState->sessionKey != msg->sessionKey)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (cgc_mbServerState->userID != msg->userID)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      CGCMB_Connection *connection = cgc_FindConnectionByID(msg->connectionID);
      if (connection == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      for (int i=0; i < MAX_OPEN_FILES; i++)
      {
        if (connection->openFiles[i] == NULL)
        {
          connection->openFiles[i] = cgc_CreateFile(connection->openTree, msg->filename, msg->userID, msg->mode);
          if (connection->openFiles[i] != NULL)
          {
            // Send affirmative response
            CGCMB_Message *mbResponse = cgc_CreateBlankCGCMBMessage();
            mbResponse->header->command = CGCMB_FILE_CREATE_RESPONSE;
            cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
            cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
            cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
            cgc_AddToData(mbResponse->parameters, (uint8_t *)&connection->openFiles[i]->fileID, sizeof(connection->openFiles[i]->fileID));
            cgc_TransmitCGCMBMessage(mbResponse);
            cgc_DestroyCGCMBMessage(&mbResponse);
            return 0;
          } else {
            cgc_SendErrorResponse(CGCMB_ERROR_FILE);
            break;
          }
        }
      }
      cgc_SendErrorResponse(CGCMB_ERROR_FULL);
      break;
    }
    case CGCMB_FILE_CLOSE:
    {
      if (cgc_mbServerState->state != SESSION)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_FILE_CLOSE_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (cgc_mbServerState->sessionKey != msg->sessionKey)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (cgc_mbServerState->userID != msg->userID)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      CGCMB_Connection *connection = cgc_FindConnectionByID(msg->connectionID);
      if (connection == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      fs_file *file = cgc_FindFileByID(connection, msg->fileID);
      if (file == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      cgc_CloseFile(file);
      CGCMB_Message *mbResponse = cgc_CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_FILE_CLOSE_RESPONSE;
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->fileID, sizeof(msg->fileID));
      cgc_TransmitCGCMBMessage(mbResponse);
      cgc_DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_FILE_READ:
    {
      if (cgc_mbServerState->state != SESSION)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_FILE_READ_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (cgc_mbServerState->sessionKey != msg->sessionKey)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (cgc_mbServerState->userID != msg->userID)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      CGCMB_Connection *connection = cgc_FindConnectionByID(msg->connectionID);
      if (connection == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      fs_file *file = cgc_FindFileByID(connection, msg->fileID);
      if (file == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      if ((msg->bytesToRead == 0) || (msg->bytesToRead > MAX_READ_SIZE))
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        break;
      }
      uint8_t *data = cgc_calloc(msg->bytesToRead);
      if (cgc_ReadFile(data, file, msg->readOffset, msg->bytesToRead) != 0)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FILE);
        cgc_free(data);
        break;
      }
      CGCMB_Message *mbResponse = cgc_CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_FILE_READ_RESPONSE;
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->bytesToRead, sizeof(msg->bytesToRead));
      cgc_AddToData(mbResponse->data, data, msg->bytesToRead);
      cgc_TransmitCGCMBMessage(mbResponse);
      cgc_free(data);
      cgc_DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_FILE_WRITE:
    {
      if (cgc_mbServerState->state != SESSION)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_FILE_WRITE_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (cgc_mbServerState->sessionKey != msg->sessionKey)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (cgc_mbServerState->userID != msg->userID)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      CGCMB_Connection *connection = cgc_FindConnectionByID(msg->connectionID);
      if (connection == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      fs_file *file = cgc_FindFileByID(connection, msg->fileID);
      if (file == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      if ((msg->bytesToWrite == 0) || (msg->bytesToWrite > MAX_WRITE_SIZE))
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        break;
      }
      if (cgc_WriteFile(file, msg->bytes, msg->writeOffset, msg->bytesToWrite) != 0)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FILE);
        break;
      }
      CGCMB_Message *mbResponse = cgc_CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_FILE_WRITE_RESPONSE;
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->fileID, sizeof(msg->fileID));
      cgc_TransmitCGCMBMessage(mbResponse);
      cgc_DestroyCGCMBMessage(&mbResponse);
      break;
    }

    case CGCMB_TRANSACTION:
    {
      if (cgc_mbServerState->state != SESSION)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_STATE);
        return -1;
      }
      CGCMB_TRANSACTION_Message *msg = mbMessage->parsed;
      if (msg == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_FORMAT);
        return -1;
      }
      if (cgc_mbServerState->sessionKey != msg->sessionKey)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_SESSION);
        return -1;
      }
      if (cgc_mbServerState->userID != msg->userID)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_USER);
        return -1;
      }
      CGCMB_Connection *connection = cgc_FindConnectionByID(msg->connectionID);
      if (connection == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      if (connection->openTree == NULL) 
      {
        cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      if (cgc_strcmp(connection->openTree->serviceType, "EYEPSEE") != 0)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_TRANSACTION);
        break;
      }
      fs_file *file = cgc_FindFileByID(connection, msg->fileID);
      if (file == NULL)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      if (file->fileID != connection->openTree->files[0]->fileID)
      {
        cgc_SendErrorResponse(CGCMB_ERROR_NOT_FOUND);
        break;
      }
      void *pcResponse;
      uint32_t pcResponseLength;
      uint8_t errorCode;
      errorCode = cgc_HandleCGCRPCMessage(mbMessage->data->data, mbMessage->data->count, &pcResponse, &pcResponseLength);
      CGCMB_Message *mbResponse = cgc_CreateBlankCGCMBMessage();
      mbResponse->header->command = CGCMB_TRANSACTION_RESPONSE;
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->sessionKey, sizeof(msg->sessionKey));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->userID, sizeof(msg->userID));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&msg->connectionID, sizeof(msg->connectionID));
      cgc_AddToData(mbResponse->parameters, (uint8_t *)&errorCode, sizeof(errorCode));
      if ((pcResponseLength > 0) && (pcResponse != NULL))
      {
        cgc_AddToData(mbResponse->data, pcResponse, pcResponseLength);
        cgc_free(pcResponse);
      }
      cgc_TransmitCGCMBMessage(mbResponse);
      cgc_DestroyCGCMBMessage(&mbResponse);
      break;
    }
    case CGCMB_ECHO:
    {
      mbMessage->header->command = CGCMB_ECHO_RESPONSE;
      cgc_TransmitCGCMBMessage(mbMessage);
      break;
    }
    case CGCMB_END_SESSION:
    {
      cgc_mbServerState->state = CLOSED;
      mbMessage->header->command = CGCMB_END_SESSION_RESPONSE;
      cgc_TransmitCGCMBMessage(mbMessage);
      return 1;
    }
    default:
    {
      cgc_SendErrorResponse(CGCMB_ERROR_MSG);
      break;
    }
  }
  return 0;
}


void cgc_DestroyCGCMBMessage(CGCMB_Message **pmbMessage)
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
      cgc__terminate(-1);
    }
    switch(mbMessage->header->command)
    {
      case CGCMB_NEGOTIATE:
      {
        CGCMB_NEGOTIATE_Message *msg = mbMessage->parsed;
        cgc_free(msg->dialects);
        break;
      }
      case CGCMB_SESSION_SETUP: 
      {
        CGCMB_SESSION_SETUP_Message *msg = mbMessage->parsed;
        if (msg != NULL)
        {
          cgc_free(msg->password);
          cgc_free(msg->accountName);
        }
        break;
      }
      case CGCMB_TREE_CONNECT:
      {
        CGCMB_TREE_CONNECT_Message *msg = mbMessage->parsed;
        if (msg != NULL)
        {
          cgc_free(msg->password);
          cgc_free(msg->path);
          cgc_free(msg->service);
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
          cgc_free(msg->filename);
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
          cgc_free(msg->bytes);
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
        cgc__terminate(-1);
      }
    }
    cgc_free(mbMessage->parsed);
  }

  if (mbMessage->data != NULL)
  {
    cgc_free(mbMessage->data->data);
    cgc_free(mbMessage->data);
  }
  if (mbMessage->parameters != NULL)
  {
    cgc_free(mbMessage->parameters->data);
    cgc_free(mbMessage->parameters);
  }
  cgc_free(mbMessage->header);
  cgc_free(mbMessage);
  *pmbMessage = NULL;
  return;
}

CGCMB_Message *cgc_CreateBlankCGCMBMessage()
{
  CGCMB_Message *mbMessage = cgc_calloc(sizeof(CGCMB_Message));
  mbMessage->data = cgc_calloc(sizeof(CGCMB_Data));
  mbMessage->parameters = cgc_calloc(sizeof(CGCMB_Data));
  mbMessage->header = cgc_calloc(sizeof(CGCMB_Header));
  mbMessage->header->protocol = CGCMB_MAGIC;
  return mbMessage;
}

int cgc_VerifyCGCMBMessage(CGCMB_Message *mbMessage)
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

void cgc_TransmitCGCMBMessage(CGCMB_Message *mbMessage)
{       
  if (cgc_VerifyCGCMBMessage(mbMessage) != 0)
  {       
    return;
  }
  // Convert to transport and send
  TransportMessage *tpMessage = cgc_calloc(sizeof(TransportMessage));
  tpMessage->size = mbMessage->data->count + sizeof(mbMessage->data->count);
  tpMessage->size += mbMessage->parameters->count + sizeof(mbMessage->parameters->count);
  tpMessage->size += sizeof(mbMessage->header->security) + sizeof(mbMessage->header->flags) + sizeof(mbMessage->header->status) + sizeof(mbMessage->header->command) + sizeof(mbMessage->header->protocol);
  if (tpMessage->size > MAX_TRANSPORT_SIZE)
  {
    cgc_SendErrorResponse(CGCMB_ERROR_LENGTH);
    cgc_DestroyTransportMessage(&tpMessage);
    return;
  }
  tpMessage->data = cgc_calloc(tpMessage->size);
  uint8_t *pdata = tpMessage->data;
  cgc_memcpy(pdata, &mbMessage->header->protocol, sizeof(mbMessage->header->protocol)); pdata += sizeof(mbMessage->header->protocol);
  cgc_memcpy(pdata, &mbMessage->header->command, sizeof(mbMessage->header->command)); pdata += sizeof(mbMessage->header->command);
  cgc_memcpy(pdata, &mbMessage->header->status, sizeof(mbMessage->header->status)); pdata += sizeof(mbMessage->header->status);
  cgc_memcpy(pdata, &mbMessage->header->flags, sizeof(mbMessage->header->flags)); pdata += sizeof(mbMessage->header->flags);
  cgc_memcpy(pdata, mbMessage->header->security, sizeof(mbMessage->header->security)); pdata += sizeof(mbMessage->header->security);
  cgc_memcpy(pdata, &mbMessage->parameters->count, sizeof(mbMessage->parameters->count)); pdata += sizeof(mbMessage->parameters->count);
  if (mbMessage->parameters->count > 0)
  {
    cgc_memcpy(pdata, mbMessage->parameters->data, mbMessage->parameters->count); pdata += mbMessage->parameters->count;
  }
  cgc_memcpy(pdata, &mbMessage->data->count, sizeof(mbMessage->data->count)); pdata += sizeof(mbMessage->data->count);
  if (mbMessage->data->count > 0)
  {
    cgc_memcpy(pdata, mbMessage->data->data, mbMessage->data->count); pdata += mbMessage->data->count;
  }

  cgc_SendTransportMessage(tpMessage);
  cgc_DestroyTransportMessage(&tpMessage);

}