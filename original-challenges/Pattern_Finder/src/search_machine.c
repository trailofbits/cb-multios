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
#include "safe.h"
#include "search_machine.h"
#include "trie.h"

int InitializeSearchMachine(search_machine* SearchMachine, trie* Trie)
{
  SearchMachine->Trie = Trie;

  // For each keyword in the keyword tree, set out(Node-For-Keyword) = {Keyword}
  size_t TerminalCount;
  trie** Terminals = GatherTerminals(Trie, &TerminalCount);

  // Each state has an out (set of patterns recognized upon entering it
  // out :: Map StateID [String]
  SearchMachine->Out = xcalloc(GetTrieCount(), sizeof(list*));
  for (size_t TerminalIndex = 0; TerminalIndex < TerminalCount; ++TerminalIndex)
  {
    size_t DataLength;
    size_t TerminalIdentifier = Terminals[TerminalIndex]->Identifier;
    trie_unit* DataUpToNode = GetDataString(Terminals[TerminalIndex], &DataLength);
    Assert(DataUpToNode != NULL, "ISM1");
    AllocateAndInitializeListHead(&(SearchMachine->Out[TerminalIdentifier]), DataUpToNode);
  }

  SearchMachine->Fail = xcalloc(GetTrieCount(), sizeof(trie *));

  // goto :: Map (StateID, Symbol) StatePtr
  SearchMachine->Goto = xcalloc(sizeof(void *), GetTrieCount());

  // Copy over trie links into goto
  for (size_t TrieIndex = 0; TrieIndex < GetTrieCount(); TrieIndex++)
  {
    SearchMachine->Goto[TrieIndex] = xcalloc(sizeof(trie*), UNIT_CARDINALITY);
    trie* TrieToCopy = FindInTrieByIdentifier(Trie, TrieIndex);
    memcpy(SearchMachine->Goto[TrieIndex], TrieToCopy->Children, sizeof(trie*) * UNIT_CARDINALITY);
  }

  // g(ROOT, a) := ROOT forall a in SIGMA where a doesn't leave ROOT
  for (size_t AlphabetIndex = 0; AlphabetIndex < UNIT_CARDINALITY; ++AlphabetIndex)
  {
    if (Trie->Children[AlphabetIndex] == NULL)
    {
      SearchMachine->Goto[ROOT_IDENTIFIER][AlphabetIndex] = Trie;
    }
  }

  return 0;
}

void FreeSearchMachine(search_machine* SearchMachine)
{
  if (SearchMachine)
  {
    // FreeSignatureDatabase will get the Trie

    for (size_t ListIndex = 0; ListIndex < GetTrieCount(); ++ListIndex)
    {
      if (SearchMachine->Out[ListIndex])
      {
        FreeList(SearchMachine->Out[ListIndex]);
        for (size_t OtherListIndex = 0; OtherListIndex < GetTrieCount(); ++OtherListIndex)
        {
          if (OtherListIndex != ListIndex && SearchMachine->Out[OtherListIndex] == SearchMachine->Out[ListIndex])
          {
            SearchMachine->Out[OtherListIndex] = NULL;
          }
        }
        SearchMachine->Out[ListIndex] = NULL;
      }
    }

    if (SearchMachine->Fail)
    {
      free(SearchMachine->Fail);
      SearchMachine->Fail = NULL;
    }

    if (SearchMachine->Goto)
    {
      for (size_t GotoIndex = 0; GotoIndex < GetTrieCount(); ++GotoIndex)
      {
        if (SearchMachine->Goto[GotoIndex])
        {
          free(SearchMachine->Goto[GotoIndex]);
          SearchMachine->Goto[GotoIndex] = NULL;
        }
      }
    }

    free(SearchMachine);
  }
}

match* FindMatches(search_machine *SearchMachine, trie_unit* Data, size_t DataSize, size_t* NumMatches)
{
  size_t MaxMatches = 0;
  match* Matches = NULL;
  *NumMatches = 0;

  trie* Node = SearchMachine->Trie;

  for (size_t DataIndex = 0; DataIndex < DataSize; ++DataIndex)
  {
    while (SearchMachine->Goto[Node->Identifier] == NULL || SearchMachine->Goto[Node->Identifier][Data[DataIndex]] == NULL)
    {
      Node = SearchMachine->Fail[Node->Identifier];
    }

    Node = SearchMachine->Goto[Node->Identifier][Data[DataIndex]];

    if (SearchMachine->Out[Node->Identifier] != NULL)
    {
      if (*NumMatches == MaxMatches)
      {
        size_t NewMaxMatches = MaxMatches * 2 + 1;
        Assert(NewMaxMatches > MaxMatches, "MATCH");
        match* NewMatches = xcalloc(sizeof(match), NewMaxMatches);
        memcpy(NewMatches, Matches, sizeof(match) * MaxMatches);
        MaxMatches = NewMaxMatches;
        free(Matches);
        Matches = NewMatches;
      }

      Matches[*NumMatches].Point = DataIndex;
      Matches[*NumMatches].List = SearchMachine->Out[Node->Identifier];
      *NumMatches = *NumMatches + 1;
    }
  }

  return Matches;
}
