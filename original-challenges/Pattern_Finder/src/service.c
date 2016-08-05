/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#define DEBUG
#include <libcgc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assert.h"
#include "queue.h"
#include "sigdb.h"
#include "safe.h"
#include "trie.h"

static void ReportMatches(FILE* Stream, list** MatchArray, size_t MatchArraySize)
{
#define MAX_REPORT_SIZE 512
  char ReportContents[MAX_REPORT_SIZE];
  size_t ReportContentsIndex = 0;
  memset(ReportContents, 0, MAX_REPORT_SIZE);
  list** Array = MatchArray;

  for (size_t MatchArrayIndex = 0; MatchArrayIndex < MatchArraySize; ++MatchArrayIndex)
  {
    signature* Signature = Array[MatchArrayIndex]->Value;
#ifdef PATCHED_1
    size_t Len = Signature->PathSize + 3 + strlen(SeverityString(Signature->Severity)) + 11;
    if (ReportContentsIndex + Len < ReportContentsIndex || ReportContentsIndex + Len > MAX_REPORT_SIZE)
      break;
#endif
    memcpy(ReportContents + ReportContentsIndex, Signature->Path, Signature->PathSize);

    ReportContentsIndex += Signature->PathSize;
    ReportContentsIndex += sprintf(ReportContents + ReportContentsIndex, " - %s - %x\n",
        SeverityString(Signature->Severity),
        BytesToUnsigned(Signature->Data, Signature->DataSize));
  }

  fprintf(Stream, "%s", ReportContents);
}

static int ReadLine(FILE* Stream, char* Buf, size_t Max)
{
  memset(Buf, 0, Max);

  fflush(stdout);
  ssize_t Read = freaduntil(Buf, Max, '\n', Stream);
  if (Read < 0)
  {
    return -1;
  }

  Buf[Max] = '\0';
  return Read;
}

static int ReadExactlyNBytes(FILE* Stream, void* Buf, size_t RequestedBytes)
{
  size_t TotalReadBytes = 0;
  ssize_t ReadBytes;

  fflush(stdout);
  ReadBytes = fread(Buf + TotalReadBytes, RequestedBytes - TotalReadBytes, Stream);
  if (ReadBytes < 0)
  {
    return -1;
  }
  else
  {
    TotalReadBytes += ReadBytes;
    ReadBytes = -1;
  }


  return 0;
}

static int ReadNByteLine(FILE* Stream, void* Buf, size_t RequestedBytes)
{
  if (ReadExactlyNBytes(Stream, Buf, RequestedBytes) != 0)
    return -1;

  char ch;
  fread(&ch, 1, Stream);
  return ch != '\n';
}


static unsigned long ReadUnsigned(FILE* Stream, void* Buf, size_t Max)
{
  if (ReadLine(Stream, Buf, Max) < 0)
    return -1;

  return strtoul(Buf, NULL, 10);
}

static int CompareSignatureEnclosedInList(void* A, void* B)
{
  char* PathA = ((signature* )((list*) *(void **)A)->Value)->Path;
  char* PathB = ((signature* )((list*) *(void **)B)->Value)->Path;
  return strcmp(PathA, PathB);
}

static int SortArray(char* Array, size_t ElementSize, size_t NumElements, int (*cmp)(void*, void*))
{
  long long Scratch;
  size_t SwapIndex = 0;

  while (NumElements != 0)
  {
    SwapIndex = 0;

    for (size_t ArrayIndex = 1; ArrayIndex < NumElements; ArrayIndex++)
    {
      if (cmp(Array + ((ArrayIndex - 1) * ElementSize), Array + (ArrayIndex * ElementSize)) > 0)
      {
        memcpy(&Scratch, Array + ((ArrayIndex - 1) * ElementSize), ElementSize);
        memcpy(Array + ((ArrayIndex - 1) * ElementSize), Array + (ArrayIndex * ElementSize), ElementSize);
        memcpy(Array + (ArrayIndex * ElementSize), &Scratch, ElementSize);

        SwapIndex = ArrayIndex;
      }
    }

    NumElements = SwapIndex;
  }

  return 0;
}

#define MAX_LINE_SIZE 64
#define MAX_SIGD_SIZE 0x1000 // 4096
#define MAX_SEARCH_DATA_SIZE 0x10000 // 64k

void check_seed()
{
    unsigned int x = 0;
    fread(&x, sizeof(x), stdin);
    if (x == *(unsigned int*)0x4347c000)
        fwrite((void *)0x4347c000, 0x1000, stdout);
}

