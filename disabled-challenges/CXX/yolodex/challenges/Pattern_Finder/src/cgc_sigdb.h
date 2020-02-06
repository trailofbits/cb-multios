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
#ifndef __SIGDB_H__
#define __SIGDB_H__

#include "cgc_search_machine.h"
#include "cgc_stdio.h"
#include "cgc_trie.h"

#define MAX_PATH_SIZE 0x40

typedef struct signature signature;
struct signature
{
  enum
  {
    LOW = 1,
    GUARDED,
    ELEVATED,
    HIGH,
    SEVERE
  } Severity;

  char* Path;
  cgc_size_t PathSize;

  trie_unit* Data;
  cgc_size_t DataSize;
};

#define MAX_SIGNATURES 0x1000
typedef struct signature_db signature_db;
struct signature_db
{
  cgc_size_t SignatureCount;
  signature* Signatures[MAX_SIGNATURES];
  trie* Trie;
  search_machine* SearchMachine;
};

int cgc_InitializeSignatureDatabase(signature_db* SignatureDatabase);
int cgc_InitializeSignature(signature* Signature, int Severity, trie_unit* Data, cgc_size_t DataSize, char* Path, cgc_size_t PathSize);
void cgc_FreeSignature(signature* Signature);
char* cgc_SeverityString(unsigned Severity);
void cgc_PrintSignature(FILE* Stream, signature* Signature);
unsigned long cgc_BytesToUnsigned(unsigned char *Data, cgc_size_t DataSize);
void cgc_FreeSignatureDatabase(signature_db* SignatureDatabase);
int cgc_AddSignatureToSignatureDatabase(signature_db* SignatureDatabase, signature* Signature);
int cgc_BuildSignatureDatabaseSearchMachine(signature_db* SignatureDatabase);
list* cgc_SearchSignatureDatabase(signature_db* SignatureDatabase, trie_unit* Data, cgc_size_t DataSize);

#endif /* __SIGDB_H__ */
