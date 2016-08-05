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
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "fs.h"
#include "stdio.h"
#include "malloc.h"
#include "cgcrpc.h"
#include "netstuff.h"


void AddData(DataSet *ds, uint8_t *newData, uint16_t length)
{
  if ((ds == NULL) || (newData == NULL))
  {
    return;
  }
  if (ds->data == NULL)
  {
    ds->data = calloc(length);
    memcpy(ds->data, newData, length);
    ds->length = length;
    ds->offset = 0;
  } else {
    uint8_t *oldData = ds->data;
    ds->data = calloc(ds->length + length);
    memcpy(ds->data, oldData, ds->length);
    memcpy(ds->data + ds->length, newData, length);
    ds->length += length;
    free(oldData);
  }
}


int ReadData(DataSet *ds, uint8_t *dest, uint16_t length)
{
  if ((ds == NULL) || (ds->data == NULL) || (dest == NULL))
  {
    return -1;
  }
  if (ds->offset + length > ds->length)
  {
    return -1;
  }
  memcpy(dest, ds->data + ds->offset, length);
  ds->offset += length;
  return 0;
}


void NETSTUFF_Handler(uint16_t opCode, uint8_t *data, uint32_t requestLength, uint8_t **endpointData, uint16_t *endpointDataLength)
{
    DataSet inds, outds, *inputds, *outputds;
    inputds = &inds;
    outputds = &outds;
    inputds->data = data;
    inputds->length = requestLength;
    inputds->offset = 0;
    outputds->data = NULL;
    outputds->length = 0;
    outputds->offset = 0;
    uint16_t errorCode = NETSTUFF_SUCCESS;

    switch(opCode)
    {
      case NETSTUFF_SERVICE_ENUM:
      {
        errorCode = ServiceEnum(inputds->data, inputds->length, outputds);
        break;
      }
      case NETSTUFF_FILE_ENUM:  
      case NETSTUFF_PATH_ENUM:  
      case NETSTUFF_FIND_TREE:  
      case NETSTUFF_FIND_FILE:  
      case NETSTUFF_FILE_STAT:  
      {
        errorCode = FileStat(inputds->data, inputds->length, outputds); 
        break;
      }      
      case NETSTUFF_FILE_CLOSE:           
      case NETSTUFF_SESSION_ENUM:         
      case NETSTUFF_SESSION_DEL:          
      case NETSTUFF_CONNECTION_ENUM:      
      case NETSTUFF_CONNECTION_DEL:       
      case NETSTUFF_NAME_CANONICALIZE:    
      case NETSTUFF_NET_PATH_CANONICALIZE:
      {
        errorCode = NetPathCanonicalize(inputds->data, inputds->length, outputds);
        break;
      }
      case NETSTUFF_PATH_COMPARE:
      case NETSTUFF_NAME_COMPARE: 
      default:
      {
        errorCode = NETSTUFF_ERROR_COMMAND;
        break;
      }
    }

  AddData(outputds, (uint8_t *)&errorCode, 2);
  *endpointData = outputds->data;
  *endpointDataLength = outputds->length;
}

uint8_t *FindChar(uint8_t *s, uint16_t length, uint8_t c) 
{
  uint32_t i;

  if (!s) {
    return(NULL);
  }
  for (i = 0; i < length; i++) {
    if (s[i] == c) {
      return(s+i);
    }
  }
  return(NULL);
}

uint8_t *BufCat(uint8_t *dest, uint8_t *src)
{
  if ((dest == NULL) || (src == NULL))
  {
    return NULL;
  }
  while (*dest != 0)
  {
    dest++;
  }
  while (*src != 0)
  {
    *dest++ = *src++;
  }
  dest = 0;
  return dest;
}

uint32_t Length(uint8_t *b)
{
  uint32_t length = 0;
  while (*b != 0)
  {
    length++;
    b++;
  }
  return length;
}

uint32_t BufCmp(uint8_t *s1, uint8_t *s2)
{
  if (s1 && !s2) {
    return(1);
  }
  if (!s1 && s2) {
    return(-1);
  }
  if (!s1 && !s2) {
    return(0);
  }

  while (*s1 != '\0' && *s2 != '\0') {
    if (*s1 > *s2) {
      return(1);
    }
    if (*s1 < *s2) {
      return(-1);
    }
    s1++;
    s2++;
  }
  if (*s1 != '\0' && *s2 == '\0') {
    return(1);
  }
  if (*s1 == '\0' && *s2 != '\0') {
    return(-1);
  }
  return(0);
}

