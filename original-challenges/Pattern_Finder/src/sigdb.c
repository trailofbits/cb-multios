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
#include <string.h>

#include "assert.h"
#include "list.h"
#include "safe.h"
#include "sigdb.h"
#include "queue.h"

/*
 * Signature
 */
int InitializeSignature(signature* Signature, int Severity, trie_unit* Data, size_t DataSize, char* Path, size_t PathSize)
{
  if (!Signature || !Data || !Path)
    return -1;

  if (PathSize > MAX_PATH_SIZE - 1)
    return -1;

  if (Severity < LOW || Severity > SEVERE)
    return -1;

  Signature->Severity = Severity;

  Signature->Data = xcalloc(DataSize + 1, sizeof(trie_unit));
  memcpy(Signature->Data, Data, DataSize * sizeof(trie_unit));
  Signature->DataSize = DataSize * sizeof(trie_unit);
  fprintf(stderr, "(%s)\n", Signature->Data);

  Signature->PathSize = PathSize;
  Signature->Path = xcalloc(sizeof(char), PathSize + 1);
  memcpy(Signature->Path, Path, PathSize);

  return 0;
}

void FreeSignature(signature* Signature)
{
  if (Signature)
  {
    if (Signature->Data)
    {
      free(Signature->Data);
      Signature->Data = NULL;
    }

    if (Signature->Path)
    {
      free(Signature->Path);
      Signature->Path = NULL;
    }

    free(Signature);
  }
}

unsigned long BytesToUnsigned(unsigned char *Data, size_t DataSize)
{
  unsigned long hash = 5381;

  for (size_t Index = 0; Index < DataSize; ++Index)
  {
    hash = ((hash << 5) + hash) + Data[Index];
  }

  return hash;
}


char* SeverityString(unsigned Severity)
{
  switch (Severity)
  {
    case LOW:
      return "LOW";
    case GUARDED:
      return "GUARDED";
    case ELEVATED:
      return "ELEVATED";
    case HIGH:
      return "HIGH";
    case SEVERE:
      return "SEVERE";
    default:
      return "UNKNOWN";
  }
}

void PrintSignature(FILE* Stream, signature* Signature)
{
  fprintf(Stream, "%s - %s - %x\n",
      Signature->Path,
      SeverityString(Signature->Severity),
      BytesToUnsigned(Signature->Data, Signature->DataSize));
}

/*
 * Database
 */
int InitializeSignatureDatabase(signature_db* SignatureDatabase)
{
  if (!SignatureDatabase)
    return -1;

  SignatureDatabase->SignatureCount = 0;
  memset(SignatureDatabase->Signatures, 0, sizeof(signature *) * MAX_SIGNATURES);

  SignatureDatabase->Trie = NULL;
  SignatureDatabase->SearchMachine = xcalloc(1, sizeof(search_machine));

  return 0;
}

void FreeSignatureDatabase(signature_db* SignatureDatabase)
{
  if (SignatureDatabase)
  {
    for (size_t SignatureIndex = 0; SignatureIndex < SignatureDatabase->SignatureCount; ++SignatureIndex)
    {
      if (SignatureDatabase->Signatures[SignatureIndex])
      {
        FreeSignature(SignatureDatabase->Signatures[SignatureIndex]);
        SignatureDatabase->Signatures[SignatureIndex] = NULL;
      }
    }

    if (SignatureDatabase->Trie)
    {
      FreeTrie(SignatureDatabase->Trie);
      SignatureDatabase->Trie = NULL;
    }

    if (SignatureDatabase->SearchMachine)
    {
      FreeSearchMachine(SignatureDatabase->SearchMachine);
    }

    free(SignatureDatabase);
  }
}

int AddSignatureToSignatureDatabase(signature_db* SignatureDatabase, signature* Signature)
{
  if (SignatureDatabase->SignatureCount == MAX_SIGNATURES)
    return -1;

  SignatureDatabase->Signatures[SignatureDatabase->SignatureCount] = Signature;
  SignatureDatabase->SignatureCount += 1;
  return 0;
}

