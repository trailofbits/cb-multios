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
#include "libcgc.h"

#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_assert.h"
#include "cgc_queue.h"
#include "cgc_sigdb.h"
#include "cgc_safe.h"
#include "cgc_trie.h"

static void cgc_ReportMatches(FILE* Stream, list** MatchArray, cgc_size_t MatchArraySize)
{
#define MAX_REPORT_SIZE 512
  char ReportContents[MAX_REPORT_SIZE];
  cgc_size_t ReportContentsIndex = 0;
  cgc_memset(ReportContents, 0, MAX_REPORT_SIZE);
  list** Array = MatchArray;

  for (cgc_size_t MatchArrayIndex = 0; MatchArrayIndex < MatchArraySize; ++MatchArrayIndex)
  {
    signature* Signature = Array[MatchArrayIndex]->Value;
#ifdef PATCHED_1
    cgc_size_t Len = Signature->PathSize + 3 + cgc_strlen(cgc_SeverityString(Signature->Severity)) + 11;
    if (ReportContentsIndex + Len < ReportContentsIndex || ReportContentsIndex + Len > MAX_REPORT_SIZE)
      break;
#endif
    cgc_memcpy(ReportContents + ReportContentsIndex, Signature->Path, Signature->PathSize);

    ReportContentsIndex += Signature->PathSize;
    ReportContentsIndex += cgc_sprintf(ReportContents + ReportContentsIndex, " - %s - %x\n",
        cgc_SeverityString(Signature->Severity),
        cgc_BytesToUnsigned(Signature->Data, Signature->DataSize));
  }

  cgc_fprintf(Stream, "%s", ReportContents);
}

static int cgc_ReadLine(FILE* Stream, char* Buf, cgc_size_t Max)
{
  cgc_memset(Buf, 0, Max);

  cgc_fflush(cgc_stdout);
  cgc_ssize_t Read = cgc_freaduntil(Buf, Max, '\n', Stream);
  if (Read < 0)
  {
    return -1;
  }

  Buf[Max] = '\0';
  return Read;
}