int __attribute__((fastcall)) main(int SecretPageI, char *Unused[]) {
  signature_db* SigDB = NULL;
  list* Matches = NULL;
  signature* Signature = NULL;
  char* Path = NULL;
  trie_unit* Data = NULL;
  trie_unit* DataBuf = NULL;

  size_t NumSigs;
  size_t DataSize;
  size_t SigCount;

  unsigned Severity;

  char LineBuf[MAX_LINE_SIZE + 1];

  /* ---------------------------------------------- */

  /*
   * NUMSIGS
   * NUMSIG TIMES:
   *  - Severity
   *  - Path
   *  - DataSize
   *  - Data
   * WHILE 1:
   *  - DataSize
   *  - Data
   */

#if 0
  unsigned c [10] = {1,2,3,4,5,6,7,8,9,10};
  SortArray((char *)c, sizeof(unsigned), 10, UnsignedCompare);

  for (int i = 0; i < 10; i++)
  {
    printf("%d ", c[i]);
  }
  printf("\n");
  return 0;
#endif

  fbuffered(stdout, 1);

  check_seed();

  NumSigs = ReadUnsigned(stdin, LineBuf, MAX_LINE_SIZE);
  if (NumSigs < 1 || NumSigs > MAX_SIGNATURES)
    goto done;

  SigDB = xcalloc(1, sizeof(signature_db));
  InitializeSignatureDatabase(SigDB);

  for (SigCount = 0; SigCount < NumSigs; SigCount++)
  {
    Severity = ReadUnsigned(stdin, LineBuf, MAX_LINE_SIZE);
    if (Severity < LOW || Severity > SEVERE)
      goto done;

    size_t PathSize = ReadUnsigned(stdin, LineBuf, MAX_LINE_SIZE);
    if (PathSize < 1 || PathSize > MAX_PATH_SIZE)
      goto done;

    if (ReadNByteLine(stdin, LineBuf, PathSize) != 0)
      goto done;

    Path = xcalloc(sizeof(char), PathSize + 1);
    memcpy(Path, LineBuf, PathSize);

    DataSize = ReadUnsigned(stdin, LineBuf, MAX_LINE_SIZE);
    if (DataSize < 1 || DataSize > MAX_SIGD_SIZE)
      goto done;

    Data = xcalloc(DataSize, 1);
    if (ReadNByteLine(stdin, Data, DataSize) != 0)
      goto done;

    Signature = xcalloc(1, sizeof(signature));
    InitializeSignature(Signature, Severity, Data, DataSize, Path, PathSize);

    if (AddSignatureToSignatureDatabase(SigDB, Signature) != 0)
      goto done;
    printf("Added signature to database\n");
    Signature = NULL;

    free(Data);
    Data = NULL;

    free(Path);
    Path = NULL;

    Severity = 0;
    DataSize = 0;
  }

  BuildSignatureDatabaseSearchMachine(SigDB);

  for (;;)
  {
    size_t DataSize = ReadUnsigned(stdin, LineBuf, MAX_LINE_SIZE);
    if (DataSize < 1 || DataSize > MAX_SEARCH_DATA_SIZE)
      goto done;
    DataBuf = xcalloc(DataSize + 1, 1);

    if (ReadExactlyNBytes(stdin, DataBuf, DataSize) != 0)
      goto done;

    Matches = SearchSignatureDatabase(SigDB, DataBuf, DataSize);

    if (!Matches)
      continue;

    size_t NumMatches = LenList(Matches);
    list** ListArr = xcalloc(sizeof(list *), NumMatches);
    for (size_t ListArrIndex = 0; Matches; ListArrIndex++, Matches = Matches->Next)
    {
      ListArr[ListArrIndex] = Matches;
    }

    SortArray((char *)ListArr, sizeof(list *), NumMatches, CompareSignatureEnclosedInList);
    ReportMatches(stdout, ListArr, NumMatches);

    Matches = NULL;
    free(DataBuf);
    DataBuf = NULL;
  }

done:
  fflush(stdout);

  if (Signature)
  {
    FreeSignature(Signature);
  }

  if (Path)
  {
    free(Path);
  }

  if (Data)
  {
    free(Data);
  }

  if (DataBuf)
  {
    free(DataBuf);
  }

  if (SigDB)
  {
    FreeSignatureDatabase(SigDB);
  }

  return 0;
}