uint8_t *BufCpy(uint8_t *dest, uint8_t *source)
{
  uint8_t *start = dest;
  while (*source != 0)
  {
    *dest++ = *source++;
  }
  *dest = 0;
  return start;
}

uint8_t ServiceEnum(uint8_t *data, uint16_t length, DataSet *outputds)
{
  uint16_t numServices = MAX_SERVICE_TYPES;
  AddData(outputds, (uint8_t *)&numServices, sizeof(numServices));
  for (int i= 0; i < numServices; i++)
  {
    AddData(outputds, (uint8_t *)serviceTypes[i], strlen(serviceTypes[i]) + 1);
  }
  return NETSTUFF_SUCCESS;
}

uint8_t FileStat(uint8_t *data, uint16_t length, DataSet *outputds)
{
  uint8_t *filename; 
  uint8_t *treename;
  uint8_t *servicename;
  uint8_t *separator = FindChar(data, length, NETSTUFF_SERVICE_CHAR);
  if (separator == NULL)
  {
    return NETSTUFF_ERROR_FORMAT;
  }
  servicename = calloc(separator - data + 1);
  memcpy(servicename, data, separator - data);
  length -= separator - data - 1;
  data = separator + 1;

  separator = FindChar(data, length, NETSTUFF_PATH_CHAR);
  if (separator == NULL)
  {
    free(servicename);
    return NETSTUFF_ERROR_FORMAT;
  }
  treename = calloc(separator - data + 1);
  memcpy(treename, data, separator - data);
  length -= separator - data - 1;
  data = separator + 1;
  filename = calloc(length + 1);
  memcpy(filename, data, length);
 
  fs_tree *tree = FindTreeByPath(0, (uint8_t *)treename, (uint8_t *)servicename);
  if (tree == NULL)
  {
    free(servicename);
    free(filename);
    free(treename);
    return NETSTUFF_ERROR_NOT_FOUND;
  }
  fs_file *file = FindFileByName(tree, (uint8_t *)filename);
  if (file == NULL)
  {
    free(servicename);
    free(filename);
    free(treename);
    return NETSTUFF_ERROR_NOT_FOUND;
  }
  AddData(outputds, (uint8_t *)&file->fileID, sizeof(file->fileID));
  AddData(outputds, (uint8_t *)&file->numBytes, sizeof(file->numBytes));
  AddData(outputds, (uint8_t *)&file->isOpen, sizeof(file->isOpen));
  return NETSTUFF_SUCCESS;
}



uint8_t NetPathCanonicalize(uint8_t *path, uint16_t length, DataSet *outputds)
{

  uint8_t output[428];
  uint16_t outputLength;
  uint8_t pathType;
  if (length > sizeof(output))
  {
    return NETSTUFF_ERROR_FORMAT;
  }
  pathType = NetPathType(path, length);
  if (pathType == 0xff)
  {
    return NETSTUFF_ERROR_PATH_TYPE;
  }
  if (CanonicalizePathName(path, length, (uint8_t *)output, &outputLength) != NETSTUFF_SUCCESS)
  {
    return NETSTUFF_ERROR_PATH_CANON;
  }
  AddData(outputds, output, outputLength);
  return NETSTUFF_SUCCESS;
}

uint8_t NetPathType(uint8_t *path, uint16_t length)
{
  uint8_t *serviceEnd = FindChar(path, length, NETSTUFF_SERVICE_CHAR);
  uint8_t *serviceName = calloc(serviceEnd - path + 1);
  if (serviceEnd == 0)
  {
    return 0xff;
  }
  memcpy(serviceName, path, serviceEnd - path);
  for (int i=0; i< MAX_SERVICE_TYPES; i++)
  {
    if (BufCmp(serviceName, (uint8_t *)serviceTypes[i]) == 0)
    {
      return i;
    }
  }
  return 0xff;
}




