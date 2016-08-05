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
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"
#include "filesystem.h"
#include "loader.h"

ExecutableInMemory *LoadSharedLibrary(FileNode *file)
{
  //Read data from file and verify
  if (file == NULL)
  {
    return NULL;
  }
  ExecutableInMemory *sl = calloc(sizeof(ExecutableInMemory));

  ExecutableFileHeader *header = (ExecutableFileHeader *)file->contents;
  if (header->size != file->size)
  {
    debug_print("Invalid file header: size $d != $d\n", header->size, file->size);
    return NULL;
  }
  if (header->magic != EXECUTABLE_FILE_MAGIC)
  {
    debug_print("Invalid file header: magic\n");
    return NULL;
  }
  if ((header->type != EXECUTABLE_TYPE_LIBRARY)&&(header->type != EXECUTABLE_TYPE_EXECUTABLE))
  {
    debug_print("Invalid file header: type\n");
    return NULL;
  }
  if (header->functionCount == 0)
  {
    debug_print("Invalid file header: functions\n");
    return NULL;
  }
  if (header->functionTableOffset != sizeof(ExecutableFileHeader))
  {
    debug_print("Invalid file header: function table offset\n");
    return NULL;
  }
  if (header->resourceCount * sizeof(ResourceEntry) > file->size - sizeof(ExecutableFileHeader) - header->functionCount * sizeof(FunctionTableEntry))
  {
    debug_print("Invalid file header: resource size\n");
    return NULL;
  }
  if (header->resourceOffset > file->size - header->resourceCount * sizeof(ResourceEntry))
  {
    debug_print("Invalid file header: resource offset\n");
    return NULL;
  }
  if (header->functionsSize > file->size - sizeof(ExecutableFileHeader) - header->functionCount * sizeof(FunctionTableEntry) - header->resourceCount * sizeof(ResourceEntry))
  {
    debug_print("Invalid file header: functions size\n");
    return NULL;
  }
  if (header->functionsOffset > file->size - header->functionsSize)
  {
    debug_print("Invalid file header: functions size\n");
    return NULL;
  }
  sl->type = header->type;
  sl->functionCount = header->functionCount;
  sl->functionTable = calloc(header->functionCount * sizeof(FunctionTableEntry));
  memcpy(sl->functionTable, file->contents + header->functionTableOffset, header->functionCount * sizeof(FunctionTableEntry));
  for (int i = 0; i < sl->functionCount; i++)
  {
    sl->functionTable[i].offset -= header->functionsOffset;
  }
  sl->resourceCount = header->resourceCount;
  sl->resourceTable = calloc(header->resourceCount * sizeof(ResourceEntry));
  memcpy(sl->resourceTable, file->contents + header->resourceOffset, header->resourceCount * sizeof(ResourceEntry));
  sl->functions = calloc(header->functionsSize);
  memcpy(sl->functions, file->contents + header->functionsOffset, header->functionsSize);

  uint8_t *mainAddress = GetFunctionAddress("SharedLibraryMain", sl);
  ExecuteFunction(mainAddress);
  return sl;
}

uint8_t *GetFunctionAddress(char *name, ExecutableInMemory *sl)
{
  if (sl == NULL)
  {
    return NULL;
  }
  for(int i = 0; i < sl->functionCount; i++)
  {
    if (strcmp(name, sl->functionTable[i].name) == 0)
    {
      return sl->functions + sl->functionTable[i].offset;
    }
  }
  return NULL;
}

void FreeLibrary(ExecutableInMemory *sl)
{
  if (sl)
  {
    free(sl->functions);
    free(sl);
  }
}

int ExecuteFunction(uint8_t *address)
{
  if (address == NULL)
  {
    return -1;
  }
  uint32_t regA = 0;
  char opcode = *address++;
  while (opcode != OPCODE_EXIT)
  {
    switch(opcode)
    {
      case OPCODE_READ_MEM:
      {
        uint32_t *source = *(uint32_t **)address; 
        address += 4;
        regA = *source;
        break;
      }
      case OPCODE_WRITE_MEM:
      {
        uint32_t *dest = *(uint32_t **)address; 
        address += 4;
        uint32_t value = *(uint32_t *)address;
        address += 4;
        *dest = value;
        break;
      }
      case OPCODE_WRITE_REG:
      {
        uint32_t *dest = *(uint32_t **)address;
        address += 4;
        *dest = regA;
        break;
      }
      case OPCODE_OUTPUT:
      {
        transmit_fixed((uint8_t *)&regA, 4);
        break;
      }
      default:
        debug_print("Invalid Instruction\n");
        _terminate(-2);
    }
    opcode = *address++;
  }
  return regA;
}

char *LookupResource(ExecutableInMemory *sl, uint16_t index)
{
  if (sl == NULL)
  {
    return NULL;
  }
  if (index >= sl->resourceCount)
  {
    debug_print("Invalid Resource index $d\n", index);
    return NULL;
  }
  return sl->resourceTable[index].value;
}