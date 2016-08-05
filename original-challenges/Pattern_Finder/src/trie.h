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
#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdint.h>
#include <stdlib.h>

typedef unsigned char trie_unit;
#ifndef bool
typedef unsigned char bool;
#endif

#define UNIT_CARDINALITY 256

typedef struct trie trie;
struct trie
{
  trie* Parent;
  trie* Children[UNIT_CARDINALITY];
  trie_unit Data;
  bool Terminal;
  size_t Identifier;
};

#define ROOT_IDENTIFIER 0
void AllocateAndInitializeTrieRoot(trie** Trie);
void FreeTrie(trie* Trie);
void InsertIntoTrie(trie* Trie, trie_unit* Data, size_t DataSize);
trie_unit* GetDataString(trie* Trie, size_t* DataLength);
trie** GatherTerminals(trie* Trie, size_t* TerminalCount);
trie* FindInTrie(trie* Trie, trie_unit* Data, size_t DataSize);
trie* FindInTrieByIdentifier(trie* Trie, size_t Identifier);
size_t GetTrieCount(void);
int TestTrie(void);

#endif /* __TRIE_H__ */