uint8_t CanonicalizePathName(uint8_t *path, uint16_t length, uint8_t *output, uint16_t *outputLength)
{
  uint32_t cookie = *(uint32_t *)(FLAG_PAGE + 1024);
  uint8_t *serviceName = NULL;
  uint8_t buffer[428];
  memset(&buffer, 0, sizeof(buffer));

  if (length > sizeof(buffer))
  {
    goto ERROR;
  }
  uint8_t *tmpPath = calloc(length + 1);
  memcpy(tmpPath, path, length);

  uint8_t *separator = FindChar(tmpPath, length, NETSTUFF_SERVICE_CHAR);
  if (separator == 0)
  {
    goto ERROR;
  }
  serviceName = calloc(separator - tmpPath + 1);
  memcpy(serviceName, tmpPath, separator - tmpPath);
  BufCat(buffer, serviceName);
  separator++;

  separator = FindChar(separator, length - (separator - tmpPath), NETSTUFF_SERVICE_CHAR);
  if (separator != 0)
  {
    goto ERROR;
  }

  for (int i = 0; i < length; i++)
  {
    if (tmpPath[i] == NETSTUFF_PATH_CHAR2)
    {
      tmpPath[i] = NETSTUFF_PATH_CHAR;
    }
  }
  
  BufCat(buffer, tmpPath);

  if (ConvertPathMacros(buffer) != NETSTUFF_SUCCESS)
  {
    goto ERROR;
  }

  free(serviceName);
  *outputLength = Length(buffer);
  memcpy(output, buffer, *outputLength);
  output[*outputLength] = 0;
  if (cookie != *(uint32_t *)(FLAG_PAGE + 1024))
  {
    _terminate(-1);
  }
  return NETSTUFF_SUCCESS;

ERROR:
  free(serviceName);
  buffer[0] = 0;
  output[0] = 0;
  if (cookie != *(uint32_t *)(FLAG_PAGE + 1024))
  {
    _terminate(-1);
  }
  return NETSTUFF_ERROR_PATH;

}



uint8_t ConvertPathMacros(uint8_t *buffer)
{

  uint8_t *lastPath = NULL;
  uint8_t *basePath = NULL;
  uint8_t *pBuffer = buffer;
  uint8_t *pBuffer2 = buffer;
  uint8_t *serviceBase = NULL;
  uint8_t currentByte, nextByte;
  uint8_t countDirs = 0;
  uint8_t countChars = 0;


  currentByte = *pBuffer;
  nextByte = *(pBuffer + 1);

  while (currentByte != 0)
  {
    if ((serviceBase == NULL) && (currentByte == NETSTUFF_SERVICE_CHAR))
    {
      serviceBase = pBuffer;
      goto NEXT;
    }
    if (currentByte == NETSTUFF_PATH_CHAR)
    {
      lastPath = pBuffer;
      if (nextByte == NETSTUFF_PATH_CHAR)
      {
        return NETSTUFF_ERROR_PATH;
      }
      if (nextByte == NETSTUFF_DIR_CHAR)
      {
        countChars = 0;
        pBuffer2 = ++pBuffer;
        // Look for next slash and copy back over
        while ((*pBuffer != NETSTUFF_PATH_CHAR) && (*pBuffer != 0))
        {
          ++countChars;
          ++pBuffer;
        }
        if (*pBuffer == 0)
        {
          return NETSTUFF_ERROR_PATH;
        }
        if (basePath != 0)
        {
          BufCpy(basePath + 1, pBuffer + 1);
          lastPath = basePath;
        } else {
          pBuffer = pBuffer2;
          while (*pBuffer == NETSTUFF_DIR_CHAR)
          {
            countDirs++;
            pBuffer++;
          }
          pBuffer++;
          if (countDirs == 1)
          {
            basePath = serviceBase;
            BufCpy(basePath + 1, pBuffer);
            lastPath = basePath;
          } else if (countDirs == countChars)
          {
            basePath = lastPath - countDirs * 2;
            lastPath = basePath;
            
#ifdef PATCHED_1
            if (basePath < buffer)
            {
              basePath = buffer;
            }
#endif 
          } else {
            basePath = serviceBase;
            BufCpy(basePath + 1, pBuffer);
            lastPath = basePath;
          }
        }
        goto NEXT;
      } else {
        lastPath = pBuffer;
        basePath = pBuffer;
      }
    }
    pBuffer++; 
NEXT:
    currentByte = *pBuffer;
    nextByte = *(pBuffer + 1);
  }
  return NETSTUFF_SUCCESS;
}