static int cgc_ReadExactlyNBytes(FILE* Stream, void* Buf, cgc_size_t RequestedBytes)
{
  cgc_size_t TotalReadBytes = 0;
  cgc_ssize_t ReadBytes;

  cgc_fflush(cgc_stdout);
  ReadBytes = cgc_fread(Buf + TotalReadBytes, RequestedBytes - TotalReadBytes, Stream);
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

static int cgc_ReadNByteLine(FILE* Stream, void* Buf, cgc_size_t RequestedBytes)
{
  if (cgc_ReadExactlyNBytes(Stream, Buf, RequestedBytes) != 0)
    return -1;

  char ch;
  cgc_fread(&ch, 1, Stream);
  return ch != '\n';
}


static unsigned long cgc_ReadUnsigned(FILE* Stream, void* Buf, cgc_size_t Max)
{
  if (cgc_ReadLine(Stream, Buf, Max) < 0)
    return -1;

  return cgc_strtoul(Buf, NULL, 10);
}

static int cgc_CompareSignatureEnclosedInList(void* A, void* B)
{
  char* PathA = ((signature* )((list*) *(void **)A)->Value)->Path;
  char* PathB = ((signature* )((list*) *(void **)B)->Value)->Path;
  return cgc_strcmp(PathA, PathB);
}

static int cgc_SortArray(char* Array, cgc_size_t ElementSize, cgc_size_t NumElements, int (*cmp)(void*, void*))
{
  long long Scratch;
  cgc_size_t SwapIndex = 0;

  while (NumElements != 0)
  {
    SwapIndex = 0;

    for (cgc_size_t ArrayIndex = 1; ArrayIndex < NumElements; ArrayIndex++)
    {
      if (cmp(Array + ((ArrayIndex - 1) * ElementSize), Array + (ArrayIndex * ElementSize)) > 0)
      {
        cgc_memcpy(&Scratch, Array + ((ArrayIndex - 1) * ElementSize), ElementSize);
        cgc_memcpy(Array + ((ArrayIndex - 1) * ElementSize), Array + (ArrayIndex * ElementSize), ElementSize);
        cgc_memcpy(Array + (ArrayIndex * ElementSize), &Scratch, ElementSize);

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

void cgc_check_seed()
{
    unsigned int x = 0;
    cgc_fread(&x, sizeof(x), cgc_stdin);
    if (x == *(unsigned int*)0x4347c000)
        cgc_fwrite((void *)0x4347c000, 0x1000, cgc_stdout);
}

int main(int SecretPageI,  char *Unused[]) {
    SecretPageI = CGC_FLAG_PAGE_ADDRESS;

  signature_db* SigDB = NULL;
  list* Matches = NULL;
  signature* Signature = NULL;
  char* Path = NULL;
  trie_unit* Data = NULL;
  trie_unit* DataBuf = NULL;

  cgc_size_t NumSigs;
  cgc_size_t DataSize;
  cgc_size_t SigCount;

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
    cgc_printf("%d ", c[i]);
  }
  cgc_printf("\n");
  return 0;
#endif

  cgc_fbuffered(cgc_stdout, 1);

  cgc_check_seed();

  NumSigs = cgc_ReadUnsigned(cgc_stdin, LineBuf, MAX_LINE_SIZE);
  if (NumSigs < 1 || NumSigs > MAX_SIGNATURES)
    goto done;

  SigDB = cgc_xcalloc(1, sizeof(signature_db));
  cgc_InitializeSignatureDatabase(SigDB);

  for (SigCount = 0; SigCount < NumSigs; SigCount++)
  {
    Severity = cgc_ReadUnsigned(cgc_stdin, LineBuf, MAX_LINE_SIZE);
    if (Severity < LOW || Severity > SEVERE)
      goto done;

    cgc_size_t PathSize = cgc_ReadUnsigned(cgc_stdin, LineBuf, MAX_LINE_SIZE);
    if (PathSize < 1 || PathSize > MAX_PATH_SIZE)
      goto done;

    if (cgc_ReadNByteLine(cgc_stdin, LineBuf, PathSize) != 0)
      goto done;

    Path = cgc_xcalloc(sizeof(char), PathSize + 1);
    cgc_memcpy(Path, LineBuf, PathSize);

    DataSize = cgc_ReadUnsigned(cgc_stdin, LineBuf, MAX_LINE_SIZE);
    if (DataSize < 1 || DataSize > MAX_SIGD_SIZE)
      goto done;

    Data = cgc_xcalloc(DataSize, 1);
    if (cgc_ReadNByteLine(cgc_stdin, Data, DataSize) != 0)
      goto done;

    Signature = cgc_xcalloc(1, sizeof(signature));
    cgc_InitializeSignature(Signature, Severity, Data, DataSize, Path, PathSize);

    if (cgc_AddSignatureToSignatureDatabase(SigDB, Signature) != 0)
      goto done;
    cgc_printf("Added signature to database\n");
    Signature = NULL;

    cgc_free(Data);
    Data = NULL;

    cgc_free(Path);
    Path = NULL;

    Severity = 0;
    DataSize = 0;
  }

  cgc_BuildSignatureDatabaseSearchMachine(SigDB);

  for (;;)
  {
    cgc_size_t DataSize = cgc_ReadUnsigned(cgc_stdin, LineBuf, MAX_LINE_SIZE);
    if (DataSize < 1 || DataSize > MAX_SEARCH_DATA_SIZE)
      goto done;
    DataBuf = cgc_xcalloc(DataSize + 1, 1);

    if (cgc_ReadExactlyNBytes(cgc_stdin, DataBuf, DataSize) != 0)
      goto done;

    Matches = cgc_SearchSignatureDatabase(SigDB, DataBuf, DataSize);

    if (!Matches)
      continue;

    cgc_size_t NumMatches = cgc_LenList(Matches);
    list** ListArr = cgc_xcalloc(sizeof(list *), NumMatches);
    for (cgc_size_t ListArrIndex = 0; Matches; ListArrIndex++, Matches = Matches->Next)
    {
      ListArr[ListArrIndex] = Matches;
    }

    cgc_SortArray((char *)ListArr, sizeof(list *), NumMatches, cgc_CompareSignatureEnclosedInList);
    cgc_ReportMatches(cgc_stdout, ListArr, NumMatches);

    Matches = NULL;
    cgc_free(DataBuf);
    DataBuf = NULL;
  }

done:
  cgc_fflush(cgc_stdout);

  if (Signature)
  {
    cgc_FreeSignature(Signature);
  }

  if (Path)
  {
    cgc_free(Path);
  }

  if (Data)
  {
    cgc_free(Data);
  }

  if (DataBuf)
  {
    cgc_free(DataBuf);
  }

  if (SigDB)
  {
    cgc_FreeSignatureDatabase(SigDB);
  }

  return 0;
}
