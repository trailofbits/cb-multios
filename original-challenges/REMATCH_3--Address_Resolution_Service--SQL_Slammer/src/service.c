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
#include "libc.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "linkedlist.h"
#include "service.h"

linkedList *serverList;
int adminPortOffset;

int GetNextAdminPort()
{
  adminPortOffset = (adminPortOffset + 4) % 4096;
  return adminPortOffset;
}

serverInfo *CreateServer(int length)
{
  serverInfo *pServer = calloc(sizeof(serverInfo));
  pServer->name = GenerateRandomString(length);
  pServer->instances = NewList(LIST_INSTANCE);
  return pServer;
}

instanceInfo *CreateInstance(int length)
{
  instanceInfo *pInstance = calloc(sizeof(instanceInfo));
  pInstance->name = GenerateRandomString(length);
  pInstance->port = GenerateRandomNumber(0, 65535);
  pInstance->adminPortOffset = GetNextAdminPort();
  return pInstance;
}

void AddInstanceToServer(serverInfo *pServer, instanceInfo *pInstance)
{
  AddToList(pServer->instances, pInstance, LIST_INSTANCE);
  pInstance->server = pServer;
}

serverInfo *FindServer(char *name)
{
  link *listItem = serverList->root;
  while (listItem != NULL) 
  {
    serverInfo *server = listItem->object;
    if (server == NULL) 
    {
      continue;
    }
    if (strcmp(server->name, name) == 0)
    {
      return server;
    }
    listItem = listItem->next;
  }
  return NULL;
}

instanceInfo *FindInstance(char *name)
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
      if (strcmp(instance->name, name) == 0)
      {
        return instance;
      }
      listItem2 = listItem2->next;
    }
    listItem = listItem->next;
  }
  return NULL;
}

void InitializeSimulation() 
{
  adminPortOffset = 0;
  serverList = NewList(LIST_SERVER);
  // Create Servers
  int numServers = GenerateRandomNumber(10,32);
  int nameLength = GenerateRandomNumber(34, 64);
  for (int i=0; i<numServers; i++) 
  {
    serverInfo *server = CreateServer(nameLength - i);
    AddToList(serverList, server, LIST_SERVER);
    // Create and link instances to servers
    int numInstances = GenerateRandomNumber(1, 15);
    int instanceLength = GenerateRandomNumber(32, 64);
    for(int j=0; j<numInstances; j++) 
    {
      instanceInfo *instance = CreateInstance(instanceLength - j);
      AddInstanceToServer(server, instance);
    }
  }
}

void QueryOne(query *pCurrentQuery, response *pCurrentResponse) 
{
  char name[64];
  for (int i=0; i< 64; i++) {
    name[i] = i;
  }
  printf("Query One\n");
  // Send info for one instance
#ifdef PATCHED_1
  strncpy(name, (char *)pCurrentQuery->data, 64);
#else
  strcpy(name, (char *)pCurrentQuery->data);
#endif
  instanceInfo *instance = FindInstance(name);
  if (instance == NULL) 
  {
    printf("Not found\n");
    return;
  }
  AddToResponse(pCurrentResponse, "instance:");
  AddToResponse(pCurrentResponse, instance->name);
  AddToResponse(pCurrentResponse, ":");
  AddToResponse(pCurrentResponse, "tcp:");
  char number[12];
  sprintf(number, "$d", instance->port);
  AddToResponse(pCurrentResponse, number);
  AddToResponse(pCurrentResponse, ":");
  AddToResponse(pCurrentResponse, "server:");
  AddToResponse(pCurrentResponse, instance->server->name);
  AddToResponse(pCurrentResponse, ":");
  return;
}

int main(void) 
{
  char inputBuffer[1024];
  
  InitializeRandomness();
  InitializeSimulation();


  while (1) 
  {

    int bytesReceived = ReceiveUntil(inputBuffer, sizeof(inputBuffer), '\n');
    if (bytesReceived < 0) 
    {
      break;
    }
    if (bytesReceived == 0) 
    {
      continue;
    }
    query *pCurrentQuery = ParseQuery(inputBuffer);
    response *pCurrentResponse = GenerateBlankResponse();
    switch (pCurrentQuery->type)
    {
      case QUERY_ALL:
      {
        printf("Query All\n");
        // List all servers in network
        link *listItem = serverList->root;
        while (listItem != NULL) 
        {
          serverInfo *server = listItem->object;
          if (server == NULL) 
          {
            continue;
          }
          AddToResponse(pCurrentResponse, "server:");
          AddToResponse(pCurrentResponse, server->name);
          AddToResponse(pCurrentResponse, ":");
          listItem = listItem->next;
        } 
        break;
      }
      case QUERY_SERVER:
      {
        printf("Query Server\n");
        // List all instances on a server
        char *name = (char *)pCurrentQuery->data;
        serverInfo *server = FindServer(name);
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
          AddToResponse(pCurrentResponse, "instance:");
          AddToResponse(pCurrentResponse, instance->name);
          AddToResponse(pCurrentResponse, ":");
          listItem = listItem->next;
        }
        break;
      }
      case QUERY_ONE:
      {
        QueryOne(pCurrentQuery, pCurrentResponse);
        break;
      }
      case QUERY_ADMIN:
      {
        // Send admin info for one instance
        printf("Query Admin\n");
        int version = pCurrentQuery->data[0];
        if (version != 1)
        {
          printf("Invalid Query\n");
          _terminate(0);
        }
        char instanceName[64];
        strncpy(instanceName, (char *)&pCurrentQuery->data[1], 64);
        instanceInfo *instance = FindInstance(instanceName);
        if (instance == NULL) 
        {
          printf("Instance Not Found\n");
          _terminate(0);
        }
        AddToResponse(pCurrentResponse, "admin:");
        char number[12];
        memset(number, 0, sizeof(number));
        uint16_t adminPort = *(uint16_t *)((uint8_t *)FLAG_PAGE + instance->adminPortOffset);
        sprintf(number, "$x", (int)adminPort);
        AddToResponse(pCurrentResponse, number);
        AddToResponse(pCurrentResponse, ":");
        break;
      }
      default:
      {
        // Invalid Query
        printf("Invalid Query\n");
        _terminate(0);
        break;
      }
    }
    SendResponse(pCurrentResponse);
    pCurrentQuery = DestroyQuery(pCurrentQuery);
    pCurrentResponse = DestroyResponse(pCurrentResponse);
  }
  return 0;
}