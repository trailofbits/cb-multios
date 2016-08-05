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
#ifndef LOADER_H
#define LOADER_H

#define EXECUTABLE_FILE_MAGIC 0xC67CC76C

#define EXECUTABLE_TYPE_LIBRARY     0xe1
#define EXECUTABLE_TYPE_EXECUTABLE  0xe2

#define OPCODE_READ_MEM   0x37  
#define OPCODE_WRITE_MEM  0x38
#define OPCODE_WRITE_REG  0x39
#define OPCODE_EXIT       0x40
#define OPCODE_OUTPUT     0x41
#define OPCODE_INPUT      0x42

#pragma pack(push,1)
typedef struct ExecutableFileHeader_s {
  uint32_t  size;
  uint32_t  magic;
  uint8_t   type;
  uint16_t  functionCount;
  uint16_t  functionTableOffset;
  uint16_t  resourceCount;
  uint16_t  resourceOffset;
  uint16_t  functionsSize;
  uint16_t  functionsOffset;
} ExecutableFileHeader;
// Followed by Function Table
// Followed by Resource Entries
// FOllowed by function bodies

typedef struct FunctionTableEntry_s {
  char      name[64];
  uint16_t  index;
  uint32_t  offset; // offset within file when in file, offset in functions when in memory
} FunctionTableEntry;

typedef struct ResourceEntry_s {
  uint16_t  type;
  char      value[64];
} ResourceEntry;
#pragma pack(pop)

typedef struct ExecutableInMemory_s {
  uint8_t             type;
  uint16_t            functionCount;
  FunctionTableEntry  *functionTable;
  uint16_t            resourceCount;
  ResourceEntry       *resourceTable;
  uint8_t             *functions;
} ExecutableInMemory;

ExecutableInMemory *LoadSharedLibrary(FileNode *file); // Calls SharedLibraryMain inside
uint8_t *GetFunctionAddress(char *name, ExecutableInMemory *sl); // Get the address of the function
void FreeLibrary(ExecutableInMemory *sl);
int ExecuteFunction(uint8_t *address);
char *LookupResource(ExecutableInMemory *sl, uint16_t index);

#endif