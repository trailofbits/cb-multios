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
#include "cgc_libc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_malloc.h"
#include "cgc_linkedlist.h"
#include "cgc_service.h"

linkedList *serverList;
int adminPortOffset;

int cgc_GetNextAdminPort()
{
  adminPortOffset = (adminPortOffset + 4) % 4096;
  return adminPortOffset;
}

serverInfo *cgc_CreateServer(int length)
{
  serverInfo *pServer = cgc_calloc(sizeof(serverInfo));
  pServer->name = cgc_GenerateRandomString(length);
  pServer->instances = cgc_NewList(LIST_INSTANCE);
  return pServer;
}

instanceInfo *cgc_CreateInstance(int length)
{
  instanceInfo *pInstance = cgc_calloc(sizeof(instanceInfo));
  pInstance->name = cgc_GenerateRandomString(length);
  pInstance->port = cgc_GenerateRandomNumber(0, 65535);
  pInstance->adminPortOffset = cgc_GetNextAdminPort();
  return pInstance;
}

void cgc_AddInstanceToServer(serverInfo *pServer, instanceInfo *pInstance)
{
  cgc_AddToList(pServer->instances, pInstance, LIST_INSTANCE);
  pInstance->server = pServer;
}

serverInfo *cgc_FindServer(char *name)
{
  link *listItem = serverList->root;
  while (listItem != NULL) 
  {
    serverInfo *server = listItem->object;
    if (server == NULL) 
    {
      continue;
    }
    if (cgc_strcmp(server->name, name) == 0)
    {
      return server;
    }
    listItem = listItem->next;
  }
  return NULL;
}

instanceInfo *cgc_FindInstance(char *name)
{
  link *listItem = serverList->root;
  while (listItem != NULL) 
  {
    serverInfo *server = listItem->object;
    if (server == NULL) 
    {
      continue;
    }
    link *listItem2 = server->instances->root;
    while (listItem2 != NULL) 
    {
      instanceInfo *instance = listItem2->object;
      if (instance == NULL)
      {
        continue;
      }
      if (cgc_strcmp(instance->name, name) == 0)
      {
        return instance;
      }
      listItem2 = listItem2->next;
    }
    listItem = listItem->next;
  }
  return NULL;
}

void cgc_InitializeSimulation() 
{
  adminPortOffset = 0;
  serverList = cgc_NewList(LIST_SERVER);
  // Create Servers
  int numServers = cgc_GenerateRandomNumber(10,32);
  int nameLength = cgc_GenerateRandomNumber(34, 64);
  for (int i=0; i<numServers; i++) 
  {
    serverInfo *server = cgc_CreateServer(nameLength - i);
    cgc_AddToList(serverList, server, LIST_SERVER);
    // Create and link instances to servers
    int numInstances = cgc_GenerateRandomNumber(1, 15);
    int instanceLength = cgc_GenerateRandomNumber(32, 64);
    for(int j=0; j<numInstances; j++) 
    {
      instanceInfo *instance = cgc_CreateInstance(instanceLength - j);
      cgc_AddInstanceToServer(server, instance);
    }
  }
}

void cgc_QueryOne(query *pCurrentQuery, response *pCurrentResponse) 
{
  char name[64];
  for (int i=0; i< 64; i++) {
    name[i] = i;
  }
  cgc_printf("Query One\n");
  // Send info for one instance
#ifdef PATCHED_1
  cgc_strncpy(name, (char *)pCurrentQuery->data, 64);
#else
  cgc_strcpy(name, (char *)pCurrentQuery->data);
#endif
  instanceInfo *instance = cgc_FindInstance(name);
  if (instance == NULL) 
  {
    cgc_printf("Not found\n");
    return;
  }
  cgc_AddToResponse(pCurrentResponse, "instance:");
  cgc_AddToResponse(pCurrentResponse, instance->name);
  cgc_AddToResponse(pCurrentResponse, ":");
  cgc_AddToResponse(pCurrentResponse, "tcp:");
  char number[12];
  cgc_sprintf(number, "$d", instance->port);
  cgc_AddToResponse(pCurrentResponse, number);
  cgc_AddToResponse(pCurrentResponse, ":");
  cgc_AddToResponse(pCurrentResponse, "server:");
  cgc_AddToResponse(pCurrentResponse, instance->server->name);
  cgc_AddToResponse(pCurrentResponse, ":");
  return;
}

