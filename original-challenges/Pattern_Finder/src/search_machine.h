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
#ifndef __SEARCH_MACHINE_H__
#define __SEARCH_MACHINE_H__

#include "list.h"
#include "trie.h"

typedef struct search_machine search_machine;
struct search_machine
{
  // Root of trie we built form signatures
  trie* Trie;

  // Out :: Map TrieIdentifier [Trie]
  list** Out;

  // Out :: Map TrieIdentifier Trie
  trie** Fail;

  // Goto :: Map (TrieIdentifier, Char)  Trie
  trie*** Goto;
};

typedef struct match match;
struct match
{
  // Location in search input where pattern matches
  size_t Point;

  // List of matching strings
  list* List;
};

int InitializeSearchMachine(search_machine* SearchMachine, trie* Trie);
void FreeSearchMachine(search_machine* SearchMachine);
match* FindMatches(search_machine *SearchMachine, trie_unit* Data, size_t DataSize, size_t* NumMatches);

#endif /* __SEARCH_MACHINE_H */