int BuildSignatureDatabaseTrie(signature_db* SignatureDatabase)
{
  if (!SignatureDatabase)
    return -1;

  AllocateAndInitializeTrieRoot(&SignatureDatabase->Trie);

  for (size_t SignatureIndex = 0; SignatureIndex < SignatureDatabase->SignatureCount; ++SignatureIndex)
  {
    InsertIntoTrie(SignatureDatabase->Trie,
        SignatureDatabase->Signatures[SignatureIndex]->Data,
        SignatureDatabase->Signatures[SignatureIndex]->DataSize);
  }

  return 0;
}

int BuildSignatureDatabaseSearchMachine(signature_db* SignatureDatabase)
{
  if (!SignatureDatabase)
    return -1;

  if (!SignatureDatabase->Trie && BuildSignatureDatabaseTrie(SignatureDatabase) != 0)
    return -1;

  InitializeSearchMachine(SignatureDatabase->SearchMachine, SignatureDatabase->Trie);

  search_machine* SM = SignatureDatabase->SearchMachine;

  // Phase 2
  queue* Queue = xcalloc(1, sizeof(queue));
  InitializeQueue(Queue);

  for (size_t AlphabetIndex = 0; AlphabetIndex < UNIT_CARDINALITY; ++AlphabetIndex)
  {
    trie* Node = SM->Goto[ROOT_IDENTIFIER][AlphabetIndex];
    //if (Node && Node->Identifier != ROOT_IDENTIFIER)
    if (!Node || Node->Identifier != ROOT_IDENTIFIER)
    {
      SM->Fail[Node->Identifier] = SM->Trie;
      Enqueue(Queue, Node);
    }
  }

  while (Peek(Queue) != NULL)
  {
    trie* R = Dequeue(Queue);

    for (size_t AlphabetIndex = 0; AlphabetIndex < UNIT_CARDINALITY; ++AlphabetIndex)
    {
      trie* S = SM->Goto[R->Identifier][AlphabetIndex];

      // Not 100% about this
      if (S)
      {
        Enqueue(Queue, S);
        trie* ST = SM->Fail[R->Identifier];

        // Not 100% about this
        while (!SM->Goto[ST->Identifier][AlphabetIndex])
        {
          ST = SM->Fail[ST->Identifier];
        }

        SM->Fail[S->Identifier] = SM->Goto[ST->Identifier][AlphabetIndex];

        // out(u) = out(u) UNION out(fail(u))
        SM->Out[S->Identifier] = UniqExtendList(SM->Out[S->Identifier], SM->Out[SM->Fail[S->Identifier]->Identifier]);
      }
    }
  }

  FreeQueue(Queue);
  Queue = NULL;
  return 0;
}

list* SearchSignatureDatabase(signature_db* SignatureDatabase, trie_unit* Data, size_t DataSize)
{
  size_t NumMatches;
  if (!SignatureDatabase || !Data || !DataSize)
   return NULL;

  if (!SignatureDatabase->SearchMachine)
    return NULL;

  match* Matches = FindMatches(SignatureDatabase->SearchMachine, Data, DataSize, &NumMatches);

  // Translate signature identifiers to signatures
  list* MatchingSignatures = NULL;
  for (size_t MatchIndex = 0; MatchIndex < NumMatches; ++MatchIndex)
  {
    list* MatchList = Matches[MatchIndex].List;
    for (; MatchList; MatchList = MatchList->Next)
    {
      for (size_t SignatureDatabaseIndex = 0; SignatureDatabaseIndex < SignatureDatabase->SignatureCount; ++SignatureDatabaseIndex)
      {
        if (memcmp(SignatureDatabase->Signatures[SignatureDatabaseIndex]->Data,
              MatchList->Value,
              SignatureDatabase->Signatures[SignatureDatabaseIndex]->DataSize) == 0)
        {
          if (!MatchingSignatures)
            AllocateAndInitializeListHead(&MatchingSignatures, SignatureDatabase->Signatures[SignatureDatabaseIndex]);
          else
            UniqAppendToList(MatchingSignatures, SignatureDatabase->Signatures[SignatureDatabaseIndex]);
        }
      }
    }
  }

  return MatchingSignatures;
}