int main(int cgc_argc, char *cgc_argv[]) 
{
  char inputBuffer[1024];
  
  cgc_InitializeRandomness();
  cgc_InitializeSimulation();


  while (1) 
  {

    int bytesReceived = cgc_ReceiveUntil(inputBuffer, sizeof(inputBuffer), '\n');
    if (bytesReceived < 0) 
    {
      break;
    }
    if (bytesReceived == 0) 
    {
      continue;
    }
    query *pCurrentQuery = cgc_ParseQuery(inputBuffer);
    response *pCurrentResponse = cgc_GenerateBlankResponse();
    switch (pCurrentQuery->type)
    {
      case QUERY_ALL:
      {
        cgc_printf("Query All\n");
        // List all servers in network
        link *listItem = serverList->root;
        while (listItem != NULL) 
        {
          serverInfo *server = listItem->object;
          if (server == NULL) 
          {
            continue;
          }
          cgc_AddToResponse(pCurrentResponse, "server:");
          cgc_AddToResponse(pCurrentResponse, server->name);
          cgc_AddToResponse(pCurrentResponse, ":");
          listItem = listItem->next;
        } 
        break;
      }
      case QUERY_SERVER:
      {
        cgc_printf("Query Server\n");
        // List all instances on a server
        char *name = (char *)pCurrentQuery->data;
        serverInfo *server = cgc_FindServer(name);
        if (server == NULL) 
        {
          continue;
        }
        link *listItem = server->instances->root;
        while (listItem != NULL) 
        {
          instanceInfo *instance = listItem->object;
          if (instance == NULL) 
          {
            continue;
          }
          cgc_AddToResponse(pCurrentResponse, "instance:");
          cgc_AddToResponse(pCurrentResponse, instance->name);
          cgc_AddToResponse(pCurrentResponse, ":");
          listItem = listItem->next;
        }
        break;
      }
      case QUERY_ONE:
      {
        cgc_QueryOne(pCurrentQuery, pCurrentResponse);
        break;
      }
      case QUERY_ADMIN:
      {
        // Send admin info for one instance
        cgc_printf("Query Admin\n");
        int version = pCurrentQuery->data[0];
        if (version != 1)
        {
          cgc_printf("Invalid Query\n");
          cgc__terminate(0);
        }
        char instanceName[64];
        cgc_strncpy(instanceName, (char *)&pCurrentQuery->data[1], 64);
        instanceInfo *instance = cgc_FindInstance(instanceName);
        if (instance == NULL) 
        {
          cgc_printf("Instance Not Found\n");
          cgc__terminate(0);
        }
        cgc_AddToResponse(pCurrentResponse, "admin:");
        char number[12];
        cgc_memset(number, 0, sizeof(number));
        uint16_t adminPort = *(uint16_t *)((uint8_t *)FLAG_PAGE + instance->adminPortOffset);
        cgc_sprintf(number, "$x", (int)adminPort);
        cgc_AddToResponse(pCurrentResponse, number);
        cgc_AddToResponse(pCurrentResponse, ":");
        break;
      }
      default:
      {
        // Invalid Query
        cgc_printf("Invalid Query\n");
        cgc__terminate(0);
        break;
      }
    }
    cgc_SendResponse(pCurrentResponse);
    pCurrentQuery = cgc_DestroyQuery(pCurrentQuery);
    pCurrentResponse = cgc_DestroyResponse(pCurrentResponse);
  }
  return 0;
}